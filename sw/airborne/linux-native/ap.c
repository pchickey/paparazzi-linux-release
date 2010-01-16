/*
 * $Id: main_ap.c 4165 2009-09-12 21:29:01Z hecto $
 *  
 * Copyright (C) 2003-2006  Pascal Brisset, Antoine Drouin
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA. 
 *
 */

/** \file main_ap.c
 *  \brief AP ( AutoPilot ) process
 *
 *   This process is reponsible for the collecting the different sensors data, fusing them to obtain
 * aircraft attitude and running the different control loops
 */

#define MODULES_C

#include <math.h>

#include "main_ap.h"

#include "init_hw.h"
#include "adc.h"
#include "fw_h_ctl.h"
#include "fw_v_ctl.h"
#include "gps.h"
#include "infrared.h"
#include "ap_downlink.h"
#include "nav.h"
#include "autopilot.h"
#include "estimator.h"
#include "settings.h"
#include "sys_time.h"
#include "flight_plan.h"
#include "datalink.h"
#include "xbee.h"

#include "ap_state.h"

bool_t power_switch;
uint8_t fatal_error_nb = 0;
static const uint16_t version = 1;

uint8_t pprz_mode = PPRZ_MODE_AUTO2;
uint8_t lateral_mode = LATERAL_MODE_MANUAL;
uint8_t rc_settings_mode = 0;
uint8_t mcu1_status = 0;

bool_t kill_throttle = FALSE;

float slider_1_val, slider_2_val;

bool_t launch = FALSE;

uint8_t vsupply;	// deciVolt
static int16_t current;	// milliAmpere

float energy; 		// Fuel consumption (mAh)

bool_t gps_lost = FALSE;

#define Min(x, y) (x < y ? x : y)
#define Max(x, y) (x > y ? x : y)

static inline uint8_t pprz_mode_update( void ) {
  return FALSE;
}

// using ap_state.h, ap.c and fbw.c share the ap_state_t struct and ap_state pointer
static struct ap_state_t _ap_state;
struct ap_state_t* ap_state = &_ap_state;

#define INIT_MSG_NB 2

uint8_t ac_ident = AC_ID;

void navigation_task(void);
void reporting_task(void);


void periodic_task_ap( void ) {
  static uint8_t _20Hz   = 0;
  static uint8_t _10Hz   = 0;
  static uint8_t _4Hz   = 0;
  static uint8_t _1Hz   = 0;

  _20Hz++;
  if (_20Hz>=3) _20Hz=0;
  _10Hz++;
  if (_10Hz>=6) _10Hz=0;
  _4Hz++;
  if (_4Hz>=15) _4Hz=0;
  _1Hz++;
  if (_1Hz>=60) _1Hz=0;

  reporting_task();
  
  if (!_1Hz) {
    if (estimator_flight_time) estimator_flight_time++;
    datalink_time++;

  }
  switch(_4Hz) {
  case 0:
    estimator_propagate_state();
    navigation_task();
    break;
  case 1:
    if (!estimator_flight_time) 
    {
      estimator_flight_time = 1;
      launch = TRUE; /* Not set in non auto launch */
      DOWNLINK_SEND_TAKEOFF(DefaultChannel, &cpu_time_sec);
    }
    break;
    /*  default: */
  }

  if (!_20Hz)
    {
      ir_update();
      estimator_update_state_infrared();
      h_ctl_attitude_loop(); /* Set  h_ctl_aileron_setpoint & h_ctl_elevator_setpoint */
      v_ctl_throttle_slew();
      
      ap_state->commands[COMMAND_THROTTLE] = v_ctl_throttle_slewed;
      ap_state->commands[COMMAND_ROLL] = h_ctl_aileron_setpoint;
      ap_state->commands[COMMAND_PITCH] = h_ctl_elevator_setpoint;

    }
}


void init_ap( void ) {
  /************* Sensors initialization ***************/
  ir_init();
  gps_init();
  Uart0Init();
  Uart1Init();
  /************ Internal status ***************/
  h_ctl_init();
  v_ctl_init();
  estimator_init();
#ifdef ALT_KALMAN
  alt_kalman_init();
#endif
  nav_init();
}


/*********** EVENT ***********************************************************/
void event_task_ap( void ) {
  if (GpsBuffer()) {
    ReadGpsBuffer();
  }
  if (gps_msg_received) {
    /* parse and use GPS messages */
      parse_gps_msg();
    gps_msg_received = FALSE;
    if (gps_pos_available) {
      gps_verbose_downlink = !launch;
      UseGpsPosNoSend(estimator_update_state_gps);
      gps_downlink();
      gps_pos_available = FALSE;
    }
  }

  if (PprzBuffer()) {
    ReadPprzBuffer();
    if (pprz_msg_received) {
      pprz_parse_payload();
      pprz_msg_received = FALSE;
    }
  }
  if (dl_msg_available) {
    dl_parse_msg();
    dl_msg_available = FALSE;
  }

} /* event_task_ap() */



