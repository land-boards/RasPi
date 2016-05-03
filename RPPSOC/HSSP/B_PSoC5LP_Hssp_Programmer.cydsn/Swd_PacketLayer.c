/*******************************************************************************
* File Name: Swd_PacketLayer.c
* Version 3.0
*
* Description:
*  This file provides the source code for the packet layer functions of the SWD protocol.
*  This includes SWD Read packet, SWD Write packet.
*
* Note:
*  The functions in SWD packet layer use the bit banging macros, functions
*  in "Swd_PhysicalLayer.h"
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include "Swd_PacketLayer.h"

/* "Swd_PhysicalLayer.h" file contains the bit banging routines for programming */
#include "Swd_PhysicalLayer.h"

/********************************************************************************
*   Global Variable definitions
********************************************************************************/
unsigned char Swd_packetHeader; /* Stores the 8-bit SWD Packet header */
unsigned char Swd_packetAck;    /* Stores the 3-bit SWD Packet ACK data */
unsigned char Swd_packetData[DATA_BYTES_PER_PACKET];  /* 4-byte Read, Write packet data */

/********************************************************************************
*   Function Definitions
********************************************************************************/

/*******************************************************************************
* Function Name: Swd_SendByte
********************************************************************************
*
* Summary:
*  Sends a byte of data on the SWD lines (SWDIO, SWDCK)
*
* Parameters:
*  txByte:
*       Data byte to be sent by host on SWDIO line (Least significant bit sent first)
*
* Return:
*  None.
*
* Note:
*  This function is called for sending SWD header data in SWD Read/Write packets,
*  and also to send data in a SWD Write packet.
*
*******************************************************************************/
static void Swd_SendByte(unsigned char txByte)
{
    unsigned char loop=0;
    
    /* Loop for 8-bits of a byte */
    for(loop = 0; loop < 8; loop++)
    {
        if(txByte & LSB_BIT_MASK) /* Send a '1' */
        {
            SetSwdckLow();
            SetSwdioHigh();
            SetSwdckHigh();
        }
        else  /* Send a '0' */
        {
            SetSwdckLow();
            SetSwdioLow();
            SetSwdckHigh();            
        }
        
        txByte = txByte >> 1; /* Make the next bit to send as LS bit */
    }
}

/*******************************************************************************
* Function Name: Swd_SendByteFast
********************************************************************************
*
* Summary:
*  Sends a byte of data on the SWD lines (SWDIO, SWDCK)
*
* Parameters:
*  txByte:
*       Data byte to be sent by host on SWDIO line (Least significant bit sent first)
*
* Return:
*  None.
*
* Note:
*  1.) This function does the same task as Swd_SendByte() function, but it uses
*      bit banging macros in its definition instead of functions. This is to speed
*      up the function execution time to meet the device acquire timing specifications.
*  2.) This function is called by the function Swd_WritePacketFast() for sending the
*      header byte, data bytes in a SWD Write packet.
*
*******************************************************************************/
static void Swd_SendByteFast(unsigned char txByte)
{
    unsigned char loop=0;
    
    /* Loop for 8-bits of a byte */
    for(loop = 0; loop < 8; loop++)
    {
        if(txByte & LSB_BIT_MASK) /* Send a '1' */
        {
            SWDCK_OUTPUT_LOW;
            SWDIO_OUTPUT_HIGH;
            SWDCK_OUTPUT_HIGH;
        }
        else  /* Send a '0' */
        {
            SWDCK_OUTPUT_LOW;
            SWDIO_OUTPUT_LOW;
            SWDCK_OUTPUT_HIGH;            
        }
        
        txByte = txByte >> 1; /* Make the next bit to send as LS bit */
    }
}

