/*******************************************************************************
* File Name: DeviceAcquire.c
* Version 3.0
*
* Description:
*  This file provides the source code for "Step1: Enter Programming Mode" in Programming flow.
*  It also has the routine to exit programming mode.
*  This step is provided as separate .c, .h file as the procedure to enter target programming 
*  mode has strict timing requirements.
*
* Note:
*  Refer to the PSoC 5LP Programming specifications for details on timing requirements.
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include "DeviceAcquire.h"

/* "Swd_PhysicalLayer.h" file contains the bit banging routines for SWD protocol.
   "Swd_PacketLayer.h" file contains the packet definitions for the SWD protocol."  */
#include "Swd_PhysicalLayer.h"
#include "Swd_PacketLayer.h"

/********************************************************************************
*   Function Definitions
********************************************************************************/

/*******************************************************************************
* Function Name: AcquireTargetDevice
********************************************************************************
*
* Summary:
*  Sends the SWD packets corresponding to "Step1: Enter Programming Mode" in the
*  PSoC 5LP Programming flow
*
* Parameters:
*  None.
*
* Return:
*  ack - Variable that holds the status of the SWD transaction
*    ACK response is stored as a byte. Possible ACK values are:
*       0x01 - SWD_OK_ACK (SUCCESS)
*       0x02 - SWD_WAIT_ACK
*       0x04 - SWD_FAULT_ACK
*       0x1x - There was a timeout error in Device Acquire (Indicated by Bit 4 being set)
*              which will happen if the entire step could not be completed in time Ttestmode.
*              Treat it similar to SWD_FAULT_ACK and abort operation.
*
* Note:
*  This function has strict requirements for execution time after generating pulse on XRES pin.
*  It calls the time optimized function Swd_WritePacketFast() to send the SWD acquire packets quickly. 
*
*  While porting this code to your Host processor, try to ensure that very few function calls are
*  used inside this function. The timing requirements for device acquire are documented in
*  the "PSoC 5LP Device Programming Specifications". A execution time optimized code is required
*  to meet these timing requirements.
*
*  This function is called by function EnterProgrammingMode() in ProgrammingSteps.c to acquire
*  the target device and enter its programming mode
*
*******************************************************************************/

