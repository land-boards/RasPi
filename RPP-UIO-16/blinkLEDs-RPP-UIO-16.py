#!/usr/bin/env python

'''blinkLEDs-RPP-UIO-16.py

Code to blink all of the LEDs on the RPP-UIO-16 card for a Raspberry Pi Model B Plus.

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
	time.sleep(0.25)
	GPIO.output(channel, 0)
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

# Set all of the pins to outputs

GPIO.setup(I2C_3, GPIO.OUT)
GPIO.setup(I2C_4, GPIO.OUT)
GPIO.setup(UART_3, GPIO.OUT)
GPIO.setup(UART_4, GPIO.OUT)
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
	blinkLED(I2C_4)
	blinkLED(UART_3)
	blinkLED(UART_4)
	blinkLED(SPI0_3)
	blinkLED(SPI0_4)
	blinkLED(SPI0_5)
	blinkLED(SPI0_6)
	blinkLED(SPI1_6)
	blinkLED(IO4)
	blinkLED(IO18)
	blinkLED(IO17)
	blinkLED(IO27)
	blinkLED(IO23)
	blinkLED(IO22)
	blinkLED(IO24)
	blinkLED(IO25)
	blinkLED(IO5)
	blinkLED(IO6)
	blinkLED(IO12)
	blinkLED(IO13)
	blinkLED(IO19)
	blinkLED(IO16)
	blinkLED(IO26)
	blinkLED(IO20)
	blinkLED(IO21)
