/* This file has been generated from /home/pat/paparazzi3/conf/messages.xml and /home/pat/paparazzi3/conf/telemetry/default.xml */
/* Please DO NOT EDIT */


/* Macros for Ap process channel DefaultChannel */
#define TELEMETRY_MODE_Ap_DefaultChannel_default 0
#define PERIOD_ALIVE_DefaultChannel_0 (5)
#define PERIOD_GPS_DefaultChannel_0 (0.25)
#define PERIOD_NAVIGATION_DefaultChannel_0 (1.)
#define PERIOD_ATTITUDE_DefaultChannel_0 (0.5)
#define PERIOD_ESTIMATOR_DefaultChannel_0 (0.5)
#define PERIOD_WP_MOVED_DefaultChannel_0 (0.5)
#define PERIOD_CIRCLE_DefaultChannel_0 (1.05)
#define PERIOD_DESIRED_DefaultChannel_0 (1.05)
#define PERIOD_BAT_DefaultChannel_0 (1.1)
#define PERIOD_BARO_MS5534A_DefaultChannel_0 (1.0)
#define PERIOD_SEGMENT_DefaultChannel_0 (1.2)
#define PERIOD_CALIBRATION_DefaultChannel_0 (2.1)
#define PERIOD_NAVIGATION_REF_DefaultChannel_0 (9.)
#define PERIOD_PPRZ_MODE_DefaultChannel_0 (5.)
#define PERIOD_DOWNLINK_DefaultChannel_0 (5.1)
#define PERIOD_DL_VALUE_DefaultChannel_0 (1.5)
#define PERIOD_IR_SENSORS_DefaultChannel_0 (1.2)
#define PERIOD_GYRO_RATES_DefaultChannel_0 (1.1)
#define PERIOD_SURVEY_DefaultChannel_0 (2.1)
#define PERIOD_GPS_SOL_DefaultChannel_0 (2.0)
#define TELEMETRY_MODE_Ap_DefaultChannel_minimal 1
#define PERIOD_ALIVE_DefaultChannel_1 (5)
#define PERIOD_ATTITUDE_DefaultChannel_1 (4)
#define PERIOD_GPS_DefaultChannel_1 (1.05)
#define PERIOD_ESTIMATOR_DefaultChannel_1 (1.3)
#define PERIOD_WP_MOVED_DefaultChannel_1 (1.4)
#define PERIOD_CIRCLE_DefaultChannel_1 (3.05)
#define PERIOD_DESIRED_DefaultChannel_1 (4.05)
#define PERIOD_BAT_DefaultChannel_1 (1.1)
#define PERIOD_SEGMENT_DefaultChannel_1 (3.2)
#define PERIOD_CALIBRATION_DefaultChannel_1 (5.1)
#define PERIOD_NAVIGATION_REF_DefaultChannel_1 (9.)
#define PERIOD_NAVIGATION_DefaultChannel_1 (3.)
#define PERIOD_PPRZ_MODE_DefaultChannel_1 (5.)
#define PERIOD_DOWNLINK_DefaultChannel_1 (5.1)
#define PERIOD_DL_VALUE_DefaultChannel_1 (1.5)
#define PERIOD_IR_SENSORS_DefaultChannel_1 (5.2)
#define PERIOD_GYRO_RATES_DefaultChannel_1 (10.1)
#define PERIOD_SURVEY_DefaultChannel_1 (2.1)
#define PERIOD_GPS_SOL_DefaultChannel_1 (5.0)
#define TELEMETRY_MODE_Ap_DefaultChannel_extremal 2
#define PERIOD_ALIVE_DefaultChannel_2 (5)
#define PERIOD_GPS_DefaultChannel_2 (5.1)
#define PERIOD_ESTIMATOR_DefaultChannel_2 (5.3)
#define PERIOD_BAT_DefaultChannel_2 (10.1)
#define PERIOD_DESIRED_DefaultChannel_2 (10.2)
#define PERIOD_NAVIGATION_DefaultChannel_2 (5.4)
#define PERIOD_PPRZ_MODE_DefaultChannel_2 (5.5)
#define PERIOD_DOWNLINK_DefaultChannel_2 (5.7)
#define PeriodicSendAp_DefaultChannel() {  /* 60Hz */ \
  if (telemetry_mode_Ap_DefaultChannel == TELEMETRY_MODE_Ap_DefaultChannel_default) {\
    static uint8_t i15 = 0; i15++; if (i15>=15) i15=0;\
    static uint8_t i30 = 0; i30++; if (i30>=30) i30=0;\
    static uint8_t i60 = 0; i60++; if (i60>=60) i60=0;\
    static uint8_t i63 = 0; i63++; if (i63>=63) i63=0;\
    static uint8_t i66 = 0; i66++; if (i66>=66) i66=0;\
    static uint8_t i72 = 0; i72++; if (i72>=72) i72=0;\
    static uint8_t i90 = 0; i90++; if (i90>=90) i90=0;\
    static uint8_t i120 = 0; i120++; if (i120>=120) i120=0;\
    static uint8_t i126 = 0; i126++; if (i126>=126) i126=0;\
    static uint16_t i300 = 0; i300++; if (i300>=300) i300=0;\
    static uint16_t i306 = 0; i306++; if (i306>=306) i306=0;\
    static uint16_t i540 = 0; i540++; if (i540>=540) i540=0;\
    if (i15 == 0) {\
      PERIODIC_SEND_GPS(DefaultChannel);\
    } \
    if (i30 == 6) {\
      PERIODIC_SEND_ATTITUDE(DefaultChannel);\
    } \
    else if (i30 == 12) {\
      PERIODIC_SEND_ESTIMATOR(DefaultChannel);\
    } \
    else if (i30 == 18) {\
      PERIODIC_SEND_WP_MOVED(DefaultChannel);\
    } \
    if (i60 == 24) {\
      PERIODIC_SEND_NAVIGATION(DefaultChannel);\
    } \
    else if (i60 == 30) {\
      PERIODIC_SEND_BARO_MS5534A(DefaultChannel);\
    } \
    if (i63 == 36) {\
      PERIODIC_SEND_CIRCLE(DefaultChannel);\
    } \
    else if (i63 == 42) {\
      PERIODIC_SEND_DESIRED(DefaultChannel);\
    } \
    if (i66 == 48) {\
      PERIODIC_SEND_BAT(DefaultChannel);\
    } \
    else if (i66 == 54) {\
      PERIODIC_SEND_GYRO_RATES(DefaultChannel);\
    } \
    if (i72 == 60) {\
      PERIODIC_SEND_SEGMENT(DefaultChannel);\
    } \
    else if (i72 == 66) {\
      PERIODIC_SEND_IR_SENSORS(DefaultChannel);\
    } \
    if (i90 == 72) {\
      PERIODIC_SEND_DL_VALUE(DefaultChannel);\
    } \
    if (i120 == 78) {\
      PERIODIC_SEND_GPS_SOL(DefaultChannel);\
    } \
    if (i126 == 84) {\
      PERIODIC_SEND_CALIBRATION(DefaultChannel);\
    } \
    else if (i126 == 90) {\
      PERIODIC_SEND_SURVEY(DefaultChannel);\
    } \
    if (i300 == 96) {\
      PERIODIC_SEND_ALIVE(DefaultChannel);\
    } \
    else if (i300 == 102) {\
      PERIODIC_SEND_PPRZ_MODE(DefaultChannel);\
    } \
    if (i306 == 108) {\
      PERIODIC_SEND_DOWNLINK(DefaultChannel);\
    } \
    if (i540 == 114) {\
      PERIODIC_SEND_NAVIGATION_REF(DefaultChannel);\
    } \
  }\
  if (telemetry_mode_Ap_DefaultChannel == TELEMETRY_MODE_Ap_DefaultChannel_minimal) {\
    static uint8_t i63 = 0; i63++; if (i63>=63) i63=0;\
    static uint8_t i66 = 0; i66++; if (i66>=66) i66=0;\
    static uint8_t i78 = 0; i78++; if (i78>=78) i78=0;\
    static uint8_t i84 = 0; i84++; if (i84>=84) i84=0;\
    static uint8_t i90 = 0; i90++; if (i90>=90) i90=0;\
    static uint8_t i126 = 0; i126++; if (i126>=126) i126=0;\
    static uint8_t i180 = 0; i180++; if (i180>=180) i180=0;\
    static uint8_t i183 = 0; i183++; if (i183>=183) i183=0;\
    static uint8_t i192 = 0; i192++; if (i192>=192) i192=0;\
    static uint8_t i240 = 0; i240++; if (i240>=240) i240=0;\
    static uint8_t i243 = 0; i243++; if (i243>=243) i243=0;\
    static uint16_t i300 = 0; i300++; if (i300>=300) i300=0;\
    static uint16_t i306 = 0; i306++; if (i306>=306) i306=0;\
    static uint16_t i312 = 0; i312++; if (i312>=312) i312=0;\
    static uint16_t i540 = 0; i540++; if (i540>=540) i540=0;\
    static uint16_t i606 = 0; i606++; if (i606>=606) i606=0;\
    if (i63 == 0) {\
      PERIODIC_SEND_GPS(DefaultChannel);\
    } \
    if (i66 == 6) {\
      PERIODIC_SEND_BAT(DefaultChannel);\
    } \
    if (i78 == 12) {\
      PERIODIC_SEND_ESTIMATOR(DefaultChannel);\
    } \
    if (i84 == 18) {\
      PERIODIC_SEND_WP_MOVED(DefaultChannel);\
    } \
    if (i90 == 24) {\
      PERIODIC_SEND_DL_VALUE(DefaultChannel);\
    } \
    if (i126 == 30) {\
      PERIODIC_SEND_SURVEY(DefaultChannel);\
    } \
    if (i180 == 36) {\
      PERIODIC_SEND_NAVIGATION(DefaultChannel);\
    } \
    if (i183 == 42) {\
      PERIODIC_SEND_CIRCLE(DefaultChannel);\
    } \
    if (i192 == 48) {\
      PERIODIC_SEND_SEGMENT(DefaultChannel);\
    } \
    if (i240 == 54) {\
      PERIODIC_SEND_ATTITUDE(DefaultChannel);\
    } \
    if (i243 == 60) {\
      PERIODIC_SEND_DESIRED(DefaultChannel);\
    } \
    if (i300 == 66) {\
      PERIODIC_SEND_ALIVE(DefaultChannel);\
    } \
    else if (i300 == 72) {\
      PERIODIC_SEND_PPRZ_MODE(DefaultChannel);\
    } \
    else if (i300 == 78) {\
      PERIODIC_SEND_GPS_SOL(DefaultChannel);\
    } \
    if (i306 == 84) {\
      PERIODIC_SEND_CALIBRATION(DefaultChannel);\
    } \
    else if (i306 == 90) {\
      PERIODIC_SEND_DOWNLINK(DefaultChannel);\
    } \
    if (i312 == 96) {\
      PERIODIC_SEND_IR_SENSORS(DefaultChannel);\
    } \
    if (i540 == 102) {\
      PERIODIC_SEND_NAVIGATION_REF(DefaultChannel);\
    } \
    if (i606 == 108) {\
      PERIODIC_SEND_GYRO_RATES(DefaultChannel);\
    } \
  }\
  if (telemetry_mode_Ap_DefaultChannel == TELEMETRY_MODE_Ap_DefaultChannel_extremal) {\
    static uint16_t i300 = 0; i300++; if (i300>=300) i300=0;\
    static uint16_t i306 = 0; i306++; if (i306>=306) i306=0;\
    static uint16_t i318 = 0; i318++; if (i318>=318) i318=0;\
    static uint16_t i324 = 0; i324++; if (i324>=324) i324=0;\
    static uint16_t i330 = 0; i330++; if (i330>=330) i330=0;\
    static uint16_t i342 = 0; i342++; if (i342>=342) i342=0;\
    static uint16_t i606 = 0; i606++; if (i606>=606) i606=0;\
    static uint16_t i612 = 0; i612++; if (i612>=612) i612=0;\
    if (i300 == 0) {\
      PERIODIC_SEND_ALIVE(DefaultChannel);\
    } \
    if (i306 == 6) {\
      PERIODIC_SEND_GPS(DefaultChannel);\
    } \
    if (i318 == 12) {\
      PERIODIC_SEND_ESTIMATOR(DefaultChannel);\
    } \
    if (i324 == 18) {\
      PERIODIC_SEND_NAVIGATION(DefaultChannel);\
    } \
    if (i330 == 24) {\
      PERIODIC_SEND_PPRZ_MODE(DefaultChannel);\
    } \
    if (i342 == 30) {\
      PERIODIC_SEND_DOWNLINK(DefaultChannel);\
    } \
    if (i606 == 36) {\
      PERIODIC_SEND_BAT(DefaultChannel);\
    } \
    if (i612 == 42) {\
      PERIODIC_SEND_DESIRED(DefaultChannel);\
    } \
  }\
}

