// Pat Hickey and Bradley Lord, Jan 2010
// This file is part of paparazzi and licensed under the GPL

#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <pthread.h>
#include "adc.h"

// We no longer have on-chip analog to digital converters. Our ADCs come from
// an Arduino attached to a serial port at ADC_PATH, operating at ADC_BAUD. 
// The Arduino outputs analog readings in an NMEA style sentence: $A1,234\r\n 
// Each sentence is expected to start with a '$A' followed by the channel number, 
// a comma, and then the digital reading as an integer. 
// The serial port is read as a file stream in a separate thread. We have not 
// implemented any sort of read/write locking on the adc_buf objects yet, so 
// this may be totally unsafe.


// The following buffers are used by generated code to read analog inputs.

/** First NB_ADC for bank 0, others for bank 2 */
static struct adc_buf* buffers[NB_ADC*2];

volatile uint16_t adc0_val[NB_ADC] = {1,  2,  3,  4,  5,  6,  7,  8};
volatile uint16_t adc1_val[NB_ADC] = {9, 10, 11, 12, 13, 14, 15, 16};

void adc_buf_channel(uint8_t adc_channel, struct adc_buf* s, uint8_t av_nb_sample) {
  buffers[adc_channel] = s;
  s->av_nb_sample = av_nb_sample;
}

// adc_init launches a worker thread.
void adc_init(void) 
{ 
  pthread_t adc_reader_thread;
  pthread_create(&adc_reader_thread, NULL, adc_reader, NULL);
}

// adc_reader is the worker thread. It needs no arguments.
void *adc_reader(void *macht_nicht)
{
  int adc_fd;
  adc_fd = open(ADC_PATH, O_RDONLY | O_NOCTTY);
    if (adc_fd < 0) { perror("adc_fd could not be opened"); exit(-1); }
  // The settings are simple ('cooked') here because we expect the carraige 
  // returns to flush the tty buffer frequently.
  struct termios tio;
  bzero(&tio, sizeof(tio));
  tio.c_cflag = ADC_BAUD | CS8 | CREAD;
  tio.c_lflag = ICANON;
  tcflush(adc_fd, TCIFLUSH);
  tcsetattr(adc_fd, TCSANOW, &tio);

  // We read as a FILE stream so we don't have to worry about blocking
  FILE *adc_file;
  adc_file = fdopen(adc_fd, "r");

  // this fgets is just to get the first line out of the device
  // the first line might be garbage, the second onwards should be fine
  char readbuf[255];
  fgets(readbuf, 255, adc_file);

  int result;
  char prefix;
  int channel, data;
  while (1)
  {
    // read out the string prefix
    result = fscanf(adc_file,"$%c",&prefix);
    if (result >= 1) 
    { 
     if (prefix == 'A')
     {
        result = fscanf(adc_file,"%d,%d", &channel, &data);
        if (result >= 2) 
        {
          adc_buffer_insert(channel,data);
        }
      fgets(readbuf, 255, adc_file); // flush rest of the line
      }
      else // prefix wasn't an 'A'
      { 
        fgets(readbuf, 255, adc_file); // consume the rest of the line
      }
    }
    else // we didn't cach a dollar sign as our first char
    fgets(readbuf, 255, adc_file); // consume the rest of the line
  }
  return 0;
}

// We insert directly into the channel specified by the Arduino.
// Make sure to use that channel number in the conf files.
// This code came right out of the ADC ISR. It would be
// a good idea to implement some sort of locking on this write,
// as well as any reads, to garuntee integrity. We haven't found any
// serious issues with it to date, though.
void adc_buffer_insert(int channel, int data)
{
  struct adc_buf* buf = buffers[channel];
  if (buf) {
    uint8_t new_head = buf->head + 1;
    if (new_head >= buf->av_nb_sample) new_head = 0;
    buf->sum -= buf->values[new_head];
    buf->values[new_head] = data;
    buf->sum += data;
    buf->head = new_head;   
  }
  return;
}
