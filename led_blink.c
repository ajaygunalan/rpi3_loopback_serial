#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>

#define PIN_NUMBER 1
#define enHigh  digitalWrite(PIN_NUMBER, HIGH);
#define enLow   digitalWrite(PIN_NUMBER, LOW);


int main(void)
{
    wiringPiSetup();
    pinMode(PIN_NUMBER, OUTPUT);
 
    for (;;)
    {
        enHigh; 
        delay(1000); 
        enLow;
        delay(1000);
    }
    return 0;
}
