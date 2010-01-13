/* This file has been generated from /home/pat/paparazzi3/conf/airframes/linuxfc.xml */
/* Please DO NOT EDIT */

#ifndef MODULES_H
#define MODULES_H 

#ifdef USE_MODULES

#define MODULES_IDLE  0
#define MODULES_RUN   1
#define MODULES_START 2
#define MODULES_STOP  3

#include "std.h"


#ifdef MODULES_C

static inline void modules_init(void) {
}

static inline void modules_periodic_task(void) {

}

static inline void modules_event_task(void) {
}

#endif // MODULES_C

#ifdef MODULES_DATALINK_C

#include "messages.h"
#include "airframe.h"
static inline void modules_parse_datalink(uint8_t msg_id __attribute__ ((unused))) {
}

#endif // MODULES_DATALINK_C

#endif // USE_MODULES

#endif // MODULES_H
