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
#ifndef RASPIPINS_H
#define RASPIPINS_H

#include <project.h>

// BCM

enum BCM_PINS
{
    IO_2,
    IO_3,
    IO_4,
    IO_14,
    IO_15,
    IO_17,
    IO_18,
    IO_27,
    IO_22,
    IO_23,
    IO_24,
    IO_10,
    IO_9,
    IO_25,
    IO_11,
    IO_8,
    IO_7,
    IO_5,
    IO_6,
    IO_12,
    IO_13,
    IO_19,
    IO_16,
    IO_26,
    IO_20,
    IO_21
};

void setRasPiPinValue(uint8 bcmPinNum, uint8 value);
void setRasPiPinDrive(uint8 bcmPinNum, uint8 value);

#endif

/* [] END OF FILE */
