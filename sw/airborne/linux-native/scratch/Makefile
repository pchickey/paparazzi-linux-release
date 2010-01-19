
CC=gcc
CFLAGS=-g -O0 -pthread -lrt

PAP_INCLUDES=-I/home/pat/paparazzi3/sw/include -I/home/pat/paparazzi3/sw/airborne -I/home/pat/paparazzi3/sw/airborne/linux-native -I/home/pat/paparazzi3/var/LINUXFC/

all : libgpstest

libgpstest: ../gps_libgps.c libgpstest.c ../gps_libgps.h
	$(CC) $(PAP_INCLUDES) -L/home/pat/src/gpsd-2.90/.libs/ -lgps libgpstest.c ../gps_libgps.c -o libgpstest

fopentty: fopen_tty.c
	$(CC) -DADC_PATH=\"/dev/ftdi1\" -DADC_BAUD=B19200 \
	fopen_tty.c -o fopentty

servo_hw_test: servo_hw_test.c
	$(CC) $(PAP_INCLUDES) -DPOLOLU_PATH=\"/dev/ttyACM0\" -DSERVOS_NB=4 -DPOLOLU_BAUD=B9600 \
	../servos_hw.c servo_hw_test.c -o servo_hw_test

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
	rm libgpstest
	
#rm ttytest readgpsqueue readattqueue servo_hw_test servotest uarttest
