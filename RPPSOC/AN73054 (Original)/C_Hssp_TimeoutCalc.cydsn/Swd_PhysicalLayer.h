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
* SWDIO pin on host side - CMOS output (host writes data to target ),
*                          High Z digital input (host reads data from target
*                          PSoC 5LP or when host is not programming target
*                          PSoC 5LP (idle))
*
* SWDCK pin on host side - CMOS output (when host is programming target ),
*                          High Z digital input (when host is not programming target  (idle))
*
* XRES pin on host side -  CMOS output (when host is programming target )
*                          High Z digital input (when host is not programming target  (idle))
*
* Modify these as applicable to your Host Programmer
********************************************************************************/

#define SWDIO_DRIVEMODE_HIGHZIN         (SWDIO_PIN_DM_REG = (SWDIO_PIN_DM_REG & HIGHZIN_DM_ANDMASK) | HIGHZIN_DM_ORMASK)        
#define SWDIO_DRIVEMODE_CMOSOUT         (SWDIO_PIN_DM_REG = (SWDIO_PIN_DM_REG & CMOSOUT_DM_ANDMASK) | CMOSOUT_DM_ORMASK)

#define SWDCK_DRIVEMODE_HIGHZIN         (SWDCK_PIN_DM_REG = (SWDCK_PIN_DM_REG & HIGHZIN_DM_ANDMASK) | HIGHZIN_DM_ORMASK)
#define SWDCK_DRIVEMODE_CMOSOUT         (SWDCK_PIN_DM_REG = (SWDCK_PIN_DM_REG & CMOSOUT_DM_ANDMASK) | CMOSOUT_DM_ORMASK)
                                           
#define XRES_DRIVEMODE_CMOSOUT          (XRES_PIN_DM_REG = (XRES_PIN_DM_REG & CMOSOUT_DM_ANDMASK) | CMOSOUT_DM_ORMASK)
#define XRES_DRIVEMODE_HIGHZIN          (XRES_PIN_DM_REG = (XRES_PIN_DM_REG & HIGHZIN_DM_ANDMASK) | HIGHZIN_DM_ORMASK)


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

#define SWDIO_OUTPUT_HIGH      (SWDIO_PRT_OUT_REG = SWDIO_PRT_OUT_REG | SWDIO_PIN_MASK)
#define SWDIO_OUTPUT_LOW       (SWDIO_PRT_OUT_REG = SWDIO_PRT_OUT_REG & (~SWDIO_PIN_MASK))

#define SWDCK_OUTPUT_HIGH      (SWDCK_PRT_OUT_REG = SWDCK_PRT_OUT_REG | SWDCK_PIN_MASK)
#define SWDCK_OUTPUT_LOW       (SWDCK_PRT_OUT_REG = SWDCK_PRT_OUT_REG & (~SWDCK_PIN_MASK))

#define XRES_OUTPUT_HIGH       (XRES_PRT_OUT_REG = XRES_PRT_OUT_REG | XRES_PIN_MASK)
#define XRES_OUTPUT_LOW        (XRES_PRT_OUT_REG = XRES_PRT_OUT_REG & (~XRES_PIN_MASK))

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

#define SWDIO_INPUT_READ      ((SWDIO_PRT_IN_REG >> SWDIO_PIN_NUM) & 0x01)

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
