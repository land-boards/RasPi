#!/usr/bin/env python

'''fastTest-RPT2.py

Code to test a RPIO-TINY-2 card.

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
	
def testPair(ch1,ch2):
	'''Function to test I/O Pair.
	Sets one pin to be an output and the other pin to be an input. 
	Set the output high and check the input matches.
	Set the output low and check the output matches.
	Then switch the input/output channels and repeat.
	'''
	GPIO.setup(ch1, GPIO.OUT)
	GPIO.setup(ch2, GPIO.IN)
	GPIO.output(ch1, 1)
	time.sleep(0.01)
	if GPIO.input(ch2) != 1:
		print 'Error reading high on channels', ch1, ch2
		return False
	GPIO.output(ch1, 0)
	time.sleep(0.01)
	if GPIO.input(ch2) != 0:
		print 'Error reading low on channels', ch1, ch2
		return False
	GPIO.setup(ch1, GPIO.IN)
	# 
	GPIO.setup(ch2, GPIO.OUT)
	GPIO.setup(ch1, GPIO.IN)
	GPIO.output(ch2, 1)
	time.sleep(0.01)
	if GPIO.input(ch1) != 1:
		print 'Error reading high on channels', ch1, ch2
		return False
	GPIO.output(ch2, 0)
	time.sleep(0.01)
	if GPIO.input(ch1) != 0:
		print 'Error reading low on channels', ch1, ch2
		return False
	GPIO.setup(ch2, GPIO.IN)
	return True
	
def daisyTests():
	if testPair(I2C_3,I2C_4) == False:
		print 'Test failed'
		return False
	if testPair(UART_3,UART_4) == False:
		print 'Test failed'
		return False
	if testPair(SPI0_3,SPI0_4) == False:
		print 'Test failed'
		return False
	if testPair(SPI0_5,SPI0_6) == False:
		print 'Test failed'
		return False
	return True
	
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

# Set all of the pins to outputs

GPIO.setup(IO4, GPIO.OUT)
GPIO.setup(IO18, GPIO.OUT)
GPIO.setup(IO17, GPIO.OUT)
GPIO.setup(IO27, GPIO.OUT)
GPIO.setup(IO23, GPIO.OUT)
GPIO.setup(IO22, GPIO.OUT)
GPIO.setup(IO24, GPIO.OUT)
GPIO.setup(IO25, GPIO.OUT)
GPIO.setup(SPI1_6, GPIO.OUT)

# CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

print 'Daisy chain connectors on I2C, UART and SP0'
print 'LEDs on 5V outputs and SP1'

while 1:
	if daisyTests() == True:
		print 'Daisy test passed'
	else:
		print 'Daisy test failed'
		break;
	blinkLED(IO4)
	blinkLED(IO18)
	blinkLED(IO17)
	blinkLED(IO27)
	blinkLED(IO22)
	blinkLED(IO23)
	blinkLED(IO24)
	blinkLED(IO25)
	blinkLED(SPI1_6)
