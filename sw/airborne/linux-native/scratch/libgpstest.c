#include <stdio.h>
#include <unistd.h>

#include "gps_libgps.h"

int main (void)
{
  gps_init();
  printf("gps initialized successfully\n");
  while(1)
  {
    gps_update();
    usleep(16000);
  }
}
