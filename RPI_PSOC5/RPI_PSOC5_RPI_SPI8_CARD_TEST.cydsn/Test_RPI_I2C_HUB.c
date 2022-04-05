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

// Test an RPI_I2C_HUB
// Requires 4 DIGIO-8 cards
// Test bounces an LED across the four DIGIO-8 cards

#include <project.h>
#include "RPI_PSOC5.h"

// ////////////////////////////////////////////////////////////////////////////
// init_RPII2CHUB() - Initialize the RPI_I2C_HUB and (4) I2CIO-8 cards
// ////////////////////////////////////////////////////////////////////////////

void init_RPII2CHUB(void)
{
    uint8 I2CMUX_SLAVE_ADDR = 0x71;
    uint8 cMessage[2];
    uint8 channel;
    
    I2C1_Start();
    
    // initialize the four DIGIO8 cards
    for (channel = 0; channel < 4; channel++)
    {
        cMessage[0] = 0x04 | channel;
        I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
        while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
        initDIGIO8Card(0x20);
    }
}

// ////////////////////////////////////////////////////////////////////////////
// test_RPII2CHUB()
// ////////////////////////////////////////////////////////////////////////////

void test_RPII2CHUB(void)
{
    uint8 I2CMUX_SLAVE_ADDR = 0x71;
    uint8 I2CIO8_SLAVE_ADDR = 0x20;
    uint8 cMessage[2];
    uint8 rdIntStat;
    
    //I2C1_Start();
    
    init_RPII2CHUB();
    putStringToUSB("Initialized RPI-I2C-HUB card\n\r");
    
    putStringToUSB("Polling interrupts\n\r");

    while (0u == USBUART_DataIsReady())
    {
        I2C1_MasterReadBuf(I2CMUX_SLAVE_ADDR,cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
        while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_RD_CMPLT));
//        I2C1_MasterSendStop();
//        I2C1_MasterClearStatus();
        //while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
        rdIntStat = ((cMessage[0] >> 4) & 0xf);
        if ((rdIntStat & 0x01) == 0x01)
        {
            putStringToUSB("Int=0\n\r");
            cMessage[0] = 0x04;
            I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
            while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
            //readDIGIO8Card(I2CIO8_SLAVE_ADDR);
            readRegisterDIGIO8Card(I2CIO8_SLAVE_ADDR,MCP23008_INTCAP_REGADR); // Clear interrupt LED
        }
        if ((rdIntStat & 0x02) == 0x02)
        {
            cMessage[0] = 0x05;
            I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
            while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
            putStringToUSB("Int=1\n\r");
            //readDIGIO8Card(I2CIO8_SLAVE_ADDR);
            readRegisterDIGIO8Card(I2CIO8_SLAVE_ADDR,MCP23008_INTCAP_REGADR); // Clear interrupt LED
       }
        if ((rdIntStat & 0x04) == 0x04)
        {
            cMessage[0] = 0x06;
            I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
            while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
            putStringToUSB("Int=2\n\r");
            //readDIGIO8Card(I2CIO8_SLAVE_ADDR);
            readRegisterDIGIO8Card(I2CIO8_SLAVE_ADDR,MCP23008_INTCAP_REGADR); // Clear interrupt LED
        }
        if ((rdIntStat & 0x08) == 0x08)
        {
            cMessage[0] = 0x07;
            I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
            while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
            putStringToUSB("Int=3\n\r");
            //readDIGIO8Card(I2CIO8_SLAVE_ADDR);
            readRegisterDIGIO8Card(I2CIO8_SLAVE_ADDR,MCP23008_INTCAP_REGADR); // Clear interrupt LED
        }
    CyDelay(200);
    }
    putStringToUSB("Done testing interrupts\n\r");
}

// ////////////////////////////////////////////////////////////////////////////
// bounceRPIHubLEDs()
// ////////////////////////////////////////////////////////////////////////////

void bounceRPIHubLEDs(void)
{
//    I2C1_Start();
    uint8 I2CMUX_SLAVE_ADDR = 0x71;
    uint8 I2CIO8_SLAVE_ADDR = 0x20;
    uint8 cMessage[2];
    uint8 channel;
    
    init_RPII2CHUB();
    putStringToUSB("Initialized RPI-I2C-HUB card\n\r");
    
    for (channel = 0; channel < 4; channel++)
    {
        cMessage[0] = 0x04 | channel;
        I2C1_MasterWriteBuf(I2CMUX_SLAVE_ADDR, cMessage, 1, I2C_EEPROM_MODE_COMPLETE_XFER);
        while (0u == (I2C1_MasterStatus() & I2C1_MSTAT_WR_CMPLT));
        writeDIGIO8Card(I2CIO8_SLAVE_ADDR, 0x01);
        CyDelay(200);
        writeDIGIO8Card(I2CIO8_SLAVE_ADDR, 0x02);
        CyDelay(200);
        writeDIGIO8Card(I2CIO8_SLAVE_ADDR, 0x04);
        CyDelay(200);
        writeDIGIO8Card(I2CIO8_SLAVE_ADDR, 0x08);
        CyDelay(200);
        writeDIGIO8Card(I2CIO8_SLAVE_ADDR, 0x00);
    }
}

/* [] END OF FILE */
