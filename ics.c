#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define PIN_NUMBER 1
#define enHigh  digitalWrite(PIN_NUMBER, HIGH);
#define enLow   digitalWrite(PIN_NUMBER, LOW);

/** Initializing variables globally **/

uint8_t buf[3];
unsigned int target_angle = 3500;
unsigned int incomingByte[6];
uint8_t id = 0;
const char *device = "/dev/serial0";
int flag ;
int ret_byt;

int main() {
	
	struct termios options ; //predefined structure
	speed_t myBaud ;	 // speed_t is a predefined datatype defined in termios header file
	int status, fd ;
	myBaud =  B115200;
	if ((fd = open (device, O_RDWR )) == -1) //checking if serial port is available for Rx/Tx
	return -1 ;
	cfsetispeed (&options, myBaud) ; //POSIX command for setting
	cfsetospeed (&options, myBaud) ;
	usleep (10000) ;	
	wiringPiSetup();
	pinMode(PIN_NUMBER, OUTPUT);		

/** Clearing the non blocking i/o flag. >>>>>IMPORTANT<<<< Transmitted data looks cleaner**/

	int flags;
	flags = fcntl(fd, F_GETFL);
	flags &= ~O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);

        while (1) {
		/** Assigning the Variables **/
                buf[0] = 0x80 + id;                         //command + servoID
                buf[1] = ((target_angle >> 7) & 0x007F);    //POS_H
                buf[2] = (target_angle& 0x007F);            //POS_L
	
		/** Flush the serial port &&  enable High **/
		serialFlush (fd);
                enHigh
               
		/** write the data && delay **/
		ret_byt = write (fd, buf, strlen (buf));
		delay(3.2);
		
	
		if(ret_byt ==3){ 
			flag = 1;
		
		serialFlush (fd);
				}
				
                while (serialDataAvail(fd)) 
		{
                       for (int n=0; n<6; n++){
                           incomingByte[n] = serialGetchar(fd);
						}
               }
	       
		if (flag ==1) { 
		enLow 
		
		flag = 0;
				}	
		
		tcdrain(fd);
		tcflush(fd, TCIOFLUSH);
			
        }
}
