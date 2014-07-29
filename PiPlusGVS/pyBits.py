'''Code to blink LEDs.

This code must be run as Superuser on the Raspberry Pi.

============
Dependencies
============

Need to: 

* sudo apt-get install python-dev
* sudo apt-get install python-pip python2.7-dev
* sudo apt-get install python-rpi.gpio
* sudo pip install flask

====
Code
====
'''

import RPi.GPIO as GPIO
import os
import time

J12 = 5
J13 = 6
J14 = 13

def blinkLED(channel):
	GPIO.output(channel, 0)
	time.sleep(0.1)
	GPIO.output(channel, 1)
	time.sleep(0.1)
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering
GPIO.setup(LED_PIN, GPIO.OUT)

while 1:
	blinkLED(J12)
	blinkLED(J13)

