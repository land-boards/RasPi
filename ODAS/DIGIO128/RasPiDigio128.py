#!/usr/bin/python
"""
====
NAME
====

RasPiDigio128.py - Raspberry Pi Digio128 example code 

* The MCP23017 is configured as two 8-bit ports (A and B)
* The DIGIO-128 has 8 of the MCP23017 parts
* MCP23017 Datasheet
*	http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf

========
SYNOPSIS
========

sudo python RasPiDigio128.py

===========
DESCRIPTION
===========

Used to demonstrate the operation of the DIGIO-128 card on the Raspberry Pi.
The demo blinks an LED attached to the least significant bit of Port A of the first MCP23017

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
IODIRA   = 0x00 # Pin direction register (PORT A)
IODIRB   = 0x01 # Pin direction register (PORT B)
IPOLA    = 0x02 # Input Polarity (PORT A)
IPOLB    = 0x03 # Input Polarity (PORT B)
GPINTENA = 0x04 # GPIO Interrupt Enable (PORT A)
GPINTENB = 0x05 # GPIO Interrupt Enable (PORT B)
INTCONA  = 0x08 # Interrupt Control Register (PORT A)
INTCONB  = 0x09 # Interrupt Control Register (PORT B)
IOCON    = 0x0A # IO Configuration Register
GPPUA    = 0x0C # Input Pullup enable (Port A)
GPPUB    = 0x0D # Input Pullup enable (Port B)
INTFA    = 0x0E # Interrupt Flag Register (Port A)
INTFB    = 0x0F # Interrupt Flag Register (Port B)
INTCAPA  = 0x10 # Interrupt Captured Register (Port A)
INTCAPB  = 0x11 # Interrupt Captured Register (Port B)
GPIOA    = 0x12 # Inputs
GPIOB    = 0x13 # Inputs
OLATA    = 0x14 # Register/Latch for outputs
OLATB    = 0x15 # Register/Latch for outputs

INTPOLACTHI = 0x02	# Interrupt Polarity Active High Flag
INTPOLACTLO = 0x00	# Interrupt Polarity Active Low Flag
INTLINE = 17		# Interrupt from the Mux card

PCA9544 = 0x71	# Mux address (on RPI-I2C-HUB)
SELCH0 = 0X04	# Select mux channel #0
SELCH1 = 0X05	# Select mux channel #1
SELCH2 = 0X06	# Select mux channel #2
SELCH3 = 0X07	# Select mux channel #3

def bounceOne():
	""" Blink an LED on the least significant bit of the first MCP23017
	"""
	bus.write_byte_data(MCP23017,OLATA,1)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCP23017,OLATA,0)	# turn off LED
	time.sleep(0.2)							# wait 1 sec

def initMCP23017():
	""" Initialize PORT A of the first MCP23017
	"""
	bus.write_byte_data(MCP23017,IODIRA,0xfe)		# Set I/O direction control for single bit output
	bus.write_byte_data(MCP23017,IOCON,INTPOLACTLO)	# Set interrupt polarity to low 
	bus.write_byte_data(MCP23017,IPOLA,0xfe)		# Set input polarity to invert
	bus.write_byte_data(MCP23017,GPINTENA,0xfe)		# Enable Interrupts on all inputs 
	bus.write_byte_data(MCP23017,OLATA,0)			# Write out all 0s
	GPIO.setup(INTLINE, GPIO.IN)                    # Interrupt line not used in the code
	bus.read_byte_data(MCP23017,GPIOA)				# Read a byte from the input port to clear any interrupts
	
def setup():
	"""setup code
	Sets the Mux port to 0 - DIGIO-128 is attached to the Mux Port #0
	Call the intitialization code for the MCP23017
	"""
	bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
	initMCP23017()

def loop():
	"""loop code
	"""
	while True:
		# Sets the Mux channel to Port #0
		bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
		# Toggle the single output line
		bounceOne()

if __name__ == '__main__':
	setup()
	loop()
	