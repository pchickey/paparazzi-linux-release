#include <stdio.h>
#include <stddef.h>
#include <mqueue.h>
#include "queues.h"
#include <string.h>
int main(void){
 char buf[9000];
 int i;
 mqd_t mq = mq_open(GPS_MQ_NAME, O_CREAT | O_RDWR);
 for (i = 0; i < 10; i++){
   ssize_t s = mq_receive(mq, &buf, 9000, 0);
   
   printf(":%s:%d\n", buf, s);
 }

}
