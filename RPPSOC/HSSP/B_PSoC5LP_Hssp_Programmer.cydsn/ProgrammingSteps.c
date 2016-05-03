/*******************************************************************************
* File Name: ProgrammingSteps.c
* Version 3.0
*
* Description:
*  This file provides the source code for the high level Programming functions used 
*  by the main code to program target device
*
* Note:
*
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include "ProgrammingSteps.h"
#include "Swd_PacketLayer.h"
#include "DeviceAcquire.h"
#include "DataFetch.h"
#include "Timeout.h"
#include "HexImage.h"

/********************************************************************************
*   Function Definitions
********************************************************************************/

/*******************************************************************************
* Function Name: IsSpcIdle
********************************************************************************
*
* Summary:
*  Polls the SPC Status register till it is idle or a timeout condition occurred,
*  whichever is earlier. For a SPC polling timeout error, the timeout error status
*  bit is set in Swd_packetAck variable
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - SPC is now in Idle condition
*  FAILURE - SPC is not in Idle condition, an error occurred
*
* Note:
*  This function is called after non volatile memory operations like Read, Write 
*  of Flash, NVL to check if status register has returned to idle state indicated by success
*  The target PSoC 5LP SPC status register value is present in the third least significant byte
*  in the 4-byte SWD read data
*******************************************************************************/
static unsigned char IsSpcIdle()
{
    unsigned short loop = 0;
    
    /* APACC ADDR Write [0x4000 4722] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x22;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE); 
        
    Swd_packetHeader =  APACC_DATA_READ; /* This header is common to all the below read packets */
    
    /* APACC DATA Read. This is Dummy read as this is first read packet */
    Swd_RawReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* Loop till SPC is not idle and timeout has not happened */
    do
    {
        /* APACC DATA Read */
        Swd_RawReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
            
        loop++;
    }while((Swd_packetData[2] != SPC_STATUS_IDLE) && (loop < SPC_POLLING_TIMEOUT));
    
    if(Swd_packetData[2] == SPC_STATUS_IDLE) /*Return success if Idle */
    {
        return(SUCCESS);
    }
    else /* Set the SPC Timeout error bit and return failure */
    {
        Swd_packetAck = Swd_packetAck | SPC_TIMEOUT_ERROR;
        return(FAILURE);
    }
}

/*******************************************************************************
* Function Name: IsSpcDataReady
********************************************************************************
*
* Summary:
*  Polls the SPC Status register till data is ready or a timeout condition occurred,
*  whichever is earlier. For a SPC polling timeout error, the timeout error status
*  bit is set in Swd_packetAck variable
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - SPC Data register has data to be read
*  FAILURE - SPC Data register has no data to be read, an error occurred
*
* Note:
*  This function is called during non volatile memory Read operations like
*  Flash read, NVL read to check if SPC Data register has data to be read.
*  The target PSoC 5LP SPC status register value is present in the third least significant byte
*  in the 4-byte SWD read data
*
*******************************************************************************/

static unsigned char IsSpcDataReady()
{
    unsigned short loop;
    
    /* APACC ADDR Write [0x4000 4722] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x22;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);  
        
    Swd_packetHeader =  APACC_DATA_READ; /* This header is common to all the below read packets */
    
    /* APACC DATA Read. This is Dummy read as this is first read packet */
    Swd_RawReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    
    loop = 0;
    
    /* Loop till SPC data is not ready and timeout has not happened */
    do
    {
        /* APACC DATA Read */
        Swd_RawReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
            
        loop++;
    }while((Swd_packetData[2] != SPC_STATUS_DATA_READY) && (loop < SPC_POLLING_TIMEOUT));
    
    if(Swd_packetData[2] == SPC_STATUS_DATA_READY) /*Return success if data is ready */
    {
        return(SUCCESS);
    }
    else /* Set the SPC Timeout error bit and return failure */
    {
        Swd_packetAck = Swd_packetAck | SPC_TIMEOUT_ERROR;
        return(FAILURE);
    }
}

/*******************************************************************************
* Function Name: GetDieTemperature
********************************************************************************
*
* Summary:
*  Measures the internal chip temperature. Returns a status value for temperature
*  measurement (SUCCESS or FAILURE)
*
* Parameters:
*  unsigned char * temperatureSign
*    - Pointer to variable where Temperature sign needs to be stored
*  unsigned char * temperatureMagnitude
*    - Pointer to variable where Temperature magnitude needs to be stored
*
* Return:
*  SUCCESS - Die Temperature data successfully received 
*  FAILURE - Die Temperature data not received 
*
* Note:
*  For PSoC 5LP HSSP, this function always returns the room temperature (25 C) and
*  SUCCESS status. This is because the internal die temperature blobk is not accurate
*  in PSoC 5LP.
*
*******************************************************************************/

static unsigned char GetDieTemperature(unsigned char * temperatureSign, unsigned char * temperatureMagnitude)
{
 	/* APACC ADDR Write [0x4000 4720] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
       for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
    Swd_packetHeader =  APACC_DATA_WRITE;
        
    /* APACC DATA Write [0x0000 00B6] */
    Swd_packetData[0] = 0xB6;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE); 
        
    /* APACC DATA Write [0x0000 00E1] */
    Swd_packetData[0] = 0xE1;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
       
    /* APACC DATA Write [0x0000 000E] */
    Swd_packetData[0] = 0x0E;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    
    /* APACC DATA Write [0x0000 0003] */
    Swd_packetData[0] = 0x03;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
        
    if(IsSpcDataReady() == FAILURE)
        return(FAILURE);

    /* APACC ADDR Write [0x4000 4720] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
        
    /* All the below SWD packets have the same header APACC_DATA_READ */        
    Swd_packetHeader =  APACC_DATA_READ;   
    
    /* APACC DATA Read - This is dummy read, next read gets temperature value */
    Swd_RawReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);        

    /* APACC DATA Read */
    Swd_RawReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    
    *temperatureSign = Swd_packetData[0]; /* Store the Sign byte of temperature */

    /* APACC DATA Read */
    Swd_RawReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);

    *temperatureMagnitude = Swd_packetData[0]; /* Store the Magnitude byte of temperature */

    if(IsSpcIdle() == SUCCESS)
        return(SUCCESS);
    else
        return(FAILURE);
}

/*******************************************************************************
* Function Name: SwitchToSwd
********************************************************************************
*
* Summary:
*  Switches the target PSoC 5LP device programming interface to SWD interface
*
* Parameters:
*  None
*
* Return:
*  SUCCESS - Successfully switched to SWD interface
*  FAILURE - SWD interface switching failed 
*
* Note:
*  The initial switching sequence is implemented in the function JtagToSwdSequence()
*  in Swd_PacketLayer.h. The Device ID read (DPACC IDCODE Read) is required to
*  complete the switching to SWD interface. The Device ID code returned by that
*  SWD packet should be ignored. Just sending the DPACC IDCODE Read packet is enough.
*
*******************************************************************************/
static unsigned char SwitchToSwd()
{
    JtagToSwdSequence();  /* Initial part of the switching sequence */
    
    /* DPACC IDCODE Read  */
    Swd_packetHeader =  DPACC_IDOCDE_READ;
    Swd_RawReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
        
    return(SUCCESS);    
    
}

/*******************************************************************************
* Function Name: EnterProgrammingMode
********************************************************************************
*
* Summary:
*  Acquires the target PSoC 5LP device and enters the device Programming mode
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Target PSoC 5LP Programming mode entered successfully 
*  FAILURE - Unable to enter Target PSoC 5LP programming mode 
*
* Note:
*  This function is called during start of device Programming in main code.
*  It calls the function AcquireTargetDevice() in DeviceAcquire.h
*
*******************************************************************************/

unsigned char EnterProgrammingMode()
{
    Swd_packetAck = AcquireTargetDevice();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    else
        return(SUCCESS);
}

/*******************************************************************************
* Function Name: ConfigureTargetDevice
********************************************************************************
*
* Summary:
*  Configures the Target PSoC 5LP device to prepare for programming
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Target PSoC 5LP device configured successfully 
*  FAILURE - Operation failed
*
* Note:
*
*******************************************************************************/

