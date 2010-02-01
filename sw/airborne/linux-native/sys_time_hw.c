#include "std.h"
#include <unistd.h>
#include "sys_time.h"
#include ACTUATORS

uint32_t cpu_time_ticks;
uint32_t last_periodic_event;

uint32_t sys_time_chrono_start; /* T0TC ticks */
uint32_t sys_time_chrono;       /* T0TC ticks */

void init_sys_time_periodic(void)
{

}

bool_t sys_time_periodic(void)
{
  return TRUE;
}

void sys_time_init(void)
{

}

