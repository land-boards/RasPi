/*******************************************************************************
* File Name: Swd_PhysicalLayer.h
* Version 3.0
*
* Description:
*  This header file contains the macro definitions, function declarations for the
*  physical layer of the  SWD protocol. These include -
*    a.) Setting a output pin high or low
*    b.) Reading the logic level of an input pin
*    c.) Configuring the drive mode of the programming pin
*
*  The pin manipulation routines are defined both as macros and functions.
*  The macros are used in AcquireTargetDevice() function in DeviceAcquire.c
*  as the function has strict timing requirements for execution.
*  Using the macros instead of fuctions reduces execution overhead.
*
*  The pin manipulation functions are used instead of macros in all other
*  places to save code space.
*
* Note:
*  The macros, functions defined here are specific to PSoC 5LP Host Programmer.
*  Modify them as applicable for your Host Programmer.
*******************************************************************************/

#ifndef __SWD_PHYSICALLAYER_H
#define __SWD_PHYSICALLAYER_H

/* Host programmer registers, mask values are defined in "RegisterDefines.h" */
#include "RegisterDefines.h"

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
**************** Macros for Host Pin Drive mode configuration *******************
*
* Uses the register definitions, mask values in "RegisterDefines.h" to
* configure the pin drive mode
*
* SWDIO pin on host side - CMOS output (host writes data to target PSoC 5LP),
*                          High Z digital input (host reads data from target
*                          PSoC 5LP or when host is not programming target
*                          PSoC 5LP (idle))
*
* SWDCK pin on host side - CMOS output (when host is programming target PSoC 5LP),
*                          High Z digital input (when host is not programming target PSoC 5LP (idle))
*
* XRES pin on host side -  CMOS output (when host is programming target PSoC 5LP)
*                          High Z digital input (when host is not programming target PSoC 5LP (idle))
*
* Modify these as applicable to your Host Programmer
********************************************************************************/

#define SWDIO_DRIVEMODE_HIGHZIN         pinMode (5, INPUT)        
#define SWDIO_DRIVEMODE_CMOSOUT         pinMode (5, OUTPUT)

#define SWDCK_DRIVEMODE_HIGHZIN         pinMode (4, INPUT)
#define SWDCK_DRIVEMODE_CMOSOUT         pinMode (4, OUTPUT)
                                           
#define XRES_DRIVEMODE_HIGHZIN          pinMode (3, INPUT)
#define XRES_DRIVEMODE_CMOSOUT          pinMode (3, OUTPUT)

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
**************** Macros for driving output pins on host side ********************
*
* Uses the register definitions, mask values in "RegisterDefines.h" to drive
* output pins either to logic high (suffixed by 'HIGH') or
* logic low (suffixed by 'LOW')
*
* Modify these as applicable to your Host Programmer
********************************************************************************/

#define SWDIO_OUTPUT_HIGH      digitalWrite (5, 1)
#define SWDIO_OUTPUT_LOW       digitalWrite (5, 0)

#define SWDCK_OUTPUT_HIGH      digitalWrite (4, 1)
#define SWDCK_OUTPUT_LOW       digitalWrite (4, 0)

#define XRES_OUTPUT_HIGH       digitalWrite (3, 1)
#define XRES_OUTPUT_LOW        digitalWrite (3, 0)

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
**************** Macro for reading input pin on host side ***********************
*
* Uses the register definitions, mask values in "RegisterDefines.h" to read
* the SWDIO pin in input mode
*
* This macro returns '0x01' if the SWDIO input pin is at logic high,
* or '0x00' if the SWDIO input pin is at logic low
*
* Modify this as applicable to your Host Programmer
********************************************************************************/

#define SWDIO_INPUT_READ      digitalRead (5)

/********************************************************************************
*   Function Prototypes
********************************************************************************/
/* The below fuctions are for pin manipulation, and their definitions in
*  Swd_PhysicalLayer.c are the same as the corresponding macro defitnions above. */

void SetSwdckHigh(void);
void SetSwdckLow(void);
void SetSwdckCmosOutput(void);
void SetSwdckHizInput(void);
void SetSwdioHigh(void);
void SetSwdioLow(void);
void SetSwdioCmosOutput(void);
unsigned char ReadSwdio(void);
void SetSwdioHizInput(void);
void SetXresHigh(void);
void SetXresLow(void);
void SetXresCmosOutput(void);
void SetXresHizInput(void);

#endif /* __SWD_PHYSICALLAYER_H */
//[] END OF FILE