/*******************************************************************************
* Function Name: Swd_ReceiveByte
********************************************************************************
*
* Summary:
*  Receives a byte of data on the SWD lines (SWDIO, SWDCK)
*
* Parameters:
*  None.
*
* Return:
*  rxByte:
*       Data byte received by host on SWDIO line (Least significant bit is first received bit)
* Note:
*  This function is called for reading data bytes in a SWD Read Packet
*
*******************************************************************************/
static unsigned char Swd_ReceiveByte()
{
    unsigned char loop=0;
    unsigned char rxBit = 0;
    unsigned char rxByte = 0;
    
    /* Loop for 8-bits of a byte */
    for(loop = 0; loop < 8; loop++)
    {
        SetSwdckLow();
        rxBit = ReadSwdio(); /* Read the SWDIO input line */
        SetSwdckHigh();
        
        rxByte = rxByte >> 1;
        
        if(rxBit) /* Received a '1' */
        {
            rxByte = rxByte | MSB_BIT_MASK;
        }
        else /* Received a '0' */
        {
            rxByte = rxByte & (~MSB_BIT_MASK);   
        }  
        
    }
    
    return(rxByte);
}

/*******************************************************************************
* Function Name: Swd_FirstTurnAroundPhase
********************************************************************************
*
* Summary:
*  Generates one SWDCK clock cycle for Turnaround phase of a SWD packet.
*  SWDIO drive mode is changed to High-Z drive mode so that the host can read the data on the SWDIO.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  This function is called during SWD Read/Write packets
*
*******************************************************************************/
static void Swd_FirstTurnAroundPhase()
{
    SetSwdioHizInput(); /* Change to High-Z drive mode for host to read the SWDIO line */
    
    SetSwdckLow();
    SetSwdckHigh();
}

/*******************************************************************************
* Function Name: Swd_SecondTurnAroundPhase
********************************************************************************
*
* Summary:
*  Generates one SWDCK clock cycle for Turnaround phase of a SWD packet.
*  SWDIO drive mode is changed to CMOS output drive mode so that the host can write data on SWDIO.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  This function is called during SWD Read/Write packets
*
*******************************************************************************/
static void Swd_SecondTurnAroundPhase()
{
    SetSwdioCmosOutput(); /* Change to CMOS output drive mode for host to write to SWDIO */
    
    SetSwdckLow();
    SetSwdckHigh();
}

/*******************************************************************************
* Function Name: Swd_GetAckSegment
********************************************************************************
*
* Summary:
*  Gets the 3-bit ACK response in a SWD packet
*
* Parameters:
*  None.
*
* Return:
*  ack:
*   3-bit ACK response is returned as a byte. Three possible return values are:
*       0x01 - SWD_OK_ACK
*       0x02 - SWD_WAIT_ACK
*       0x04 - SWD_FAULT_ACK
*       Any other return value - Undefined ACK code.
*                                Treat it similar to SWD_FAULT_ACK and abort operation.
*
* Note:
*  This function is called during SWD Read/Write packets
*
*******************************************************************************/
static unsigned char Swd_GetAckSegment()
{
    unsigned char ack = 0;
    unsigned char rxBit = 0;
    unsigned char loop = 0;
    
    /* ACK bits are received lsb bit first */
    for(loop = 0; loop < NUMBER_OF_ACK_BITS; loop++)
    {
        SetSwdckLow();
        rxBit = ReadSwdio(); /* Store the ACK bit received */
        SetSwdckHigh();
        
        ack = ack | (rxBit << loop); /* Concatenate the ACK bit with ACK data byte */
    }
    
    return(ack);   
}

/*******************************************************************************
* Function Name: Swd_SendParity
********************************************************************************
*
* Summary:
*  Sends the 1-bit parity data on SWD lines
*
* Parameters:
*  parity:
*    1-bit parity data received as a byte (either '1' or '0')
*
* Return:
*  None.
*
* Note:
*  This function is called during SWD Write packet
*
*******************************************************************************/
static void Swd_SendParity(unsigned char parity)
{
    /* Make the clock low, Send SWDIO data, Make Clock high */
    
    SetSwdckLow();
    if(parity)
    {
        SetSwdioHigh();
    }
    else
    {
        SetSwdioLow();
    }
    SetSwdckHigh();    
}

