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

#ifndef PSOC_MENU_H
#define PSOC_MENU_H

#include <project.h>

void printMenuOptions(void);
void putStringToUSB(char *);
void psocMenu(void);
void addToReceiveBuffer(uint16, uint8 *);
void clearReceiveBuffer(void);

extern uint8 receiveBuffer[80];
extern uint8 receiveBufferPtr;
extern uint8 gotCRorLF;

#endif

/* [] END OF FILE */
