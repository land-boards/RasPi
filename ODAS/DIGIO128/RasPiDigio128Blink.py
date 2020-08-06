#!/usr/bin/python
"""
====
NAME
====

RasPiDigio128Blink.py - Raspberry Pi Digio128 example code 

* The MCP23017 is configured as two 8-bit ports (A and B)
* The DIGIO-128 has 8 of the MCP23017 parts
* MCP23017 Datasheet
*	http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf

========
SYNOPSIS
========

sudo python RasPiDigio128Blink.py

===========
DESCRIPTION
===========

Used to demonstrate the operation of the DIGIO-128 card on the Raspberry Pi.
The demo blinks an LED attached to the least significant bit of Port A of the first MCP23017.
LED should have a series resistor,

===========
ENVIRONMENT
===========

* Run under Raspbian
* Uses a Raspberry Pi
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

MCPAddresses = [0x2,0x21,0x22,0x23,0x24,0x25,0x26,0x27]
#MCP23017 = 0x20 # Slave device address base
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
GPIOA    = 0x12 # Inputs (Port A)
GPIOB    = 0x13 # Inputs (Port B)
OLATA    = 0x14 # Register/Latch for outputs (Port A)
OLATB    = 0x15 # Register/Latch for outputs (Port B)

def blinkOne():
	""" Blink an LED on the least significant bit of the first MCP23017
	"""
	bus.write_byte_data(MCPAddress[0],OLATA,1)	# turn on LED
	time.sleep(0.2)							# wait 1 sec
	bus.write_byte_data(MCPAddress[0],OLATA,0)	# turn off LED
	time.sleep(0.2)							# wait 1 sec

def initMCP23017():
	""" Initialize PORTs A/B of the MCP23017 parts
	Set all pins to inputs
	"""
	for MCPAddress in MCPAddresses:
		bus.write_byte_data(MCPAddress,IODIRA,0xff)			# Set all pins to inputs
		bus.write_byte_data(MCPAddress,IOCON,INTPOLACTLO)	# Set interrupt polarity to low 
		bus.write_byte_data(MCPAddress,IPOLA,0xfe)			# Set input polarity to invert
		bus.write_byte_data(MCPAddress,GPINTENA,0xfe)		# Enable Interrupts on all inputs 
		bus.write_byte_data(MCPAddress,OLATA,0)				# Write out all 0s
		bus.read_byte_data(MCPAddress,GPIOA)				# Read a byte from the input port to clear any interrupts
		bus.write_byte_data(MCPAddress,IODIRB,0xff)			# Set all pins to inputs
		bus.write_byte_data(MCPAddress,IPOLB,0xfe)			# Set input polarity to invert
		bus.write_byte_data(MCPAddress,GPINTENB,0xfe)		# Enable Interrupts on all inputs 
		bus.write_byte_data(MCPAddress,OLATB,0)				# Write out all 0s
		bus.read_byte_data(MCPAddress,GPIOB)				# Read a byte from the input port to clear any interrupts
	
initMCP23017()	# intialize the MCP ports
bus.write_byte_data(MCPAddress[0],IODIRA,0xfe)		# Set first bit og first port to output, rest are inputs
# Toggle the single output line
while True:
	blinkOne()
