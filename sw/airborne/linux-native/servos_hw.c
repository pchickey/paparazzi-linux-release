

#include "actuators.h"
#include "paparazzi.h"
#include "airframe.h"

void servos_isr (void) {return;}

uint8_t servos_idx;


void actuators_init ( void ) {
  
  servos_idx = _NB_CHANNELS;
  /* Set all servos at their midpoints */
  /* compulsory for unaffected servos  */
  uint8_t i;
  for( i=0 ; i < _NB_CHANNELS ; i++ )
    servos_values[i] = SERVOS_TICS_OF_USEC(1500);
#ifdef SERVO_MOT
  servos_values[SERVO_MOTOR] = SERVOS_TICS_OF_USEC(SERVO_MOTOR_NEUTRAL);
#endif
#ifdef SERVO_MOTOR_LEFT
  servos_values[SERVO_MOTOR_LEFT] = SERVOS_TICS_OF_USEC(SERVO_MOTOR_LEFT_NEUTRAL);
#endif
#ifdef SERVO_MOTOR_RIGHT
  servos_values[SERVO_MOTOR_RIGHT] = SERVOS_TICS_OF_USEC(SERVO_MOTOR_RIGHT_NEUTRAL);
#endif
#ifdef SERVO_HATCH
  servos_values[SERVO_HATCH] = SERVOS_TICS_OF_USEC(SERVO_HATCH_NEUTRAL);
#endif
}


uint16_t servos_values[_NB_CHANNELS];

