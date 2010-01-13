/* This file has been generated from /home/pat/paparazzi3/var/LINUXFC/settings_modules.xml /home/pat/paparazzi3/conf/settings/basic.xml */
/* Please DO NOT EDIT */

#ifndef SETTINGS_H
#define SETTINGS_H 

#define RCSettings(mode_changed) { \
}

#include "autopilot.h"
#include "downlink.h"
#include "estimator.h"
#include "gps_ubx.h"
#include "infrared.h"
#include "nav.h"
#include "modules.h"

#define DlSetting(_idx, _value) { \
  switch (_idx) { \
    case 0: flight_altitude = _value; break;\
    case 1: nav_course = _value; break;\
    case 2: nav_IncreaseShift( _value ); _value = nav_shift; break;\
    case 3: autopilot_ResetFlightTimeAndLaunch( _value ); _value = estimator_flight_time; break;\
    case 4: nav_SetNavRadius( _value ); _value = nav_radius; break;\
    case 5: pprz_mode = _value; break;\
    case 6: launch = _value; break;\
    case 7: kill_throttle = _value; break;\
    case 8: telemetry_mode_Ap_DefaultChannel = _value; break;\
    case 9: gps_ubx_Reset( _value ); _value = gps_reset; break;\
    case 10: ir_roll_neutral = _value; break;\
    case 11: ir_pitch_neutral = _value; break;\
  }\
}
#define PeriodicSendDlValue(_chan) { \
  static uint8_t i;\
  float var;\
  if (i >= 12) i = 0;;\
  switch (i) { \
    case 0: var = flight_altitude; break;\
    case 1: var = nav_course; break;\
    case 2: var = nav_shift; break;\
    case 3: var = estimator_flight_time; break;\
    case 4: var = nav_radius; break;\
    case 5: var = pprz_mode; break;\
    case 6: var = launch; break;\
    case 7: var = kill_throttle; break;\
    case 8: var = telemetry_mode_Ap_DefaultChannel; break;\
    case 9: var = gps_reset; break;\
    case 10: var = ir_roll_neutral; break;\
    case 11: var = ir_pitch_neutral; break;\
    default: var = 0.; break;\
  }\
  DOWNLINK_SEND_DL_VALUE(_chan, &i, &var);\
  i++;\
}
static inline float settings_get_value(uint8_t i) {
  switch (i) { \
    case 0: return flight_altitude;
    case 1: return nav_course;
    case 2: return nav_shift;
    case 3: return estimator_flight_time;
    case 4: return nav_radius;
    case 5: return pprz_mode;
    case 6: return launch;
    case 7: return kill_throttle;
    case 8: return telemetry_mode_Ap_DefaultChannel;
    case 9: return gps_reset;
    case 10: return ir_roll_neutral;
    case 11: return ir_pitch_neutral;
    default: return 0.;
    }
  }

#endif // SETTINGS_H
