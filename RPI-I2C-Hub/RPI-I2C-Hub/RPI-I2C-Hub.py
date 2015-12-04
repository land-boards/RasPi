#!/usr/bin/python
"""
====
NAME
====

RPI-I2C-Hub.py - RPI-I2C-HUB example code 

========
SYNOPSIS
========

sudo python RPI-I2C-Hub.py

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
import smbus
import time

bus = smbus.SMBus(1) # Rev 2 Pi uses 1

MCP23017 = 0x20 # Device address (A0-A2)
IODIRA   = 0x00 # Pin direction register
IODIRB   = 0x01 # Pin direction register
OLATA    = 0x14 # Register for outputs
OLATB    = 0x15 # Register for outputs
GPIOA    = 0x12 # Register for inputs
GPIOB    = 0x13 # Register for inputs

PCA9544 = 0x71
SELCH0 = 0X04
SELCH1 = 0X05
SELCH2 = 0X06
SELCH3 = 0X07

def setup():
	"""setup code
	"""
	bus.write_byte_data(PCA9544,SELCH0,SELCH0)
	# Set all GPA pins as outputs by setting
	# all bits of IODIRA register to 0
	bus.write_byte_data(MCP23017,IODIRA,0x00)
	bus.write_byte_data(MCP23017,IODIRB,0x00)
	# Set output all 16 output bits to 0
	bus.write_byte_data(MCP23017,OLATA,0)
	bus.write_byte_data(MCP23017,OLATB,0)

	bus.write_byte_data(PCA9544,SELCH1,SELCH1)
	# Set all GPA pins as outputs by setting
	# all bits of IODIRA register to 0
	bus.write_byte_data(MCP23017,IODIRA,0x00)
	bus.write_byte_data(MCP23017,IODIRB,0x00)
	# Set output all 16 output bits to 0
	bus.write_byte_data(MCP23017,OLATA,0)
	bus.write_byte_data(MCP23017,OLATB,0)

def loop():
	"""loop code
	"""
	while True:
		bus.write_byte_data(PCA9544,SELCH0,SELCH0)
		bus.write_byte_data(MCP23017,OLATA,1)
		time.sleep(1)
		bus.write_byte_data(MCP23017,OLATA,0)

		bus.write_byte_data(PCA9544,SELCH1,SELCH1)
		bus.write_byte_data(MCP23017,OLATA,1)
		time.sleep(1)
		bus.write_byte_data(MCP23017,OLATA,0)

if __name__ == '__main__':
	setup()
	loop()
	