#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>

#define GPS_BAUD B9600
#define GPS_MODEM "/dev/ftdi3"

#define ATT_BAUD B19200
#define ATT_MODEM "/dev/ftdi1"

struct tty_reader_arguments
{
  char* fname;
  struct termios tio;
};

void *tty_reader( void *args )
{
  char* fname = ((struct tty_reader_arguments*) args)->fname; 
  struct termios tio = ((struct tty_reader_arguments*) args)->tio; 

  printf("thread started for %s\n",fname);

  char buf[255];
  int res;

  int fd = open(fname, O_RDONLY | O_NOCTTY);
  if (fd < 0) { perror(fname); exit(-1); }
  printf("opened %s with fd %d\n",fname,fd);

  tcflush(fd,TCIFLUSH);
  tcsetattr(fd,TCSANOW,&tio);

  while(1)
  {
    printf("%s-------",fname);
    res = read(fd,buf,255);
    printf(">\n");
    if (res > -1)
    {
      buf[res] = 0;
      printf(":%s:%d\n",buf,res);
    } 
    else 
    {
      printf("read failed: ");
      perror(fname);
    }
  }

  return NULL;
} 
int main (void)
{
  pthread_t threads[2];
  
  struct termios gps_tio, att_tio;
  
  struct tty_reader_arguments gps_args, att_args;
  gps_args.fname = GPS_MODEM;
  bzero(&(gps_args.tio),sizeof(gps_tio));
  gps_args.tio.c_cflag = GPS_BAUD | CS8 | CREAD;
  gps_args.tio.c_lflag = ICANON;
  
  att_args.fname = ATT_MODEM;
  bzero(&(att_args.tio),sizeof(att_tio));
  att_args.tio.c_cflag = ATT_BAUD | CS8 | CREAD;
  att_args.tio.c_lflag = ICANON;
  
  
  pthread_create(&threads[1], NULL, tty_reader, (void *)&att_args);
  pthread_create(&threads[0], NULL, tty_reader, (void *)&gps_args);

  pthread_exit(NULL);
}
