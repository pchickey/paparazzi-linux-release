#include <unistd.h>
#include "sys_time.h"
#include "main_fbw.h"
#include "main_ap.h"

int main(void) {
  
  init_fbw();
  init_ap();
  init_sys_time_periodic();

  while(1) {
    if (sys_time_periodic()) {
      periodic_task_fbw();
      periodic_task_ap();
    }
    event_task_fbw();
    event_task_ap();
    usleep((useconds_t)16667); // 16.667miliseconds corresponds to 60hz. 
                               // 'time' indicates that user and sys times are v small
  }
  return 0;
}







