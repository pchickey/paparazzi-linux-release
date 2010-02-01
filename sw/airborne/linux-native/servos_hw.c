#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "std.h"
#include "actuators.h"
#include "paparazzi.h"
#include "airframe.h"

uint16_t servos_values[SERVOS_NB];
int pololu_fd;
void servo_send(int fd, int servo, uint8_t value);

void actuators_init(void) 
{  
  pololu_fd = open(POLOLU_PATH, O_WRONLY | O_NOCTTY);
    if (pololu_fd < 0) { perror("couldn't open pololu servo device"); exit(-1); }
  
  struct termios tio;
  bzero(&tio, sizeof(tio));
  tio.c_cflag = POLOLU_BAUD | CS8 | CREAD;
  tio.c_lflag = ICANON;
  tcflush(pololu_fd, TCIFLUSH);
  tcsetattr(pololu_fd, TCSANOW, &tio);

  int ii;
  for(ii=0; ii < SERVOS_NB; ii++ )
    servos_values[ii] = 220;

  actuators_send_to_pololu();
}

void actuators_send_to_pololu(void)
{
  if ( pololu_fd < 0 ) return;
  servo_send(pololu_fd, 0, Chop(servos_values[0],0,254));
  servo_send(pololu_fd, 1, Chop(servos_values[1],0,254));
  servo_send(pololu_fd, 2, Chop(servos_values[2],0,254));
  servo_send(pololu_fd, 3, Chop(servos_values[3],0,254));
}

// mini ssc protocol for pololu micro maestro
// http://www.pololu.com/docs/0J40/5.e
void servo_send(int fd, int servo, uint8_t value)
{
  uint8_t msg[3];
  msg[0] = (uint8_t) 0xFF;
  msg[1] = (uint8_t) servo;
  msg[2] = value;
  write(fd,msg,(ssize_t)3);
  // debug pch
  // printf("write servo %d value %d\n", msg[1], msg[2]);

}

 
