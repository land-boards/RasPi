
import time as t
import smbus
import RPi.GPIO as GPIO

IODIRA   = 0x00 # Pin direction register
IODIRB   = 0x01 # Pin direction register
IPOLA    = 0x02 # 
IPOLB    = 0x03 # 
GPINTENA = 0x04 # 
GPINTENB = 0x05 # 
INTCONA  = 0x08 # 
INTCONB  = 0x09 # 
IOCON    = 0x0A # 
GPPUA    = 0x0C # 
GPPUB    = 0x0D # 
INTFA    = 0x0E # 
INTFB    = 0x0F # 
INTCAPA  = 0x10 # 
INTCAPB  = 0x11 # 
GPIOA    = 0x12 # Inputs
GPIOB    = 0x13 # Inputs
OLATA    = 0x14 # Register for outputs
OLATB    = 0x15 # Register for outputs
INTPOLACTHI = 0x02
INTPOLACTLO = 0x00
INTLINE = 17

# MCP23017 objects that hold the byte state of each register and the inherent address
MCPs = []
MCP1 = {
    "address": 0x20,
    "A": 0xFF,
    "B": 0xFF
}
MCP2 = {
    "address": 0x21,
    "A": 0xFF,
    "B": 0xFF
}
MCP3 = {
    "address": 0x22,
    "A": 0xFF,
    "B": 0xFF
}
MCP4 = {
    "address": 0x23,
    "A": 0xFF,
    "B": 0xFF
}
MCP5 = {
    "address": 0x24,
    "A": 0xFF,
    "B": 0xFF
}
MCP6 = {
    "address": 0x25,
    "A": 0xFF,
    "B": 0xFF
}
MCP7 = {
    "address": 0x26,
    "A": 0xFF,
    "B": 0xFF
}
MCP8 = {
    "address": 0x27,
    "A": 0xFF,
    "B": 0xFF
}

# add the MCPs to the list
MCPs.append(MCP1)
MCPs.append(MCP2)
MCPs.append(MCP3)
MCPs.append(MCP4)
MCPs.append(MCP5)
MCPs.append(MCP6)
MCPs.append(MCP7)
MCPs.append(MCP8)

# Object representation of a board. 
# The board holds on to each output pin/relay/light in the form of a list. 
# The pin/relay/light holds on to an MCP, a register, and its local index
board = {
    # MCP1
    0:  [MCP1, "A", 1],
    1:  [MCP1, "A", 2],
    2:  [MCP1, "A", 3],
    3:  [MCP1, "A", 4],
    4:  [MCP1, "A", 5],
    5:  [MCP1, "A", 6],
    6:  [MCP1, "A", 7],
    7:  [MCP1, "A", 8],
    8:  [MCP1, "B", 1],
    9:  [MCP1, "B", 2],
    10: [MCP1, "B", 3],
    11: [MCP1, "B", 4],
    12: [MCP1, "B", 5],
    13: [MCP1, "B", 6],
    14: [MCP1, "B", 7],
    15: [MCP1, "B", 8],

    # MCP2
    16: [MCP2, "A", 1],
    17: [MCP2, "A", 2],
    18: [MCP2, "A", 3],
    19: [MCP2, "A", 4],
    20: [MCP2, "A", 5],
    21: [MCP2, "A", 6],
    22: [MCP2, "A", 7],
    23: [MCP2, "A", 8],
    24: [MCP2, "B", 1],
    25: [MCP2, "B", 2],
    26: [MCP2, "B", 3],
    27: [MCP2, "B", 4],
    28: [MCP2, "B", 5],
    29: [MCP2, "B", 6],
    30: [MCP2, "B", 7],
    31: [MCP2, "B", 8],

    # MCP3
    32: [MCP3, "A", 1],
    33: [MCP3, "A", 2],
    34: [MCP3, "A", 3],
    35: [MCP3, "A", 4],
    36: [MCP3, "A", 5],
    37: [MCP3, "A", 6],
    38: [MCP3, "A", 7],
    39: [MCP3, "A", 8],
    40: [MCP3, "B", 1],
    41: [MCP3, "B", 2],
    42: [MCP3, "B", 3],
    43: [MCP3, "B", 4],
    44: [MCP3, "B", 5],
    45: [MCP3, "B", 6],
    46: [MCP3, "B", 7],
    47: [MCP3, "B", 8],

    # MCP4
    48: [MCP4, "A", 1],
    49: [MCP4, "A", 2],
    50: [MCP4, "A", 3],
    51: [MCP4, "A", 4],
    52: [MCP4, "A", 5],
    53: [MCP4, "A", 6],
    54: [MCP4, "A", 7],
    55: [MCP4, "A", 8],
    56: [MCP4, "B", 1],
    57: [MCP4, "B", 2],
    58: [MCP4, "B", 3],
    59: [MCP4, "B", 4],
    60: [MCP4, "B", 5],
    61: [MCP4, "B", 6],
    62: [MCP4, "B", 7],
    63: [MCP4, "B", 8],

    # MCP5
    64: [MCP5, "A", 1],
    65: [MCP5, "A", 2],
    66: [MCP5, "A", 3],
    67: [MCP5, "A", 4],
    68: [MCP5, "A", 5],
    69: [MCP5, "A", 6],
    70: [MCP5, "A", 7],
    71: [MCP5, "A", 8],
    72: [MCP5, "B", 1],
    73: [MCP5, "B", 2],
    74: [MCP5, "B", 3],
    75: [MCP5, "B", 4],
    76: [MCP5, "B", 5],
    77: [MCP5, "B", 6],
    78: [MCP5, "B", 7],
    79: [MCP5, "B", 8],

    # MCP6
    80: [MCP6, "A", 1],
    81: [MCP6, "A", 2],
    82: [MCP6, "A", 3],
    83: [MCP6, "A", 4],
    84: [MCP6, "A", 5],
    85: [MCP6, "A", 6],
    86: [MCP6, "A", 7],
    87: [MCP6, "A", 8],
    88: [MCP6, "B", 1],
    89: [MCP6, "B", 2],
    90: [MCP6, "B", 3],
    91: [MCP6, "B", 4],
    92: [MCP6, "B", 5],
    93: [MCP6, "B", 6],
    94: [MCP6, "B", 7],
    95: [MCP6, "B", 8],

    # MCP7
    96: [MCP7, "A", 1],
    97: [MCP7, "A", 2],
    98: [MCP7, "A", 3],
    99: [MCP7, "A", 4],
    100: [MCP7, "A", 5],
    101: [MCP7, "A", 6],
    102: [MCP7, "A", 7],
    103: [MCP7, "A", 8],
    104: [MCP7, "B", 1],
    105: [MCP7, "B", 2],
    106: [MCP7, "B", 3],
    107: [MCP7, "B", 4],
    108: [MCP7, "B", 5],
    109: [MCP7, "B", 6],
    110: [MCP7, "B", 7],
    111: [MCP7, "B", 8],

    # MCP8
    112: [MCP8, "A", 1],
    113: [MCP8, "A", 2],
    114: [MCP8, "A", 3],
    115: [MCP8, "A", 4],
    116: [MCP8, "A", 5],
    117: [MCP8, "A", 6],
    118: [MCP8, "A", 7],
    119: [MCP8, "A", 8],
    120: [MCP8, "B", 1],
    121: [MCP8, "B", 2],
    122: [MCP8, "B", 3],
    123: [MCP8, "B", 4],
    124: [MCP8, "B", 5],
    125: [MCP8, "B", 6],
    126: [MCP8, "B", 7],
    127: [MCP8, "B", 8],
}

