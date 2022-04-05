/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include "RPI_PSOC5.h"

uint8 myWrBuffer[2];

void debugRPPUIO16(void)
{
    
}

void debugRPPGVS(void)
{
    
}

void debugRASPIGVS(void)
{
    
}

void debugRPPGVSCFG(void)
{
    
}

//////////////////////////////////////////////////////////////////////////////
// uint8 readRegisterDIGIO8Card(ctrlAdr) - 
//////////////////////////////////////////////////////////////////////////////

uint8 readRegisterDIGIO8CardX(uint8 slaveAdr, uint8 ctrlAdr)
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

void writeRegisterDIGIO8CardX(uint8 slaveAdr, uint8 ctrlAdr, uint8 ctrlVal)
{
    I2C1_MasterClearStatus();
    myWrBuffer[0] = ctrlAdr;
    myWrBuffer[1] = ctrlVal;
    I2C1_MasterWriteBuf(slaveAdr, myWrBuffer, 2, I2C1_MODE_COMPLETE_XFER);
    while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
    I2C1_MasterClearStatus();
}

void debugRPIHub(void)
{
    char debugStr[80];
    char muxNum[2];
    putStringToUSB("Testing...\n\r");
    uint8 I2CMUX_SLAVE_ADDR = 0x71;
    uint8 cMessage[2];
    uint8 channel;
    uint8 rdVal;
    uint8 pass1Fail0 = 1;
    
    putStringToUSB("Calling I2C1_Start()...\n\r");
    I2C1_Start();
    putStringToUSB("Called I2C1_Start()...\n\r");
    
    // initialize the four DIGIO8 cards
    for (channel = 0; channel < 4; channel++)
    {
        strcpy(debugStr,"Setting mux channel = 0x");
        muxNum[0] = '0' + channel;
        muxNum[1] = 0;
        strcat(debugStr,muxNum);
        strcat(debugStr,"\n\r");
        putStringToUSB(debugStr);
        cMessage[0] = 0x04 | channel;
        I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
        while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
        putStringToUSB("Testing DIGIO Card");
        writeRegisterDIGIO8CardX(0x20,MCP23008_IODIR_REGADR,MCP23008_IODIR_DEFVAL);
        rdVal = readRegisterDIGIO8CardX(0x20,MCP23008_IODIR_REGADR);
        if (rdVal == MCP23008_IODIR_DEFVAL)
        {
            putStringToUSB("... OK\n\r");
        }
        else
        {
            putStringToUSB("...*** Read back FAILED ***\n\r");
            pass1Fail0 = 0;
         }
    }
   if (pass1Fail0 == 1)
    {
        putStringToUSB("All tests passed\n\r");
    }
    else
    {
        putStringToUSB("\n\r*** TESTS FAILED ***\n\n\r");
    }
}

/* [] END OF FILE */
