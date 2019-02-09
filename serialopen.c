#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "wiringSerial.h"

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
