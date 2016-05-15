/*******************************************************************************
* File Name: Timeout.h
* Version 3.0
*
* Description:
*  This header file contains the definitions for timeout parameters, function
*  declaration for the delay routine. These definitions will vary based on host processor used
*  to program target. Change the timeout values based on your Host processor.
*
* Note:
* Refer to the TimeoutCalc.h header file in the other project "C_Hssp_TimeoutCalc"
* for details on the procedure to calculate these parameters for your specific
* host programmer
*******************************************************************************/
#ifndef __TIMEOUT_H
#define __TIMEOUT_H

/********************************************************************************
*   Macro definitions
********************************************************************************/

/*************************** HOST PROCESSOR SPECIFIC ***************************
* Refer to the TimeoutCalc.h header file in the other project "C_Hssp_TimeoutCalc"
* for details on the procedure to calculate these parameters for your specific
* host programmer
********************************************************************************/

// #define XRES_PULSE_100US  630
#define TIME_WINDOW_68US 125
#define DEVICE_ACQUIRE_TIMEOUT 7
#define SPC_POLLING_TIMEOUT 13889

/********************************************************************************
*   Function Prototypes
********************************************************************************/
void DelayHundredUs(void);

#endif /* __TIMEOUT_H */
//[] END OF FILE
