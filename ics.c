#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define PIN_NUMBER 1
#define enHigh  digitalWrite(PIN_NUMBER, HIGH);
#define enLow   digitalWrite(PIN_NUMBER, LOW);

/** Initializing variables globally **/

uint8_t buf[3];
unsigned int target_angle = 7500;
unsigned int incomingByte[6];
uint8_t id = 3;
const char *device = "/dev/serial0";
int flag ;
int ret_byt;
int no_by_avail_rx;

int main() {

	struct termios options ; //predefined structure
	speed_t myBaud ;	 // speed_t is a predefined datatype defined in termios header file
	int status, fd, tx_cmpltd ;
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
		tcdrain(fd);
                enHigh

		/** write the data && delay **/
		ret_byt = write (fd, buf, strlen (buf));
		//delay(3.4);


		/** Set the Flag **/
		if(ret_byt == 3){
			flag = 1;
		}
		else {
			flag = 0;
		}

		/** Wait Untill TX finished **/
		//tx_cmpltd = tcdrain(fd);

		/** Flush the Serial Port **/
		//tcflush(fd, TCIOFLUSH);

		/** see the avail no. of bytes in rx and read 1 byte
		int rx_by_ava;
		while (ioctl (fd, FIONREAD, &rx_by_ava ) > 0) {
			int garbage;
			read(fd, &garbage , 1);
		} **/

		/** Set the Enable Low **/
		enLow

		/**if (tx_cmpltd == 0 && flag == 1) {
			printf("enablwlow");

			flag = 0;
			tx_cmpltd = 2;
		} **/


		/** Read Serial Data **/
		while (ioctl(fd, FIONREAD, &no_by_avail_rx) > 0) {
			for (int n=0; n<6; n++){
			incomingByte[n] = read(fd, &incomingByte, 1);
			no_by_avail_rx = 0;
			}
		}
		
		/** Update the target angle **/
		if(target_angle < 11500) {
			target_angle += 100;
		}
  
		else {
			target_angle = 3500; 
		}

		delay(500); //Milliseconds


        }
}
