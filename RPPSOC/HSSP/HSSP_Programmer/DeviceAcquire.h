/*******************************************************************************
* File Name: DeviceAcquire.h
* Version 3.0 plus WiringPi modifications
*
* Description:
*  This header file contains the macros, function declarations  for
*  "Step1: Enter Programming Mode" in Programming flow and
*   also to exit programming mode.
*  This step is provided as separate .c, .h file as the procedure to enter target 
*  programming mode has strict timing requirements.
*
* Note:
*
*******************************************************************************/
#ifndef __DEVICEACQUIRE_H
#define __DEVICEACQUIRE_H

/********************************************************************************
*   Macro definitions
********************************************************************************/

/* Header data for SWD packets sent in "Step1: Enter Programming Mode" */
#define PORT_ACQUIRE_KEY_HEADER 0x99
#define TESTMODE_ADDRESS_HEADER 0x8B
#define TESTMODE_KEY_HEADER     0xBB

/* Precalculated parity bit values for three SWD packets sent 
   in "Step1: Enter Programming Mode" */
#define PARITY_PORT_ACQUIRE_KEY 0 
#define PARITY_TESTMODE_ADDRESS 1
#define PARITY_TESTMODE_KEY     1

/* This is the bit field definition for the Timeout error in "Step1: Enter Programming Mode".
*  This error code will be appended to actual ACK data stored in the global variable Swd_packetAck */
#define PORT_ACQUIRE_TIMEOUT_ERROR 0x10

/********************************************************************************
*   Function Prototypes
********************************************************************************/
unsigned char AcquireTargetDevice(void);
void ReleaseTargetDevice(void);

#endif /* __DEVICEACQUIRE_H */
//[] END OF FILE
