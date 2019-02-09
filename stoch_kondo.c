#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include "wiringPi.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

int serialOpen (const char *device, const int baud)
{
  struct termios options ;
  speed_t myBaud = B1152000 ;
  int     status, fd ;
 if ((fd = open (device, O_RDWR | O_NOCTTY | O_NDELAY)) == -1)
    return -1 ;
 cfsetispeed (&options, myBaud) ;
 cfsetospeed (&options, myBaud) ;
usleep (10000) ;
}