unsigned char AcquireTargetDevice()
{
    unsigned char total_packet_count;
    unsigned short time_elapsed;
    
    total_packet_count = 0;
    
    /* Set the initial state of the programming pins */
    
    /* Host XRES pin must be in strong drive mode, and is driven high by default */
    XRES_DRIVEMODE_CMOSOUT;
    XRES_OUTPUT_HIGH;
    
    /* Host SWDCK pin must be in strong drive mode, and is driven low by default */   
    SWDCK_DRIVEMODE_CMOSOUT;
    SWDCK_OUTPUT_LOW;
    
    /* Host SWDIO pin must be in strong drive mode, and is driven low by default */ 
    SWDIO_DRIVEMODE_CMOSOUT;
    SWDIO_OUTPUT_LOW;  
    
	/* calculate the actual maximum speed of the GPIO lines 	*/
	unsigned int deltaCount = 0;
	deltaCount =  micros();
	/* Measure the time it takes to do 100 clocks				*/
	for (time_elapsed = 0; time_elapsed < 100; time_elapsed++)
	{
		SWDCK_OUTPUT_LOW;
		SWDCK_OUTPUT_LOW;
	}
	deltaCount = micros() - deltaCount;	/* time in uS that it took to do 100 clocks	*/
	deltaCount = 7000/deltaCount;

    /* Generate a Reset pulse of 100 uS. Minimum XRES pulse width is 1 uS for PSoC 5LP.
       The Delay function need not be accurate, it can be more than 100 uS as well. It will not 
       affect the programming operation */
    XRES_OUTPUT_LOW;
    delayMicroseconds(99);
    XRES_OUTPUT_HIGH;
    
	unsigned int endCount;
	endCount =  micros() + 68;
	for (time_elapsed = 0; time_elapsed < deltaCount; time_elapsed++)
	{
		SWDCK_OUTPUT_LOW;
		SWDCK_OUTPUT_HIGH;
	}

    /* Send the Port Acquire SWD packet continuously till OK ACK or timeout occurs.
       For the first packet alone, sometimes an ACK of "0x07" may be received. So, we
       will loop till the first packet receives an OK ACK, else timeout. */
    Swd_packetHeader =  PORT_ACQUIRE_KEY_HEADER;
    Swd_packetData[3] = 0x7B;
	Swd_packetData[2] = 0x0C;
	Swd_packetData[1] = 0x06;
	Swd_packetData[0] = 0xDB;    
    do
    {
        Swd_WritePacketFast(PARITY_PORT_ACQUIRE_KEY); 
        total_packet_count++;
    }
	while((Swd_packetAck != SWD_OK_ACK) && (total_packet_count < DEVICE_ACQUIRE_TIMEOUT));

    /* If OK ACK is not received for Port Acquire key, abort operation and retun the SWD packet ack */
    if(Swd_packetAck != SWD_OK_ACK)
    {
        return((Swd_packetAck | PORT_ACQUIRE_TIMEOUT_ERROR));
    }

    /* Send the Test mode address SWD packet. Repeat for WAIT ACK till timeout occurs */
    Swd_packetHeader =  TESTMODE_ADDRESS_HEADER;
    Swd_packetData[3] = 0x40;
	Swd_packetData[2] = 0x05;
	Swd_packetData[1] = 0x02;
	Swd_packetData[0] = 0x10;    
    do
    {
        Swd_WritePacketFast(PARITY_TESTMODE_ADDRESS); 
        total_packet_count++;
    }
	while((Swd_packetAck == SWD_WAIT_ACK) && (total_packet_count < DEVICE_ACQUIRE_TIMEOUT));
    
    if(Swd_packetAck != SWD_OK_ACK)
    {
        return((Swd_packetAck | PORT_ACQUIRE_TIMEOUT_ERROR));
    }
    
    /* Send the Test mode key SWD packet. Repeat for WAIT ACK till timeout occurs */
    Swd_packetHeader =  TESTMODE_KEY_HEADER;
    Swd_packetData[3] = 0xEA;
	Swd_packetData[2] = 0x7E;
	Swd_packetData[1] = 0x30;
	Swd_packetData[0] = 0xA9;    
    do
    {
        Swd_WritePacketFast(PARITY_TESTMODE_KEY); 
        total_packet_count++;
    }
	while((Swd_packetAck == SWD_WAIT_ACK) && (total_packet_count < DEVICE_ACQUIRE_TIMEOUT));
    
    /* If the total number of SWD packets sent is higher than the timeout count,
       set the timeout error bit */
    if((total_packet_count > DEVICE_ACQUIRE_TIMEOUT) || (Swd_packetAck != SWD_OK_ACK))
    {
        return((Swd_packetAck | PORT_ACQUIRE_TIMEOUT_ERROR));
    }
    /* If total number of SWD packet tries is less than DEVICE_ACQUIRE_TIMEOUT, Device Acquire Operation is success
       and return OK ACK */
    else
    {
       return(Swd_packetAck); 
    }
}

/*******************************************************************************
* Function Name: ReleaseTargetDevice
********************************************************************************
*
* Summary:
*  Releases the target PSoC 5LP device from Programming mode
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  This function is called by ExitProgrammingMode() in ProgrammingSteps.c to release
*  the target device after completing Programming operation
*
*******************************************************************************/
void ReleaseTargetDevice()
{
    /* Drive the SWDIO, SWDCK outputs low */
    SetSwdckLow();
    SetSwdioLow();
    
    /* Make SWDIO, SWDCK High-Z after completing Programming */    
    SetSwdioHizInput();
    SetSwdckHizInput();
    
    /* Generate active low rest pulse for 100 uS */
    SetXresLow();
    delayMicroseconds(99);
    SetXresHigh();

    /* Make XRES High-Z after generating the reset pulse */  
    SetXresHizInput();
}
