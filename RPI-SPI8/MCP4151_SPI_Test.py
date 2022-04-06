#!/usr/bin/python
# 
# MCP4151_SPI_Test.py
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

spi = spidev.SpiDev()
spi.open(0, 0)		# bus,device
spi.max_speed_hz = 976000	# speed

def write_pot(input):
    msb = input >> 8
    lsb = input & 0xFF
    spi.xfer([msb, lsb])

while True:
    for i in range(0x00, 0x07F, 1):
        write_pot(i)
        time.sleep(.005)
    for i in range(0x07F, 0x00, -1):
        write_pot(i)
        time.sleep(.005)
