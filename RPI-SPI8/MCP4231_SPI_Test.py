#!/usr/bin/python
# 
# MCP4231_SPI_Test.py
#	Test SPI-POTX2 card on the Raspberry Pi using RPI_SPI8 SPI mux card
# 	Makes triangle waves
# 
# Hardware
# RPI_SPI8 SPI mux card Wiki page:
#	http://land-boards.com/blwiki/index.php?title=RPI_SPI8
# SPI-POTX2 Dual Digital Pot Wiki page:
#	http://land-boards.com/blwiki/index.php?title=SPI-POTX2
# 
# Software
# Original mcp4151 (digital pot) code at
#	https://www.takaitra.com/mcp4151-digital-potentiometer-raspberry-pi/
# Setup SPI at
#	https://www.takaitra.com/spi-device-raspberry-pi/
# 
# Run with -
# chmod +x MCP4231_SPI_Test.py
# sudo ./MCP4231_SPI_Test.py

import spidev
import time
import RPi.GPIO  as  GPIO

# Set the next line to False if directly connecting to Raspberry Pi SPI bus
USING_RPI_SPI8_CARD = True

spi = spidev.SpiDev()
spi.open(0, 0)		# bus,device
spi.max_speed_hz = 976000	# speed

if USING_RPI_SPI8_CARD:
	A0Pin = 15
	A1Pin = 13
	A2Pin = 11
	GPIO.setmode(GPIO.BOARD)		# Set the board mode  to numbers pins by physical location
	GPIO.setup(A0Pin, GPIO.OUT)		# A0
	GPIO.setup(A1Pin, GPIO.OUT)		# A1
	GPIO.setup(A2Pin, GPIO.OUT)		# A2

def set_RPI_SPI8_MuxPort(muxPort):
	if USING_RPI_SPI8_CARD:
		muxPort &= 0x7
		if (muxPort & 1) == 1:
			GPIO.output(A0Pin, GPIO.HIGH)
		else:
			GPIO.output(A0Pin, GPIO.LOW)
		if (muxPort & 2) == 2:
			GPIO.output(A1Pin, GPIO.HIGH)
		else:
			GPIO.output(A1Pin, GPIO.LOW)
		if (muxPort & 4) == 4:
			GPIO.output(A2Pin, GPIO.HIGH)
		else:
			GPIO.output(A2Pin, GPIO.LOW)
	return

# write_pot(potNum,input)
#	potNum - 0,1 - the two pots on the SPI-POTX2 card
#	potVal = 0-127 - 7-bit pot value
def write_pot(potNum,potVal):
	msb = (potNum & 1) << 4
	lsb = potVal & 0x7F
	spi.xfer([msb, lsb])

# Test loop follows
while True:
	for channelNum in range(0,8):
		set_RPI_SPI8_MuxPort(channelNum)
		for potNum in range(0,2):
			for i in range(0x00, 0x7F, 1):
				write_pot(potNum,i)
				# time.sleep(.001)
			for i in range(0x7F, 0x00, -1):
				write_pot(potNum,i)
				# time.sleep(.001)
