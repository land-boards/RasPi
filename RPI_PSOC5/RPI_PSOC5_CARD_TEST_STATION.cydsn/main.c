/*******************************************************************************
* File Name: main.c
*
* Version: 2.0
*
* Description:
*   The is based on the Cypress Virtual Com port code. 
*   Receives data from the serial port, then sends back the received data.
*
* Related Document:
*  Universal Serial Bus Specification Revision 2.0
*  Universal Serial Bus Class Definitions for Communications Devices
*  Revision 1.2
*
*   Test software for Raspberry Pi cards
*   Runs on the the RPI_PSOC5 card
*      http://land-boards.com/blwiki/index.php?title=RPI_PSOC5
*   Tests the following cards
*       RPP-UIO-16 Card
*       RPPSOC Card
*       RASPI-PLUS-GVS-CFG Card
*       RASPI-GVS Card
*       RASPI-PLUS-GVS Card
*       RPI-I2C-HUB Card
*       RPI-SPI8 Card
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include "stdio.h"
#include "RPI_PSOC5.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow usage of the floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
//    asm (".global _printf_float");
#endif

#define USBFS_DEVICE    (0u)

/* The inBuffer size is equal to the maximum packet size of the IN and OUT bulk
* endpoints.
*/
#define USBUART_Buffer_SIZE (64u)

void putStringToUSB(char * stringToPutOutUSB);

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main function performs the following actions:
*   1. Waits until VBUS becomes valid and starts the USBFS component which is
*      enumerated as virtual Com port.
*   2. Waits until the device is enumerated by the host.
*   3. Waits for data coming from the hyper terminal
*   4. Parse command.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    uint16 inCount;
    uint8 inBuffer[USBUART_Buffer_SIZE];
        
    CyGlobalIntEnable;

    /* Start USBFS operation with 5-V operation. */
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);

    // enable I2C interrupts
	I2C_EEPROM_EnableInt();  
	//Start I2C
	I2C_EEPROM_Start();
    
    // Default to no daughtercard
    cardType = UNSELECTED_CARD;
    
//    printMenuOptions();
    
    for(;;)
    {
        /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_IsConfigurationChanged())
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_GetConfiguration())
            {
                /* Enumeration is done, enable OUT endpoint to receive data 
                 * from host. */
                USBUART_CDC_Init();
            }
        }

        /* Service USB CDC when device is configured. */
        if (0u != USBUART_GetConfiguration())
        {
            /* Check for input data from host. */
            if (0u != USBUART_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                inCount = USBUART_GetAll(inBuffer);
                addToReceiveBuffer(inCount,inBuffer);
				if (gotCRorLF == 1)
				{
                    psocMenu();
				}
                if (USBUART_Buffer_SIZE == inCount)
                {
                    
                    while (0u == USBUART_CDCIsReady()); // Wait until component is ready to send data to PC.
                    
                    USBUART_PutData(NULL, 0u);          // Send zero-length packet to PC.
                }
            }
        }
    }
}

/* [] END OF FILE */