unsigned char ConfigureTargetDevice()
{     
    /* Switch to SWD interface */    
    if(SwitchToSwd() == FAILURE)
        return(FAILURE);
    
    /* DPACC DP CTRLSTAT Write [0x50000000]  */
    Swd_packetHeader =  DPACC_DP_CTRLSTAT_WRITE;
    Swd_packetData[3] = 0x50;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x00;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
        
    /* DPACC DP SELECT Write [0x00000000]  */
    Swd_packetHeader =  DPACC_DP_SELECT_WRITE;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x00;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);        

    /* APACC AP CTRLSTAT Write [0x22000002]  */
    Swd_packetHeader =  APACC_AP_CTRLSTAT_WRITE;
    Swd_packetData[3] = 0x22;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x02;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE); 

    /* APACC ADDR Write [0xE000 EDF0] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0xE0;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0xED;Swd_packetData[0] = 0xF0;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* APACC DATA Write [0xA05F 0001] */
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[3] = 0xA0;Swd_packetData[2] = 0x5F;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x01;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);        

    /* APACC ADDR Write [0x4008 000C] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x08;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x0C;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* APACC DATA Write [0x0000 0002] */
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x02;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE); 
        
    /* APACC ADDR Write [0x4000 43A0] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x43;Swd_packetData[0] = 0xA0;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* APACC DATA Write [0x0000 00BF] */
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0xBF;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);        

    /* APACC ADDR Write [0x4000 4200] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x42;Swd_packetData[0] = 0x00;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* APACC DATA Write [0x0000 0002] */
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x02;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);  
        
        
     /* APACC ADDR Write [0x4000 46E8] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x46;Swd_packetData[0] = 0xE8;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);    
    
    /* APACC DATA Write [0x0000 0040] */
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x40;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
 
    return(SUCCESS);   
}

/*******************************************************************************
* Function Name: VerifyDeviceId
********************************************************************************
*
* Summary:
*  Verifies if the Device under test(DUT) is compatible with hex file
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Target PSoC 5LP device is compatible with hex file to be programmed
*  FAILURE - Operation failed
*
* Note:
*  This step is very important to ensure that the correct hex file is programmed 
*  to the target device. Programming an incompatible hex file to device may
*  result in unintended operation which cannot be guaranteed by Cypress
*******************************************************************************/
unsigned char VerifyDeviceId()
{
    unsigned char i;
    unsigned char deviceSiliconId[DEVICE_SILICON_ID_BYTE_LENGTH];
    
    /* Load the DEVICE SILICON ID data from hex file in to array deviceSiliconId[]  */
    LoadDeviceSiliconId(&deviceSiliconId[0]);

    /* APACC ADDR Write [0x4008 001C] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x08;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0x1C;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);  
        
    /* Read DEVICE SILICON ID */
    Swd_packetHeader =  APACC_DATA_READ;
    Swd_ReadPacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    
    /* Check if the target Device DEVICE SILICON ID and DEVICE SILICON ID in hex file match */
    for(i = 0; i < DEVICE_SILICON_ID_BYTE_LENGTH; i++)
    {
        if(Swd_packetData[i] != deviceSiliconId[i])
        {
            /* Set the verification error bit for DEVICE SILICON ID mismatch and return failure */
            Swd_packetAck = Swd_packetAck | VERIFICATION_ERROR; 
            return(FAILURE);
        }
    }    
        
    return(SUCCESS);
}

/*******************************************************************************
* Function Name: EraseFlash
********************************************************************************
*
* Summary:
*  Erases the entire Flash memory of Target PSoC 5LP device along with protection data
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Flash memory erased successfully 
*  FAILURE - Operation failed
*
* Note:
*
*******************************************************************************/
unsigned char EraseFlash()
{
    /* APACC ADDR Write [0x4000 4720] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
        
    /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
       for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */        
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
    
    /* APACC DATA Write [0x0000 00B6] */
    Swd_packetData[0] = 0xB6;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);  
        
    /* APACC DATA Write [0x0000 00DC] */
    Swd_packetData[0] = 0xDC;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE); 
        
    /* APACC DATA Write [0x0000 0009] */
    Swd_packetData[0] = 0x09;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    
    if(IsSpcIdle() == SUCCESS)
        return(SUCCESS);
    else
        return(FAILURE);
}

/*******************************************************************************
* Function Name: ProgramDeviceConfigNvl
********************************************************************************
*
* Summary:
*  Programs the Device Configuration NVL with the data from hex file
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Device Configuration NVL programmed successfully 
*  FAILURE - Operation failed
*
* Note:
*  To maximize the endurance of the NVL's, the programming is done only if the hex file
*  NVL data is different from NVL data already programmed in device. This checking is done
*  inside this function
*******************************************************************************/
unsigned char ProgramDeviceConfigNvl()
{
    unsigned char byteCount;
    unsigned char updateNvlFlag, enablePullupFlag;
    unsigned char eccBitChangedFlag;
    unsigned char deviceConfigNvl[NVL_BYTE_LENGTH];
    unsigned char deviceConfigNvl_readData[NVL_BYTE_LENGTH];
    
    LoadDeviceConfigNvl(&deviceConfigNvl[0]); /* Load the NVL data from hex file in to array DeviceConfigNvl[] */

      
    /* Read the NVL data already programmed in to the PSoC 5LP device */
    for(byteCount = 0; byteCount < NVL_BYTE_LENGTH; byteCount++)
    {
        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
           for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */            
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00; 
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
          
        /* APACC DATA Write [0x0000 00D6] */
        Swd_packetData[0] = 0xD6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);   
            
        /* APACC DATA Write [0x0000 0003] */
        Swd_packetData[0] = 0x03;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 0080] */
        Swd_packetData[0] = 0x80;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [byteCount] */
        Swd_packetData[0] = byteCount;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        if(IsSpcDataReady() == FAILURE)
            return(FAILURE);

        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 

        /* APACC DATA Read */
        Swd_packetHeader =  APACC_DATA_READ;
        Swd_ReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
        
        deviceConfigNvl_readData[byteCount] = Swd_packetData[0];
        
        if(IsSpcIdle() == FAILURE)
            return(FAILURE);      
    }
    
    updateNvlFlag = 0, eccBitChangedFlag = 0;
	enablePullupFlag = 0;
    
    /* Compare the data read from the device against the data to be 
       programmed. The NVL is programmed only when the data differ.
       This is because the NVL's have less endurance.*/
    for(byteCount = 0; byteCount < NVL_BYTE_LENGTH; byteCount++)
    {
        if(deviceConfigNvl_readData[byteCount] != deviceConfigNvl[byteCount])
        {
            updateNvlFlag = 0x01;
            
            if(byteCount == ECC_BYTE_LOCATION)
            {
                if((deviceConfigNvl_readData[ECC_BYTE_LOCATION] ^ deviceConfigNvl[ECC_BYTE_LOCATION]) & ECC_BIT_MASK )
                   eccBitChangedFlag = 0x01;                
            }
        }
    }
    
    /* Program NVL's if data needs to be updated */
    if(updateNvlFlag == 0x01)
    {
		enablePullupFlag =  ((deviceConfigNvl[2] & 0x80) == 0x80) && ((deviceConfigNvl_readData[0] & 0x0C) != 0x08);
		
		if (enablePullupFlag == 1)
		{
            /* APACC ADDR Write [0x4000 500A] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x50;Swd_packetData[0] = 0x0A;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);	
				
			/* APACC DATA Read */
	        Swd_packetHeader =  APACC_DATA_READ;
	        Swd_ReadPacket();
	        if(Swd_packetAck != SWD_OK_ACK)
	            return(FAILURE);
				
			Swd_packetData[2] = (Swd_packetData[2] & 0xF0) | 0x05;
			
			Swd_WritePacket();
	        if(Swd_packetAck != SWD_OK_ACK)
	            return(FAILURE); 				
		}

        for(byteCount = 0; byteCount < NVL_BYTE_LENGTH; byteCount++)
        {
            /* APACC ADDR Write [0x4000 4720] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
                
            /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
               for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */                
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
            
            /* APACC DATA Write [0x0000 00B6] */
            Swd_packetData[0] = 0xB6;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);        
               
            /* APACC DATA Write [0x0000 00D3] */
            Swd_packetData[0] = 0xD3;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
               
            /* APACC DATA Write [0x0000 0000] */
            Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
               
            /* APACC DATA Write [0x0000 0080] */
            Swd_packetData[0] = 0x80;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);                 
               
            /* APACC DATA Write [byteCount] */
            Swd_packetData[0] = byteCount;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);                
               
            /* APACC DATA Write [deviceConfigNvl[byteCount]] */
            Swd_packetData[0] = deviceConfigNvl[byteCount];
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
            
            if(IsSpcIdle() == FAILURE)
                return(FAILURE);             
        }
        
        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
            
        /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
           for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */            
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00; 
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
           
        /* APACC DATA Write [0x0000 00D9] */
        Swd_packetData[0] = 0xD9;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 0006] */
        Swd_packetData[0] = 0x06;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
           
        /* APACC DATA Write [0x0000 0080] */
        Swd_packetData[0] = 0x80;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);   
            
        if(IsSpcIdle() == FAILURE)
            return(FAILURE);  
    }
    
    /* Reacquire the  device if the ECC NVL bit changed */
    if(eccBitChangedFlag == 0x01)
    {
        if(EnterProgrammingMode() != SUCCESS)
            return(FAILURE);
        if(ConfigureTargetDevice() != SUCCESS)
            return(FAILURE);
    }
    
    return(SUCCESS);    
}


