

#include "actuators.h"
#include "paparazzi.h"
#include "airframe.h"

void servos_isr (void) {return;}

uint8_t servos_idx;

void actuators_init ( void ) 
{  
  servos_idx = _NB_CHANNELS;
  /* Set all servos at their midpoints */
  /* compulsory for unaffected servos  */
  uint8_t i;
  for( i=0 ; i < _NB_CHANNELS ; i++ )
    servos_values[i] = SERVOS_TICS_OF_USEC(1500);
}


uint16_t servos_values[_NB_CHANNELS];

