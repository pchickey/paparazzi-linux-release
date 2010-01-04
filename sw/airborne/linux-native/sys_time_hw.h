/*
 * Paparazzi $Id: sys_time_hw.h 3726 2009-07-18 18:22:45Z poine $
 *
 * Copyright (C) 2005 Pascal Brisset, Antoine Drouin
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

/*
 *\brief ARM7 timing functions 
 *
 */

#ifndef SYS_TIME_HW_H
#define SYS_TIME_HW_H

#include "std.h"

extern uint32_t cpu_time_ticks;
extern uint32_t last_periodic_event;

void init_sys_time_periodic(void);
bool_t sys_time_periodic(void);
void sys_time_init( void );

#define T0_PCLK_DIV = 1000000 // garbage

#define SYS_TICS_OF_SEC(s)   (uint32_t)(s * PCLK / T0_PCLK_DIV + 0.5)
#define SYS_TICS_OF_USEC(us) SYS_TICS_OF_SEC((us) * 1e-6)
#define SYS_TICS_OF_NSEC(ns) SYS_TICS_OF_SEC((ns) * 1e-9)
#define SIGNED_SYS_TICS_OF_SEC(s) (int32_t)(s * PCLK / T0_PCLK_DIV + 0.5)
#define SIGNED_SYS_TICS_OF_USEC(us) SIGNED_SYS_TICS_OF_SEC((us) * 1e-6)

#define SEC_OF_SYS_TICS(st) (st / PCLK * T0_PCLK_DIV)

#define GET_CUR_TIME_FLOAT() ((float)cpu_time_sec + SEC_OF_SYS_TICS((float)cpu_time_ticks))

#define FIFTY_MS          SYS_TICS_OF_SEC( 50e-3 )
#define AVR_PERIOD_MS     SYS_TICS_OF_SEC( 16.666e-3 )
#ifndef PERIODIC_TASK_PERIOD
#define PERIODIC_TASK_PERIOD AVR_PERIOD_MS
#endif

#define TIME_TICKS_PER_SEC SYS_TICS_OF_SEC(1)

#define InitSysTimePeriodic() last_periodic_event = 0; // garbage pch 28dec09

// static inline bool_t sys_time_periodic( void ) {
// if ( dif >= PERIODIC_TASK_PERIOD) {
//    last_periodic_event += PERIODIC_TASK_PERIOD;
//    cpu_time_ticks += PERIODIC_TASK_PERIOD;
//    if (cpu_time_ticks > TIME_TICKS_PER_SEC) {
//      cpu_time_ticks -= TIME_TICKS_PER_SEC;
//      cpu_time_sec++;
//   }
//    return TRUE;
//  }
//   return FALSE;
// }

/** Busy wait, in microseconds */
// static inline void sys_time_usleep(uint32_t us) {
// }

#endif /* SYS_TIME_HW_H */
