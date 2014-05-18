'''Code to read a switch and light an LED.
Based on code found at http://makezine.com/projects/tutorial-raspberry-pi-gpio-pins-and-python/
This code must be run as Superuser on the Raspberry Pi.
'''

import RPi.GPIO as GPIO

class TalkToAPi:
	'''Simple code to talk to the low level bits of a Raspberry Pi
	'''
	
	def __init__(self):
		'''constructor 
		'''
		GPIO.setmode(GPIO.BOARD)	# setup GPIO using Board numbering
		GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)
		GPIO.setup(23, GPIO.OUT)

	def getSwitchValue(self):
		'''poll the value of a switch
		
		:returns: True if the switch is pressed, false if the switch is not pressed
		'''
		if(GPIO.input(24) == 0):
			print 'getSwitchValue: Button pressed'
			return True
		else:
			print 'getSwitchValue: Button is not pressed'
			return False
			
	def controlLED(self, ledState):
		'''turns off or on a LED

		:param ledState: True to turn the light on, false to turn light off
		'''
		ledVal = ledState
		return
		
	def getGPIOLibVersion(self):
		'''Returns the GPIO library version that is being used.
		
		:returns: GPIO library version as a string
		'''
		return GPIO.VERSION
		
	def stopUsingRPi:
		'''Free up the Raspbetty Pi pins when you are done using them
		'''
		GPIO.cleanup()