/*******************************************************************************
* Function Name: Swd_ReceiveParity
********************************************************************************
*
* Summary:
*  Receives the 1-bit parity data on SWD lines
*
* Parameters:
*  None.
*
* Return:
*  parity:
*    1-bit parity data returned as a byte (either '1' or '0')
*
* Note:
*  This function is called during SWD Read packet
*
*******************************************************************************/
static unsigned char Swd_ReceiveParity()
{
    unsigned char parity;
    
    /* Make the clock low, Read SWDIO data, Make Clock high */
    
    SetSwdckLow();
    parity = ReadSwdio();
    SetSwdckHigh();    
    
    return(parity);
}

/*******************************************************************************
* Function Name: Swd_SendDummyClocks
********************************************************************************
*
* Summary:
*  Sends three SWDCK clock cycles with SWDIO line held low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  This function is called during SWD Read/Write packets.
*
*******************************************************************************/
static void Swd_SendDummyClocks()
{
    unsigned char loop;
    
    /* Send three SWDCK clock cycles with SWDIO line held low */   
    SetSwdioLow();
    for(loop = 0; loop < NUMBER_OF_DUMMY_SWD_CLOCK_CYCLES; loop++)
    {
       SetSwdckLow();       
       SetSwdckHigh(); 
    }
}

/*******************************************************************************
* Function Name: Swd_CountOneBits
********************************************************************************
*
* Summary:
*  Counts the number of 1's in a byte
*
* Parameters:
*  dataByte:
*   Byte for which the number of 1's need to be found
*
* Return:
*  count:
*   Number of 1's present in dataByte
*
* Note:
*  This function is used for computing parity of data
*
*******************************************************************************/
static unsigned char Swd_CountOneBits(unsigned char dataByte)
{
    unsigned char count = 0;
    unsigned char i;
    
    /* Loop for 8-bits of a byte */
    /* Increment count variable if LS bit is set */
    for(i = 0; i < 8; i++)
    {
        if(dataByte & LSB_BIT_MASK)
        {
            count++; 
        }
        
        dataByte = dataByte >> 1;
    }
    
    return(count);
}

/*******************************************************************************
* Function Name: Swd_ComputeDataParity
********************************************************************************
*
* Summary:
*  Computes Even parity  of 4-byte data
*
* Parameters:
*  Swd_packetData[DATA_BYTES_PER_PACKET] - Global variable that holds the data
*
* Return:
*   Even parity bit
*   0x01 - Parity is '1' if 4-byte data has an odd number of 1's
*   0x00 - Parity is '0' if 4-byte data has an even number of 1's
*
* Note:
*  This function is called during SWD Read/Write packets
*
*******************************************************************************/
static unsigned char Swd_ComputeDataParity()
{
    unsigned char count = 0;
    unsigned char i;
    
    /* Count number of 1's in 4-byte data */
    for(i = 0; i < DATA_BYTES_PER_PACKET; i++)
    {
        count = count + Swd_CountOneBits(Swd_packetData[i]);
    }
    
    /* Return even parity. If Lsb bit is 1, it implies the number of 1's is odd,
    and hence the even parity bit is set. For even number of 1's, parity bit is 0 */
    return(count & LSB_BIT_MASK);
}