def initMCP23017(): #Init the MCPs
    for MCP in MCPs:
        bus.write_byte_data(MCP["address"],IODIRA,0x00)		# Set I/O direction control for A
        bus.write_byte_data(MCP["address"],IODIRB,0x00)		# Set I/O direction control for B   
        bus.write_byte_data(MCP["address"],IOCON,INTPOLACTLO)	# Set interrupt polarity to low
        bus.write_byte_data(MCP["address"],IPOLA,0x00)			# Set input polarity to invert
        bus.write_byte_data(MCP["address"],GPINTENA,0x00)		# Enable Interrupts on all inputs 
        bus.write_byte_data(MCP["address"],GPINTENB,0x00)		# Enable Interrupts on all inputs 
        bus.write_byte_data(MCP["address"],OLATA,0x00)			# Write out all 0s
        bus.write_byte_data(MCP["address"],OLATB,0x00)			# Write out all 0s
        GPIO.setup(INTLINE, GPIO.IN)
        bus.read_byte_data(MCPs[i]["address"],GPIOA)

def allOff(): #Turn off all the lights
    for MCP in MCPs:
        MCP["A"] = 0x00
        MCP["B"] = 0x00
        bus.write_byte_data(MCP["address"],OLATA,0x00)
        bus.write_byte_data(MCP["address"],OLATB,0x00)

def allOn(): #Turn on all the lights
    for MCP in MCPs:
        MCP["A"] = 0xFF
        MCP["B"] = 0xFF
        bus.write_byte_data(MCP["address"],OLATA,0xFF)
        bus.write_byte_data(MCP["address"],OLATB,0xFF)

def toggle(idx): # given a global index of the light-board, toggle the light
    MCP = board[idx][0]
    reg = board[idx][1]
    pos = board[idx][2]
    MCP[reg] = toggleKthBit(MCP[reg], pos)
    if reg=="A":
        bus.write_byte_data(MCP["address"],OLATA,MCP[reg])
    else:
        bus.write_byte_data(MCP["address"],OLATB,MCP[reg])

def toggleKthBit(n, k): #given a bit index in a byte, toggle the bit, n=current state of the of the MCP register, k=the position of the bit in the byte that you want to change
    return (n ^ (1 << (k-1)))

GPIO.setmode(GPIO.BCM)	# setup GPIO using Board numbering
DEVICE_BUS = 1
bus = smbus.SMBus(DEVICE_BUS) # create the I2C bus
initMCP23017() # setup the parts
t.sleep(0.5)

try:
    # Turn on all the lights in sequence, then off in sequence. 5x
    for i in range(5):
        for i in range(128):
            t.sleep(.01)
            toggle(i)
        for i in range(128):
            t.sleep(.01)
            toggle(i)
except KeyboardInterrupt as e:
    print("Quit the Loop")
    allOff()