/*******************************************************************************
* Function Name: ProgramFlash
********************************************************************************
*
* Summary:
*  Programs the Flash memory with data from the hex file
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Flash memory programmed successfully 
*  FAILURE - Operation failed
*
* Note:
* 
*******************************************************************************/
unsigned char ProgramFlash()
{
    unsigned char  arrayCount;
    unsigned short rowCount;
    unsigned short rowOffset;
    unsigned short byteCount; 
    unsigned char numOfArrays;
    unsigned short numOfFlashRows;
    unsigned short rowsPerArray;
    unsigned short bytesPerFlashRow;
    unsigned char temperatureSign;
    unsigned char temperatureMagnitude;  
    unsigned char flashRowData[MAXIMUM_BYTES_PER_FLASH_ROW];
    
    numOfFlashRows   = GetFlashRowCount(); /* Get the total number of flash rows in the Target PSoC 5LP device */
    bytesPerFlashRow = GetFlashRowByteSize(); /* Get the number of bytes per Flash row */
    
    numOfArrays = GetFlashArrayCount();  /* Get the total number of flash arrays in the Target PSoC 5LP device */
    
    /* Call the GetDieTemperature function twice. PSoC 5LP device returns the correct temperature value
       only from the second time call of the GetDieTemperature function. */
    if(GetDieTemperature(&temperatureSign, &temperatureMagnitude) == FAILURE)
        return(FAILURE);
    if(GetDieTemperature(&temperatureSign, &temperatureMagnitude) == FAILURE)
        return(FAILURE);

    /* APACC AP CTRLSTAT WRITE [0x22000002] */
    Swd_packetHeader =  APACC_AP_CTRLSTAT_WRITE;
    Swd_packetData[3] = 0x22; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x02;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
    
    /* Do programming operation for all flash arrays */
    for(arrayCount = 0; arrayCount < numOfArrays;arrayCount++)
    {
        /* Calculate the rows in the current flash array. All flash arrays except the last one will have 256 flash rows */
        if(arrayCount == (numOfArrays - 1))
        {
            rowsPerArray = numOfFlashRows - (arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY);
        }
        else
        {
            rowsPerArray = MAXIMUM_ROWS_PER_FLASH_ARRAY;
        }
        
        /* Starting row number of the current flash array */
        rowOffset = arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY;
        
        rowCount = 0;    
        
        /* Program all the flash rows in the array. Two rows (odd, even) are programmed during each loop iteration */
        while(rowCount < rowsPerArray)
        {
            /* Programming of the even number flash row */
            
            /* Get the data to be programmed for the current flash row */
            LoadFlashRowData( (rowCount + rowOffset), bytesPerFlashRow, &flashRowData[0]); 
            
            /* APACC ADDR Write [0x2000 0000] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [[(0x0002 D5B6) | (arrayCount << 24)] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = arrayCount; Swd_packetData[2] = 0x02; Swd_packetData[1] = 0xD5; Swd_packetData[0] = 0xB6;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);   
                
            byteCount = 0;
            
            /* Load the flash row programming data */
            while(byteCount < bytesPerFlashRow)
            {
                /* APACC ADDR Write [(0x20000000) + byteCount + 0x4] */
                Swd_packetHeader =  APACC_ADDR_WRITE;
                Swd_packetData[3] = 0x20;
                Swd_packetData[2] = 0x00;
                Swd_packetData[1] = (unsigned char)(((unsigned long)byteCount + 0x04) >> 8);
                Swd_packetData[0] = (unsigned char)((unsigned long)byteCount + 0x04);
                Swd_WritePacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE); 
                    
                /* APACC DATA Write [d3d2d1d0] */
                Swd_packetHeader =  APACC_DATA_WRITE;
                Swd_packetData[3] = flashRowData[byteCount + 3];
                Swd_packetData[2] = flashRowData[byteCount + 2];
                Swd_packetData[1] = flashRowData[byteCount + 1];
                Swd_packetData[0] = flashRowData[byteCount];
                Swd_WritePacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE);     
                    
                byteCount = byteCount + 4;
            }
            
            /* APACC ADDR Write [[(0x20000000)+ (L - 1) + 0x05] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20;
            Swd_packetData[2] = 0x00;
            Swd_packetData[1] = (unsigned char)(((unsigned long)(bytesPerFlashRow - 1) + 0x05) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)(bytesPerFlashRow - 1) + 0x05);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            /* APACC DATA Write [0xB600 0000] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0xB6; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);              

            /* APACC ADDR Write [0x20000000 + (L - 1) + 0x09] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20;
            Swd_packetData[2] = 0x00;
            Swd_packetData[1] = (unsigned char)(((unsigned long)(bytesPerFlashRow - 1) + 0x09) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)(bytesPerFlashRow - 1) + 0x09);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            /* APACC DATA Write [(0x000007DA) | (arrayCount << 16)] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = arrayCount; Swd_packetData[1] = 0x07; Swd_packetData[0] = 0xDA;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);     

            /* APACC ADDR Write [0x20000000 + (BYTES_PER_FLASH_ROW - 1) + 0xD] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20;
            Swd_packetData[2] = 0x00;
            Swd_packetData[1] = (unsigned char)(((unsigned long)(bytesPerFlashRow - 1) + 0x0D) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)(bytesPerFlashRow - 1) + 0x0D);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            /* APACC DATA Write [(0x00 << 24) | (Temp_Magnitude << 16) | (Temp_Sign << 8) | (rowCount & 0xFF)] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00;
            Swd_packetData[2] = temperatureMagnitude;
            Swd_packetData[1] = temperatureSign;
            Swd_packetData[0] = (unsigned char)(rowCount & 0xFF);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);

            /* APACC ADDR Write [0x4000 7018] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x70; Swd_packetData[0] = 0x18;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0000] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
     
            /* APACC ADDR Write [0x4000 7010] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x70; Swd_packetData[0] = 0x10;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0021]  */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x21;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    

            /* APACC ADDR Write [0x4000 7600] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x76; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0080]  */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x80;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 

            /* APACC ADDR Write [0x4000 7604] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x76; Swd_packetData[0] = 0x04;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x4000 2000]   */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x20; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 

            /* APACC ADDR Write [0x4000 7800] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x78; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  

            /* APACC DATA Write [(0x01FF 0000) + L + 15] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = (unsigned char)(((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15) >> 24);
            Swd_packetData[2] = (unsigned char)(((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15) >> 16);
            Swd_packetData[1] = (unsigned char)(((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);

            /* APACC ADDR Write [0x4000 7804]  */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x78; Swd_packetData[0] = 0x04;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x4720 0000]    */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x47; Swd_packetData[2] = 0x20; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
            
            if(IsSpcIdle() == FAILURE)
                return(FAILURE);

            /* APACC ADDR Write [0x4000 7014]  */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x70; Swd_packetData[0] = 0x14;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0001]    */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x01;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);   
            
            /* Programming of even numbered flash row */
                
            rowCount++;
            
            /* Get the data to be programmed for the current flash row */
            LoadFlashRowData( (rowCount + rowOffset), bytesPerFlashRow, &flashRowData[0]); 

            /* APACC ADDR Write [0x2000 0200] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x02; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0002 D5B6 | (arrayCount << 24)] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = arrayCount; Swd_packetData[2] = 0x02; Swd_packetData[1] = 0xD5; Swd_packetData[0] = 0xB6;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);   
                
            byteCount = 0;
            
            /* Load the flash row programming data */
            while(byteCount < bytesPerFlashRow)
            {
                /* APACC ADDR Write [0x20000000 + byteCount + 0x204] */
                Swd_packetHeader =  APACC_ADDR_WRITE;
                Swd_packetData[3] = 0x20;
                Swd_packetData[2] = 0x00;
                Swd_packetData[1] = (unsigned char)(((unsigned long)byteCount + 0x204) >> 8);
                Swd_packetData[0] = (unsigned char)((unsigned long)byteCount + 0x204);
                Swd_WritePacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE); 
                    
                /* APACC DATA Write [d3d2d1d0] */
                Swd_packetHeader =  APACC_DATA_WRITE;
                Swd_packetData[3] = flashRowData[byteCount + 3];
                Swd_packetData[2] = flashRowData[byteCount + 2];
                Swd_packetData[1] = flashRowData[byteCount + 1];
                Swd_packetData[0] = flashRowData[byteCount];
                Swd_WritePacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE);     
                    
                byteCount = byteCount + 4;
            }
        
            /* APACC ADDR Write [0x20000000 + (BYTES_PER_FLASH_ROW - 1) + 0x205] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20;
            Swd_packetData[2] = 0x00;
            Swd_packetData[1] = (unsigned char)(((unsigned long)(bytesPerFlashRow - 1) + 0x205) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)(bytesPerFlashRow - 1) + 0x205);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            /* APACC DATA Write [0xB600 0000] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0xB6; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);              

            /* APACC ADDR Write [0x20000000 + (BYTES_PER_FLASH_ROW - 1) + 0x209] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20;
            Swd_packetData[2] = 0x00;
            Swd_packetData[1] = (unsigned char)(((unsigned long)(bytesPerFlashRow - 1) + 0x209) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)(bytesPerFlashRow - 1) + 0x209);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            /* APACC DATA Write [0x000007DA | (arrayCount << 16)] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = arrayCount; Swd_packetData[1] = 0x07; Swd_packetData[0] = 0xDA;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);     

            /* APACC ADDR Write [0x20000000 + (BYTES_PER_FLASH_ROW - 1) + 0x20D] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x20;
            Swd_packetData[2] = 0x00;
            Swd_packetData[1] = (unsigned char)(((unsigned long)(bytesPerFlashRow - 1) + 0x20D) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)(bytesPerFlashRow - 1) + 0x20D);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            /* APACC DATA Write[(rowCount & 0xFF) | (0x1901 << 8)] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00;
            Swd_packetData[2] = temperatureMagnitude;
            Swd_packetData[1] = temperatureSign;
            Swd_packetData[0] = (unsigned char)(rowCount) & 0xFF;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);

            /* APACC ADDR Write [0x4000 7028] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x70; Swd_packetData[0] = 0x28;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0100] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x01; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
     
            /* APACC ADDR Write [0x4000 7020] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x70; Swd_packetData[0] = 0x20;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0021]  */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x21;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    

            /* APACC ADDR Write [0x4000 7608] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x76; Swd_packetData[0] = 0x08;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0080]  */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x80;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 

            /* APACC ADDR Write [0x4000 760C] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x76; Swd_packetData[0] = 0x0C;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x4000 2000]   */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x20; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 

            /* APACC ADDR Write [0x4000 7808] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x78; Swd_packetData[0] = 0x08;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  

            /* APACC DATA Write [(0x01FF 0000) + L + 15] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = (unsigned char)(((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15) >> 24);
            Swd_packetData[2] = (unsigned char)(((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15) >> 16);
            Swd_packetData[1] = (unsigned char)(((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15) >> 8);
            Swd_packetData[0] = (unsigned char)((unsigned long)bytesPerFlashRow + 0x01FF0000 + 15);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);

            /* APACC ADDR Write [0x4000 780C]  */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x78; Swd_packetData[0] = 0x0C;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x4720 0200]    */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x47; Swd_packetData[2] = 0x20; Swd_packetData[1] = 0x02; Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
            
            if(IsSpcIdle() == FAILURE)
                return(FAILURE);

            /* APACC ADDR Write [0x4000 7024]  */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x70; Swd_packetData[0] = 0x24;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 0001]    */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00; Swd_packetData[2] = 0x00; Swd_packetData[1] = 0x00; Swd_packetData[0] = 0x01;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);   
                
            rowCount++;        
        }
    }
    
    if(IsSpcIdle() == FAILURE)
        return(FAILURE);        
    return(SUCCESS);
}

