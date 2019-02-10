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
#include <time.h>

#include "wiringSerial.h"


#define PIN_NUMBER 1
#define enHigh  digitalWrite(PIN_NUMBER, HIGH);
#define enLow   digitalWrite(PIN_NUMBER, LOW);
uint8_t buf[3];
unsigned int target_angle = 3500;
unsigned int incomingByte[6];
uint8_t id = 0;
const char *device = "/dev/serial0";
int flag ;
int ret_byt;


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
	//enLow
//int flags;
//flags = fcntl(fd, F_GETFL);
//flags &= ~O_NONBLOCK;
//fcntl(fd, F_SETFL, flags);

        while (1) {
		
		/** Assing the Variables **/
                buf[0] = 0x80 + id;                         //command + servoID
                buf[1] = ((target_angle >> 7) & 0x007F);    //POS_H
                buf[2] = (target_angle& 0x007F);            //POS_L
		// printf("%d \n %d",sizeof(buf[1]), sizeof(buf[2]));
		
		/** Flush the serial port &&  enable High **/
		serialFlush (fd);
                enHigh
                //serialPuts(fd, buf);
		
		/** write the data && Flush the port && Set the Flag **/
		ret_byt = write (fd, buf, strlen (buf));
		serialFlush (fd);
		
		if(ret_byt == 3){
			flag = 1;
			// printf("%d", ret_byt);
		}
		else {
			flag = 0;
		}
		
		/** see the avail no. of bytes in rx and make enable LOW **/
		int rx_by_ava;
		while (ioctl (fd, FIONREAD, &rx_by_ava ) > 0) {
			if (flag == 1 && tcdrain(fd) == 0) {
				enLow
				flag = 0;
			}
		
		}
		
	
		
		/** Read Serial Data**/
		while (ioctl (fd, FIONREAD, &rx_by_ava ) > 0) {
			for (int n=0; n<6; n++){
			incomingByte[n] = serialGetchar(fd);
			}
		}
		
		
		

		// delay(0.32);
		//serialFlush (fd);
		// enLowc

		//if (tcdrain(fd) != 0)
		//perror("tcdrain error");

		//else
		//write (fd, buf, strlen (buf));


               

	 }
		//tcdrain(fd);
		//tcflush(fd, TCIOFLUSH);

        }



