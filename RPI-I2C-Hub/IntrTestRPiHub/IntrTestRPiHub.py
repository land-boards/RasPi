#!/usr/bin/python
"""
====
NAME
====

IntrTestRPiHub.py - RPI-I2C-HUB Interrupt test code 

========
SYNOPSIS
========

sudo python IntrTestRPiHub.py

===========
DESCRIPTION
===========

Used to demonstrate the interrupt operation of the Raspberry Pi I2C hub card.

===========
ENVIRONMENT
===========

* Run under Raspbian
* Uses a Raspberry Pi
* Uses a RPI-I2C-HUB card
* Uses a I2CIO-8 card

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
GPIO     = 0x09 # Register for inputs
OLAT     = 0x0a # Register for outputs

INTPOLACTHI = 0x02
INTLINE = 17

PCA9544 = 0x71	# Mux address
SELCH0 = 0X04	# Select mux channel #0
SELCH1 = 0X05	# Select mux channel #1
SELCH2 = 0X06	# Select mux channel #2
SELCH3 = 0X07	# Select mux channel #3

def setup():
	"""setup code
	"""
	bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
	bus.write_byte_data(MCP23008,IODIR,0xf0)		# Set I/O direction control
	bus.write_byte_data(MCP23008,IOCON,INTPOLACTHI)	# Set interrupt polarity to high 
	bus.write_byte_data(MCP23008,IPOL,0xf0)			# Set input polarity to invert
	bus.write_byte_data(MCP23008,GPINTEN,0xf0)		# Enable Interrupts on all inputs 
	bus.write_byte_data(MCP23008,OLAT,0)			# Write out all 0s
	GPIO.setup(INTLINE, INPUT)
	
def loop():
	"""loop code
	"""
	while True:
		print 'int',GPIO.input(INTLINE)
		value =  bus.read_byte_data(MCP23008,GPIO) >> 4
		print 'value =', value
		bus.write_byte_data(MCP23008,OLAT,value)
		delay(0.5)

if __name__ == '__main__':
	setup()
	loop()
	