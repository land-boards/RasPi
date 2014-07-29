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
J15 = 19
J16 = 26
J17 = 21
J18 = 12
J19 = 18
J20 = 20

def blinkLED(channel):
	GPIO.output(channel, 1)
	time.sleep(0.25)
	GPIO.output(channel, 0)
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering
GPIO.setup(J12, GPIO.OUT)
GPIO.setup(J13, GPIO.OUT)
GPIO.setup(J14, GPIO.OUT)
GPIO.setup(J15, GPIO.OUT)
GPIO.setup(J16, GPIO.OUT)
GPIO.setup(J17, GPIO.OUT)
GPIO.setup(J18, GPIO.OUT)
GPIO.setup(J19, GPIO.OUT)
GPIO.setup(J20, GPIO.OUT)

while 1:
	blinkLED(J12)
	blinkLED(J13)
	blinkLED(J14)
	blinkLED(J15)
	blinkLED(J16)
	blinkLED(J17)
	blinkLED(J18)
	blinkLED(J19)
	blinkLED(J20)
