
#### Compilation
`gcc -o uart_rpi3_loopback uart_rpi3_loopback.c -lwiringPi`

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


=======

