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

uint8_t buf[3];
unsigned int target_angle = 3500;
unsigned int incomingByte[6];

int setPos(speed_t baud, int pos){
	