/*******************************************************************************
* Function Name: Swd_RawReadPacket
********************************************************************************
*
* Summary:
*  Sends a single SWD Read packet
*
* Parameters:
*  Swd_packetHeader - Global variable that holds the 8-bit header data for packet
*
* Return:
*  Swd_packetData[DATA_BYTES_PER_PACKET] - Global variable that holds the 4-byte data that has been read
*
*  Swd_packetAck - Global variable that holds the status of the SWD transaction
*    ACK response is stored as a byte. Three possible ACK return values are:
*       0x01 - SWD_OK_ACK
*       0x02 - SWD_WAIT_ACK
*       0x04 - SWD_FAULT_ACK
*       0x09 - SWD_OK_ACK, but Parity error in data received
*       Any other ACK value - Undefined ACK code.
*                             Treat it similar to SWD_FAULT_ACK and abort operation.
*
* Note:
*  1.)Swd_RawReadPacket() is called during SPC Polling operations when the host must read the
*     SPC status register continuously till a Programming operation is completed or data is ready to be read.
*
*  2.)This function is called duing continuous multi byte read operations from the SPC_DATA register
*  
*  3.)This function is called during IDCODE instruction for reading the Device DEVICE SILICON ID
*
*  4.)This function is not called during normal SWD read transactions. To read a register data,
*     two SWD Read packets must be sent (call this function twice). This method of reading twice
*     has been implemented in SWD_ReadPacket() function which will be called during normal read transactions. 
*
********************************************************************************/
void Swd_RawReadPacket()
{
    unsigned char parity;
    unsigned char loop = 0;
    unsigned char i;
    
    do
    {
        Swd_SendByte(Swd_packetHeader); /* 8-bit Header data */       
                
        Swd_FirstTurnAroundPhase();   /* First Turnaround phase */
        
        Swd_packetAck = Swd_GetAckSegment(); /* Get the 3-bit ACK data */
        
        /* Read 4-byte data and store in Global array Swd_packetData[] */
        for(i = 0; i < DATA_BYTES_PER_PACKET; i++)
        {
            Swd_packetData[i] = Swd_ReceiveByte();
        }
        
        parity = Swd_ReceiveParity(); /* Parity phase */        
        
        Swd_SecondTurnAroundPhase();  /* Second Turnaround phase */
        
        Swd_SendDummyClocks();  /* Dummy clock phase since clock is not free running */
		
		loop++;
        
        /* Repeat for a WAIT ACK till timeout loop expires */
        
    }while((Swd_packetAck == SWD_WAIT_ACK ) && (loop < NUMBER_OF_WAIT_ACK_LOOPS));
    
    /* For a OK ACK, check the parity bit received with parity computed */
    if(Swd_packetAck == SWD_OK_ACK)
    {
        if(parity != Swd_ComputeDataParity())
        {
            Swd_packetAck = Swd_packetAck | SWD_PARITY_ERROR; /* Set the Parity error bit in ACK code */
        }
    }
    
    /* Swd_packetAck global variable holds the status of the SWD transaction */
}

/*******************************************************************************
* Function Name: Swd_ReadPacket
********************************************************************************
*
* Summary:
*  Sends a SWD Read packet twice to perform an actual SWD read operation
*
* Parameters:
*  Swd_packetHeader - Global variable that holds the 8-bit header data for packet
*
* Return:
*  Swd_packetData[DATA_BYTES_PER_PACKET] - Global variable that holds the 4-byte data that has been read
*
*  Swd_packetAck - Global variable that holds the status of the SWD transaction
*    ACK response is stored as a byte. Three possible ACK values are:
*       0x01 - SWD_OK_ACK
*       0x02 - SWD_WAIT_ACK
*       0x04 - SWD_FAULT_ACK
*       0x09 - SWD_OK_ACK, but Parity error in data received
*       Any other ACK value - Undefined ACK code.
*                             Treat it similar to SWD_FAULT_ACK and abort operation.
*
* Note:
*  1.)Swd_ReadPacket() function is called during normal SWD read transactions. To read a register data,
*     two SWD Read packets must be sent. This method of reading twice  has been implemented in this SWD_ReadPacket() function.  
*
********************************************************************************/
void Swd_ReadPacket()
{
    /* First SWD read transaction only initiates register read on Target PSoC 5LP
       The second read packet returns the original data */
       
    Swd_RawReadPacket();
    
    /* Stop transaction if OK ACK has not been received */
    if(Swd_packetAck != SWD_OK_ACK)
    {
        /* Swd_packetAck global variable holds the status of the SWD transaction */
        return;
    }
    
    /* Second SWD read transaction reads the actual data */
    Swd_RawReadPacket(); 

    /* Swd_packetAck global variable holds the status of the SWD transaction */
    /* Swd_packetData[] global array holds the 4-byte data that has been read */
}

