#!/usr/bin/env python

'''pyRPIO-TINY.py

Code to blink all of the LEDs on the RPIO-TINY card for a Raspberry Pi Model B.

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

# Assign all of the GPIO lines (by board pin numbering) to their corresponding jacks 
# on the RPIO-TINY card.

J1 = 2
J2 = 3
J3 = 4
J4 = 17
J5 = 27
J6 = 22
J7 = 19
J8 = 9
J9 = 11
J10 = 14
J11 = 15
J12 = 18
J13 = 23
J14 = 24
J15 = 25
J16 = 8
J17 = 7

OE = 4

def blinkLED(channel):
	'''Function to blink an LED attached to an output channel
	Drives line high for a short time and then drives it low.
	The high level output turns on the LED.
	'''
	GPIO.output(channel, 1)
	time.sleep(0.25)
	GPIO.output(channel, 0)
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

# Set all of the pins to outputs
GPIO.setup(J1, GPIO.OUT)
GPIO.setup(J2, GPIO.OUT)
GPIO.setup(J3, GPIO.OUT)
GPIO.setup(J4, GPIO.OUT)
GPIO.setup(J5, GPIO.OUT)
GPIO.setup(J6, GPIO.OUT)
GPIO.setup(J7, GPIO.OUT)
GPIO.setup(J8, GPIO.OUT)
GPIO.setup(J9, GPIO.OUT)
GPIO.setup(J10, GPIO.OUT)
GPIO.setup(J11, GPIO.OUT)
GPIO.setup(J12, GPIO.OUT)
GPIO.setup(J13, GPIO.OUT)
GPIO.setup(J14, GPIO.OUT)
GPIO.setup(J15, GPIO.OUT)
GPIO.setup(J16, GPIO.OUT)
GPIO.setup(J17, GPIO.OUT)

# Blink all of the LEDs one at a time forever
# CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

while 1:
	blinkLED(J1)
	blinkLED(J2)
	blinkLED(J3)
	blinkLED(J4)
	blinkLED(J5)
	blinkLED(J6)
	blinkLED(J7)
	blinkLED(J8)
	blinkLED(J9)
	blinkLED(J10)
	blinkLED(J11)
	blinkLED(J12)
	blinkLED(J13)
	blinkLED(J14)
	blinkLED(J15)
	blinkLED(J16)
	blinkLED(J17)
