#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <math.h>

#define POLOLU_PATH_LONG "/dev/serial/by-id/usb-Pololu_Corporation_Pololu_Micro_Maestro_6-Servo_Controller_00001644-if00"
#define POLOLU_PATH "/dev/ttyACM0"
#define POLOLU_BAUD B9600

void servo_send(int,int,uint8_t);

void servo_send(int fd, int servo, uint8_t value)
{
  uint8_t msg[3];
  msg[0] = (uint8_t) 0xFF;
  msg[1] = (uint8_t) servo;
  msg[2] = value; // (value >= (uint8_t)255) ? value : 254;

  printf("%X sending servo %d value %d\n", msg[0], msg[1], msg[2]);

  write(fd,msg,(ssize_t)3);
}

int main (void)
{

  int fd = open(POLOLU_PATH_LONG, O_RDWR | O_NOCTTY);
    if (fd < 0) { printf("%s ", POLOLU_PATH); perror("couldn't open"); exit(-1); }
  struct termios tio;
 
  bzero(&tio, sizeof(tio));
  tio.c_cflag = POLOLU_BAUD | CS8 | CREAD;
  tio.c_lflag = ICANON;

  

  int ii;
  uint8_t servo_out;
  for (ii = 0;;ii++)
  { 
    servo_out = 128 + (uint8_t)(40*sin( ((float)ii)/10.f));
    servo_send(fd, 1, servo_out);
    servo_send(fd, 2, servo_out);
    servo_send(fd, 3, servo_out);
    usleep(20000);
  }
  return 0;
}