/*******************************************************************************
* Function Name: VerifyFlash
********************************************************************************
*
* Summary:
*  Verifies if the Flash memory data programmed and Flash data in hex file match.
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Flash memory data programmed and Flash data in hex file match
*  FAILURE - Operation failed
*
* Note:
*  
*******************************************************************************/

unsigned char VerifyFlash()
{
   
    unsigned char  arrayCount;
    unsigned short rowCount;
    unsigned short rowOffset;
    unsigned short byteCount; 
    unsigned char  numOfArrays;
    unsigned short numOfFlashRows;
    unsigned short rowsPerArray;
    unsigned short bytesPerFlashRow;
    unsigned long  address;  
    unsigned char  flashRowData[MAXIMUM_BYTES_PER_FLASH_ROW];
    unsigned char  flashRowData_readData[MAXIMUM_BYTES_PER_FLASH_ROW];
    
    numOfFlashRows   = GetFlashRowCount(); /* Get the total number of flash rows in the Target PSoC 5LP device */
    bytesPerFlashRow = GetFlashRowByteSize(); /* Get the number of bytes per Flash row */
    
    numOfArrays = GetFlashArrayCount();     /* Get the total number of flash arrays in the Target PSoC 5LP device */
    
    /* Do verify operation for all flash arrays */
    for(arrayCount = 0; arrayCount < numOfArrays;arrayCount++)
    {
        /* Calculate the rows in the current flash array. All flash arrays except the last one will have 256 flash rows */
        if(arrayCount == (numOfArrays - 1))
        {
            rowsPerArray = numOfFlashRows - (arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY);
        }
        else
        {
            rowsPerArray = MAXIMUM_ROWS_PER_FLASH_ARRAY;
        }
        
        /* Starting row number of the current flash array */
        rowOffset = arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY;
        
        rowCount = 0;
    
        /* Do the verification for each flash row of the array in a loop */
        while(rowCount < rowsPerArray)
        {
            /* Get the flash row data that was supposed to be programmed in to the device.
               This data will be compared against the flash row data read from the Target PSoC 5LP device */
            LoadFlashRowData( (rowCount + rowOffset), bytesPerFlashRow, &flashRowData[0]); 
            
            address = rowCount * CODE_BYTES_PER_FLASH_ROW; /* Starting address of the flash row first byte */
            
            /* APACC ADDR Write [0x4000 4720] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
                
            /* APACC DATA Write [0x0000 00B6] */
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0xB6;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);
                
            /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
               for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */             
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
            
            /* APACC DATA Write [0x0000 00D7] */
            Swd_packetData[0] = 0xD7;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
              
            /* APACC DATA Write [0x0000 0004] */
            Swd_packetData[0] = 0x04;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
                
            /* APACC DATA Write [arrayCount] */
            Swd_packetData[0] = arrayCount;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);                 

            /* APACC DATA Write [(address >> 16) & 0xFF] */
            Swd_packetData[1] = 0x00;
            Swd_packetData[0] = (unsigned char) ((address >> 16) & 0xFF);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);       
                
            /* APACC DATA Write [(address >> 8) & 0xFF] */
            Swd_packetData[0] = (unsigned char) ((address >> 8) & 0xFF);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);      
              
            /* APACC DATA Write [address  & 0xFF] */
            Swd_packetData[0] = (unsigned char) (address & 0xFF);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);    
              
            /* APACC DATA Write [0x0000 00FF] */
            Swd_packetData[0] = (unsigned char) (CODE_BYTES_PER_FLASH_ROW - 1);
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);
                
            if(IsSpcDataReady() == FAILURE)
                return(FAILURE);    

            /* APACC ADDR Write [0x4000 4720] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
                
            /* All the below SWD packets have the same header APACC_DATA_READ */             
            Swd_packetHeader =  APACC_DATA_READ;

            /* APACC DATA Read. This is Dummy read as this is first read packet */
            Swd_RawReadPacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
            
            for(byteCount = 0; byteCount < CODE_BYTES_PER_FLASH_ROW; byteCount++)
            {
                /* APACC DATA Read */
                Swd_RawReadPacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE);
                    
                flashRowData_readData[byteCount] = Swd_packetData[0];
            }
			
			/* If ECC is disabled, the ECC region data also needs to be read for verification */
	        if(bytesPerFlashRow == (CODE_BYTES_PER_FLASH_ROW + ECC_BYTES_PER_FLASH_ROW))
	        {
            
	            /* If ECC is disabled, the ECC region data also needs to be read for verification */
	            if(bytesPerFlashRow == (CODE_BYTES_PER_FLASH_ROW + ECC_BYTES_PER_FLASH_ROW))
	            {
	            
	                address = (rowCount * ECC_BYTES_PER_FLASH_ROW) | 0x00800000; /* ECC region address */
	                
	                /* APACC ADDR Write [0x4000 4720] */
	                Swd_packetHeader =  APACC_ADDR_WRITE;
	                Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE); 
	                    
	                /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
	                   for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */                 
	                Swd_packetHeader =  APACC_DATA_WRITE;
	                Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
	                
	                /* APACC DATA Write [0x0000 00B6] */
	                Swd_packetData[0] = 0xB6;
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);        
	                    
	                /* APACC DATA Write [0x0000 00D7] */
	                Swd_packetHeader =  APACC_DATA_WRITE;
	                Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;Swd_packetData[0] = 0xD7;
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);    
	                    
	                /* APACC DATA Write [0x0000 0004] */
	                Swd_packetData[0] = 0x04;
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);  
	                    
	                /* APACC DATA Write [arrayCount] */
	                Swd_packetData[0] = arrayCount;
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);                 
	        
	                /* APACC DATA Write [(address >> 16) & 0xFF] */
	                Swd_packetData[0] = (unsigned char) ((address >> 16) & 0xFF);
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);           
	                    
	                /* APACC DATA Write [(address >> 8) & 0xFF] */
	                Swd_packetData[0] = (unsigned char) ((address >> 8) & 0xFF);
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);      
	                    
	                /* APACC DATA Write [address  & 0xFF] */
	                Swd_packetData[0] = (unsigned char) (address & 0xFF);
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);    
	                    
	                /* APACC DATA Write [0x0000 001F] */
	                Swd_packetData[0] = (unsigned char) (ECC_BYTES_PER_FLASH_ROW - 1);
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);    
	        
	                if(IsSpcDataReady() == FAILURE)
	                    return(FAILURE);    
	        
	                /* APACC ADDR Write [0x4000 4720] */
	                Swd_packetHeader =  APACC_ADDR_WRITE;
	                Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
	                Swd_WritePacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE);
	                    
	                /* All the below SWD packets have the same header APACC_DATA_READ */                 
	                Swd_packetHeader =  APACC_DATA_READ;
	        
	                /* APACC DATA Read. This is Dummy read as this is first read packet */
	                Swd_RawReadPacket();
	                if(Swd_packetAck != SWD_OK_ACK)
	                    return(FAILURE); 
	                
	                /* Read the bytes from the ECC region */
	                for(byteCount = 0; byteCount < ECC_BYTES_PER_FLASH_ROW; byteCount++)
	                {
	                    /* APACC DATA Read */
	                    Swd_RawReadPacket();
	                    if(Swd_packetAck != SWD_OK_ACK)
	                        return(FAILURE);
	                        
	                    flashRowData_readData[CODE_BYTES_PER_FLASH_ROW + byteCount] = Swd_packetData[0];
	                }            
	            } 
			}
            
            /* Compare the flash data read from the device against the actual data to be programmed */
            for(byteCount = 0; byteCount < bytesPerFlashRow; byteCount++)
            {
                if(flashRowData_readData[byteCount] != flashRowData[byteCount])
                {
                    /* Set the verification error bit for Flash data mismatch and return failure */
                    Swd_packetAck = Swd_packetAck | VERIFICATION_ERROR; 
                    return(FAILURE);
                }
            }
            
            rowCount++; /* Next flash row to be verified */
        }
    }
    
    return(SUCCESS);     
}

