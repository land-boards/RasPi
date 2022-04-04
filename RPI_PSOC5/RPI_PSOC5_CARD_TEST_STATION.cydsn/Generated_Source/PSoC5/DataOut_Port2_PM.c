/*******************************************************************************
* File Name: DataOut_Port2_PM.c
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

#include "DataOut_Port2.h"

/* Check for removal by optimization */
#if !defined(DataOut_Port2_Sync_ctrl_reg__REMOVED)

static DataOut_Port2_BACKUP_STRUCT  DataOut_Port2_backup = {0u};

    
/*******************************************************************************
* Function Name: DataOut_Port2_SaveConfig
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
void DataOut_Port2_SaveConfig(void) 
{
    DataOut_Port2_backup.controlState = DataOut_Port2_Control;
}


/*******************************************************************************
* Function Name: DataOut_Port2_RestoreConfig
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
void DataOut_Port2_RestoreConfig(void) 
{
     DataOut_Port2_Control = DataOut_Port2_backup.controlState;
}


/*******************************************************************************
* Function Name: DataOut_Port2_Sleep
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
void DataOut_Port2_Sleep(void) 
{
    DataOut_Port2_SaveConfig();
}


/*******************************************************************************
* Function Name: DataOut_Port2_Wakeup
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
void DataOut_Port2_Wakeup(void)  
{
    DataOut_Port2_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
