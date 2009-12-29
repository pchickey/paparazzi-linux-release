


#ifndef SERVOS_HW_H
#define SERVOS__HW_H

#include <inttypes.h>
#include "std.h"

#include "sys_time.h"


#define SERVOS_TICS_OF_USEC(s) s
#define ChopServo(x,a,b) Chop(x, a, b)

#if defined NB_CHANNELS
#define _NB_CHANNELS Chop(NB_CHANNELS,0,10)
#else
#define _NB_CHANNELS 10
#endif

#define SERVOS_ISR servos_isr


extern uint16_t servos_values[_NB_CHANNELS];

#define Actuator(i) servos_values[i]
#define ActuatorsCommit() {}

extern uint8_t servos_idx;
void servos_isr(void);

#endif /* SERVOS_HW_H */
