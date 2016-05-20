/*******************************************************************************
* File Name: main.c
* Version 3.0
*
* Description:
*  This file has the main function that calls the top level HSSP functions in 
*  sequence to program the target PSoC 5LP
*******************************************************************************/

#include <stdio.h>
#include <wiringPi.h>

#include "ProgrammingSteps.h"

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
    wiringPiSetup();
    printf("Land Boards, LLC - Programming PSoC\n");
	
    /* Start the HSSP Programming and store the status */
    programResult = ProgramDevice();
    
    if(programResult == SUCCESS) /* HSSP completed successfully */
    {
        printf("HSSP Success\n");    
    }
    else /* HSSP Failure */
    { 
        /* Display the step number where the HSSP failed */
        printf("HSSP Failed Step %d - ",currentStep);
		switch (currentStep)
		{
			case 1:
				printf("Failed to Enter Programming Mode\n");
				break;
			case 2:
				printf("Configure Target Device Failed\n");
				break;
			case 3:
				printf("Verify JTAG ID Failed\n");
				break;
			case 4:
				printf("Erase Flash Failed\n");
				break;
			case 5:
				printf("Program Device Configuration NVL Failed\n");
				break;
			case 6:
				printf("Program Flash Failed\n");
				break;
			case 7:
				printf("Verify Flash Failed\n");
				break;
			case 8:
				printf("Program WO NVL Failed\n");
				break;
			case 9:
				printf("Program Flash Protection Failed\n");
				break;
			case 10:
				printf("Verify Flash Protection  Failed\n");
				break;
			case 11:
				printf("Checksum Validation Failed\n");
				break;
			case 12:
				printf("Program EERROM Failed\n");
				break;
			case 13:
				printf("Verify EERROM Failed\n");
				break;
			default:
				printf("Unexpected error condition\n");
		}
        
        /* Get the HSSP error status */
        errorStatus = ReadHsspErrorStatus();        
        
        printf("Error code: %d\n",errorStatus);
        
        /* If the errorStatus contains THE SPC_TIMEOUT_ERROR error condition,
           read the SPC status register */
 
        if(errorStatus & SPC_TIMEOUT_ERROR)
        {
            spcErrorStatus = ReadSpcStatusReg();
            printf(" SPC %d\n",spcErrorStatus);            
        }
    } 

 printf("Exiting\n");
 return 0;
}