/*******************************************************************************
* Function Name: ProgramWriteOnceNvl
********************************************************************************
*
* Summary:
*  Programs the Write Once NVL with data from hex file
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Write Once NVL programmed successfully 
*  FAILURE - Operation failed
*
* Note:
*  To maximize the endurance of the NVL's, the programming is done only if the hex file
*  NVL data is different from NVL data already programmed in device. This checking is done
*  inside this function. You can ignore this step if device security feature avaialble 
*  by programming the correct 32-bit key to the Write Once NVL is not required for your application.
*  Refer the device Technical Reference Manual for details on the WO NVL
*******************************************************************************/

unsigned char ProgramWriteOnceNvl()
{
    unsigned char  byteCount;
    unsigned char  updateNvlFlag;
    unsigned char writeOnceNvl[NVL_BYTE_LENGTH];
    unsigned char writeOnceNvl_readData[NVL_BYTE_LENGTH];
    
    LoadWriteOnceNvl(&writeOnceNvl[0]); /* Load the NVL data from hex file in to array WriteOnceNvl[]  */  
    
    /* Read the NVL data already programmed in to the Target PSoC 5LP device */
    for(byteCount = 0; byteCount < NVL_BYTE_LENGTH; byteCount++)
    {
        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
            
        /* APACC DATA Write [0x0000 00D6] */
        Swd_packetData[0] = 0xD6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 0003] */
        Swd_packetData[0] = 0x03;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 00F8] */
        Swd_packetData[0] = 0xF8;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [byteCount] */
        Swd_packetData[0] = byteCount;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        if(IsSpcDataReady() == FAILURE)
            return(FAILURE);

        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 

        /* APACC DATA Read */
        Swd_packetHeader =  APACC_DATA_READ;
        Swd_ReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
        
        writeOnceNvl_readData[byteCount] = Swd_packetData[0];
        
        if(IsSpcIdle() == FAILURE)
            return(FAILURE);      
    }
    
    byteCount = 0;
    updateNvlFlag = 0;
    
    /* Compare the data read from the device against the data to be 
       programmed. The NVL is programmed only when the data differ.
       This is because the NVL's have less endurance.*/    
    for(byteCount = 0; byteCount < NVL_BYTE_LENGTH; byteCount++)
    {
        if(writeOnceNvl_readData[byteCount] != writeOnceNvl[byteCount])
        {
            updateNvlFlag = 0x01;
        }
    }
    
    /* Program the NVL's if data needs to be updated */
    if(updateNvlFlag == 0x01)
    {
        for(byteCount = 0; byteCount < NVL_BYTE_LENGTH; byteCount++)
        {
            /* APACC ADDR Write [0x4000 4720] */
            Swd_packetHeader =  APACC_ADDR_WRITE;
            Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
                
            Swd_packetHeader =  APACC_DATA_WRITE;
            Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00; 
            
            /* APACC DATA Write [0x0000 00B6] */
            Swd_packetData[0] = 0xB6;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);        
               
            /* APACC DATA Write [0x0000 00D3] */
            Swd_packetData[0] = 0xD3;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
               
            /* APACC DATA Write [0x0000 0000] */
            Swd_packetData[0] = 0x00;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);  
               
            /* APACC DATA Write [0x0000 00F8] */
            Swd_packetData[0] = 0xF8;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);                 
               
            /* APACC DATA Write [byteCount] */
            Swd_packetData[0] = byteCount;
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);                
              
            /* APACC DATA Write [WriteOnceNvl[byteCount]] */
            Swd_packetData[0] = writeOnceNvl[byteCount];
            Swd_WritePacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE); 
            
            if(IsSpcIdle() == FAILURE)
                return(FAILURE);             
        }
        
        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
            
        /* APACC DATA Write [0x0000 00D9] */
        Swd_packetData[0] = 0xD9;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        /* APACC DATA Write [0x0000 0006] */
        Swd_packetData[0] = 0x06;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
         
        /* APACC DATA Write [0x0000 00F8] */
        Swd_packetData[0] = 0xF8;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);   
            
        if(IsSpcIdle() == FAILURE)
            return(FAILURE);  
    }
    
    return(SUCCESS);   
}

