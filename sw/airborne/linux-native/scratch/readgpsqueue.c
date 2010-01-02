#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>
#include <unistd.h>
#include "queues.h"

#define die(msg) { perror(msg); exit(EXIT_FAILURE); }

void print_hex( unsigned char *, int);

static void msgprinter( union sigval sv )
{
  struct mq_attr attr;
  ssize_t nr;
  void *buf;
  mqd_t mqdes;
  struct sigevent mq_callback;

  printf("entered msgprinter\n");

  mqdes = *((mqd_t *) sv.sival_ptr);
  
  printf("re-registering notify\n");

  mq_callback.sigev_notify = SIGEV_THREAD;
  mq_callback.sigev_notify_function = msgprinter;
  mq_callback.sigev_notify_attributes = NULL;
  mq_callback.sigev_value.sival_ptr = &mqdes;

  if (mq_notify(mqdes, &mq_callback) == -1) die("mq_notify re-register");

  if (mq_getattr(mqdes, &attr) == -1) die("mq_getattr");
  buf = malloc(attr.mq_msgsize);
    if (buf == NULL) die("malloc");
  
  do {
    nr = mq_receive(mqdes, buf, attr.mq_msgsize, NULL);
    printf("> %d\n",nr);
    print_hex((unsigned char *) buf, nr);
  } while (nr > -1);
  
  free(buf);
  printf("exiting msgprinter\n");
}

void print_hex(unsigned char* data, int len)
{
  int ii;
  for (ii = 0; ii < len; ii++)
    printf("%x ", data[ii]);
  if (len > 0) printf("\n");
}

int main (void)
{
  printf("entering main\n");
  mqd_t mqdes;
  struct sigevent mq_callback;
  
  mqdes = mq_open(GPS_MQ_NAME, O_RDONLY | O_CREAT, 0666, NULL );
  if (mqdes == (mqd_t) -1) die("mq_open");

  printf("mq opened\n");

  mq_callback.sigev_notify = SIGEV_THREAD;
  mq_callback.sigev_notify_function = msgprinter;
  mq_callback.sigev_notify_attributes = NULL;
  mq_callback.sigev_value.sival_ptr = &mqdes;

  if (mq_notify(mqdes, &mq_callback) == -1) die("mq_notify");

  printf("pausing main\n");
  pause();
}

