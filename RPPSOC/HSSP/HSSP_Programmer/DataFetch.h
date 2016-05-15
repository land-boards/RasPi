/*******************************************************************************
* File Name: DataFetch.h
* Version 3.0
*
* Description:
*  This header file contains the definitions for the size of Programming data,
*  and declarations for the functions used in getting the Programming data
*  from Hex file image. The fuction definitions in corresponding
*  DataFetch.c file will have to be modified if the method of getting programming data 
*  is changed.
*
* Note:
*
*******************************************************************************/
#ifndef __DATAFETCH_H
#define __DATAFETCH_H
    
#include "HexImage.h"

/********************************************************************************
*   Header file Inclusion
********************************************************************************/

/********************************************************************************
*   Macro definitions
********************************************************************************/

/* The below definitions are not dependent on hex file and are always constant */
#define CODE_BYTES_PER_FLASH_ROW      256
#define ECC_BYTES_PER_FLASH_ROW       32
#define MAXIMUM_BYTES_PER_FLASH_ROW   (CODE_BYTES_PER_FLASH_ROW + ECC_BYTES_PER_FLASH_ROW)
#define DEVICE_SILICON_ID_BYTE_LENGTH 4
#define NVL_BYTE_LENGTH               4
#define CHECKSUM_BYTE_LENGTH          2

#define MAXIMUM_ROWS_PER_FLASH_ARRAY  256

/***************************************
*        Function Prototypes
***************************************/
void LoadDeviceSiliconId(unsigned char * deviceSiliconId);
void LoadDeviceConfigNvl(unsigned char * deviceConfigNvl);
void LoadWriteOnceNvl(unsigned char * writeOnceNvl);
void LoadFlashRowData(unsigned short rowNumber, unsigned short rowByteSize, unsigned char * flashRowData);
void LoadFlashProtectionData(unsigned short protectionByteSize, unsigned char * flashRowData);
void LoadChecksumData(unsigned char * checksumData);

unsigned short GetFlashRowCount(void);
unsigned char GetFlashArrayCount(void);
unsigned short GetFlashRowByteSize(void);

#if (EEPROM_DATA_PRESENT_HEX_FILE)
    void LoadEepromRowData(unsigned char rowNumber, unsigned char * eepromRowData);
    unsigned char GetEepromRowCount(void);
    unsigned char GetEepromSectorCount(void);
#endif /* (EEPROM_DATA_PRESENT_HEX_FILE) */

#endif /* __DATAFETCH_H */
//[] END OF FILE
