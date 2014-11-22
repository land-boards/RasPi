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
	time.sleep(0.25)
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
while (True):
	channel = 0
	duration = 150
	while duration < 600:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.1)
		duration += 10
	channel = 6
	duration = 150
	while duration < 600:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.1)
		duration += 10
	channel = 7
	duration = 150
	while duration < 600:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.1)
		duration += 10
	channel = 8
	duration = 5
	while duration < 4096:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.01)
		duration += 10
	channel = 9
	duration = 5
	while duration < 4096:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.01)
		duration += 10
	blinkLED(J4)
	blinkLED(J5)
	blinkLED(J6)
