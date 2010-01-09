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

/** First NB_ADC for bank 0, others for bank 2 */
static struct adc_buf* buffers[NB_ADC*2];

volatile uint16_t adc0_val[NB_ADC] = {1,  2,  3,  4,  5,  6,  7,  8};
volatile uint16_t adc1_val[NB_ADC] = {9, 10, 11, 12, 13, 14, 15, 16};

void adcISR0 ( void );
void adcISR1 ( void );

void adc_buf_channel(uint8_t adc_channel, struct adc_buf* s, uint8_t av_nb_sample) {
  buffers[adc_channel] = s;
  s->av_nb_sample = av_nb_sample;
}

// below is code by pch and brad lord

void adc_init(void) 
{ 
  pthread_t adc_reader_thread;
  pthread_create(&adc_reader_thread, NULL, adc_reader, NULL);
}

void *adc_reader(void *macht_nicht)
{
  int adc_fd;
  adc_fd = open(ADC_PATH, O_RDONLY | O_NOCTTY);
    if (adc_fd < 0) { perror("adc_fd could not be opened"); exit(-1); }
  struct termios tio;
  bzero(&tio, sizeof(tio));
  tio.c_cflag = ADC_BAUD | CS8 | CREAD;
  tio.c_lflag = ICANON;
  tcflush(adc_fd, TCIFLUSH);
  int res = tcsetattr(adc_fd, TCSANOW, &tio);
  printf("tcsetattr returned %d\n", res); perror("tcsetattr");

  FILE *adc_file;
  adc_file = fdopen(adc_fd, "r");

  // this fgets is just to get the first line out of the device
  // the first line might be garbage, the second onwards should be fine
  char readbuf[255];
  fgets(readbuf, 255, adc_file);

  int result;
  // read out the string prefix
  char prefix;
  int channel, data;
  while (1)
  {
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
      else // prefix == S (EQ)
      { 
        fgets(readbuf, 255, adc_file); // consume the rest of the line
      }
    }
    else // we didn't cach a dollar sign as our first char
    fgets(readbuf, 255, adc_file); // consume the rest of the line
  }
  return 0;
}

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