/*******************************************************************************
* Function Name: ProgramFlashProtection
********************************************************************************
*
* Summary:
*  Programs the Flash Protection settings with Protection data from hex file
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Flash protection settings programmed successfully 
*  FAILURE - Operation failed
*
* Note:
*  You can ignore this step if there is no need for any flash protection in your application.
*  The initital step EraseFlash() sets all the protection bytes in the unprotected configuration.
*******************************************************************************/

unsigned char ProgramFlashProtection()
{
    unsigned char  arrayCount;
    unsigned short byteCount; 
    unsigned char  numOfArrays;
    unsigned short numOfFlashRows;
    unsigned short rowsPerArray;
    unsigned short protectionBytesPerArray;
    unsigned short bytesPerFlashRow; 
    unsigned char  flashRowData[MAXIMUM_BYTES_PER_FLASH_ROW]; 
    unsigned short protectionByteSize;
    unsigned short protectionByteOffset;
	unsigned char temperatureSign;
    unsigned char temperatureMagnitude; 
   
    numOfFlashRows   = GetFlashRowCount(); /* Get the total number of flash rows in the Target PSoC 5LP device */
    bytesPerFlashRow = GetFlashRowByteSize(); /* Get the number of bytes per Flash row */
    
    numOfArrays = GetFlashArrayCount(); /* Get the total number of flash arrays in the Target PSoC 5LP device */   
    
    /* Total number of protection bytes. Each protection byte correspons to four flash rows */ 
    protectionByteSize = (numOfFlashRows / 4); 
    
    protectionByteOffset = 0; /* Protection byte offset in current flash array initialized to zero */
    
    LoadFlashProtectionData(protectionByteSize, &flashRowData[0]); /* Load flash protection data for all flash arrays */    
	
    if(GetDieTemperature(&temperatureSign, &temperatureMagnitude) == FAILURE)
    return(FAILURE);
    
    /* Do programming operation for all flash arrays */
    for(arrayCount = 0; arrayCount < numOfArrays; arrayCount++)
    {
        /* Calculate the rows in the current flash array. All flash arrays except the last one will have 256 flash rows */
        if(arrayCount == (numOfArrays - 1))
        {
            rowsPerArray = numOfFlashRows - (arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY);
        }
        else
        {
            rowsPerArray = MAXIMUM_ROWS_PER_FLASH_ARRAY;
        }
        
        /* Protection byte count in the current flash array */
        protectionBytesPerArray = rowsPerArray/4;       
                
        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00; 
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
      
        /* APACC DATA Write [0x0000 00D5] */
        Swd_packetData[0] = 0xD5;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
      
        /* APACC DATA Write [0x0000 0002] */
        Swd_packetData[0] = 0x02;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
         
        /* APACC DATA Write [arrayCount] */
        Swd_packetData[0] = arrayCount;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
        
        for(byteCount = 0; byteCount < bytesPerFlashRow; byteCount++)
        {
            if(byteCount < protectionBytesPerArray)
            {
                /* APACC DATA Write [Protection byte] */
                Swd_packetData[0] = flashRowData[protectionByteOffset];
                Swd_WritePacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE); 
                    
                protectionByteOffset++; 
            }
            else
            {
                /* APACC DATA Write [0x0000 0000] */
                Swd_packetData[0] = 0x00;
                Swd_WritePacket();
                if(Swd_packetAck != SWD_OK_ACK)
                    return(FAILURE);            
            }
        }    
                       
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);       

        /* APACC DATA Write [0x0000 00DE]  */
        Swd_packetData[0] = 0xDE;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);   
            
        /* APACC DATA Write [0x0000 000B] */
        Swd_packetData[0] = 0x0B;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [arrayCount] */
        Swd_packetData[0] = arrayCount;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 0000]*/
        Swd_packetData[0] = 0x00;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
			
		/* APACC DATA Write [Temp_Sign] */
        Swd_packetData[0] = temperatureSign;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
			
		/* APACC DATA Write [Temp_Magnitude]*/
        Swd_packetData[0] = temperatureMagnitude;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);

        if(IsSpcIdle() == FAILURE)
            return(FAILURE);            
    }    
    return(SUCCESS);
}

/*******************************************************************************
* Function Name: VerifyFlashProtection
********************************************************************************
*
* Summary:
*  Verifies if the Flash protection data programmed and Flash protection data in hex file match.
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Flash protection data programmed and Flash protection in hex file match
*  FAILURE - Operation failed
*
* Note:
*  Skip this step if there is a no need for Flash protection
*  in your application (ProgramFlashProtection() step should have been skipped)
*  
*******************************************************************************/
unsigned char VerifyFlashProtection()
{    
    unsigned char arrayCount;
    unsigned short byteCount; 
    unsigned char numOfArrays;
    unsigned short numOfFlashRows;
    unsigned short rowsPerArray;
    unsigned short protectionBytesPerArray;
    unsigned char flashRowData[MAXIMUM_BYTES_PER_FLASH_ROW];
    unsigned char flashRowData_readData[MAXIMUM_BYTES_PER_FLASH_ROW];
 
    unsigned short protectionByteSize;
    unsigned short protectionByteOffset;
   
    numOfFlashRows   = GetFlashRowCount(); /* Get the total number of flash rows in the Target PSoC 5LP device */
    
    numOfArrays = GetFlashArrayCount(); /* Get the total number of flash arrays in the Target PSoC 5LP device */ 
    
    /* Total number of protection bytes. Each protection byte correspons to four flash rows */
    protectionByteSize = (numOfFlashRows / 4);
    
    protectionByteOffset = 0;  /* Protection byte offset in current flash array initialized to zero */
    
    LoadFlashProtectionData(protectionByteSize, &flashRowData[0]); /* Load flash protection data for all flash arrays */      
    
    /* Do verify operation for all flash arrays */    
    for(arrayCount = 0; arrayCount < numOfArrays; arrayCount++)
    {   
        /* Calculate the rows in the current flash array. All flash arrays except the last one will have 256 flash rows */
        if(arrayCount == (numOfArrays - 1))
        {
            rowsPerArray = numOfFlashRows - (arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY);
        }
        else
        {
            rowsPerArray = MAXIMUM_ROWS_PER_FLASH_ARRAY;
        }
        
        protectionBytesPerArray = rowsPerArray/4; /* Protection byte count in the current flash array */  

        /* Read the flash protection data from the Target PSoC 5LP device */

        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);   
            
        /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
           for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */         
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;  
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
          
        /* APACC DATA Write [0x0000 00DD] */
        Swd_packetData[0] = 0xDD;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 000A] */
        Swd_packetData[0] = 0x0A;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
            
        /* APACC DATA Write [arrayCount] */
        Swd_packetData[0] = arrayCount;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);     
           
        /* APACC DATA Write [0x0000 0000] */
        Swd_packetData[0] = 0x00;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);    

        if(IsSpcDataReady() == FAILURE)
            return(FAILURE);    

        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        /* All the below SWD packets have the same header APACC_DATA_READ */ 
        Swd_packetHeader =  APACC_DATA_READ;

        /* APACC DATA Read. This is Dummy read as this is first read packet */
        Swd_RawReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
        
        /* Store the protection bytes read from the Target PSoC 5LP device.
           Even if the protection byte size is maximum of 64, 256 bytes
           will be read in this step. The rest of the bytes will not be used
           for comparison */
        for(byteCount = 0; byteCount < CODE_BYTES_PER_FLASH_ROW; byteCount++)
        {
            /* APACC DATA Read */
            Swd_RawReadPacket();
            if(Swd_packetAck != SWD_OK_ACK)
                return(FAILURE);
                
            if(byteCount < protectionBytesPerArray)
            {                
                flashRowData_readData[protectionByteOffset] = Swd_packetData[0];               
                protectionByteOffset++;
            }
        }       
    }
    
    /* Compare the protection bytes read from the device
    with the actual data to be programmed */
    for(byteCount = 0; byteCount < protectionByteSize; byteCount++)
    {
        if(flashRowData_readData[byteCount] != flashRowData[byteCount])
        {
            /* Set the verification error bit for Flash protection data mismatch and return failure */
            Swd_packetAck = Swd_packetAck | VERIFICATION_ERROR; 
            return(FAILURE);
        }
    }
     
    return(SUCCESS);
}

