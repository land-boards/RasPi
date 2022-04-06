#!/usr/bin/python
# 
# MCP4231_SPI_Test.py
# Original code at
#	https://www.takaitra.com/mcp4151-digital-potentiometer-raspberry-pi/
# Setup SPI at
#	https://www.takaitra.com/spi-device-raspberry-pi/
# 
# Sample code to write Digital Pot
# Triangle wave
# Run with -
# chmod +x pot-control.py
# sudo ./pot-control.py
# 

import spidev
import time
import RPi.GPIO  as  GPIO

spi = spidev.SpiDev()
spi.open(0, 0)		# bus,device
spi.max_speed_hz = 976000	# speed

A0Pin = 22
A1Pin = 27
A2Pin = 17

GPIO.setmode(GPIO.BOARD)		# Set the board mode  to numbers pins by physical location
GPIO.setup(A0Pin, GPIO.OUT)		# A0
GPIO.setup(A1Pin, GPIO.OUT)		# A1
GPIO.setup(A2Pin, GPIO.OUT)		# A2
GPIO.output(A0Pin, GPIO.LOW)	# A0 = 0
GPIO.output(A1Pin, GPIO.LOW)	# A1 = 0
GPIO.output(A2Pin, GPIO.LOW)	# A2  =0

def write_pot(input):
    msb = input >> 8
    lsb = input & 0xFF
    spi.xfer([msb, lsb])

while True:
    for i in range(0x00, 0x07F, 1):
        write_pot(i)
        time.sleep(.001)
    for i in range(0x07F, 0x00, -1):
        write_pot(i)
        time.sleep(.001)
