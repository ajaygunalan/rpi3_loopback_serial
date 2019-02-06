/*
	UART communication on Raspberry Pi using C (WiringPi Library)
	http://www.electronicwings.com
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int serial_port ;
  char dat;
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(1){

		printf("Serial Input> ");
		scanf("%c", &dat);
		serialPutchar(serial_port, dat);
		delay(3);
		//dat = serialGetchar (serial_port);
		printf ("Serial Output> %c", dat);
		if(serialDataAvail(serial_port))
			putchar(serialGetchar(serial_port));
		fflush (stdout) ;
		//serialPutchar(serial_port, dat);
		// }
	}
}


