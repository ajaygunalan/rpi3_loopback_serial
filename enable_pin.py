#!/usr/bin/env python
 
import wiringpi as wpi
import time

enPin = 1
 
wpi.wiringPiSetup()
wpi.pinMode(enPin, 1)
 
while True:
    wpi.digitalWrite(enPin, 1)
    time.sleep(0.01)
    wpi.digitalWrite(enPin, 0)
    time.sleep(0.01)
