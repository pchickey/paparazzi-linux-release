#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <mqueue.h>
#include "queues.h"

#define GPS_BAUD B38400
#define GPS_MODEM "/dev/ftdi3"

#define ATT_BAUD B19200
#define ATT_MODEM "/dev/ftdi1"

void mq_send_gps(void*, void*, int);
void mq_send_att(void*, void*, int);

void print_callback(void*, void*, int);

struct tty_reader_arguments
{
  char* fname;
  struct termios tio;
  void (*callback)(void*, void*, int);
  void *cb_args;
};

struct mq_send_args
{
  mqd_t queue;
};

void mq_send_gps( void* v_args, void* data, int len )
{
  struct mq_send_args* args = (struct mq_send_args *) v_args;
  mq_send(args->queue, data, len, 0);
}

void mq_send_att( void* v_args, void* data_v, int len )
{
  struct att_msg msg;
  char * data = (char *) data_v;
  struct mq_send_args* args = (struct mq_send_args *) v_args;

  // expecting data to be a string like
  // "$A0,254\r\n"
  // or "$A1,21\r\n"
  // where data[2] is the channel number,
  // and data[4] begins the value
  data[len] = 0;
  printf("%s",data);
  
  msg.channel = atoi(&data[2]);
  msg.value = atoi(&data[4]);

  if (msg.channel > 0 && msg.channel <= 3)
  {
//    printf("parsed channel %d value %d\n", msg.channel, msg.value);
    mq_send(args->queue,(char *)&msg,sizeof(msg), 0);
//    printf("message sent\n");
  }
}

void print_callback( void* nachtmicht, void* str_v, int len )
{
  char * str = (char *) str_v;
  str[len] = 0;
  printf(":%s",str);
}

void *tty_reader( void *v_args )
{
  struct tty_reader_arguments* args = (struct tty_reader_arguments *) v_args;

  printf("thread started for %s\n",args->fname);

  char buf[255];
  int res;

  int fd = open(args->fname, O_RDONLY | O_NOCTTY);
  if (fd < 0) { perror(args->fname); exit(-1); }
  printf("opened %s with fd %d\n",args->fname,fd);

  tcflush(fd,TCIFLUSH);
  tcsetattr(fd,TCSANOW,&(args->tio));

  while(1)
  {
//    printf("%s---",args->fname);
    res = read(fd,buf,255);
//    printf(">%d\n", res);
    if (res > -1)
    {
      args->callback(args->cb_args,buf,res);
    } 
    else 
    {
      printf("read failed: ");
      perror(args->fname);
    }
  }
  return NULL;
} 

int main( void )
{
  pthread_t gps_thread, att_thread;
  struct tty_reader_arguments gps_args, att_args;

  mqd_t gps_queue = mq_open(GPS_MQ_NAME, O_WRONLY | O_CREAT, 0666, NULL);

  bzero(&gps_args,sizeof(gps_args));
  gps_args.fname = GPS_MODEM;
  gps_args.tio.c_cflag = GPS_BAUD | CS8 | CREAD;
  gps_args.tio.c_lflag = ICANON;
  gps_args.callback = mq_send_gps;
  
  struct mq_send_args gps_cbargs;
  gps_cbargs.queue = gps_queue;
  gps_args.cb_args = &gps_cbargs; 

  // pthread_create(&gps_thread, NULL, tty_reader, (void *)&gps_args);
  
  // setup attitude thread:

  mqd_t att_queue = mq_open(ATT_MQ_NAME, O_WRONLY | O_CREAT, 0666, NULL);
  
  bzero(&att_args,sizeof(att_args));
  att_args.fname = ATT_MODEM;
  att_args.tio.c_cflag = ATT_BAUD | CS8 | CREAD;
  att_args.tio.c_lflag = ICANON;
  att_args.callback = mq_send_att;
  struct mq_send_args att_cbargs; 
  gps_cbargs.queue = att_queue;
  att_args.cb_args = &att_queue;

  pthread_create(&att_thread, NULL, tty_reader, (void *)&att_args);

  pthread_exit(NULL);
}




