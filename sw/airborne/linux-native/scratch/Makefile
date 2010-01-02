
CC=gcc
CFLAGS= -pthread -lrt


all : ttytest readgpsqueue

readgpsqueue : readgpsqueue.c queues.h
	$(CC) $(CFLAGS) readgpsqueue.c -o readgpsqueue

ttytest : ttytest.c queues.h
	$(CC) $(CFLAGS) ttytest.c -o ttytest

.PHONY: clean

clean:
	rm ttytest readgpsqueue
