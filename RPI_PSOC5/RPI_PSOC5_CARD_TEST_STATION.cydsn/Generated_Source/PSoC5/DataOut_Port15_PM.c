/*******************************************************************************
* File Name: DataOut_Port15_PM.c
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

#include "DataOut_Port15.h"

/* Check for removal by optimization */
#if !defined(DataOut_Port15_Sync_ctrl_reg__REMOVED)

static DataOut_Port15_BACKUP_STRUCT  DataOut_Port15_backup = {0u};

    
/*******************************************************************************
* Function Name: DataOut_Port15_SaveConfig
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
void DataOut_Port15_SaveConfig(void) 
{
    DataOut_Port15_backup.controlState = DataOut_Port15_Control;
}


/*******************************************************************************
* Function Name: DataOut_Port15_RestoreConfig
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
void DataOut_Port15_RestoreConfig(void) 
{
     DataOut_Port15_Control = DataOut_Port15_backup.controlState;
}


/*******************************************************************************
* Function Name: DataOut_Port15_Sleep
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
void DataOut_Port15_Sleep(void) 
{
    DataOut_Port15_SaveConfig();
}


/*******************************************************************************
* Function Name: DataOut_Port15_Wakeup
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
void DataOut_Port15_Wakeup(void)  
{
    DataOut_Port15_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
