#!/usr/bin/env python

'''sw-led.py

Code to read J4 and send it out on J6 on an RPI-MDI board.

This code must be run as Superuser on the Raspberry Pi.

========
Hardware
========

+--------------------+
| J5              J4 |
| J6         D2  D1  |
|  J1     J2     J3  |
+--------------------+


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

J4 = 25
J5 = 4
J6 = 22

GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

# Set all of the pins to outputs
GPIO.setup(J4, GPIO.IN)
GPIO.setup(J5, GPIO.IN)
GPIO.setup(J6, GPIO.OUT)

# Blink all of the LEDs one at a time forever
# CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

while GPIO.input(J5):
	readVal = GPIO.input(J4)
	GPIO.output(J6, not readVal)
