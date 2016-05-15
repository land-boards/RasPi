/*******************************************************************************
* File Name: Timeout.c
* Version 3.0
*
* Description:
*  This file provides source code for the delay routine used in the HSSP application
*
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include "Timeout.h"

/********************************************************************************
*   Function Definitions
********************************************************************************/

/*******************************************************************************
* Function Name: DelayHundredUs
********************************************************************************
*
* Summary:
*  Generates an approximate delay for 100 microseconds
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The delay is introduced by using a for loop with a predefined iteration
*  determined by the parameter XRES_PULSE_100US in the header file Timeout.h. 
*
*******************************************************************************/

void DelayHundredUs(void)
{
    delayMicroseconds(99);
}

/* [] END OF FILE */
