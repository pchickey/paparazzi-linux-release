/* This file is part of paparazzi and licensed under the GPL */
/* Modifications by Pat Hickey (pat@moreproductive.org), Jan 2010, for Linux port */

#include "airframe.h"
#include "actuators.h"
#include "main_fbw.h"
#include "ap_state.h"

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
  SetActuatorsFromCommands(ap_state->commands);
  return;
}
