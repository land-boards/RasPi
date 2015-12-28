#!/usr/bin/python
"""
====
NAME
====

R-Hub-Intr-4x8.py - RPI-I2C-HUB example code 

========
SYNOPSIS
========

sudo python R-Hub-Intr-4x8.py

===========
DESCRIPTION
===========

Used to demonstrate the operation of the Raspberry Pi I2C hub card.

===========
ENVIRONMENT
===========

* Run under Raspbian
* Uses a Raspberry Pi
* Uses a RPI-I2C-HUB card
* Uses (4) I2CIO-8 cards 

====
BUGS
====

None known.

======
AUTHOR
======

Doug Gilliland
"""

import smbus	# I2C library
import time		# used for sleep function
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering

bus = smbus.SMBus(1) # Rev 2 Pi uses 1

MCP23008 = 0x20 # Slave device address base
IODIR    = 0x00 # Pin direction register
IPOL     = 0x01 # 
GPINTEN  = 0x02 # 
INTCON   = 0x04 # 
IOCON    = 0x05 # 
GPPU     = 0x06 # 
INTF     = 0x07 # 
INTCAP   = 0x08 # 
GPIOMCP  = 0x09 # Register for inputs
OLAT     = 0x0a # Register for outputs

INTPOLACTHI = 0x02
INTPOLACTLO = 0x00
INTLINE = 17

PCA9544 = 0x71	# Mux address
SELCH0 = 0X04	# Select mux channel #0
SELCH1 = 0X05	# Select mux channel #1
SELCH2 = 0X06	# Select mux channel #2
SELCH3 = 0X07	# Select mux channel #3

def bounceOne():
	bus.write_byte_data(MCP23008,OLAT,1)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23008,OLAT,2)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23008,OLAT,4)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23008,OLAT,8)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23008,OLAT,0)	# turn off LED

def initI2CIO8():
	bus.write_byte_data(MCP23008,IODIR,0xf0)		# Set I/O direction control
	bus.write_byte_data(MCP23008,IOCON,INTPOLACTLO)	# Set interrupt polarity to high 
	bus.write_byte_data(MCP23008,IPOL,0xf0)			# Set input polarity to invert
	bus.write_byte_data(MCP23008,GPINTEN,0xf0)		# Enable Interrupts on all inputs 
	bus.write_byte_data(MCP23008,OLAT,0)			# Write out all 0s
	GPIO.setup(INTLINE, GPIO.IN)
	
def setup():
	"""setup code
	"""
	bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
	initI2CIO8()

	bus.write_byte_data(PCA9544,SELCH1,SELCH1)	# Select I2C bus #1
	initI2CIO8()

	bus.write_byte_data(PCA9544,SELCH2,SELCH2)	# Select I2C bus #2
	initI2CIO8()

	bus.write_byte_data(PCA9544,SELCH3,SELCH3)	# Select I2C bus #3
	initI2CIO8()

def loop():
	"""loop code
	"""
	while True:
		bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
		bounceOne()

		bus.write_byte_data(PCA9544,SELCH1,SELCH1)
		bounceOne()
		
		bus.write_byte_data(PCA9544,SELCH2,SELCH2)
		bounceOne()
		
		bus.write_byte_data(PCA9544,SELCH3,SELCH3)
		bounceOne()
		
		if GPIO.input(INTLINE) == 0:
			time.sleep(0.005)
			chInt = bus.read_byte_data(PCA9544,0) >> 4
			print 'Input changed on channel ',chInt,
			if chInt == 1:
				bus.write_byte_data(PCA9544,SELCH0,SELCH0)
				value =  bus.read_byte_data(MCP23008,GPIOMCP) >> 4
				print 'value =', value
			if chInt == 2:
				bus.write_byte_data(PCA9544,SELCH1,SELCH1)
				value =  bus.read_byte_data(MCP23008,GPIOMCP) >> 4
				print 'value =', value
			if chInt == 4:
				bus.write_byte_data(PCA9544,SELCH2,SELCH2)
				value =  bus.read_byte_data(MCP23008,GPIOMCP) >> 4
				print 'value =', value
			if chInt == 8:
				bus.write_byte_data(PCA9544,SELCH3,SELCH3)
				value =  bus.read_byte_data(MCP23008,GPIOMCP) >> 4
				print 'value =', value

if __name__ == '__main__':
	setup()
	loop()
	