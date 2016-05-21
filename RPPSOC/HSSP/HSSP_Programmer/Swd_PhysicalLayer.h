/*******************************************************************************
* File Name: Swd_PhysicalLayer.h
* Version 3.0 plus WiringPi modifications
* Based on
*	http://wiringpi.com/
*
* Description:
*  This header file contains the macro definitions, function declarations for the
*  physical layer of the SWD protocol. 
*  These include -
*    a.) Setting a output pin high or low
*    b.) Reading the logic level of an input pin
*    c.) Setting a pin as input or output
*
*  The pin manipulation routines are defined both as macros and functions.
*  The macros are used in AcquireTargetDevice() function in DeviceAcquire.c
*  as the function has strict timing requirements for execution.
*  Using the macros instead of functions reduces execution overhead.
*  This is not as much of an advantage with the Raspberry Pi since the 
*  DigitalWrite function is very quick.
*  Does not need to use the register definitions or mask values in 
*  "RegisterDefines.h" to drive output pins since that is all handled by WiringPi.
*
* Note:
*
*******************************************************************************/

#ifndef __SWD_PHYSICALLAYER_H
#define __SWD_PHYSICALLAYER_H

#define TRIG_Pin	7
#define SWDIO_Pin	5
#define SWDCK_Pin	4
#define XRES_Pin	3

/********* WiringPi Functions for Host Pin Direction configuration *************
* Does not need to use the register definitions or mask values in 
* "RegisterDefines.h" to drive output pins since that is all handled by WiringPi.
*
* SWDIO pin on host side - CMOS output (host writes data to target PSoC 5LP),
*                          High Z digital input ((host reads data from target)
*                          PSoC 5LP or when host is not programming target
*                          PSoC 5LP (idle))
*
* SWDCK pin on host side - CMOS output (when host is programming target PSoC 5LP),
*                          High Z digital input (when host is not programming target 
*                          PSoC 5LP (idle))
*
* XRES pin on host side -  CMOS output (when host is programming target PSoC 5LP)
*                          High Z digital input (when host is not programming target 
*                          PSoC 5LP (idle))
********************************************************************************/

#define TRIG_DRIVEMODE_CMOSOUT         	pinMode(TRIG_Pin,OUTPUT)

#define SWDIO_DRIVEMODE_HIGHZIN         pinMode(SWDIO_Pin,INPUT)
#define SWDIO_DRIVEMODE_CMOSOUT         pinMode(SWDIO_Pin,OUTPUT)

#define SWDCK_DRIVEMODE_HIGHZIN         pinMode(SWDCK_Pin,INPUT)
#define SWDCK_DRIVEMODE_CMOSOUT         pinMode(SWDCK_Pin,OUTPUT)
                                           
#define XRES_DRIVEMODE_HIGHZIN          pinMode(XRES_Pin,INPUT)
#define XRES_DRIVEMODE_CMOSOUT          pinMode(XRES_Pin,OUTPUT)

/********* WiringPi Functions for driving output pins on host side **************
********************************************************************************/

#define TRIG_OUTPUT_LOW       digitalWrite(TRIG_Pin,0)
#define TRIG_OUTPUT_HIGH      digitalWrite(TRIG_Pin,1)

#define SWDIO_OUTPUT_HIGH      digitalWrite(SWDIO_Pin,1)
#define SWDIO_OUTPUT_LOW       digitalWrite(SWDIO_Pin,0)

#define SWDCK_OUTPUT_HIGH      digitalWrite(SWDCK_Pin,1)
#define SWDCK_OUTPUT_LOW       digitalWrite(SWDCK_Pin,0)

#define XRES_OUTPUT_HIGH       digitalWrite(XRES_Pin,1)
#define XRES_OUTPUT_LOW        digitalWrite(XRES_Pin,0)

/********** WiringPi Functions reading input pin on host side *******************
* This function returns '0x01' if the SWDIO input pin is at logic high,
* or '0x00' if the SWDIO input pin is at logic low
********************************************************************************/

#define SWDIO_INPUT_READ      digitalRead(SWDIO_Pin) & 0x1

/********************************************************************************
* Function Prototypes
********************************************************************************/

void SetSwdckHigh(void);
void SetSwdckLow(void);
void SetSwdckCmosOutput(void);
void SetSwdckHizInput(void);
void SetSwdioHigh(void);
void SetSwdioLow(void);
void SetSwdioCmosOutput(void);
void SetSwdioHizInput(void);
unsigned char ReadSwdio(void);
void SetXresHigh(void);
void SetXresLow(void);
void SetXresCmosOutput(void);
void SetXresHizInput(void);
void trigger(void);

#endif
