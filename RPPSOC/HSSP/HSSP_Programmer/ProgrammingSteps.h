/*******************************************************************************
* File Name: ProgrammingSteps.h
* Version 3.0 plus WiringPi modifications
*
* Description:
*  This header file contains high level definitions and function declarations associated with 
*  programming of the target device
*
* Note:
*
*******************************************************************************/

#ifndef __PROGRAMMINGSTEPS_H
#define __PROGRAMMINGSTEPS_H
    
#include "HexImage.h"

/********************************************************************************
*   Macro definitions
********************************************************************************/

/* Return value definitions for high level Programming functions */
#define FAILURE 0
#define SUCCESS (!FAILURE)

/* This bit field is set if the SPC does not return the success status code
   within the SPC Polling timeout duration*/
#define SPC_TIMEOUT_ERROR  0x20 

/* This bit field is set in the case of mismatch of Device silicon ID, flash data,
    flash protection data, eeprom data, checksum data */
#define VERIFICATION_ERROR 0x40

/* SWD Packet Header definitions */
#define DPACC_READBUFF_WRITE   0x99
#define DPACC_IDOCDE_READ      0xA5
#define APACC_ADDR_WRITE       0x8B
#define APACC_DATA_READ        0x9F
#define APACC_DATA_WRITE       0xBB

#define DPACC_DP_CTRLSTAT_WRITE  0xA9
#define DPACC_DP_SELECT_WRITE    0xB1
#define APACC_AP_CTRLSTAT_WRITE  0xA3

/* SPC Status Register definitions */
#define SPC_STATUS_IDLE       0x02
#define SPC_STATUS_DATA_READY 0x01

/* Error Correcting Code (ECC) feature definitions.
   ECC setting is bit 3 of byte 3 of the 4-byte Device Config NVL data */
#define ECC_BYTE_LOCATION 0x03
#define ECC_BIT_MASK      0x08

/********************************************************************************
*   Function Prototypes
********************************************************************************/

unsigned char EnterProgrammingMode(void);
unsigned char ConfigureTargetDevice(void);
unsigned char VerifyDeviceId(void);
unsigned char EraseFlash(void);
unsigned char ProgramDeviceConfigNvl(void);
unsigned char ProgramFlash(void);
unsigned char VerifyFlash(void);
unsigned char ProgramWriteOnceNvl(void);
unsigned char ProgramFlashProtection(void);
unsigned char VerifyFlashProtection(void);
unsigned char VerifyChecksum(void);
void ExitProgrammingMode(void);

#if (EEPROM_DATA_PRESENT_HEX_FILE)
    unsigned char ProgramEeprom(void);
    unsigned char VerifyEeprom(void);    
#endif /* (EEPROM_DATA_PRESENT_HEX_FILE) */

unsigned char ReadHsspErrorStatus(void);
unsigned char ReadSpcStatusReg(void);

#endif /* __PROGRAMMINGSTEPS_H */
