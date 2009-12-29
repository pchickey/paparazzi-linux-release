#include "sys_time.h"
#include ACTUATORS


uint32_t cpu_time_ticks;
uint32_t last_periodic_event;

uint32_t sys_time_chrono_start; /* T0TC ticks */
uint32_t sys_time_chrono;       /* T0TC ticks */

void TIMER0_ISR ( void ) {
      SERVOS_ISR();
}
