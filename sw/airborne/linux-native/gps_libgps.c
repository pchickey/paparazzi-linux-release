// Use libgps library to provide paparazzi with position information
// Pat Hickey 18 Jan 2010
// This file is part of paparazzi and is licensed by the GPL

// This code uses the latest release of gpsd, 2.90. This version
// of gpsd breaks compatibility with previous releases. Please check
// your version if you get compile or runtime errors.

// Don't refer to `man 3 libgps` for information about the c library
// http://gpsd.berlios.de/libgps.html has more recent for information 
// about the library. It is also the best source on the gpsd daemon.
// For this code to work, you'll need to configure gpsd separately.

// This code eliminates the parsing of NMEA sentences or UBX messages, 
// using the more capable gpsd instead. gpsd also supports multiple
// connections, so that you can use gps in multiple applications.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <gps.h> // libgps

#include "std.h"
#include "gps_ppz.h" // paparazzi gps had to be renamed because of naming conflict
#include "gps_libgps.h" // prototypes for these functions

// These global variables come right from gps_ubx.c:
uint8_t gps_mode;
uint16_t gps_week;
uint32_t gps_itow;
int32_t gps_alt;
uint16_t gps_gspeed;
int16_t gps_climb;
int16_t gps_course;
int32_t gps_utm_east, gps_utm_north;
uint8_t gps_utm_zone;
uint8_t gps_mode;
volatile bool_t gps_msg_received;
bool_t gps_pos_available;
uint8_t ubx_id, ubx_class;
int32_t gps_lat, gps_lon;
uint16_t gps_reset;
uint16_t gps_PDOP;
uint32_t gps_Pacc, gps_Sacc;
uint8_t gps_numSV;

// Variables used within gps_libgps.c:

void gps_init(void)
{
  struct gps_data_t gps_con; 
  int res;
  res = gps_open_r("localhost", "2947", &gps_con);
    if (res < 0) { perror("libgps open failed"); exit(-1); }
  gps_stream(&gps_con, WATCH_ENABLE, NULL);
  
  pthread_t gps_update_thread;
  pthread_create(&gps_update_thread, NULL, &gps_update, (void *)&gps_con);
}

void *gps_update(void *gps_con_a)
{
  struct gps_data_t *gps_con = (struct gps_data_t *) gps_con_a;
  printf("calling gps_update\n");
  while(1)
  {
    gps_poll(gps_con);
    printf("gps polled: status %d lat %f lon %f time %f \n", gps_con->status, gps_con->fix.latitude, gps_con->fix.longitude, gps_con->fix.time);
  } 
}

