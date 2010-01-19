// Use libgps library to provide paparazzi with position information
// Pat Hickey 18 Jan 2010
// This file is part of paparazzi and is licensed by the GPL

// refer to `man 3 libgps` for information about the c library
// and http://gpsd.berlios.de/ for information about the gpsd daemon.
// for this code to work, you'll need to configure gpsd separately.

// this code eliminates the parsing of NMEA sentences or UBX messages, 
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
#include "gps_ppz.h" // paparazzi gps

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
void gps_callback(struct gps_data_t *, char *, size_t, int);

void gps_init(void)
{
  struct gps_data_t *libgps_con; 
  libgps_con = gps_open("localhost", "2947");
    if (libgps_con == NULL) { perror("libgps open returned NULL"); exit(-1); }
  
  pthread_t callback_thread; 
  gps_set_callback(libgps_con, &gps_callback, &callback_thread);
  
}

void gps_callback(struct gps_data_t *gps_data, char *buf, size_t len, int level)
{
  printf("gps_callback called\n");




}
