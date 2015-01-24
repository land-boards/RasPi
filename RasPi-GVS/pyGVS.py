#!/usr/bin/env python

'''pyGVS.py

Code to blink all of the LEDs on the GVS card for a Raspberry Pi Model B.

This code must be run as Superuser on the Raspberry Pi.

GPIO_4 is the output enable for the 3.3V<>5V voltage translators.
GPIO_4 needs to be set high for the voltage translators to turn on.

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
# on the GVS card.

J1_3 = 2
J1_4 = 3
J2_3 = 14
J2_4 = 15
J3 = 18
J4 = 17
J5 = 27
J6 = 23
J7 = 22
J8 = 24
J9 = 25
J10_3 = 10
J10_4 = 9
J10_5 = 11
J10_6 = 8
J11_6 = 7

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
GPIO.setup(J3, GPIO.OUT)
GPIO.setup(J4, GPIO.OUT)
GPIO.setup(J5, GPIO.OUT)
GPIO.setup(J6, GPIO.OUT)
GPIO.setup(J7, GPIO.OUT)
GPIO.setup(J8, GPIO.OUT)
GPIO.setup(J9, GPIO.OUT)
GPIO.setup(J11_6, GPIO.OUT)
GPIO.setup(J1_3, GPIO.OUT)
GPIO.setup(J1_4, GPIO.OUT)
GPIO.setup(J2_3, GPIO.OUT)
GPIO.setup(J2_4, GPIO.OUT)
GPIO.setup(J10_3, GPIO.OUT)
GPIO.setup(J10_4, GPIO.OUT)
GPIO.setup(J10_5, GPIO.OUT)
GPIO.setup(J10_6, GPIO.OUT)
GPIO.setup(OE, GPIO.OUT)

# After setting the channels to all be outputs, enable the voltage translators
GPIO.output(OE, 1)

# Blink all of the LEDs one at a time forever
# CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

while 1:
	blinkLED(J1_3)
	blinkLED(J1_4)
	blinkLED(J2_3)
	blinkLED(J2_4)
	blinkLED(J3)
	blinkLED(J4)
	blinkLED(J5)
	blinkLED(J6)
	blinkLED(J7)
	blinkLED(J8)
	blinkLED(J9)
	blinkLED(J10_3)
	blinkLED(J11_6)
	blinkLED(J10_4)
	blinkLED(J10_5)
	blinkLED(J10_6)
