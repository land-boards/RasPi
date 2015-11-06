import smbus
import time

bus = smbus.SMBus(1) # Rev 2 Pi uses 1

MCP23008 = 0x20 # Device address (A0-A2)
IODIR    = 0x00 # Pin direction register
OLAT     = 0x0a # Register for outputs
GPIO     = 0x09 # Register for inputs

PCA9544 = 0x71
SELCH0 = 0X04
SELCH1 = 0X05
SELCH2 = 0X06
SELCH3 = 0X07

bus.write_byte_data(PCA9544,SELCH0,SELCH0)
# Set all GPA pins as outputs by setting
# all bits of IODIRA register to 0
bus.write_byte_data(MCP23008,IODIR,0x00)
# Set output all 16 output bits to 0
bus.write_byte_data(MCP23008,OLAT,0)

bus.write_byte_data(PCA9544,SELCH1,SELCH1)
# Set all GPA pins as outputs by setting
# all bits of IODIRA register to 0
bus.write_byte_data(MCP23008,IODIR,0x00)
# Set output all 16 output bits to 0
bus.write_byte_data(MCP23008,OLAT,0)

bus.write_byte_data(PCA9544,SELCH2,SELCH2)
# Set all GPA pins as outputs by setting
# all bits of IODIRA register to 0
bus.write_byte_data(MCP23008,IODIR,0x00)
# Set output all 16 output bits to 0
bus.write_byte_data(MCP23008,OLAT,0)

bus.write_byte_data(PCA9544,SELCH3,SELCH3)
# Set all GPA pins as outputs by setting
# all bits of IODIRA register to 0
bus.write_byte_data(MCP23008,IODIR,0x00)
# Set output all 16 output bits to 0
bus.write_byte_data(MCP23008,OLAT,0)

while True:
	bus.write_byte_data(PCA9544,SELCH0,SELCH0)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)

	bus.write_byte_data(PCA9544,SELCH1,SELCH1)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)
	
	bus.write_byte_data(PCA9544,SELCH2,SELCH2)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)
	
	bus.write_byte_data(PCA9544,SELCH3,SELCH3)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)
	
	
