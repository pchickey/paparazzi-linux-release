#ifndef SERVOS_HW_H
#define SERVOS__HW_H

#include <inttypes.h>
#include "std.h"
#include "airframe.h"

// don't expect pololu baud to change or matter,
// since the usb serial device is virtual.
// I set it through termios for good luck
#ifndef POLOLU_BAUD
#define POLOLU_BAUD B9600 
#endif

// we dont use tics or usecs, but others depend on this macro
#define SERVOS_TICS_OF_USEC(s) s

extern uint16_t servos_values[SERVOS_NB];
extern void actuators_send_to_pololu(void);

#define Actuator(i) servos_values[i]
#define ActuatorsCommit() actuators_send_to_pololu()

#endif /* SERVOS_HW_H */
