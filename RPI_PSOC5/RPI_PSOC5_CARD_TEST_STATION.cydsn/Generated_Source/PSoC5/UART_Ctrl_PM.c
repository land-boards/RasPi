/*******************************************************************************
* File Name: UART_Ctrl_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_Ctrl.h"

/* Check for removal by optimization */
#if !defined(UART_Ctrl_Sync_ctrl_reg__REMOVED)

static UART_Ctrl_BACKUP_STRUCT  UART_Ctrl_backup = {0u};

    
/*******************************************************************************
* Function Name: UART_Ctrl_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_Ctrl_SaveConfig(void) 
{
    UART_Ctrl_backup.controlState = UART_Ctrl_Control;
}


/*******************************************************************************
* Function Name: UART_Ctrl_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void UART_Ctrl_RestoreConfig(void) 
{
     UART_Ctrl_Control = UART_Ctrl_backup.controlState;
}


/*******************************************************************************
* Function Name: UART_Ctrl_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_Ctrl_Sleep(void) 
{
    UART_Ctrl_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Ctrl_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_Ctrl_Wakeup(void)  
{
    UART_Ctrl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
