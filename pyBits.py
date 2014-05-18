'''Code to read a switch and light an LED
'''

import RPi.GPIO as GPIO

class TalkToAPi:
	'''Simple code to talk to the low level bits of a Raspberry Pi
	'''
	
	def __init__(self):
		'''constructor 
		'''
		GPIO.setmode(GPIO.BOARD)	
	def getSwitchValue(self):
		'''poll the value of a switch
		
		:returns: True if the switch is pressed, false if the switch is not pressed
		'''
		return True
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