/*******************************************************************************
* Function Name: VerifyChecksum
********************************************************************************
*
* Summary:
*  Verifies if the Checksum of Flash memory data and Checksum data in hex file match.
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Checksum data of Flash memory and Checksum data in hex file match
*  FAILURE - Operation failed
*
* Note:
*  
*******************************************************************************/
unsigned char VerifyChecksum()
{
    unsigned char checksumData[CHECKSUM_BYTE_LENGTH];
    unsigned char checksumData_readData[CHECKSUM_BYTE_LENGTH];    
    unsigned short runningChecksum = 0;    
    unsigned char arrayCount;
    unsigned short byteCount; 
    unsigned char numOfArrays;
    unsigned short numOfFlashRows;
    unsigned short rowsPerArray;
    
    runningChecksum = 0; /* Initialize the checksum of all flash arrays to zero */
   
    numOfFlashRows   = GetFlashRowCount(); /* Get the total number of flash rows in the Target PSoC 5LP device */
    
    numOfArrays = GetFlashArrayCount(); /* Get the total number of flash arrays in the Target PSoC 5LP device */ 
    
    /* Get the checksum data from the hex file. This will be the reference for checksum verification */    
    LoadChecksumData(&checksumData[0]);   
    
    /* Cumulatively calculate checksum for all flash arrays */ 
    for(arrayCount = 0; arrayCount < numOfArrays; arrayCount++)
    {
        /* Calculate the rows in the current flash array. All flash arrays except the last one will have 256 flash rows */
        if(arrayCount == (numOfArrays - 1))
        {
            rowsPerArray = numOfFlashRows - (arrayCount * MAXIMUM_ROWS_PER_FLASH_ARRAY);
        }
        else
        {
            rowsPerArray = MAXIMUM_ROWS_PER_FLASH_ARRAY;
        }
    
        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
            
        /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
           for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */          
        Swd_packetHeader =  APACC_DATA_WRITE;
        Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;
        
        /* APACC DATA Write [0x0000 00B6] */
        Swd_packetData[0] = 0xB6;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);   
      
        /* APACC DATA Write [0x0000 00DF] */
        Swd_packetData[0] = 0xDF;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
           
        /* APACC DATA Write [0x0000 000C] */
        Swd_packetData[0] = 0x0C;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
           
        /* APACC DATA Write [arrayCount] */
        Swd_packetData[0] = arrayCount;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);     
           
        /* APACC DATA Write [0x0000 0000] */
        Swd_packetData[0] = 0x00;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);    
           
        /* APACC DATA Write [0x0000 0000] */
        Swd_packetData[0] = 0x00;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);     
           
        /* APACC DATA Write [0x0000 0000] */
        Swd_packetData[0] = 0x00;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
           
        /* APACC DATA Write [Number of rows minus one] */
        Swd_packetData[0] = (unsigned char) (rowsPerArray - 1);
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);

        if(IsSpcDataReady() == FAILURE)
            return(FAILURE);    

        /* APACC ADDR Write [0x4000 4720] */
        Swd_packetHeader =  APACC_ADDR_WRITE;
        Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
        Swd_WritePacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        /* All the below SWD packets have the same header APACC_DATA_READ */          
        Swd_packetHeader =  APACC_DATA_READ;

        /* APACC DATA Read. This is Dummy read as this is first read packet */
        Swd_RawReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
        
        /* Device returns 4-byte checksum, but the hex file has only
           the LSB 2-byte checksum. So ignore the first two MSB bytes read from the device */
        Swd_RawReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);        
        Swd_RawReadPacket();
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE); 
            
        Swd_RawReadPacket();
        checksumData_readData[1] = Swd_packetData[0];
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);  
            
        Swd_RawReadPacket();
        checksumData_readData[0] = Swd_packetData[0];
        if(Swd_packetAck != SWD_OK_ACK)
            return(FAILURE);
        
        /* Add the current flash array checksum to the running checksum of all flash arrays */
        runningChecksum = runningChecksum + (((unsigned short)(checksumData_readData[1])) << 8) + (unsigned short)(checksumData_readData[0]);
            
        if(IsSpcIdle() == FAILURE)
            return(FAILURE); 
    }
    
    /* Split the running 16-bit checksum in to two bytes */
    checksumData_readData[0] = (unsigned char) (runningChecksum & 0xFF);
    checksumData_readData[1] = (unsigned char) ((runningChecksum >> 8) & 0xFF);
    
    /* Compare the 2-byte checksum read from Target PSoC 5LP with the 2-byte checksum from the hex file */
    for(byteCount = 0; byteCount < CHECKSUM_BYTE_LENGTH; byteCount++)
    {
        if(checksumData_readData[byteCount] != checksumData[byteCount])
        {
            /* Set the verification error bit for Checksum data mismatch and return failure */
            Swd_packetAck = Swd_packetAck | VERIFICATION_ERROR; 
            return(FAILURE);
        }
    }
    
    return(SUCCESS);
}

#if (EEPROM_DATA_PRESENT_HEX_FILE)

