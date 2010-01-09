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


int main (void)
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

  printf("first line read was %s\n", readbuf);

  int result;

  // read out the string prefix
  char prefix;
  int channel, data;
  while (1)
  {
    result = fscanf(adc_file,"$%c",&prefix);
    if (result >= 1) // printf("didn't read prefix character\n");
    { 
      if (prefix == 'A')
     {
        result = fscanf(adc_file,"%d,%d", &channel, &data);
        if (result < 2) printf("didnt get channel and data, result was %d\n", result);
        else
        {
          printf("parsed channel %d data %d\n", channel, data);
        }
      fgets(readbuf, 255, adc_file); // flush rest of the line
      }
      else // prefix == S (EQ)
      { 
        fgets(readbuf, 255, adc_file); // cleanup the rest of the line
        printf("prefix not A: rest of line %s\n", readbuf);
      }
    }
  }
  return 0;
}


