/*******************************************************************************
* File Name: TimeoutCalc.c
* Version 3.0
*
* Description:
*  This file provides source code for the functions used to calculate the 
*  timeout parameters used in the HSSP application
*
* Note:
*  Refer to the header file TimeoutCalc.h for the procedure to calculate the 
*  timeout parameters
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include "TimeoutCalc.h"
#include "Swd_PhysicalLayer.h"
#include "Swd_PacketLayer.h"

/********************************************************************************
*   Function Definitions
********************************************************************************/

/*******************************************************************************
* Function Name: TestDelayHundredUs
********************************************************************************
*
* Summary:
*  This function is used to calculate the timing parameter XRES_PULSE_100US
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  Refer to the explanation of the parameter XRES_PULSE_100US in the file
*  TimeoutCalc.h for details on using this function to calculate the parameter
*  XRES_PULSE_100US  
*
*******************************************************************************/

void TestDelayHundredUs(void)
{
    unsigned short timestamp;
        
    digitalWrite(5,1); /* Make the pin low before start of the delay */
	delayMicroseconds(100);
    digitalWrite(5,0); /* Make the pin high after end of the delay */
}

/*******************************************************************************
* Function Name: TestSwdReadPacket
********************************************************************************
*
* Summary:
*  This function is used to calculate the timing parameter SPC_POLLING_TIMEOUT
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  Refer to the explanation of the parameter SPC_POLLING_TIMEOUT in the file
*  TimeoutCalc.h for details on using this function to calculate the parameter
*  SPC_POLLING_TIMEOUT  
*
*******************************************************************************/
void TestSwdReadPacket()
{       
    digitalWrite(5,1); /* Make the pin low before sending SWD read packet */     

    Swd_RawReadPacket(); /* Send a single SWD read packet */
        
    digitalWrite(5,0); /* Make the pin high after sending SWD read packet */
}

/*******************************************************************************
* Function Name: TestAcquirePacket
********************************************************************************
*
* Summary:
*  This function is used to calculate the timing parameter DEVICE_ACQUIRE_TIMEOUT
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  Refer to the explanation of the parameter DEVICE_ACQUIRE_TIMEOUT in the file
*  TimeoutCalc.h for details on using this function to calculate the parameter
*  DEVICE_ACQUIRE_TIMEOUT  
*
*******************************************************************************/
void TestAcquirePacket()
{
    digitalWrite(5,1); /* Make the pin low before sending SWD acquire packet */

    /* Send a dummy packet with all zeros since this is a test function  */
    Swd_packetHeader =  0x00;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x00;
    Swd_WritePacketFast(0x00);

    digitalWrite(5,0);  /* Make the pin high after sending SWD acquire packet */
}

/*******************************************************************************
* Function Name: TestSwdck
********************************************************************************
*
* Summary:
*  This function is used to calculate the timing parameter TIME_WINDOW_68US
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  Refer to the explanation of the parameter TIME_WINDOW_68US in the file
*  TimeoutCalc.h for details on using this function to calculate the parameter
*  TIME_WINDOW_68US  
*
*******************************************************************************/
void TestSwdck()
{
    unsigned short time_elapsed;
       
    digitalWrite(5,1); /* Make the pin low before sending SWD clock train */
    
    /* For loop that does a clocking of the SWDCK for >= 68 us duration */
    for(time_elapsed = 0; time_elapsed < TIME_WINDOW_68US; time_elapsed++)
    {
        SWDCK_OUTPUT_LOW;
        SWDCK_OUTPUT_HIGH;
    }
    
    digitalWrite(5,0); /* Make the pin high after sending SWD clock train */
}

/* [] END OF FILE */
