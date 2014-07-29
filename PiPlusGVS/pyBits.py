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

LED_PIN = 5

GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, 1)