/*******************************************************************************
* Function Name: Swd_WritePacket
********************************************************************************
*
* Summary:
*  Sends a single SWD Write packet
*
* Parameters:
*  Swd_packetHeader - Global variable that holds the 8-bit header data for packet
*  Swd_packetData[DATA_BYTES_PER_PACKET] - Global variable that holds the data to be sent
*
* Return:
*  Swd_packetAck - Global variable that holds the status of the SWD transaction
*    ACK response is stored as a byte. Three possible ACK return values are:
*       0x01 - SWD_OK_ACK
*       0x02 - SWD_WAIT_ACK
*       0x04 - SWD_FAULT_ACK
*       Any other ACK value - Undefined ACK code.
*                             Treat it similar to SWD_FAULT_ACK and abort operation.
*
* Note:
*  This function is called for Address Write, Data Write operations
*
********************************************************************************/
void Swd_WritePacket()
{
    unsigned char parity;
    unsigned char loop = 0;
    unsigned char i;
    
    parity = Swd_ComputeDataParity(); /* Compute Even parity for 4-byte data */  
    
    do
    {
        Swd_SendByte(Swd_packetHeader); /* 8-bit Header data */
        
        Swd_FirstTurnAroundPhase();   /* First Turnaround phase */
        
        Swd_packetAck = Swd_GetAckSegment();  /* Get the 3-bit ACK data */
        
        Swd_SecondTurnAroundPhase();   /* Second Turnaround phase */
        
        /* Send 4-byte data stored in Global array Swd_packetData[] */
        for(i = 0; i < DATA_BYTES_PER_PACKET; i++)
        {
            Swd_SendByte(Swd_packetData[i]); 
        }
        
        Swd_SendParity(parity);  /* Parity phase */
        
        Swd_SendDummyClocks();   /* Dummy clock phase since clock is not free running */
        
        loop++;
        
        /* Repeat for a WAIT ACK till timeout loop expires */
        
    }while((Swd_packetAck == SWD_WAIT_ACK ) && (loop < NUMBER_OF_WAIT_ACK_LOOPS));
    
    /* Swd_packetAck global variable holds the status of the SWD transaction */
}

/*******************************************************************************
* Function Name: Swd_WritePacketFast
********************************************************************************
*
* Summary:
*  Sends a single SWD Write packet
*
* Parameters:
*  Swd_packetHeader - Global variable that holds the 8-bit header data for packet
*  Swd_packetData[DATA_BYTES_PER_PACKET] - Global variable that holds the data to be sent
*  dataParityBit - Precalculated even parity bit of the 4-byte data in Swd_packetData[]
*
* Return:
*  Swd_packetAck - Global variable that holds the status of the SWD transaction
*    ACK response is stored as a byte. Three possible ACK return values are:
*       0x01 - SWD_OK_ACK
*       0x02 - SWD_WAIT_ACK
*       0x04 - SWD_FAULT_ACK
*       Any other ACK value - Undefined ACK code.
*                             Treat it similar to SWD_FAULT_ACK and abort operation.
*
* Note:
*  1.) This function is a modified implementation of Swd_WritePacket() optimized for
*      execution time to meet the timing requirements to acquire the Target PSoC 5LP device
*  2.) The function is defined using the bit banging macros in Swd_PhysicalLayer.h
*  3.) The function expects the precalculated even parity bit of the 4-byte SWD packet
*      data as one of its parameters to speed up the time to send SWD packer
*  4.) It sends the SWD packet only once for any SWD ACK data received
*  5.) No "for" loops are used for iterative operations like reading 3-bit ACK data,
*      sending 4 data bytes, sending dummy clock cycles to speed up execution
*  6.) This function is called by AcquireTargetDevice() in DeviceAcquire.c.
*
********************************************************************************/
void Swd_WritePacketFast(unsigned char dataParityBit)
{
    
    Swd_packetAck = 0;
    
    /* 8-bit Header data.
       Use the time optimized function Swd_SendByteFast() to send byte */
    Swd_SendByteFast(Swd_packetHeader); 
    
    /* First Turnaround phase */
    SWDIO_DRIVEMODE_HIGHZIN; /* Change to High-Z to read ACK data */  
    SWDCK_OUTPUT_LOW;
    SWDCK_OUTPUT_HIGH; 
 
    SWDCK_OUTPUT_LOW;
    Swd_packetAck = Swd_packetAck | (SWDIO_INPUT_READ); // Concatenate the 1st ACK bit with ACK data byte 
    SWDCK_OUTPUT_HIGH;
    
    SWDCK_OUTPUT_LOW;
    Swd_packetAck = Swd_packetAck | (SWDIO_INPUT_READ << 1); // Concatenate the 2nd ACK bit with ACK data byte 
    SWDCK_OUTPUT_HIGH;    

    SWDCK_OUTPUT_LOW;
    Swd_packetAck = Swd_packetAck | (SWDIO_INPUT_READ << 2); // Concatenate the 3rd ACK bit with ACK data byte 
    SWDCK_OUTPUT_HIGH;    
    
    /* Second Turnaround phase */
    SWDIO_DRIVEMODE_CMOSOUT;
    SWDCK_OUTPUT_LOW;
    SWDCK_OUTPUT_HIGH;   
    
    /* Send 4-byte data stored in Global array Swd_packetData[].
       Use the time optimized function Swd_SendByteFast() to send bytes */
    Swd_SendByteFast(Swd_packetData[0]); 
    Swd_SendByteFast(Swd_packetData[1]); 
    Swd_SendByteFast(Swd_packetData[2]); 
    Swd_SendByteFast(Swd_packetData[3]); 

    /* Parity phase */
    SWDCK_OUTPUT_LOW;
    if(dataParityBit)
    {
        SWDIO_OUTPUT_HIGH;
    }
    else
    {
        SWDIO_OUTPUT_LOW;
    }
    SWDCK_OUTPUT_HIGH;
    
    /* Dummy clock phase since clock is not free running */
    SWDIO_OUTPUT_LOW;       
    
    /* First Dummy clock */
    SWDCK_OUTPUT_LOW;       
    SWDCK_OUTPUT_HIGH; 
    
    /* Second Dummy clock */
    SWDCK_OUTPUT_LOW;       
    SWDCK_OUTPUT_HIGH;

    /* Third Dummy clock */
    SWDCK_OUTPUT_LOW;       
    SWDCK_OUTPUT_HIGH;    
    
    /* Swd_packetAck global variable holds the status of the SWD transaction */
}

