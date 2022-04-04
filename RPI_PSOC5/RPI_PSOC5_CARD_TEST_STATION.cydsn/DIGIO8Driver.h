/* ========================================
 *
 * Copyright LAND BOARDS, LLC, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Land Boards.
 *
 * ========================================
*/

#ifndef DIGIO8DRIVER_H
#define DIGIO8DRIVER_H
    
#include <project.h>
    
#define MPC23008_SLAVE_ADDR    0x20
    
#define MCP23008_IODIR_REGADR    0x00
#define MCP23008_IPOL_REGADR     0x01
#define MCP23008_GPINTEN_REGADR  0x02
#define MCP23008_DEFVAL_REGADR   0x03
#define MCP23008_INTCON_REGADR   0x04
#define MCP23008_IOCON_REGADR    0x05
#define MCP23008_GPPU_REGADR     0x06
#define MCP23008_INTF_REGADR     0x07
#define MCP23008_INTCAP_REGADR   0x08
#define MCP23008_GPIO_REGADR     0x09
#define MCP23008_OLAT_REGADR     0x0a

#define MCP23008_IODIR_DEFVAL    0xf0       // Upper 4 bits=JumperIns, lower=LEDS
#define MCP23008_GPIO_DEFVAL     0x00
#define MCP23008_IPOL_DEFVAL     0xf0       // Input polarity = invert jumpers
#define MCP23008_INTCON_DEFVAL   0x00       // 
#define MCP23008_GPINTEN_DEFVAL  0xf0       // Disable GPIO for interrupt on change
#define MCP23008_IOCON_DEFVAL    0x00       // Disable sequential,  active-low
#define MCP23008_GPPU_DEFVAL     0xf0       // Default pullups

uint8 readRegisterDIGIO8Card(uint8, uint8);
void writeRegisterDIGIO8Card(uint8, uint8, uint8);
void writeDIGIO8Card(uint8, uint8);
uint8 readDIGIO8Card(uint8);
void initDIGIO8Card(uint8);
 
#endif

/* [] END OF FILE */
