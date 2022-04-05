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

#include "RPI_PSOC5.h"
#include "stdio.h"

void readEEPROM(uint8 * eepromBuffer)
{
    uint8 SLAVE_ADDR = 0x50;
    uint8 cMessage[2];
    uint16 cLength = 256;
    
    cMessage[0] = 0;
    cMessage[1] = 0;
    
    //write a dummy byte to initialize the address word counter of 
    //eeprom to start address for read back operation. First location 
    //of cMessage array has word address.
    
    I2C_EEPROM_MasterWriteBuf(SLAVE_ADDR, cMessage, 2, I2C_EEPROM_MODE_COMPLETE_XFER);
    
    //wait until Transfer is complete
    while((I2C_EEPROM_MasterStatus() & I2C_EEPROM_MSTAT_WR_CMPLT )==0);
    
    //Delay for setting address in EEPROM
    CyDelayUs(1);
    
    //Read the 16 bytes from slave, staring from word address specified by iMessage
    //SLAVE_ADDR is the slave address in this API
    //cRx_Buffer is the pointer to array where data has to be stored after reading from EEPROM.
    //cLength-1 is the number of bytes which have to be read from EEPROM
    //I2C_MODE_COMPLETE_XFER, is to read data completly before sending stop command.
    
    I2C_EEPROM_MasterReadBuf(SLAVE_ADDR, eepromBuffer, cLength-1, I2C_EEPROM_MODE_COMPLETE_XFER );
            
    //wait until Transfer is complete
    while((I2C_EEPROM_MasterStatus() & I2C_EEPROM_MSTAT_RD_CMPLT )==0); 
}

void dumpEEPROM(uint8 * eepromBuffer)
{
    char lineBuffer[8];
    lineBuffer[0] = 0;
    uint16 linesLoop = 0;
    uint16 charsLoop = 0;
    for (linesLoop = 0; linesLoop < 16; linesLoop++)
    {
        char lineString[65];
        lineString[0] = 0;
        sprintf(lineString,"%04x ",linesLoop<<4);
        for (charsLoop = 0; charsLoop < 16; charsLoop++)
        {
            sprintf(lineBuffer, " %02x",eepromBuffer[(linesLoop<<4)+charsLoop]);
            strcat(lineString, lineBuffer);
        }
        strcat(lineString, "  ");
        USBUART_PutData((uint8 *)lineString, strlen(lineString));
        while (0u == USBUART_CDCIsReady());
        lineString[0] = 0;
        // Form a character string for the 
        for (uint16 charCol = 0; charCol < 16; charCol++)
        {
            // print if the char is printable
            if ((eepromBuffer[(linesLoop<<4)+charCol] >= 0x21) && (eepromBuffer[(linesLoop<<4)+charCol] <= 0x7E))
            {
                lineString[charCol] = eepromBuffer[(linesLoop<<4)+charCol];
            }
            else
            {
                lineString[charCol] = '.';
            }
            lineString[charCol+1] = 0;
        }
        strcat(lineString, "\n\r");
        USBUART_PutData((uint8 *)lineString, strlen(lineString));
        while (0u == USBUART_CDCIsReady());
    }
}

//////////////////////////////////////////////////////////////////////////////
// void writeEEPROM() - Take the EEPROM source and move it to a 32-byte buffer
// Call the routine to write the 32-byte buffers to the EEPROM

uint8 writeEEPROM(uint16 targetHat)
{
    uint8 array32Bytes[34];
    uint16 srcPointer = 0;
    uint16 dstPointer;
    
    if (targetHat == RPPUIO16)
    {
        for (uint16 blockNumber = 0; blockNumber < NUM_32_BYTE_BLOCKS; blockNumber++)
        {
            dstPointer = 0;
            array32Bytes[dstPointer++] = 0;                         // 
            array32Bytes[dstPointer++] = (blockNumber<<5) & 0xff;   // Set the starting address
            for (uint16 loopCounter = 0; loopCounter< 32; loopCounter++)
            {
                if (srcPointer < RPP_UIO16_EEPROM_LENGTH)
                    array32Bytes[dstPointer++] = rpp_uio_16_eeprom[srcPointer];
                else
                    array32Bytes[dstPointer++] = 0;
                srcPointer++;
            }
            writeEEPROMBlock(array32Bytes);
        }
        return(1);
    }
    else if (targetHat == RPPGVSCFG)
    {
        for (uint16 blockNumber = 0; blockNumber < NUM_32_BYTE_BLOCKS; blockNumber++)
        {
            dstPointer = 0;
            array32Bytes[dstPointer++] = 0;                         // 
            array32Bytes[dstPointer++] = (blockNumber<<5) & 0xff;   // Set the starting address
            for (uint16 loopCounter = 0; loopCounter< 32; loopCounter++)
            {
                if (srcPointer < RPPGVSCFG_EEPROM_LENGTH)
                    array32Bytes[dstPointer++] = raspi_plus_gvs_cfg_eeprom[srcPointer];
                else
                    array32Bytes[dstPointer++] = 0;
                srcPointer++;
            }
            writeEEPROMBlock(array32Bytes);
        }
        return(1);
    }
    else if (targetHat == RPPSOC)
    {
        for (uint16 blockNumber = 0; blockNumber < NUM_32_BYTE_BLOCKS; blockNumber++)
        {
            dstPointer = 0;
            array32Bytes[dstPointer++] = 0;                         // 
            array32Bytes[dstPointer++] = (blockNumber<<5) & 0xff;   // Set the starting address
            for (uint16 loopCounter = 0; loopCounter< 32; loopCounter++)
            {
                if (srcPointer < RPPSOC_EEPROM_LENGTH)
                    array32Bytes[dstPointer++] = rppsoc_eeprom[srcPointer];
                else
                    array32Bytes[dstPointer++] = 0;
                srcPointer++;
            }
            writeEEPROMBlock(array32Bytes);
        }
        return(1);
    }
    return(0);    
}

void writeEEPROMBlock(uint8 * cMessage)
{
    //Following API writes the data from PSoC3 RAM buffer to EEPROM
    //SLAVE_ADDR is the slave address in this API
    //cMessage is the pointer to array which contains the data to be written to EEPROM.
    //cLength is the number of bytes which have to be written to EEPROM
    //I2C_MODE_COMPLETE_XFER, is to send data completly before sending stop command.

    uint8 SLAVE_ADDR = 0x50;
    uint8 cLength = 34;         // First two are the address of the block to write
    
    I2C_EEPROM_MasterWriteBuf(SLAVE_ADDR, cMessage, cLength, I2C_EEPROM_MODE_COMPLETE_XFER);
    
    //wait until Transfer is complete
    while((I2C_EEPROM_MasterStatus() & I2C_EEPROM_MSTAT_WR_CMPLT )==0); 
    
    // 10 mS delay to complete the write operation(twr)
    CyDelay(10);    
}

/* [] END OF FILE */
