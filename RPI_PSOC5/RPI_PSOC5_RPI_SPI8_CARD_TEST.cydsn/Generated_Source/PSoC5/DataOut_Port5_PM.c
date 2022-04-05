/*******************************************************************************
* File Name: DataOut_Port5_PM.c
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

#include "DataOut_Port5.h"

/* Check for removal by optimization */
#if !defined(DataOut_Port5_Sync_ctrl_reg__REMOVED)

static DataOut_Port5_BACKUP_STRUCT  DataOut_Port5_backup = {0u};

    
/*******************************************************************************
* Function Name: DataOut_Port5_SaveConfig
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
void DataOut_Port5_SaveConfig(void) 
{
    DataOut_Port5_backup.controlState = DataOut_Port5_Control;
}


/*******************************************************************************
* Function Name: DataOut_Port5_RestoreConfig
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
void DataOut_Port5_RestoreConfig(void) 
{
     DataOut_Port5_Control = DataOut_Port5_backup.controlState;
}


/*******************************************************************************
* Function Name: DataOut_Port5_Sleep
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
void DataOut_Port5_Sleep(void) 
{
    DataOut_Port5_SaveConfig();
}


/*******************************************************************************
* Function Name: DataOut_Port5_Wakeup
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
void DataOut_Port5_Wakeup(void)  
{
    DataOut_Port5_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
