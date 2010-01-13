/* This file has been generated from /home/pat/paparazzi3/conf/radios/cockpitMM.xml */
/* Please DO NOT EDIT */

#ifndef RADIO_H
#define RADIO_H 

#define RADIO_NAME "cockpitMM"

#define RADIO_CTL_NB 7

#define RADIO_CTL_D 0
#define RADIO_ROLL RADIO_CTL_D
#define RADIO_CTL_C 1
#define RADIO_PITCH RADIO_CTL_C
#define RADIO_CTL_B 2
#define RADIO_YAW RADIO_CTL_B
#define RADIO_CTL_A 3
#define RADIO_THROTTLE RADIO_CTL_A
#define RADIO_CTL_G 4
#define RADIO_GAIN1 RADIO_CTL_G
#define RADIO_CTL_E 5
#define RADIO_MODE RADIO_CTL_E
#define RADIO_CTL_F 6
#define RADIO_CALIB RADIO_CTL_F

#define PPM_PULSE_TYPE PPM_PULSE_TYPE_POSITIVE
#define PPM_DATA_MIN_LEN (900ul)
#define PPM_DATA_MAX_LEN (2100ul)
#define PPM_SYNC_MIN_LEN (5000ul)
#define PPM_SYNC_MAX_LEN (15000ul)

#define NormalizePpm() {\
  static uint8_t avg_cpt = 0; /* Counter for averaging */\
  int16_t tmp_radio;\
  tmp_radio = ppm_pulses[RADIO_ROLL] - SYS_TICS_OF_USEC(1498);\
  rc_values[RADIO_ROLL] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(rc_values[RADIO_ROLL], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = ppm_pulses[RADIO_PITCH] - SYS_TICS_OF_USEC(1498);\
  rc_values[RADIO_PITCH] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(rc_values[RADIO_PITCH], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = ppm_pulses[RADIO_YAW] - SYS_TICS_OF_USEC(1498);\
  rc_values[RADIO_YAW] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
  Bound(rc_values[RADIO_YAW], MIN_PPRZ, MAX_PPRZ); \
\
  tmp_radio = ppm_pulses[RADIO_THROTTLE] - SYS_TICS_OF_USEC(1120);\
  rc_values[RADIO_THROTTLE] = tmp_radio * (MAX_PPRZ / (float)(SIGNED_SYS_TICS_OF_USEC(2000-1120)));\
  Bound(rc_values[RADIO_THROTTLE], 0, MAX_PPRZ); \
\
  avg_rc_values[RADIO_GAIN1] += ppm_pulses[RADIO_GAIN1];\
  avg_rc_values[RADIO_MODE] += ppm_pulses[RADIO_MODE];\
  avg_rc_values[RADIO_CALIB] += ppm_pulses[RADIO_CALIB];\
  avg_cpt++;\
  if (avg_cpt == RC_AVG_PERIOD) {\
    avg_cpt = 0;\
    tmp_radio = avg_rc_values[RADIO_GAIN1] / RC_AVG_PERIOD -  SYS_TICS_OF_USEC(1498);\
    rc_values[RADIO_GAIN1] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1498))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1498))));\
    avg_rc_values[RADIO_GAIN1] = 0;\
    Bound(rc_values[RADIO_GAIN1], MIN_PPRZ, MAX_PPRZ); \
\
    tmp_radio = avg_rc_values[RADIO_MODE] / RC_AVG_PERIOD -  SYS_TICS_OF_USEC(1500);\
    rc_values[RADIO_MODE] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1500))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1500))));\
    avg_rc_values[RADIO_MODE] = 0;\
    Bound(rc_values[RADIO_MODE], MIN_PPRZ, MAX_PPRZ); \
\
    tmp_radio = avg_rc_values[RADIO_CALIB] / RC_AVG_PERIOD -  SYS_TICS_OF_USEC(1500);\
    rc_values[RADIO_CALIB] = tmp_radio * (tmp_radio >=0 ? (MAX_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(1000-1500))) : (MIN_PPRZ/(float)(SIGNED_SYS_TICS_OF_USEC(2000-1500))));\
    avg_rc_values[RADIO_CALIB] = 0;\
    Bound(rc_values[RADIO_CALIB], MIN_PPRZ, MAX_PPRZ); \
\
    rc_values_contains_avg_channels = TRUE;\
 }\
}

#endif // RADIO_H
