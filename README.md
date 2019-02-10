
#### Compilation
`gcc -o uart_rpi3_loopback uart_rpi3_loopback.c -lwiringPi`

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
* [Blocking POSIX (tcdrain)](https://linux.die.net/man/3/tcdrain)
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


=======

