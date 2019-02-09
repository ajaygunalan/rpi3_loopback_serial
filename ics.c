#include <wiringSerial.h>
#include <wiringPi.h>
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


#define PIN_NUMBER 1
#define enHigh  digitalWrite(PIN_NUMBER, HIGH);
#define enLow   digitalWrite(PIN_NUMBER, LOW);

uint8_t buf[3];
unsigned int target_angle = 3500;
unsigned int incomingByte[6];
uint8_t id = 0;
const char *device = "/dev/serial0";

int main() {
	
	struct termios options ; //predefined structure
	speed_t myBaud ;	
	int status, fd ;
	myBaud =  B115200;
	if ((fd = open (device, O_RDWR )) == -1)
	// if ((fd = open (device, O_RDWR | O_NOCTTY | O_NDELAY)) == -1)
	return -1 ;
	cfsetispeed (&options, myBaud) ;
	cfsetospeed (&options, myBaud) ;
	usleep (10000) ;	
        // int fd = serialOpen("/dev/serial0", 115200);
	wiringPiSetup();
	pinMode(PIN_NUMBER, OUTPUT);		
	enLow
//int flags;
//flags = fcntl(fd, F_GETFL);
//flags &= ~O_NONBLOCK;
//fcntl(fd, F_SETFL, flags);

        while (1) {
         
                buf[0] = 0x80 + id;                         //command + servoID
                buf[1] = ((target_angle >> 7) & 0x007F);    //POS_H
                buf[2] = (target_angle& 0x007F);            //POS_L
		serialFlush (fd);
                enHigh
                //serialPuts(fd, buf);
		write (fd, buf, strlen (buf)) ;
		delay(0.080*2.5);
		// serialFlush (fd);
		enLow
                while (serialDataAvail(fd)) {
                       for (int n=0; n<6; n++){
                           incomingByte[n] = serialGetchar(fd);
                        }
               }
		//enLow
		//delay(1);
        }
}
