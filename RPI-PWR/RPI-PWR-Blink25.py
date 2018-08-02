import RPi.GPIO as GPIO
import os
import time

def blinkLED(channel):
	GPIO.output(channel,1)
	time.sleep(1)
	GPIO.output(channel,0)
	time.sleep(1)

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)

while 1:
	blinkLED(25)
