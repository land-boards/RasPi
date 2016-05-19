/*******************************************************************************
* File Name: DataFetch.c
* Version 3.0
*
* Description:
*  This source file contains the functions to fetch data from the Hex image and load in
*  to the arrays used for Programming.
*
* Note:
*  The definitions of the functions used in this file will change based on the
*  interface used to get Hex file data.
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include "DataFetch.h"
#include "HexImage.h"

/********************************************************************************
*   Function Definitions
********************************************************************************/

/***************************** USER ATTENTION REQUIRED **************************
**************** DEPENDS ON INTERFACE USED TO GET HEX FILE DATA *****************
All the function definitions below should be modified based on the interface used 
to get Hex file data to be programmed. If a protocol like I2C, UART is used to get the
hex file data, change the function definitions accordingly */

/*******************************************************************************
* Function Name: LoadDeviceSiliconId
********************************************************************************
*
* Summary:
*  Loads the Device silicon ID data in to an array 
*
* Parameters:
*  unsigned char * deviceSiliconId - Base address of array which will store the DEVICE SILICON ID fetched
*
* Return:
*  None.
*
* Note:
*  Modify definition based on method of getting programming data
*
*******************************************************************************/
void LoadDeviceSiliconId(unsigned char * deviceSiliconId)
{
    unsigned char i;
    
    /* Silicon ID is stored in big endian format in hex file
       and should be sent in little endian format to upper layer */
    
    for(i = 0; i < DEVICE_SILICON_ID_BYTE_LENGTH; i++)
    {
        deviceSiliconId[i] = deviceSiliconId_hexFile[DEVICE_SILICON_ID_BYTE_LENGTH - 1 -i];
    }
}

/*******************************************************************************
* Function Name: LoadDeviceConfigNvl
********************************************************************************
*
* Summary:
*  Loads the Device Configuration Nvl data in to an array 
*
* Parameters:
*  unsigned char * deviceConfigNvl - Base address of array which will store the DeviceConfigNvl data fetched
*
* Return:
*  None.
*
* Note:
*  Modify definition based on method of getting programming data
*
*******************************************************************************/

void LoadDeviceConfigNvl(unsigned char * deviceConfigNvl)
{
    unsigned char i;
    
    for(i = 0; i < NVL_BYTE_LENGTH; i++)
    {
        deviceConfigNvl[i] = deviceConfigNvl_hexFile[i];
    }
  
}

/*******************************************************************************
* Function Name: LoadWriteOnceNvl
********************************************************************************
*
* Summary:
*  Loads the WriteOnce Nvl data in to an array 
*
* Parameters:
*  unsigned char * writeOnceNvl - Base address of the array which will store the WriteOnceNvl data fetched
*
* Return:
*  None.
*
* Note:
*  Modify definition based on method of getting programming data
*
*******************************************************************************/
void LoadWriteOnceNvl(unsigned char * writeOnceNvl)
{
    unsigned char i;
    
    for(i = 0; i < NVL_BYTE_LENGTH; i++)
    {
        writeOnceNvl[i] = writeOnceNvl_hexFile[i];
    }    
}

/*******************************************************************************
* Function Name: LoadFlashRowData
********************************************************************************
*
* Summary:
*  Loads the Flash row data in to an array 
*
* Parameters:
*  unsigned short rowNumber      - Flash row number for which the data has to be fetched 
*
*  unsigned short rowByteSize   - Number of bytes to be loaded in to the Flash row (256 bytes for ECC enabled, 288 bytes for ECC disabled setting)
*
*  unsigned char * flashRowData - Base address of array which will store the Flash row data fetched
*
* Return:
*  None.
*
* Note:
*  Modify definition based on the method of getting programming data
*  The flash row data size in HexImage.c is reduced by NUMBER_OF_FLASH_ROWS_REMOVED flash rows to fit the PSoC 5LP HSSP project
*  in the host programmer PSoC 5LP's flash memory. Hence the last NUMBER_OF_FLASH_ROWS_REMOVED flash rows are loaded with zero
*  for flash row programming.
*  REMOVE THIS LOGIC WHILE PORTING THE HSSP CODE TO OTHER HOST PROGRAMMER
*
*******************************************************************************/
void LoadFlashRowData(unsigned short rowNumber, unsigned short rowByteSize, unsigned char * flashRowData)
{
    unsigned short i; /* Maximum value of 'i' can be 288, so declare as 16-bit unsigned int */
    
    if(rowNumber < (NUMBER_OF_FLASH_ROWS_HEX_FILE - NUMBER_OF_FLASH_ROWS_REMOVED) )
    {
        for(i = 0; i < rowByteSize; i++)
        {
            flashRowData[i] = flashData_hexFile [rowNumber][i];
        }
    }
    else
    {
        for(i = 0; i < rowByteSize; i++)
        {
            flashRowData[i] = 0x00;
        }    
    }
}

