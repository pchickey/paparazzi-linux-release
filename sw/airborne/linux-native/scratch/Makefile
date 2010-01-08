
CC=gcc
CFLAGS=-g -pthread -lrt

PAP_INCLUDES=-I/home/pat/paparazzi3/sw/include -I/home/pat/paparazzi3/sw/airborne -I/home/pat/paparazzi3/sw/airborne/linux-native

all : servotest

servotest: servotest.c
	$(CC) $(CFLAGS) -lm servotest.c -o servotest

uarttest: ../uart_hw.c ../uart_hw.h ../../uart.h uart_main.c
	$(CC) $(CFLAGS) $(PAP_INCLUDES) -DUSE_UART0 -DUART0_FNAME=\"/dev/ftdi3\" -DUART0_BAUD=B38400 \
	../uart_hw.c uart_main.c -o uarttest

readgpsqueue : readgpsqueue.c queues.h
	$(CC) $(CFLAGS) readgpsqueue.c -o readgpsqueue

readattqueue : readattqueue.c queues.h
	$(CC) $(CFLAGS) readattqueue.c -o readattqueue

ttytest : ttytest.c queues.h
	$(CC) $(CFLAGS) ttytest.c -o ttytest

.PHONY: clean

clean:
	rm ttytest readgpsqueue readattqueue
