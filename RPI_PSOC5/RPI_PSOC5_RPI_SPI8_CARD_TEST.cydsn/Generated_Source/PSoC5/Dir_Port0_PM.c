/*******************************************************************************
* File Name: Dir_Port0_PM.c
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

#include "Dir_Port0.h"

/* Check for removal by optimization */
#if !defined(Dir_Port0_Sync_ctrl_reg__REMOVED)

static Dir_Port0_BACKUP_STRUCT  Dir_Port0_backup = {0u};

    
/*******************************************************************************
* Function Name: Dir_Port0_SaveConfig
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
void Dir_Port0_SaveConfig(void) 
{
    Dir_Port0_backup.controlState = Dir_Port0_Control;
}


/*******************************************************************************
* Function Name: Dir_Port0_RestoreConfig
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
void Dir_Port0_RestoreConfig(void) 
{
     Dir_Port0_Control = Dir_Port0_backup.controlState;
}


/*******************************************************************************
* Function Name: Dir_Port0_Sleep
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
void Dir_Port0_Sleep(void) 
{
    Dir_Port0_SaveConfig();
}


/*******************************************************************************
* Function Name: Dir_Port0_Wakeup
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
void Dir_Port0_Wakeup(void)  
{
    Dir_Port0_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