/*******************************************************************************
* Function Name: LoadFlashProtectionData
********************************************************************************
*
* Summary:
*  Loads the Flash Protection data in to an array 
*
* Parameters:
*  unsigned short protectionByteSize  - Number of protection bytes to be loaded in to the Flash row (maximum of 256 protection bytes for target PSoC 5LP)
*
*  unsigned char * flashRowData      - Base address of array which will store the Flash Protection data fetched
*
*
* Return:
*  None.
*
* Note:
*  Modify definition based on the method of getting programming data
*
*******************************************************************************/
void LoadFlashProtectionData(unsigned short protectionByteSize, unsigned char * flashRowData)
{
    unsigned short i;
    
    for(i = 0; i < protectionByteSize; i++)
    {
        flashRowData[i] = flashProtectionData_hexFile[i];
    }    
}

#if (EEPROM_DATA_PRESENT_HEX_FILE)
    
/*******************************************************************************
* Function Name: LoadEepromRowData
********************************************************************************
*
* Summary:
*  Loads the EEPROM row data in to an array 
*
* Parameters:
*  unsigned char rowNumber      - Flash row number for which the data has to be fetched 
*
*  unsigned char * eepromRowData - Base address of array which will store the
*                                  EEPROM row data fetched
*
* Return:
*  None.
*
* Note:
*  Modify definition based on the method of getting programming data.
*
*******************************************************************************/
void LoadEepromRowData(unsigned char rowNumber, unsigned char * eepromRowData)
{
    unsigned char i; 
    
    for(i = 0; i < EEPROM_ROW_BYTE_SIZE_HEX_FILE; i++)
    {
        eepromRowData[i] = eepromData_hexFile [rowNumber][i];
    }
}

#endif  /* (EEPROM_DATA_PRESENT_HEX_FILE) */

/*******************************************************************************
* Function Name: LoadChecksumData
********************************************************************************
*
* Summary:
*  Loads the Checksum data in to an array 
*
* Parameters:
*  unsigned char * checksumData - Base address of the array which will store the Checksum data fetched
*
* Return:
*  None.
*
* Note:
*  Modify definition based on the method of getting programming data
*
*******************************************************************************/
void LoadChecksumData(unsigned char * checksumData)
{
    unsigned char i;

    for(i = 0; i < CHECKSUM_BYTE_LENGTH; i++)
    {
        checksumData[i] = checksumData_hexFile[i];
    }
}

/*******************************************************************************
* Function Name: GetFlashRowCount
********************************************************************************
*
* Summary:
*  Returns the total number of Flash rows in the target PSoC 5LP device
*
* Parameters:
*  None
*
* Return:
*  unsigned short
*   Total number of Flash rows in target PSoC 5LP (maximum row count is 1024, hence return type is short (16-bit))
*
* Note:
*  The Flash row count is from the HexImage.h file. Modify the definition based
*  on the method of getting programming data
*
*******************************************************************************/
unsigned short GetFlashRowCount()
{
    return(NUMBER_OF_FLASH_ROWS_HEX_FILE);
}

/*******************************************************************************
* Function Name: GetFlashRowByteSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes per Flash row
*
* Parameters:
*  None
*
* Return:
*  unsigned short
*   This can either be 256 bytes (if ECC is enabled) or 288 bytes (if ECC is disabled)
*
* Note:
*  The Flash rowbyte size is from the HexImage.h file. Modify the definition based
*  on the method of getting programming data
*
*******************************************************************************/
unsigned short GetFlashRowByteSize()
{
    return(FLASH_ROW_BYTE_SIZE_HEX_FILE);
}

/*******************************************************************************
* Function Name: GetFlashArrayCount
********************************************************************************
*
* Summary:
*  Returns the total number of Flash arrays in the target PSoC 5LP device
*
* Parameters:
*  None
*
* Return:
*  unsigned char
*   Total number of Flash arrays in target PSoC 5LP (maximum array count is 4, hence return type is char (8-bit))
*
* Note:
*  The Flash array count is from the HexImage.h file. Modify the definition based
*  on the method of getting programming data
*
*******************************************************************************/
unsigned char GetFlashArrayCount()
{
    return(NUMBER_OF_FLASH_ARRAYS_HEX_FILE);
}

#if (EEPROM_DATA_PRESENT_HEX_FILE)

/*******************************************************************************
* Function Name: GetEepromRowCount
********************************************************************************
*
* Summary:
*  Returns the number of EEPROM rows
*
* Parameters:
*  None
*
* Return:
*  unsigned char
*   number of EEPROM rows
*
* Note:
*  The EEPROM row count is from the HexImage.h file. Modify the definition based
*  on the method of getting programming data
*
*******************************************************************************/
unsigned char GetEepromRowCount()
{
	return(NUMBER_OF_EEPROM_ROWS_HEX_FILE);
}

/*******************************************************************************
* Function Name: GetEepromSectorCount
********************************************************************************
*
* Summary:
*  Returns the number of EEPROM sectors
*
* Parameters:
*  None
*
* Return:
*  unsigned char
*   number of EEPROM sectors
*
* Note:
*  The EEPROM sector count is from the HexImage.h file. Modify the definition based
*  on the method of getting programming data
*
*******************************************************************************/
unsigned char GetEepromSectorCount()
{
	return(NUMBER_OF_EEPROM_SECTORS_HEX_FILE);
}

#endif /* (EEPROM_DATA_PRESENT_HEX_FILE) */

/* [] END OF FILE */
