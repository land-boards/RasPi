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
	delayMicroseconds(99);
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
	Swd_RawReadPacket(); /* Send a single SWD read packet */
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
	/* Send a dummy packet with all zeros since this is a test function  */
	Swd_packetHeader =  0x00;
	Swd_packetData[3] = 0x00;
	Swd_packetData[2] = 0x00;
	Swd_packetData[1] = 0x00;
	Swd_packetData[0] = 0x00;
	Swd_WritePacketFast(0x00);
}

/*******************************************************************************
* Function Name: TestSwdck
********************************************************************************
*
* Summary:
*  This function is  used to calculate the timing parameter 
*  TIME_WINDOW_68US
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  Replaced the original constant with a call to the microsecond timer on the 
*  Raspberry Pi as accessed from WiringPi.
*
*******************************************************************************/
void TestSwdck()
{
    unsigned short time_elapsed;
	/* calculate the actual maximum speed of the GPIO lines 	*/
	unsigned int deltaCount = 0;
	SetSwdckCmosOutput();
	deltaCount =  micros();
	/* Measure the time it takes to do 100 clocks				*/
	for (time_elapsed = 0; time_elapsed < 100; time_elapsed++)
    {
        SWDCK_OUTPUT_LOW;
        SWDCK_OUTPUT_LOW;
    }
	deltaCount = micros() - deltaCount;	/* time in uS that it took to do 100 clocks	*/
	deltaCount = 6800/deltaCount;

	unsigned int endCount;
	endCount =  micros() + 68;
	for (time_elapsed = 0; time_elapsed < deltaCount; time_elapsed++)
	{
		SWDCK_OUTPUT_LOW;
		SWDCK_OUTPUT_HIGH;
	}
	SetSwdckHizInput();
}