/* Macros for Fbw process channel DefaultChannel */
#define TELEMETRY_MODE_Fbw_DefaultChannel_default 0
#define PERIOD_COMMANDS_DefaultChannel_0 (5)
#define PERIOD_FBW_STATUS_DefaultChannel_0 (2)
#define PERIOD_ACTUATORS_DefaultChannel_0 (5)
#define TELEMETRY_MODE_Fbw_DefaultChannel_debug 1
#define PERIOD_PPM_DefaultChannel_1 (0.5)
#define PERIOD_RC_DefaultChannel_1 (0.5)
#define PERIOD_COMMANDS_DefaultChannel_1 (0.5)
#define PERIOD_FBW_STATUS_DefaultChannel_1 (1)
#define PERIOD_ACTUATORS_DefaultChannel_1 (5)
#define PeriodicSendFbw_DefaultChannel() {  /* 60Hz */ \
  if (telemetry_mode_Fbw_DefaultChannel == TELEMETRY_MODE_Fbw_DefaultChannel_default) {\
    static uint8_t i120 = 0; i120++; if (i120>=120) i120=0;\
    static uint16_t i300 = 0; i300++; if (i300>=300) i300=0;\
    if (i120 == 0) {\
      PERIODIC_SEND_FBW_STATUS(DefaultChannel);\
    } \
    if (i300 == 6) {\
      PERIODIC_SEND_COMMANDS(DefaultChannel);\
    } \
    else if (i300 == 12) {\
      PERIODIC_SEND_ACTUATORS(DefaultChannel);\
    } \
  }\
  if (telemetry_mode_Fbw_DefaultChannel == TELEMETRY_MODE_Fbw_DefaultChannel_debug) {\
    static uint8_t i30 = 0; i30++; if (i30>=30) i30=0;\
    static uint8_t i60 = 0; i60++; if (i60>=60) i60=0;\
    static uint16_t i300 = 0; i300++; if (i300>=300) i300=0;\
    if (i30 == 0) {\
      PERIODIC_SEND_PPM(DefaultChannel);\
    } \
    else if (i30 == 6) {\
      PERIODIC_SEND_RC(DefaultChannel);\
    } \
    else if (i30 == 12) {\
      PERIODIC_SEND_COMMANDS(DefaultChannel);\
    } \
    if (i60 == 18) {\
      PERIODIC_SEND_FBW_STATUS(DefaultChannel);\
    } \
    if (i300 == 24) {\
      PERIODIC_SEND_ACTUATORS(DefaultChannel);\
    } \
  }\
}
