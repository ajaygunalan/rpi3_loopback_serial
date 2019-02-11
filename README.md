
#### Compilation
`gcc -o uart_rpi3_loopback uart_rpi3_loopback.c -lwiringPi`

oscilloscope `800 microseconds`

### Blocking

1. [stack](https://stackoverflow.com/questions/42449987/is-the-write-function-in-c-blocking-or-non-blocking)
2. [blog](https://eklitzke.org/blocking-io-nonblocking-io-and-epoll)
3. [a](http://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html)

#### Question?
1. Why the fuck its not working with two while loop
2. How to get rid of garbage value?

Make sure UART is **configured** in RPI3, use [this](https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c) as reference. 

#### Reference
* [PiPinOut](https://www.google.com/search?q=gpio+rpi3+pinout&tbm=isch&source=iu&ictx=1&fir=uzJLoQO8mMNq7M%253A%252CO7iK81du5nUBUM%252C_&usg=AI4_-kT1FivXi9CX71rcYsEdYpg8QoGwvw&sa=X&ved=2ahUKEwiUy67JoangAhVLtI8KHQVkCLQQ9QEwAnoECAUQCA#imgrc=uzJLoQO8mMNq7M:)
* [wiringPi_Pinout](http://wiringpi.com/pins/)
* [WiringPi](http://wiringpi.com/reference/serial-library/)
* [Electronics_wing](https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c)
* [Odroid](https://wiki.odroid.com/odroid-xu4/application_note/gpio/wiringpi)
* [SerialTest](https://github.com/WiringPi/WiringPi/blob/master/examples/serialTest.c)
* [Minicom](https://medium.com/@amitasinghchauhan/serial-port-debugging-101-loopback-test-4a7e40da9055)
* [GitHub Discussion] (https://github.com/ARMmbed/mbed-os/issues/1849, https://github.com/ARMmbed/mbed-os/pull/1801)
* [open function] (http://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html)
* [Control modes in UART used in WiringPi library](http://www.delorie.com/gnu/docs/glibc/libc_364.html)
* [Reference for setting input & output baud rate](http://www.delorie.com/gnu/docs/glibc/libc_366.html)
* [Blocking POSIX (tcdrain)](https://linux.die.net/man/3/tcdrain, https://www.linuxquestions.org/questions/programming-9/serial-port-write-wait-for-transmission-complete-with-the-function-tcdrain-4175502564/)
* [posix serial](https://github.com/cbrake/linux-serial-test/blob/master/linux-serial-test.c)

#### Packages to be installed: 

1. Use minicom to test if Tx --> Rx communication is established or not.

Install minicom: `sudo apt-get install minicom`

If java packages are missing when installing minicom, install them using the following commands: 

```

sudo apt-get purge openjdk-8-jre-headless
sudo apt-get install openjdk-8-jre-headless
sudo apt-get install openjdk-8-jre

```

Test if a communication line is working by using:

`sudo minicom -D /dev/ttySo`
 

`ls -l /dev | grep `

#### Compiling and running 

Compile: gcc -o test test.c -lwiringPi
Run: ./test

#### 8/02/2019 Progress

On running ics.c, the enable pin is high briefly but turns low immediately, not waiting for the data transmission to complete. 
Need to clear the non blocking io flag.

Created two new files ics_new.c and stoch_kondo.c. stoch_kondo.c is the final library that aims to replace wiringPi completely. 
I am replacing all the functions in ics_new.c for the ease of testing. Once verified to work properly, the functions are placed in stoch_kondo.c 

Tried replacing the wiringPi library in the ics.c with all posix commands. Too many errors to handle when using this approach. 
In the end only the open and write functions were incorporated in ics.c 

Increasing the delay in the code to match enable signal with tx line worked. However, it is not dynamic to adapt to transfer any number of bits
Since the number of bits transmitted in all commands (setPos,getPos,set Curlim etc.), this approach is assumed to work for our purpose
The delay time to be used in the code is measured by plotting the channels from an Arduino whose code is perfect and has no errors.


#### 10/02/2019 Noon: 

IMPORTANT: Added tcdrain(fd) and tcflush(fd) to ics.c and each time the tx pin is high, enable pin goes high. 
However, enable pin becomes low even during data transmission (i.e, when 0 is transmitted).

#### Documentation on tcdrain() and tcflush():

[Forum on flushing unused data](https://stackoverflow.com/questions/10938882/how-can-i-flush-unread-data-from-a-tty-input-queue-on-a-unix-system)

1. The use of POSIX function tcflush() is to flush all data there in the object referred by fd, but not transmitted. 
Usage: `int tcflush(int fildes, int queue_selector);`

2. Types of queue_selectors are as follows: 

	a) TCIFLUSH, it shall flush data received but not read.
	b) TCOFLUSH, it shall flush data written but not transmitted
	c) TCIOFLUSH, it shall flush both data received but not read and data written but not transmitted.
	
[IBM support page on waiting until o/p is transmitted](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rttcd.htm)

Summary: 

tcdrain() waits till all output sent to fd is actually sent to through the port mentioned by fd
If successful, tcdrain() will return 0. Else, it returns -1.
There is an example for usage availble. 

[QNX documentation on tcdrain](http://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/t/tcdrain.html)
x
Similar to previous link. Smaller example code for the usage. 
