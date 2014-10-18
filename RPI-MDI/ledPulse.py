#!/usr/bin/python

from Adafruit_PWM_Servo_Driver import PWM
import time

# ===========================================================================
# RPI-MDI Code
# ===========================================================================

# Initialise the PWM device using the default address
pwm = PWM(0x40, debug=True)

pwm.setPWMFreq(60)                        # Set frequency to 60 Hz
while (True):
	channel = 0
	duration = 150
	while duration < 600:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.1)
		duration += 10
	channel = 8
	duration = 0
	while duration < 4095:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.1)
		duration += 10
	channel = 9
	duration = 0
	while duration < 4095:
		pwm.setPWM(channel, 0, duration)
		time.sleep(.1)
		duration += 10
