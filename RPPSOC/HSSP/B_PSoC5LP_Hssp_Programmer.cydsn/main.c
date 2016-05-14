/*******************************************************************************
* File Name: main.c
* Version 3.0
*
* Description:
*  This file has the main function that calls the top level HSSP functions in 
*  sequence to program the target PSoC 5LP
*
* Note:
*  The Character LCD functions in the main() function are for PSoC 5LP 
*  host programmer. Remove the Character LCD functions while porting the code 
*  to non PSoC 5LP host programmer.
*******************************************************************************/

/* This file has the top level HSSP routines that should be called from main application code */
//#include "ProgrammingSteps.h"

#ub=nckude "fcnprototypes.h"

/* Contains define for presence of EEPROM data in hex file */
#include "HexImage.h"

unsigned char currentStep; /* Global variable that stores the current HSSP Programming step number */

/*******************************************************************************
* Function Name: ProgramDevice
********************************************************************************
*
* Summary:
*  This function calls the top level HSSP routines from  "ProgrammingSteps.h".
*  The function returns a status value that will indicate the success or failure
*  of HSSP operation.
*
* Parameters:
*  None.
*
* Return:
*  SUCCESS - Target PSoC 5LP programmed successfully
*  FAILURE - Target PSoC 5LP programming failed
*
*
* Note:
*  In case of FAILURE return value, global variable currentStep will store the
*  step value in which the failure occurred
*******************************************************************************/

unsigned char ProgramDevice()
{
    currentStep = 0;
    
    /* Call the different sequence of steps in HSSP Programming.
       Abort operation if any of the steps fail */ 
    
    currentStep++;
    if(EnterProgrammingMode() == FAILURE)     /* Step 1 - EnterProgrammingMode */
        return(FAILURE);
    
    currentStep++;
    if(ConfigureTargetDevice() == FAILURE)    /* Step 2 - ConfigureTargetDevice */
        return(FAILURE);

    currentStep++;
    if(VerifyDeviceId() == FAILURE)             /* Step 3 - VerifyDeviceId */
        return(FAILURE);

    currentStep++;
    if(EraseFlash() == FAILURE)               /* Step 4 - EraseFlash */          
        return(FAILURE);
		
    currentStep++;
    if(ProgramDeviceConfigNvl() == FAILURE)   /* Step 5 - ProgramDeviceConfigNvl */  
        return(FAILURE);		

    currentStep++;
    if(ProgramFlash() == FAILURE)             /* Step 6 - ProgramFlash */
        return(FAILURE);

    currentStep++;
    if(VerifyFlash() == FAILURE)              /* Step 7 - VerifyFlash */
        return(FAILURE);

    currentStep++;
    if(ProgramWriteOnceNvl() == FAILURE)      /* Step 8 - ProgramWriteOnceNvl */    
        return(FAILURE);

    currentStep++;
    if(ProgramFlashProtection() == FAILURE)   /* Step 9 - ProgramFlashProtection */    
        return(FAILURE);

    currentStep++;
    if(VerifyFlashProtection() == FAILURE)    /* Step 10 - VerifyFlashProtection */    
        return(FAILURE);

    currentStep++;
    if(VerifyChecksum() == FAILURE)           /* Step 11 - VerifyChecksum */
        return(FAILURE);
	
    #if (EEPROM_DATA_PRESENT_HEX_FILE)
        currentStep++;
        if(ProgramEeprom() == FAILURE)      /* Step 12  - ProgramEeprom */
            return(FAILURE);
    		
        currentStep++;
        if(VerifyEeprom() == FAILURE)      /* Step 13 - VerifyEeprom */ 
            return(FAILURE);
    #endif /* (EEPROM_DATA_PRESENT_HEX_FILE) */
    
    ExitProgrammingMode();
        
    return(SUCCESS); /* All the steps were completed successfully */
}

int main()
{
    unsigned char programResult;  /* Variable to store the result of HSSP operation */ 
    unsigned char errorStatus;    /* Variable to store the HSSP Error status in case of failure */
    unsigned char spcErrorStatus; /* Variable to store the SPC Error status if ErrorStatus contains SPC_TIMEOUT_ERROR error*/ 
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    // LCD_Char_Start();    /* Initialize Character LCD  */
    
    // LCD_Char_Position(0,0);
    printf("Programming PSoC\n");
    return();		// remove
	
    /* Start the HSSP Programming and store the status */
    programResult = ProgramDevice();
    
    /* Character LCD will display the status of HSSP Programming  */
    LCD_Char_ClearDisplay();    
    
    if(programResult == SUCCESS) /* HSSP completed successfully */
    {
        LCD_Char_Position(0,0);
        LCD_Char_PrintString("HSSP Success");    
    }
    else /* HSSP Failure */
    { 
        /* Display the step number where the HSSP failed */
        LCD_Char_Position(0,0);
        LCD_Char_PrintString("HSSP Fail Step");
        LCD_Char_PrintNumber(currentStep);
        
        /* Get the HSSP error status and display on THE LCD */
        errorStatus = ReadHsspErrorStatus();        
        
        LCD_Char_Position(1,0);
        LCD_Char_PrintString("Err ");
        LCD_Char_PrintInt8(errorStatus);
        
        /* If the errorStatus contains THE SPC_TIMEOUT_ERROR error condition,
           read the SPC status register and display on THE LCD */
        if(errorStatus & SPC_TIMEOUT_ERROR)
        {
            spcErrorStatus = ReadSpcStatusReg();
            
            LCD_Char_PrintString(" SPC ");
            LCD_Char_PrintInt8(spcErrorStatus);            
        }
    } 

    for(;;)
    {
        
        
    }
}

/* [] END OF FILE */
