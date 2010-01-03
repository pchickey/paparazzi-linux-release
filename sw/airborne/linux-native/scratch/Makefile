
CC=gcc
CFLAGS=-g -pthread -lrt


all : ttytest readgpsqueue readattqueue

readgpsqueue : readgpsqueue.c queues.h
	$(CC) $(CFLAGS) readgpsqueue.c -o readgpsqueue

readattqueue : readattqueue.c queues.h
	$(CC) $(CFLAGS) readattqueue.c -o readattqueue

ttytest : ttytest.c queues.h
	$(CC) $(CFLAGS) ttytest.c -o ttytest

.PHONY: clean

clean:
	rm ttytest readgpsqueue readattqueue
