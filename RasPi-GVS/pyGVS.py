#!/usr/bin/env python

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

J3 = 18
J4 = 17
J5 = 27
J6 = 23
J7 = 22
J8 = 24
J9 = 25
J2_3 = 2
J2_4 = 3
J10_3 = 10
J10_4 = 9
J10_5 = 11
J10_6 = 8
J11_6 = 7

OE = 4

def blinkLED(channel):
	GPIO.output(channel, 1)
	time.sleep(0.5)
	GPIO.output(channel, 0)
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering
GPIO.setup(J3, GPIO.OUT)
GPIO.setup(J4, GPIO.OUT)
GPIO.setup(J5, GPIO.OUT)
GPIO.setup(J6, GPIO.OUT)
GPIO.setup(J7, GPIO.OUT)
GPIO.setup(J8, GPIO.OUT)
GPIO.setup(J9, GPIO.OUT)
GPIO.setup(OE, GPIO.OUT)
GPIO.setup(J2_3, GPIO.OUT)
GPIO.setup(J2_4, GPIO.OUT)
GPIO.setup(J10_3, GPIO.OUT)
GPIO.setup(J10_4, GPIO.OUT)
GPIO.setup(J10_5, GPIO.OUT)
GPIO.setup(J10_6, GPIO.OUT)
GPIO.setup(J11_6, GPIO.OUT)
GPIO.output(OE, 1)

while 1:
	blinkLED(J3)
	blinkLED(J4)
	blinkLED(J5)
	blinkLED(J6)
	blinkLED(J7)
	blinkLED(J8)
	blinkLED(J9)
	blinkLED(J2_3)
	blinkLED(J2_4)
	blinkLED(J10_3)
	blinkLED(J10_4)
	blinkLED(J10_5)
	blinkLED(J10_6)
	blinkLED(J11_6)
