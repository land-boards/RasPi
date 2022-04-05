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

#include <project.h>
#include "RPI_PSOC5.h"

void setSPIChannel(uint8);

void testRPISPI8(void)
{
    uint16 txValue;
    uint8 chNum;
    putStringToUSB("testRPISPI8() - Reached function\n\r");
    // Flush input buffer
    clearReceiveBuffer();
    putStringToUSB("testRPISPI8() - Start SPI\n\r");
    SPIM_1_Start();
    putStringToUSB("testRPISPI8() - Started SPI\n\r");
    // Blink all of the LEDs one at a time forever
    // Hit ENTER to exit
    while (1)
    {
        for (chNum = 0; chNum < 8; chNum++)
        {
            setSPIChannel(chNum);
            for (txValue = 0; txValue < 0x80; txValue++)
            {
                //putStringToUSB("testRPISPI8() - Writing data\n\r");
                SPIM_1_WriteTxData(txValue);
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

void debugRPISPI8(void)
{

}

/* [] END OF FILE */
