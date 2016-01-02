#!/usr/bin/env python

'''led1-RPPPSOC.py

Code to blink LED on the RPP-UIO-16 card for a Raspberry Pi Model B Plus.

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
# on the GVS card.

I2C_3 = 2
I2C_4 = 3
UART_3 = 14
UART_4 = 15
SPI0_3 = 10
SPI0_4 = 9
SPI0_5 = 11
SPI0_6 = 8
SPI1_6 = 7
IO4 = 4
IO5 = 5
IO6 = 6
IO12 = 12
IO13 = 13
IO16 = 16
IO17 = 17
IO18 = 18
IO19 = 19
IO20 = 20
IO21 = 21
IO22 = 22
IO23 = 23
IO24 = 24
IO25 = 25
IO26 = 26
IO27 = 27

def blinkLED(channel):
	'''Function to blink an LED attached to an output channel
	Drives line high for a short time and then drives it low.
	The high level output turns on the LED.
	'''
	GPIO.output(channel, 1)
	time.sleep(0.5)
	GPIO.output(channel, 0)
	time.sleep(0.5)
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

# Set all of the pins to outputs

GPIO.setup(IO18, GPIO.OUT)
GPIO.setup(IO17, GPIO.OUT)
GPIO.setup(IO27, GPIO.OUT)
GPIO.setup(IO22, GPIO.OUT)
GPIO.setup(IO23, GPIO.OUT)
GPIO.setup(IO24, GPIO.OUT)
GPIO.setup(IO25, GPIO.OUT)
GPIO.setup(IO5, GPIO.OUT)
GPIO.output(IO18, 0)
GPIO.output(IO17, 0)
GPIO.output(IO27, 0)
GPIO.output(IO22, 0)
GPIO.output(IO23, 0)
GPIO.output(IO24, 0)
GPIO.output(IO25, 0)
GPIO.output(IO5, 0)

# Blink all of the LEDs one at a time forever
# CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

while 1:
	blinkLED(IO18)
	blinkLED(IO17)
	blinkLED(IO27)
	blinkLED(IO22)
	blinkLED(IO23)
	blinkLED(IO24)
	blinkLED(IO25)
	blinkLED(IO5)
