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

#define LED_ON 1
#define LED_OFF 0


void testRPISPI8(void)
{
    clearReceiveBuffer();
// Set all of the RPI pins to outputs
    setRasPiPinValue(IO_9,PIN_DM_STRONG);   // SPIMISO 
    setRasPiPinValue(IO_10,PIN_DM_STRONG);  // SPIMOSI
    setRasPiPinValue(IO_11,PIN_DM_STRONG);  // SPISCK
    setRasPiPinValue(IO_8,PIN_DM_STRONG);   // SPICE0
    setRasPiPinValue(IO_22,PIN_DM_STRONG);  // A0
    setRasPiPinValue(IO_27,PIN_DM_STRONG);  // A1
    setRasPiPinValue(IO_17,PIN_DM_STRONG);  // A2
    
// Set all of the RPI pins to low
    setRasPiPinValue(IO_9,LED_ON);          // SPIMISO 
    setRasPiPinValue(IO_10,LED_ON);         // SPIMOSI
    setRasPiPinValue(IO_11,LED_ON);         // SPISCK
    setRasPiPinValue(IO_8,LED_OFF);         // SPICE0
    setRasPiPinValue(IO_22,LED_OFF);        // A0
    setRasPiPinValue(IO_27,LED_OFF);        // A1
    setRasPiPinValue(IO_17,LED_OFF);        // A2
    
// Blink all of the LEDs one at a time forever
// Hit ENTER to exit

    while (1)
    {
        setRasPiPinValue(IO_8,LED_OFF);     // SPICE0
        
        setRasPiPinValue(IO_22,LED_OFF);    // A0
        setRasPiPinValue(IO_27,LED_OFF);    // A1
        setRasPiPinValue(IO_17,LED_OFF);    // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_ON);     // A0
        setRasPiPinValue(IO_27,LED_OFF);    // A1
        setRasPiPinValue(IO_17,LED_OFF);    // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_OFF);    // A0
        setRasPiPinValue(IO_27,LED_ON);     // A1
        setRasPiPinValue(IO_17,LED_OFF);    // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_ON);     // A0
        setRasPiPinValue(IO_27,LED_ON);     // A1
        setRasPiPinValue(IO_17,LED_OFF);    // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_OFF);    // A0
        setRasPiPinValue(IO_27,LED_OFF);    // A1
        setRasPiPinValue(IO_17,LED_ON);     // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_ON);     // A0
        setRasPiPinValue(IO_27,LED_OFF);    // A1
        setRasPiPinValue(IO_17,LED_ON);     // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_OFF);    // A0
        setRasPiPinValue(IO_27,LED_ON);     // A1
        setRasPiPinValue(IO_17,LED_ON);     // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_22,LED_ON);     // A0
        setRasPiPinValue(IO_27,LED_ON);     // A1
        setRasPiPinValue(IO_17,LED_ON);     // A2
        CyDelay(500);
        
        setRasPiPinValue(IO_8,LED_ON);      // SPICE0
     	
        setRasPiPinValue(IO_9,LED_OFF);     // SPI_MISO
        CyDelay(500);
        setRasPiPinValue(IO_9,LED_ON);
        
    	setRasPiPinValue(IO_10,LED_OFF);    // SPI_MOSI
        CyDelay(500);
    	setRasPiPinValue(IO_10,LED_ON);

    	setRasPiPinValue(IO_11,LED_OFF);    // SPI_SCK
        CyDelay(500);
    	setRasPiPinValue(IO_11,LED_ON);
        // Check if a kr
        if (USBUART_DataIsReady() != 0)
            return;
    }
}

void debugRPISPI8(void)
{

}

/* [] END OF FILE */