/*******************************************************************************
* Function Name: SwdLineReset
********************************************************************************
*
* Summary:
*  Resets the SWD line by sending 51 SWDCK clock cycles with SWDIO line high
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  This function is called as part of SWD switching sequence
*
*******************************************************************************/
static void SwdLineReset()
{
    unsigned char i;
     
    /* To reset SWD line,  clock more than 50 SWDCK clock cycles with SWDIO high.   */ 
       
    SetSwdioHigh();
    
    for(i = 0; i < NUMBER_OF_SWD_RESET_CLOCK_CYCLES; i++)
    {
        SetSwdckLow();
        SetSwdckHigh();        
    }    
}

/*******************************************************************************
* Function Name: SwdLineIdle
********************************************************************************
*
* Summary:
*  Brings the SWD line that to Reset state and then to idle state by clocking 3 clock cycles with SWDIO low
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  This function is called as part of SWD switching sequence
*
*******************************************************************************/
static void SwdLineIdle()
{
    unsigned char i;
    
    /* SWD line is reset in case it is not done before calling this function */
    SwdLineReset(); 
    
    /* After SWD line is reset, at least three SWDCK clock cycles must be clocked with SWDIO low. */    
    SetSwdioLow();
    for(i = 0; i < NUMBER_OF_DUMMY_SWD_CLOCK_CYCLES; i++)
    {
        SetSwdckLow();        
        SetSwdckHigh();           
    }    
}

/*******************************************************************************
* Function Name: JtagToSwdSequence
********************************************************************************
*
* Summary:
*  Sends the JTAG to SWD switching sequence bringing the SWD line to idle state
*
* Parameters:
*  None
*
* Return:
*  None
*
* Note:
*  This function is called as part of SWD switching sequence by the function SwitchToSwd() in ProgrammingSteps.c
*
*******************************************************************************/
void JtagToSwdSequence()
{
    SwdLineReset();  /* Reset the SWD line just in case */
    
    /* Send the initial JTAG to SWD 16-bit switching sequence */
    Swd_SendByte(0x9E);
    Swd_SendByte(0xE7);
    
    SwdLineReset();  /* Reset the SWD line  */
    
    SwdLineIdle();   /* Bring the SWD line to idle state */
}

/* [] END OF FILE */
