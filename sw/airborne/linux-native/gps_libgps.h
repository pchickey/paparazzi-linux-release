// gps_libgps.h
// pch 18jan10
#ifndef _GPS_LIBGPS_H_
#define _GPS_LIBGPS_H_

#include <gps.h>
#include <pthread.h>

#define GpsFixValid() (gps_mode == 3)

void gps_init(void);
void *gps_update(void*);

pthread_mutex_t gps_mutex;

#endif
