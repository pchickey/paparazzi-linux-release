/* This file has been generated from /home/pat/paparazzi3/conf/radios/cockpitMM.xml */
/* Please DO NOT EDIT */

#ifndef CONF_RADIO_CONTROL_PPM_H
#define CONF_RADIO_CONTROL_PPM_H 

#define RADIO_NAME "cockpitMM"

#define RADIO_CONTROL_NB_CHANNEL 7

#define RADIO_CTL_D 0
#define RADIO_CONTROL_ROLL RADIO_CTL_D
#define RADIO_CTL_C 1
#define RADIO_CONTROL_PITCH RADIO_CTL_C
#define RADIO_CTL_B 2
#define RADIO_CONTROL_YAW RADIO_CTL_B
#define RADIO_CTL_A 3
#define RADIO_CONTROL_THROTTLE RADIO_CTL_A
#define RADIO_CTL_G 4
#define RADIO_CONTROL_GAIN1 RADIO_CTL_G
#define RADIO_CTL_E 5
#define RADIO_CONTROL_MODE RADIO_CTL_E
#define RADIO_CTL_F 6
#define RADIO_CONTROL_CALIB RADIO_CTL_F

#define PPM_PULSE_TYPE PPM_PULSE_TYPE_POSITIVE
#define PPM_DATA_MIN_LEN (900ul)
#define PPM_DATA_MAX_LEN (2100ul)
#define PPM_SYNC_MIN_LEN (5000ul)
#define PPM_SYNC_MAX_LEN (15000ul)

#define NormalizePpm() {\
  int16_t tmp_radio;\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_ROLL] - SYS_TICS_OF_USEC(1498);\
  radio_control.values[RADIO_CONTROL_ROLL] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(radio_control.values[RADIO_CONTROL_ROLL], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_PITCH] - SYS_TICS_OF_USEC(1498);\
  radio_control.values[RADIO_CONTROL_PITCH] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(radio_control.values[RADIO_CONTROL_PITCH], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_YAW] - SYS_TICS_OF_USEC(1498);\
  radio_control.values[RADIO_CONTROL_YAW] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(radio_control.values[RADIO_CONTROL_YAW], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_THROTTLE] - SYS_TICS_OF_USEC(1120);\
  radio_control.values[RADIO_CONTROL_THROTTLE] = tmp_radio * (MAX_PPRZ / (float)(SIGNED_SYS_TICS_OF_USEC(2000-1120)));\
  Bound(radio_control.values[RADIO_CONTROL_THROTTLE], 0, MAX_PPRZ); \
\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_GAIN1] - SYS_TICS_OF_USEC(1498);\
  radio_control.values[RADIO_CONTROL_GAIN1] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(radio_control.values[RADIO_CONTROL_GAIN1], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_MODE] - SYS_TICS_OF_USEC(1500);\
  radio_control.values[RADIO_CONTROL_MODE] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1500))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1500))));\
  Bound(radio_control.values[RADIO_CONTROL_MODE], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = booz_radio_control_ppm_pulses[RADIO_CONTROL_CALIB] - SYS_TICS_OF_USEC(1500);\
  radio_control.values[RADIO_CONTROL_CALIB] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1500))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1500))));\
  Bound(radio_control.values[RADIO_CONTROL_CALIB], MIN_PPRZ, MAX_PPRZ); \
\
}

#endif // CONF_RADIO_CONTROL_PPM_H
