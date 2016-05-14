/*******************************************************************************
* File Name: RegisterDefines.h
* Version 3.0
* Based on
*	http://wiringpi.com/download-and-install/
*
* Description:
*  This header file contains the definitions for the programming pins on the
*  host side - SWDIO, SWDCK, XRES. The definitions include:
*
*  1.) Port number, Pin number of the programming pins 
*  2.) Registers for writing to the pins, reading from the pins, 
*      configuring the pin drive modes
*  3.) Mask values for writing to, reading from an individual pin
*  4.) Mask values for configuring the different pin drive modes
*
* Note:
*  The definitions provided here are for a Raspberry Pi.
*  These definitions are used in the file Swd_PhysicalLayer.h.
*******************************************************************************/
#ifndef __REGISTERDEFINES_H
#define __REGISTERDEFINES_H
    
/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
********************  GPIO defines header file *******************
*
* Modify the header file inclusion depending on the host processor used
********************************************************************************/
//#include "cyfitter.h"

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
********************  PORT NUMBER, PIN NUMBER ASSIGNMENTS *******************
*
* Modify these port, pin assignment definitions based on host programmer
* pin selection
********************************************************************************/

//#define SWDIO_PRT_NUM   Pin_Swdio__0__PORT
//#define SWDIO_PIN_NUM   Pin_Swdio__0__SHIFT

//#define SWDCK_PRT_NUM   Pin_Swdck__0__PORT
//#define SWDCK_PIN_NUM   Pin_Swdck__0__SHIFT

//#define XRES_PRT_NUM    Pin_Xres__0__PORT
//#define XRES_PIN_NUM    Pin_Xres__0__SHIFT

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
************************  INPUT, OUTPUT, DRIVE MODE REGISTERS ***************
*
* The defines are used to change the pin output(OUT_REG), read the
* pin input (IN_REG), and also to change the pin drive mode(DM_REG).
* 
* Modify these definitions as applicable for your Host programmer.
********************************************************************************/

//#define SWDIO_PRT_OUT_REG     (*((volatile unsigned char *)Pin_Swdio__DR)) 
//#define SWDIO_PRT_IN_REG      (*((volatile unsigned char *)Pin_Swdio__PS))
//#define SWDIO_PIN_DM_REG      (*((volatile unsigned char *)Pin_Swdio__0__PC))

//#define SWDCK_PRT_OUT_REG     (*((volatile unsigned char *)Pin_Swdck__DR))
//#define SWDCK_PIN_DM_REG      (*((volatile unsigned char *)Pin_Swdck__0__PC))

//#define XRES_PRT_OUT_REG      (*((volatile unsigned char *)Pin_Xres__DR))
//#define XRES_PIN_DM_REG       (*((volatile unsigned char *)Pin_Xres__0__PC))

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
************** Mask values for manipulating Port pins ***************************
*
* These mask values will be used to modify the specific bits of a
* Port register (8-bits wide) like Port input/output registers. These will be
* used to set a output pin as high or low, or return the logic state (high or low)
* of an input pin.
* 
* Modify these as applicable for Host programmer.
******************************************************************************/
//#define XRES_PIN_MASK   Pin_Xres__0__MASK
//#define SWDCK_PIN_MASK  Pin_Swdck__0__MASK
//#define SWDIO_PIN_MASK  Pin_Swdio__0__MASK

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
********** Mask values for Pin Drive mode configuration *************************
*
* Mask definitions below are for configuring the pin drive modes of Host PSoC 5LP.
*
* Output pins should be in Strong drive (CMOS Drive) mode and input pins should
* be in High impedance digital (High-Z) drive mode.
*
* Modify these mask values as applicable for Host programmer.
********************************************************************************/
//#define HIGHZIN_DM_ANDMASK  0xF1
//#define HIGHZIN_DM_ORMASK   0x02
//#define CMOSOUT_DM_ANDMASK  0xF1
//#define CMOSOUT_DM_ORMASK   0x0C

#endif /* __REGISTERDEFINES_H */
//[] END OF FILE
