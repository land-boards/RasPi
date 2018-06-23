#!/usr/bin/python
"""
====
NAME
====

RasPiDigio128.py - Raspberry Pi Digio128 example code 

========
SYNOPSIS
========

sudo python RasPiDigio128.py

===========
DESCRIPTION
===========

Used to demonstrate the operation of the DIGIO-128 card on the Raspberry Pi.

===========
ENVIRONMENT
===========

* Run under Raspbian
* Uses a Raspberry Pi
* Uses a RPI-I2C-HUB card
* Uses a DIGIO-128 card
* http://land-boards.com/blwiki/index.php?title=DIGIO-128#DIGIO-128_on_Raspberry_Pi_Checkout

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

MCP23017 = 0x20 # Slave device address base
IODIRA   = 0x00 # Pin direction register
IODIRB   = 0x01 # Pin direction register
IPOLA    = 0x02 # 
IPOLB    = 0x03 # 
GPINTENA = 0x04 # 
GPINTENB = 0x05 # 
INTCONA  = 0x08 # 
INTCONB  = 0x09 # 
IOCON    = 0x0A # 
GPPUA    = 0x0C # 
GPPUB    = 0x0D # 
INTFA    = 0x0E # 
INTFB    = 0x0F # 
INTCAPA  = 0x10 # 
INTCAPB  = 0x11 # 
GPIOA    = 0x12 # Inputs
GPIOB    = 0x13 # Inputs
OLATA    = 0x14 # Register for outputs
OLATB    = 0x15 # Register for outputs

INTPOLACTHI = 0x02
INTPOLACTLO = 0x00
INTLINE = 17

PCA9544 = 0x71	# Mux address
SELCH0 = 0X04	# Select mux channel #0
SELCH1 = 0X05	# Select mux channel #1
SELCH2 = 0X06	# Select mux channel #2
SELCH3 = 0X07	# Select mux channel #3

def bounceOne():
	bus.write_byte_data(MCP23017,OLATA,1)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23017,OLATA,0)	# turn off LED
	time.sleep(0.2)							# wait 1 sec

def initMCP23017():
	bus.write_byte_data(MCP23017,IODIRA,0xf0)		# Set I/O direction control
	bus.write_byte_data(MCP23017,IOCON,INTPOLACTLO)	# Set interrupt polarity to low 
	bus.write_byte_data(MCP23017,IPOLA,0xf0)			# Set input polarity to invert
	bus.write_byte_data(MCP23017,GPINTENA,0xf0)		# Enable Interrupts on all inputs 
	bus.write_byte_data(MCP23017,OLATA,0)			# Write out all 0s
	GPIO.setup(INTLINE, GPIO.IN)
	bus.read_byte_data(MCP23017,GPIOA)
	
def setup():
	"""setup code
	"""
	bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
	initMCP23017()

def loop():
	"""loop code
	"""
	while True:
		bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
		bounceOne()


if __name__ == '__main__':
	setup()
	loop()
	