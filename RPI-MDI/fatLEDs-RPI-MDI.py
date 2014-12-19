#!/usr/bin/python

from Adafruit_PWM_Servo_Driver import PWM
import time
import RPi.GPIO as GPIO

# ===========================================================================
# fatRPI-MDI Code
# ===========================================================================

def blinkLED(channel):
	'''Function to blink an LED attached to an output channel
	Drives line high for a short time and then drives it low.
	The high level output turns on the LED.
	'''
	GPIO.output(channel, 1)
	time.sleep(0.5)
	GPIO.output(channel, 0)

J4 = 25
J5 = 4
J6 = 22

GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

GPIO.setup(J4, GPIO.OUT)
GPIO.setup(J5, GPIO.OUT)
GPIO.setup(J6, GPIO.OUT)

# Initialise the PWM device using the default address
pwm = PWM(0x40, debug=False)

pwm.setPWMFreq(60)                        # Set frequency to 60 Hz

pwm.setPWM(0, 0, 0)
pwm.setPWM(6, 0, 0)
pwm.setPWM(7, 0, 0)
pwm.setPWM(8, 0, 4095)
pwm.setPWM(9, 0, 4095)

def blinkPWM(channel):
	pwm.setPWM(channel, 0, 4095)
	time.sleep(0.5)
	pwm.setPWM(channel, 0, 0)

def blinkPWMH(channel):
	pwm.setPWM(channel, 0, 0)
	time.sleep(0.5)
	pwm.setPWM(channel, 0, 4095)

while (True):
	blinkPWM(0)
	blinkPWM(6)
	blinkPWM(7)
	blinkPWMH(8)
	blinkPWMH(9)
	blinkLED(J4)
	blinkLED(J5)
	blinkLED(J6)
