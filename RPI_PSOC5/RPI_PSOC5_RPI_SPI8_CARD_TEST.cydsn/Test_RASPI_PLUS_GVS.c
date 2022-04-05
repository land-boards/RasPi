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

// Function to blink an LED attached to an output channel
// Drives line high for a short time and then drives it low.
// The high level output turns on the LED.

#include <project.h>
#include "RPI_PSOC5.h"

#define LED_ON 1
#define LED_OFF 0

//void blinkLED(uint8 RPI_Pin)
//{
//	setRasPiPinValue(RPI_Pin, LED_ON);
//    CyDelay(250);
//	setRasPiPinValue(RPI_Pin, LED_OFF);
//}

void testRPPGVS(void)
{
// Set all of the RPI pins to outputs
    setRasPiPinValue(IO_2,PIN_DM_STRONG);
    setRasPiPinValue(IO_3,PIN_DM_STRONG);
    setRasPiPinValue(IO_4,PIN_DM_STRONG);
    setRasPiPinValue(IO_14,PIN_DM_STRONG);
    setRasPiPinValue(IO_15,PIN_DM_STRONG);
    setRasPiPinValue(IO_17,PIN_DM_STRONG);
    setRasPiPinValue(IO_18,PIN_DM_STRONG);
    setRasPiPinValue(IO_27,PIN_DM_STRONG);
    setRasPiPinValue(IO_22,PIN_DM_STRONG);
    setRasPiPinValue(IO_23,PIN_DM_STRONG);
    setRasPiPinValue(IO_24,PIN_DM_STRONG);
    setRasPiPinValue(IO_10,PIN_DM_STRONG);
    setRasPiPinValue(IO_9,PIN_DM_STRONG);
    setRasPiPinValue(IO_25,PIN_DM_STRONG);
    setRasPiPinValue(IO_11,PIN_DM_STRONG);
    setRasPiPinValue(IO_8,PIN_DM_STRONG);
    setRasPiPinValue(IO_7,PIN_DM_STRONG);
    setRasPiPinValue(IO_5,PIN_DM_STRONG);
    setRasPiPinValue(IO_6,PIN_DM_STRONG);
    setRasPiPinValue(IO_12,PIN_DM_STRONG);
    setRasPiPinValue(IO_13,PIN_DM_STRONG);
    setRasPiPinValue(IO_19,PIN_DM_STRONG);
    setRasPiPinValue(IO_16,PIN_DM_STRONG);
    setRasPiPinValue(IO_26,PIN_DM_STRONG);
    setRasPiPinValue(IO_20,PIN_DM_STRONG);
    setRasPiPinValue(IO_21,PIN_DM_STRONG);
    
// Set all of the RPI pins to low
    setRasPiPinValue(IO_2,LED_OFF);
    setRasPiPinValue(IO_3,LED_OFF);
    setRasPiPinValue(IO_14,LED_OFF);
    setRasPiPinValue(IO_15,LED_OFF);
    setRasPiPinValue(IO_17,LED_OFF);
    setRasPiPinValue(IO_18,LED_OFF);
    setRasPiPinValue(IO_27,LED_OFF);
    setRasPiPinValue(IO_22,LED_OFF);
    setRasPiPinValue(IO_23,LED_OFF);
    setRasPiPinValue(IO_24,LED_OFF);
    setRasPiPinValue(IO_10,LED_OFF);
    setRasPiPinValue(IO_9,LED_OFF);
    setRasPiPinValue(IO_25,LED_OFF);
    setRasPiPinValue(IO_11,LED_OFF);
    setRasPiPinValue(IO_8,LED_OFF);
    setRasPiPinValue(IO_7,LED_OFF);
    setRasPiPinValue(IO_5,LED_OFF);
    setRasPiPinValue(IO_6,LED_OFF);
    setRasPiPinValue(IO_12,LED_OFF);
    setRasPiPinValue(IO_13,LED_OFF);
    setRasPiPinValue(IO_19,LED_OFF);
    setRasPiPinValue(IO_16,LED_OFF);
    setRasPiPinValue(IO_26,LED_OFF);
    setRasPiPinValue(IO_20,LED_OFF);
    setRasPiPinValue(IO_21,LED_OFF);
    
    setRasPiPinValue(IO_4,1);   // Output Enable

// Blink all of the LEDs one at a time forever
// CTRL-C to exit which is not a particularly elegant exit strategy, but this is a demo program

	blinkLED(IO_5);
	blinkLED(IO_6);
	blinkLED(IO_13);
	blinkLED(IO_19);
    blinkLED(IO_26);
 	blinkLED(IO_21);
	blinkLED(IO_12);
	blinkLED(IO_16);
	blinkLED(IO_20);

    blinkLED(IO_18);
	blinkLED(IO_17);
	blinkLED(IO_27);
	blinkLED(IO_23);
	blinkLED(IO_22);
	blinkLED(IO_24);
	blinkLED(IO_25);
	blinkLED(IO_2);     // SDA1
	blinkLED(IO_3);     // SCL1
    blinkLED(IO_10);    // SPIMOSI
    blinkLED(IO_9);     // SPIMISO
    blinkLED(IO_11);    // SPISCK
   	blinkLED(IO_8);     // SPICE0
	blinkLED(IO_7);     // SPICE1
	blinkLED(IO_14);    // TXD0
	blinkLED(IO_15);    // RXD0
    
    
}
/* [] END OF FILE */
