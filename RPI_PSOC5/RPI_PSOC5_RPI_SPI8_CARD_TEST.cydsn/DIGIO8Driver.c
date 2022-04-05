 /* ========================================
 * DIGIO8Driver.c
 * Copyright Land Boards LLC, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Land Boards, LLC.
 *
 * ======================================== */

#include <project.h>
#include "RPI_PSOC5.h"

uint8 myWrBuffer[2];
 
//////////////////////////////////////////////////////////////////////////////
// uint8 readRegisterDIGIO8Card(ctrlAdr) - 
//////////////////////////////////////////////////////////////////////////////

uint8 readRegisterDIGIO8Card(uint8 slaveAdr, uint8 ctrlAdr)
{
    uint8 rdBuff;
    I2C1_MasterClearStatus();
    I2C1_MasterSendStart(MPC23008_SLAVE_ADDR,I2C1_WRITE_XFER_MODE);
    I2C1_MasterWriteByte(ctrlAdr);
    I2C1_MasterSendStop();
//    while ((I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT) == 0);
    I2C1_MasterSendStart(slaveAdr,I2C1_READ_XFER_MODE);
    rdBuff = I2C1_MasterReadByte(I2C1_NAK_DATA);
    I2C1_MasterSendStop();
//    while ((I2C1_MasterStatus() & I2C1_MSTAT_RD_CMPLT) == 0);
    I2C1_MasterClearStatus();
    return rdBuff;
}

//////////////////////////////////////////////////////////////////////////////
// writeRegisterDIGIO8Card(ctrlAdr, ctrlVal) - 
//////////////////////////////////////////////////////////////////////////////

void writeRegisterDIGIO8Card(uint8 slaveAdr, uint8 ctrlAdr, uint8 ctrlVal)
{
    I2C1_MasterClearStatus();
    myWrBuffer[0] = ctrlAdr;
    myWrBuffer[1] = ctrlVal;
    I2C1_MasterWriteBuf(slaveAdr, myWrBuffer, 2, I2C1_MODE_COMPLETE_XFER);
    while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
    I2C1_MasterClearStatus();
}

//////////////////////////////////////////////////////////////////////////////
// writeDIGIO8Card(uint8_t outData) - 
//////////////////////////////////////////////////////////////////////////////

void writeDIGIO8Card(uint8 slaveAdr, uint8 outData)
{
     writeRegisterDIGIO8Card(slaveAdr,MCP23008_OLAT_REGADR,outData);
}

//////////////////////////////////////////////////////////////////////////////
// readDIGIO8Card(void)
//////////////////////////////////////////////////////////////////////////////

uint8 readDIGIO8Card(uint8 slaveAdr)
{
    uint8 rdBuff;
    rdBuff = readRegisterDIGIO8Card(slaveAdr,MCP23008_GPIO_REGADR);
    return rdBuff>>4;
}

//////////////////////////////////////////////////////////////////////////////
// initDIGIO8Card(void) - 
//////////////////////////////////////////////////////////////////////////////

void initDIGIO8Card(uint8 slaveAdr)
{
    I2C1_Start();    // Kick off the I2C interface
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_IODIR_REGADR,MCP23008_IODIR_DEFVAL);
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_GPIO_REGADR,MCP23008_GPIO_DEFVAL);
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_INTCON_REGADR,MCP23008_INTCON_DEFVAL);
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_IOCON_REGADR,MCP23008_IOCON_DEFVAL);
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_IPOL_REGADR,MCP23008_IPOL_DEFVAL);
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_GPINTEN_REGADR,MCP23008_GPINTEN_DEFVAL);
    writeRegisterDIGIO8Card(slaveAdr,MCP23008_GPPU_REGADR,MCP23008_GPPU_DEFVAL);
    readRegisterDIGIO8Card(slaveAdr,MCP23008_INTCAP_REGADR); // Clear interrupt LED
}

/* [] END OF FILE */
