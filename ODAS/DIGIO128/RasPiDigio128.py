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
	bus.write_byte_data(MCP23017,OLAT,1)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23017,OLAT,1)	# turn off LED
	time.sleep(0.2)							# wait 1 sec

def initMCP23017():
	bus.write_byte_data(MCP23017,IODIR,0xf0)		# Set I/O direction control
	bus.write_byte_data(MCP23017,IOCON,INTPOLACTLO)	# Set interrupt polarity to low 
	bus.write_byte_data(MCP23017,IPOL,0xf0)			# Set input polarity to invert
	bus.write_byte_data(MCP23017,GPINTEN,0xf0)		# Enable Interrupts on all inputs 
	bus.write_byte_data(MCP23017,OLAT,0)			# Write out all 0s
	GPIO.setup(INTLINE, GPIO.IN)
	bus.read_byte_data(MCP23017,GPIOMCP)
	
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
	