import smbus	# I2C library
import time		# used for sleep function

bus = smbus.SMBus(1) # Rev 2 Pi uses 1

MCP23008 = 0x20 # Slave device address base
IODIR    = 0x00 # Pin direction register
OLAT     = 0x0a # Register for outputs
GPIO     = 0x09 # Register for inputs

PCA9544 = 0x71	# Mux address
SELCH0 = 0X04	# Select mux channel #0
SELCH1 = 0X05	# Select mux channel #1
SELCH2 = 0X06	# Select mux channel #2
SELCH3 = 0X07	# Select mux channel #3

bus.write_byte_data(PCA9544,SELCH0,SELCH0)	# Select I2C bus #0
bus.write_byte_data(MCP23008,IODIR,0x00)	# Set direction to outputs
bus.write_byte_data(MCP23008,OLAT,0)		# Write out all 0s

bus.write_byte_data(PCA9544,SELCH1,SELCH1)	# Select I2C bus #1
bus.write_byte_data(MCP23008,IODIR,0x00)
bus.write_byte_data(MCP23008,OLAT,0)

bus.write_byte_data(PCA9544,SELCH2,SELCH2)	# Select I2C bus #2
bus.write_byte_data(MCP23008,IODIR,0x00)
bus.write_byte_data(MCP23008,OLAT,0)

bus.write_byte_data(PCA9544,SELCH3,SELCH3)	# Select I2C bus #3
bus.write_byte_data(MCP23008,IODIR,0x00)
bus.write_byte_data(MCP23008,OLAT,0)

while True:
	bus.write_byte_data(PCA9544,SELCH0)	# Select I2C bus #0
	bus.write_byte_data(MCP23008,OLAT,1)	# turn on LED
	time.sleep(1)							# wait 1 sec
	bus.write_byte_data(MCP23008,OLAT,0)	# turn off LED

	bus.write_byte_data(PCA9544,SELCH1)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)
	
	bus.write_byte_data(PCA9544,SELCH2)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)
	
	bus.write_byte_data(PCA9544,SELCH3)
	bus.write_byte_data(MCP23008,OLAT,1)
	time.sleep(1)
	bus.write_byte_data(MCP23008,OLAT,0)
