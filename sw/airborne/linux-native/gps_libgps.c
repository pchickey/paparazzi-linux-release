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
#include "latlong.h"
#include "nav.h"

// These global variables come right from gps_ubx.c:
uint16_t gps_week; // Not used
uint32_t gps_itow; // Not used
int32_t gps_alt;
uint16_t gps_gspeed;
int16_t gps_climb;
int16_t gps_course;
int32_t gps_utm_east, gps_utm_north;
uint8_t gps_utm_zone;
uint8_t gps_mode;
volatile bool_t gps_msg_received;
bool_t gps_pos_available; // Not used
uint8_t ubx_id, ubx_class; // Not used
int32_t gps_lat, gps_lon;
uint16_t gps_reset; // Not used
uint16_t gps_PDOP;
uint32_t gps_Pacc, gps_Sacc; // Not used
uint8_t gps_numSV;

uint8_t gps_nb_ovrn; // Not used
uint8_t gps_nb_channels; 
struct svinfo gps_svinfos[GPS_NB_CHANNELS];

// Variables used within gps_libgps.c:
static struct gps_data_t gps_con; 

void gps_init(void)
{
  int res;
  res = gps_open_r("localhost", "2947", &gps_con);
  if (res < 0) {
    perror("libgps open failed"); 
    exit(-1); 
  }
  gps_stream(&gps_con, WATCH_ENABLE, NULL);

  pthread_mutex_init(&gps_mutex, NULL);
  
  pthread_t gps_update_thread;
  pthread_create(&gps_update_thread, NULL, &gps_update, NULL);
}

void *gps_update(void *nothing)
{
  int i;
  printf("calling gps_update\n");
  while(1)
  {
    gps_poll(&gps_con);
    // printf("gps polled: status %d lat %f lon %f time %f \n", gps_con.status, gps_con.fix.latitude, gps_con.fix.longitude, gps_con.fix.time);
    
    // acquire the gps lock:
    pthread_mutex_lock(&gps_mutex); 
    // copy the values from the libgps result object into 
    // Paparazzi's global variables:
    gps_mode = gps_con.fix.mode;
    gps_lat = gps_con.fix.latitude * 1e7;
    gps_lon = gps_con.fix.longitude * 1e7;
    gps_gspeed = gps_con.fix.speed * 100;
    gps_climb = gps_con.fix.climb;
    gps_alt = gps_con.fix.altitude * 100;
    // calculate utm values from lattitude/longitude:
    latlong_utm_of(RadOfDeg(gps_lat/1e7),RadOfDeg(gps_lon/1e7), nav_utm_zone0);
    gps_utm_east = latlong_utm_x * 100;
    gps_utm_north = latlong_utm_y * 100;
    gps_utm_zone = nav_utm_zone0;
    // libgps seems to give the course with respect to true north
    // I really hope the paparazzi is okay with that
    gps_course = gps_con.fix.track * 10;
    gps_PDOP = gps_con.dop.pdop;
    // A number of other values are only available with certain 
    // gps protocol versions. None of them are used by the autopilot,
    // so I won't worry about them for now.
    
    // Copy the satelite info:
    gps_numSV = gps_nb_channels = gps_con.satellites_visible;
    for (i = 0; i < Min(gps_nb_channels, GPS_NB_CHANNELS); i++){
      gps_svinfos[i].svid = gps_con.PRN[i];
      gps_svinfos[i].elev = gps_con.elevation[i];
      gps_svinfos[i].azim = gps_con.azimuth[i];
      // I have no idea what these next couple fields are.
      // They are not referenced anywhere in the ap code, so I hope
      // it won't break anything to give them dummy values of 0.
      gps_svinfos[i].flags = 0;
      gps_svinfos[i].qi = 0;
      gps_svinfos[i].cno = 0;
    }
    
    // Tell the main thread that a gps message has been received:
    gps_msg_received = TRUE;
    // Release the lock:
    pthread_mutex_unlock(&gps_mutex);
  } 
}

void parse_gps_msg( void ){

}