/*******************************************************************************
* Function Name: ProgramEeprom
********************************************************************************
*
* Summary:
*  Erases the entire EEPROM memory, and then programs the rows with the required
*  data
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - EEPROM programmed successfully 
*  FAILURE - Operation failed
*
* Note:
*	
*******************************************************************************/
unsigned char ProgramEeprom()
{
	unsigned char i;
    unsigned char loop_final;
    unsigned char j;     
    unsigned char temperatureSign;
    unsigned char temperatureMagnitude;  
    unsigned char eepromRowData[EEPROM_ROW_BYTE_SIZE_HEX_FILE];
	
	/* Get the number of EEPROM sectors by pasring the EEPROM data in the hex file */
	loop_final = GetEepromSectorCount();	

	
	/* Power the EEPROM memory before doing any operations */    
	
    /* APACC ADDR Write [0x4000 43AC] */
    Swd_packetHeader =  APACC_ADDR_WRITE;
    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x43;Swd_packetData[0] = 0xAC;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
	
	/* APACC DATA READ [read_data] */
	Swd_packetHeader =  APACC_DATA_READ;
	Swd_ReadPacket();
	if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);
		
    /* APACC DATA Write [read_data | 0x10] */
    Swd_packetHeader =  APACC_DATA_WRITE;
    Swd_packetData[0] = Swd_packetData[0] | 0x10;
    Swd_WritePacket();
    if(Swd_packetAck != SWD_OK_ACK)
        return(FAILURE);		
	
	/* Erase the entire EEPROM by doing sector wise erase operation */	
	for(i = 0; i < loop_final; i++)
	{
		/* APACC ADDR Write [0x4000 4720] */
	    Swd_packetHeader =  APACC_ADDR_WRITE;
	    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);	
			
	    /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
	       for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */          
	    Swd_packetHeader =  APACC_DATA_WRITE;
	    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;			
		
		/* APACC DATA Write [0x0000 00B6] */
	    Swd_packetData[0] = 0xB6;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE); 
			
		/* APACC DATA Write [0x0000 00DB] */
	    Swd_packetData[0] = 0xDB;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);			
		
		/* APACC DATA Write [0x0000 0008] */
	    Swd_packetData[0] = 0x08;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		/* APACC DATA Write [0x0000 0040] */
	    Swd_packetData[0] = 0x40;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);	
			
		/* APACC DATA Write [SectorCount] */
	    Swd_packetData[0] = i;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		if(IsSpcIdle() == FAILURE)
       	 return(FAILURE);			
	}
    
    /* Call the GetDieTemperature function */
    if(GetDieTemperature(&temperatureSign, &temperatureMagnitude) == FAILURE)
        return(FAILURE);	
	
	/* Get the number of EEPROM rows by parsing the EEPROM data in the hex file */
	loop_final = GetEepromRowCount();
	
	/* Program the EEPROM rows in sequence */
	for(i = 0; i < loop_final; i++)
	{
		/* Get the data to be programmed for the current EEPROM row */
        LoadEepromRowData(i, &eepromRowData[0]);
		
		/* APACC ADDR Write [0x4000 4720] */
	    Swd_packetHeader =  APACC_ADDR_WRITE;
	    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);	
			
	    /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
	       for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */          
	    Swd_packetHeader =  APACC_DATA_WRITE;
	    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;			
		
		/* APACC DATA Write [0x0000 00B6] */
	    Swd_packetData[0] = 0xB6;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE); 
			
		/* APACC DATA Write [0x0000 00D5] */
	    Swd_packetData[0] = 0xD5;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		/* APACC DATA Write [0x0000 0002] */
	    Swd_packetData[0] = 0x02;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
						
		/* APACC DATA Write [0x0000 0040] */
	    Swd_packetData[0] = 0x40;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		for(j = 0; j < EEPROM_ROW_BYTE_SIZE_HEX_FILE; j++)
		{
			/* APACC DATA Write [EEPROMByteData] */
		    Swd_packetData[0] = eepromRowData[j];
		    Swd_WritePacket();
		    if(Swd_packetAck != SWD_OK_ACK)
		        return(FAILURE);
		}
		
		if(IsSpcIdle() == FAILURE)
       		return(FAILURE);
			
		/* APACC ADDR Write [0x4000 4720] */
	    Swd_packetHeader =  APACC_ADDR_WRITE;
	    Swd_packetData[3] = 0x40;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x47;Swd_packetData[0] = 0x20;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);	
			
	    /* The MSB three bytes in the following data transfers are always zero. Only the LSB byte will change 
	       for each SWD packet. Also, all the below SWD packets have the same header APACC_DATA_WRITE */          
	    Swd_packetHeader =  APACC_DATA_WRITE;
	    Swd_packetData[3] = 0x00;Swd_packetData[2] = 0x00;Swd_packetData[1] = 0x00;			
		
		/* APACC DATA Write [0x0000 00B6] */
	    Swd_packetData[0] = 0xB6;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);	
			
		/* APACC DATA Write [0x0000 00DA] */
	    Swd_packetData[0] = 0xDA;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);			
									
		/* APACC DATA Write [0x0000 0007] */
	    Swd_packetData[0] = 0x07;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);			
												
		/* APACC DATA Write [0x0000 0040] */
	    Swd_packetData[0] = 0x40;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		/* APACC DATA Write [0x0000 0000] */
	    Swd_packetData[0] = 0x00;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		/* APACC DATA Write [rowCount] */
	    Swd_packetData[0] = i;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		/* APACC DATA Write [temperatureSign] */
	    Swd_packetData[0] = temperatureSign;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);
			
		/* APACC DATA Write [temperatureMagnitude] */
	    Swd_packetData[0] = temperatureMagnitude;
	    Swd_WritePacket();
	    if(Swd_packetAck != SWD_OK_ACK)
	        return(FAILURE);	
			
		if(IsSpcIdle() == FAILURE)
       		return(FAILURE);									
	}	
	return(SUCCESS);
}

/*******************************************************************************
* Function Name: VerifyEeprom
********************************************************************************
*
* Summary:
*  Verifies whether the data programmed to the EEPROM is the same as expected 
*  data
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - EEPROM verification successful
*  FAILURE - Operation failed
*
* Note:
*	
*******************************************************************************/
unsigned char VerifyEeprom()
{
    unsigned char eepromRowData[EEPROM_ROW_BYTE_SIZE_HEX_FILE];
    unsigned char eepromRowData_readData[EEPROM_ROW_BYTE_SIZE_HEX_FILE];
    unsigned char rowCount;
    unsigned char numOfEepromRows;
    unsigned char byteCount;  
	
	/* Get the total number of EEPROM rows in the PSoC device */ 
    numOfEepromRows   = GetEepromRowCount();
	
	/* Do a row-wise verify operation */
	for(rowCount = 0; rowCount < numOfEepromRows; rowCount++)
	{
		byteCount = 0;
		
		while(byteCount < EEPROM_ROW_BYTE_SIZE_HEX_FILE)		
		{
			/* APACC ADDR Write [eeprom_address] */
		    Swd_packetHeader =  APACC_ADDR_WRITE;
		    Swd_packetData[3] = 0x40;
			Swd_packetData[2] = 0x00;
			Swd_packetData[1] = 0x80 + (rowCount >> 4);
			Swd_packetData[0] = byteCount + (rowCount << 4);
		    Swd_WritePacket();
		    if(Swd_packetAck != SWD_OK_ACK)
		        return(FAILURE);
			
			/* APACC DATA Read */
			Swd_packetHeader =  APACC_DATA_READ;            
            Swd_ReadPacket();
			if(Swd_packetAck != SWD_OK_ACK)
        		return(FAILURE);
			
			eepromRowData_readData[byteCount++] = Swd_packetData[0];
			eepromRowData_readData[byteCount++] = Swd_packetData[1];
			eepromRowData_readData[byteCount++] = Swd_packetData[2];
			eepromRowData_readData[byteCount++] = Swd_packetData[3];			
		}
		
		/* Get the EEPROM row data from the hex file - reference data */
        LoadEepromRowData(rowCount, &eepromRowData[0]);
		
		for(byteCount = 0; byteCount < EEPROM_ROW_BYTE_SIZE_HEX_FILE; byteCount++)
		{
			if(eepromRowData_readData[byteCount] != eepromRowData[byteCount])
			{
				/* Set the verification error bit for Flash data mismatch and return failure */
                Swd_packetAck = Swd_packetAck | VERIFICATION_ERROR; 
                return(FAILURE);
			}
		}
	}
		
	return(SUCCESS);		
}

    #endif /* (EEPROM_DATA_PRESENT_HEX_FILE) */

/*******************************************************************************
* Function Name: ExitProgrammingMode
********************************************************************************
*
* Summary:
*  Exit the programming mode by generating a active low pulse signal on the Target PSoC 5LP
*  XRES pin. All the programming pins from the host side are chaned to High impedance
*  digital drive mode so as to not drive the programming lines when not programming
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  ReleaseTargetDevice() that is called inside this function is defined in DeviceAcquire.c
*******************************************************************************/
void ExitProgrammingMode()
{
    ReleaseTargetDevice();
}

/*******************************************************************************
* Function Name: ReadHsspErrorStatus
********************************************************************************
*
* Summary:
*  Returns the HSSP Error status in case of FAILURE return in any one of the programming steps
*
* Parameters:
*  None.
*
* Return:
*  Swd_packetAck
*      Each bit of this 8-bit return value has a specific meaning.
*
* Note:
*  Refer to the application note pdf for details on the Error status bit definitions
*******************************************************************************/
unsigned char ReadHsspErrorStatus()
{
    return(Swd_packetAck);
}

/*******************************************************************************
* Function Name: ReadSpcStatusReg
********************************************************************************
*
* Summary:
*  Returns the SPC Status register value in case a SPC_TIMEOUT_ERROR is detected
*  by calling the function ReadHsspErrorStatus()
*
* Parameters:
*  None.
*
* Return:
*  Swd_packetData[0]
*      Value of the SPC status register (stored in Swd_packetData[0])
*
* Note:
*  Refer to the Programming specifications document for details on the SPC status codes.
*  The status value returned by this function is valid only if a SPC_TIMEOUT_ERROR
*  is detected. In all other cases, this function call does not return the actual SPC
*  status register value.
*******************************************************************************/
unsigned char ReadSpcStatusReg()
{
    return(Swd_packetData[0]);
}

/* [] END OF FILE */
