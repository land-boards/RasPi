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

# Set all GPA pins as outputs by setting
# all bits of IODIRA register to 0
bus.write_byte_data(MCP23017,IODIRA,0x00)
bus.write_byte_data(MCP23017,IODIRB,0x00)

# Set output all 7 output bits to 0
bus.write_byte_data(MCP23017,OLATA,0)
bus.write_byte_data(MCP23017,OLATB,0)

while True:
	bus.write_byte_data(MCP23017,OLATA,1)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x02)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x04)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x08)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x10)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x20)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x40)
	time.sleep(1)
	bus.write_byte_data(MCP23017,OLATA,0x80)
	time.sleep(1)
  
# Set all bits to zero
bus.write_byte_data(MCP23017,OLATA,0)