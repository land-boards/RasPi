import Adafruit_MCP230xx

mcp = Adafruit_MCP230XX(busnum = 1, address = 0x27, num_gpios = 16)

# Set pins 0, 1 and 2 to output (you can set pins 0..15 this way)
mcp.config(0, OUTPUT)
mcp.config(1, OUTPUT)
mcp.config(2, OUTPUT)

# Set pin 3 to input with the pullup resistor enabled
# mcp.pullup(3, 1)
# Read pin 3 and display the results
# print "%d: %x" % (3, mcp.input(3) >> 3)

# Python speed test on output 0 toggling at max speed
while (True):
  mcp.output(0, 1)  # Pin 0 High
  mcp.output(0, 0)  # Pin 1 Low