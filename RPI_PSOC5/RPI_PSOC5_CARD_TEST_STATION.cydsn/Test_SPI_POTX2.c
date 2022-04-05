/* ========================================
 *
 * Copyright LAND BOARDS LLC, 2022
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LAND BOARDS LLC.
 *
 * Test a SPI-POTX2 card
 *  http://land-boards.com/blwiki/index.php?title=SPI-POTX2
 * Uses a RPI_SPI8 SPI Mulitplexer
 *  http://land-boards.com/blwiki/index.php?title=RPI_SPI8
 *
 * Ramps Wiper voltage on both channels of the SPI-POTX2 card
 * Tests all 8 SPI interfaces
 *
 * ========================================
*/

#include <project.h>
#include "RPI_PSOC5.h"

void setSPIChannel(uint8);

void test_SPI_POTX2(void)
{
    uint16 txValue;
    uint8 chNum;
    putStringToUSB("test_SPI_POTX2() - Reached function\n\r");
    // Flush input buffer
    clearReceiveBuffer();
    putStringToUSB("test_SPI_POTX2() - Start SPI\n\r");
    SPIM_1_Start();
    putStringToUSB("test_SPI_POTX2() - Started SPI\n\r");
    // Blink all of the LEDs one at a time forever
    // Hit ENTER to exit
    while (1)
    {
        for (chNum = 0; chNum < 8; chNum++)
        {
            setSPIChannel(chNum);
            // Pot0
            for (txValue = 0; txValue < 0x80; txValue++)
            {
                //putStringToUSB("testRPISPI8() - Writing data\n\r");
                SPIM_1_WriteTxData(txValue);        // Pot0
                //putStringToUSB("testRPISPI8() - Wait while Tx Full\n\r");
                while ((SPIM_1_TX_STATUS_REG & 0x1) != 0x01);
                //putStringToUSB("testRPISPI8() - Finished waiting while Tx is not empty\n\r");
            }
            // Pot1
            for (txValue = 0; txValue < 0x80; txValue++)
            {
                //putStringToUSB("testRPISPI8() - Writing data\n\r");
                SPIM_1_WriteTxData(0x1000|txValue);     // Pot1
                //putStringToUSB("testRPISPI8() - Wait while Tx Full\n\r");
                while ((SPIM_1_TX_STATUS_REG & 0x1) != 0x01);
                //putStringToUSB("testRPISPI8() - Finished waiting while Tx is not empty\n\r");
            }
        }
        // Check if ENTER is hit
        if (USBUART_DataIsReady() != 0)
            return;
    }
}

void setSPIChannel(uint8 channelNum)
{
    SPI_ADDR_Write(channelNum);
}

void debugSPIPOTX2(void)
{

}

/* [] END OF FILE */
