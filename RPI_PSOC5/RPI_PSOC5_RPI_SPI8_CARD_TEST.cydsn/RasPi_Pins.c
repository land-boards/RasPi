/* ========================================
 *
 * Copyright LAND BOARDS, LLC, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Land Boards.
 *
 * ========================================
*/

#include "RPI_PSOC5.h"

void setRasPiPinValue(uint8 bcmPinNum, uint8 value)
{
    switch (bcmPinNum)
    {
        case IO_2:
            IO_2_Write(value);
            break;
        case IO_3:
            IO_3_Write(value);
            break;
        case IO_4:
            IO_4_Write(value);
            break;
        case IO_14:
            IO_14_Write(value);
            break;
        case IO_15:
            IO_15_Write(value);
            break;
        case IO_17:
            IO_17_Write(value);
            break;
        case IO_18:
            IO_18_Write(value);
            break;
        case IO_27:
            IO_27_Write(value);
            break;
        case IO_22:
            IO_22_Write(value);
            break;
        case IO_23:
            IO_23_Write(value);
            break;
        case IO_24:
            IO_24_Write(value);
            break;
        case IO_10:
            IO_10_Write(value);
            break;
        case IO_9:
            IO_9_Write(value);
            break;
        case IO_25:
            IO_25_Write(value);
            break;
        case IO_11:
            IO_11_Write(value);
            break;
        case IO_8:
            IO_8_Write(value);
            break;
        case IO_7:
            IO_7_Write(value);
            break;
        case IO_5:
            IO_5_Write(value);
            break;
        case IO_6:
            IO_6_Write(value);
            break;
        case IO_12:
            IO_12_Write(value);
            break;
        case IO_13:
            IO_13_Write(value);
            break;
        case IO_19:
            IO_19_Write(value);
            break;
        case IO_16:
            IO_16_Write(value);
            break;
        case IO_26:
            IO_26_Write(value);
            break;
        case IO_20:
            IO_20_Write(value);
            break;
        case IO_21:
            IO_21_Write(value);
            break;
        }
}

// PIN_DM_STRONG

void setRasPiPinDrive(uint8 bcmPinNum, uint8 value)
{
    switch (bcmPinNum)
    {
        case IO_2:
            IO_2_SetDriveMode(value);
            break;
        case IO_3:
            IO_3_SetDriveMode(value);
            break;
        case IO_4:
            IO_4_SetDriveMode(value);
            break;
        case IO_14:
            IO_14_SetDriveMode(value);
            break;
        case IO_15:
            IO_14_SetDriveMode(value);
            break;
        case IO_17:
            IO_17_SetDriveMode(value);
            break;
        case IO_18:
            IO_18_SetDriveMode(value);
            break;
        case IO_27:
            IO_27_SetDriveMode(value);
            break;
        case IO_22:
            IO_22_SetDriveMode(value);
            break;
        case IO_23:
            IO_23_SetDriveMode(value);
            break;
        case IO_24:
            IO_24_SetDriveMode(value);
            break;
        case IO_10:
            IO_10_SetDriveMode(value);
            break;
        case IO_9:
            IO_9_SetDriveMode(value);
            break;
        case IO_25:
            IO_25_SetDriveMode(value);
            break;
        case IO_11:
            IO_11_SetDriveMode(value);
            break;
        case IO_8:
            IO_8_SetDriveMode(value);
            break;
        case IO_7:
            IO_7_SetDriveMode(value);
            break;
        case IO_5:
            IO_5_SetDriveMode(value);
            break;
        case IO_6:
            IO_6_SetDriveMode(value);
            break;
        case IO_12:
            IO_12_SetDriveMode(value);
            break;
        case IO_13:
            IO_13_SetDriveMode(value);
            break;
        case IO_19:
            IO_19_SetDriveMode(value);
            break;
        case IO_16:
            IO_16_SetDriveMode(value);
            break;
        case IO_26:
            IO_26_SetDriveMode(value);
            break;
        case IO_20:
            IO_20_SetDriveMode(value);
            break;
        case IO_21:
            IO_21_SetDriveMode(value);
            break;
        }
}

/* [] END OF FILE */
