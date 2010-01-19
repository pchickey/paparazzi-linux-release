#include <stdio.h>
#include <unistd.h>

#include "gps_libgps.h"

int main (void)
{
  gps_init();
  printf("gps initialized successfully\n");
  pause(); // work done by thread spawned in gps_init
}
