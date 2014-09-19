#!/usr/bin/env python

'''blinkLEDs.py

Code to blink all of the LEDs on the GVS-Cfg card for a Raspberry Pi Model B Plus.

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
IO4 = 4
IO18 = 18
IO17 = 17
IO27 = 27
IO23 = 23
IO22 = 22
IO24 = 24
IO25 = 25
SPI0_3 = 10
SPI0_4 = 9
SPI0_5 = 11
SPI0_6 = 8
SPI1_6 = 7
IO5 = 5
IO6 = 6
IO12 = 12
IO13 = 13
IO19 = 19
IO16 = 16
IO26 = 26
IO20 = 20
IO21 = 21

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

GPIO.setup(I2C_3, GPIO.OUT)
GPIO.setup(I2C_4, GPIO.OUT)
GPIO.setup(IO4, GPIO.OUT)
GPIO.setup(IO18, GPIO.OUT)
GPIO.setup(IO17, GPIO.OUT)
GPIO.setup(IO27, GPIO.OUT)
GPIO.setup(IO23, GPIO.OUT)
GPIO.setup(IO22, GPIO.OUT)
GPIO.setup(IO24, GPIO.OUT)
GPIO.setup(IO25, GPIO.OUT)
GPIO.setup(SPI0_3, GPIO.OUT)
GPIO.setup(SPI0_4, GPIO.OUT)
GPIO.setup(SPI0_5, GPIO.OUT)
GPIO.setup(SPI0_6, GPIO.OUT)
GPIO.setup(SPI1_6, GPIO.OUT)
GPIO.setup(IO5, GPIO.OUT)
GPIO.setup(IO6, GPIO.OUT)
GPIO.setup(IO12, GPIO.OUT)
GPIO.setup(IO13, GPIO.OUT)
GPIO.setup(IO19, GPIO.OUT)
GPIO.setup(IO16, GPIO.OUT)
GPIO.setup(IO26, GPIO.OUT)
GPIO.setup(IO20, GPIO.OUT)
GPIO.setup(IO21, GPIO.OUT)

# Blink all of the LEDs one at a time forever
# CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

while 1:
	blinkLED(I2C_3)
	blinkLed(I2C_3)
	blinkLed(I2C_4)
	blinkLed(IO4)
	blinkLed(IO18)
	blinkLed(IO17)
	blinkLed(IO27)
	blinkLed(IO23)
	blinkLed(IO22)
	blinkLed(IO24)
	blinkLed(IO25)
	blinkLed(SPI0_3)
	blinkLed(SPI0_4)
	blinkLed(SPI0_5)
	blinkLed(SPI0_6)
	blinkLed(SPI1_6)
	blinkLed(IO5)
	blinkLed(IO6)
	blinkLed(IO12)
	blinkLed(IO13)
	blinkLed(IO19)
	blinkLed(IO16)
	blinkLed(IO26)
	blinkLed(IO20)
	blinkLed(IO21)
