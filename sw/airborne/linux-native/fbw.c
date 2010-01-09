#include "actuators.h"
#include "main_fbw.h"

void init_fbw( void ) 
{
  adc_init();
  actuators_init();
  return;
}

void event_task_fbw(void) 
{
  return;
}


/************* PERIODIC ******************************************************/
void periodic_task_fbw( void ) 
{
  return;
}