void reporting_task( void ) 
{
  static uint8_t boot = TRUE;

  /** initialisation phase during boot */
  if (boot) {
    DOWNLINK_SEND_BOOT(DefaultChannel, &version);
    boot = FALSE;
  }
  /** then report periodicly */
  else {
    PeriodicSendAp_DefaultChannel();
  }
}

void navigation_task( void ) 
{
  #if defined FAILSAFE_DELAY_WITHOUT_GPS
  /** This section is used for the failsafe of GPS */
  static uint8_t last_pprz_mode;

  /** If aircraft is launched and is in autonomus mode, go into
      PPRZ_MODE_GPS_OUT_OF_ORDER mode (Failsafe) if we lost the GPS */
  if (launch) {
    if (cpu_time_sec - last_gps_msg_t > FAILSAFE_DELAY_WITHOUT_GPS) {
      if (pprz_mode == PPRZ_MODE_AUTO2 || pprz_mode == PPRZ_MODE_HOME) {
	last_pprz_mode = pprz_mode;
	pprz_mode = PPRZ_MODE_GPS_OUT_OF_ORDER;
	PERIODIC_SEND_PPRZ_MODE(DefaultChannel);
	gps_lost = TRUE;
      }
    } else /* GPS is ok */ if (gps_lost) {
      /** If aircraft was in failsafe mode, come back in previous mode */
      pprz_mode = last_pprz_mode;
      gps_lost = FALSE;

      PERIODIC_SEND_PPRZ_MODE(DefaultChannel);
    }
  }
  #endif /* GPS && FAILSAFE_DELAY_WITHOUT_GPS */
  
  common_nav_periodic_task_4Hz();
  if (pprz_mode == PPRZ_MODE_HOME)
    nav_home();
  else if (pprz_mode == PPRZ_MODE_GPS_OUT_OF_ORDER)
    nav_without_gps();
  else
    nav_periodic_task();
  
  #ifndef PERIOD_NAVIGATION_DefaultChannel_0 // If not sent periodically (in default 0 mode)
  SEND_NAVIGATION(DefaultChannel);
  #endif

  SEND_CAM(DefaultChannel);
  
  /* The nav task computes only nav_altitude. However, we are interested
     by desired_altitude (= nav_alt+alt_shift) in any case.
     So we always run the altitude control loop */
  if (v_ctl_mode == V_CTL_MODE_AUTO_ALT)
    v_ctl_altitude_loop();

  if (pprz_mode == PPRZ_MODE_AUTO2 || pprz_mode == PPRZ_MODE_HOME
			|| pprz_mode == PPRZ_MODE_GPS_OUT_OF_ORDER) {
  #ifdef H_CTL_RATE_LOOP
    /* Be sure to be in attitude mode, not roll */
    h_ctl_auto1_rate = FALSE;
  #endif
    if (lateral_mode >=LATERAL_MODE_COURSE)
      h_ctl_course_loop(); /* aka compute nav_desired_roll */
    if (v_ctl_mode >= V_CTL_MODE_AUTO_CLIMB)
      v_ctl_climb_loop();
    if (v_ctl_mode == V_CTL_MODE_AUTO_THROTTLE)
      v_ctl_throttle_setpoint = nav_throttle_setpoint;

  #if defined V_CTL_THROTTLE_IDLE
    Bound(v_ctl_throttle_setpoint, TRIM_PPRZ(V_CTL_THROTTLE_IDLE*MAX_PPRZ), MAX_PPRZ);
  #endif

  #ifdef V_CTL_POWER_CTL_BAT_NOMINAL
    if (vsupply > 0.) {
      v_ctl_throttle_setpoint *= 10. * V_CTL_POWER_CTL_BAT_NOMINAL / (float)vsupply;
      v_ctl_throttle_setpoint = TRIM_UPPRZ(v_ctl_throttle_setpoint);
    }
  #endif

    h_ctl_pitch_setpoint = nav_pitch;
    Bound(h_ctl_pitch_setpoint, H_CTL_PITCH_MIN_SETPOINT, H_CTL_PITCH_MAX_SETPOINT);
    if (kill_throttle || (!estimator_flight_time && !launch))
      v_ctl_throttle_setpoint = 0;
  }
  energy += ((float)current) / 3600.0f * 0.25f;	// mAh = mA * dt (4Hz -> hours)
}


