/*******************************************************************************
* File Name: Swd_PhysicalLayer.c
* Version 3.0
*
* Description:
*  This file provides the source code for the physical layer functions of the
*  SWD protocol. These function definitions are the same as the corresponding
*  macro definitions in Swd_PhysicalLayer.h
*******************************************************************************/

/********************************************************************************
*   Header file Inclusion
********************************************************************************/
#include <wiringPi.h>
#include "Swd_PhysicalLayer.h"

/********************************************************************************
*   Function Definitions
********************************************************************************/

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
******************* SWD Protocol Physical Layer functions ***********************
*
* All of the function definitions below are for a PSoC 5LP host programmer.
* Modify the definitions as applicable for the specific host programmer.
********************************************************************************/

/*******************************************************************************
* Function Name: SetSwdckCmosOutput
********************************************************************************
*
* Summary:
*  Sets the SWDCK pin drive mode as CMOS drive mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDCK_DRIVEMODE_CMOSOUT in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdckCmosOutput()
{
    SWDCK_DRIVEMODE_CMOSOUT;
}

/*******************************************************************************
* Function Name: SetSwdckHizInput
********************************************************************************
*
* Summary:
*  Sets the SWDCK pin drive mode as High impedance digital input.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDCK_DRIVEMODE_HIGHZIN in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdckHizInput()
{
    SWDCK_DRIVEMODE_HIGHZIN;
}

/*******************************************************************************
* Function Name: SetSwdioCmosOutput
********************************************************************************
*
* Summary:
*  Sets the SWDIO pin drive mode as CMOS drive mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDIO_DRIVEMODE_CMOSOUT in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdioCmosOutput()
{
    SWDIO_DRIVEMODE_CMOSOUT;
}

/*******************************************************************************
* Function Name: SetSwdioHizInput
********************************************************************************
*
* Summary:
*  Sets the SWDIO pin drive mode as High impedance digital input.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDIO_DRIVEMODE_HIGHZIN in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdioHizInput()
{
    SWDIO_DRIVEMODE_HIGHZIN;        
}

/*******************************************************************************
* Function Name: SetXresCmosOutput
********************************************************************************
*
* Summary:
*  Sets the XRES pin drive mode as CMOS drive mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition XRES_DRIVEMODE_CMOSOUT in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetXresCmosOutput()
{
    XRES_DRIVEMODE_CMOSOUT;
}

/*******************************************************************************
* Function Name: SetXresHizInput
********************************************************************************
*
* Summary:
*  Sets the XRES pin drive mode as High impedance digital input.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition XRES_DRIVEMODE_HIGHZIN in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetXresHizInput()
{
    XRES_DRIVEMODE_HIGHZIN;
}

/*******************************************************************************
* Function Name: SetSwdckHigh
********************************************************************************
*
* Summary:
*  Sets the SWDCK pin high
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDCK_OUTPUT_HIGH in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdckHigh()
{
    SWDCK_OUTPUT_HIGH;    
}

/*******************************************************************************
* Function Name: SetSwdckLow
********************************************************************************
*
* Summary:
*  Sets the SWDCK pin low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDCK_OUTPUT_LOW in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdckLow()
{
    SWDCK_OUTPUT_LOW;
}

/*******************************************************************************
* Function Name: SetSwdioHigh
********************************************************************************
*
* Summary:
*  Sets the SWDIO pin high
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDIO_OUTPUT_HIGH in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdioHigh()
{
    SWDIO_OUTPUT_HIGH;
}

/*******************************************************************************
* Function Name: SetSwdioLow
********************************************************************************
*
* Summary:
*  Sets the SWDIO pin low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition SWDIO_OUTPUT_LOW in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetSwdioLow()
{
    SWDIO_OUTPUT_LOW;
}

/*******************************************************************************
* Function Name: SetXresHigh
********************************************************************************
*
* Summary:
*  Sets the XRES pin high
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition XRES_OUTPUT_HIGH in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetXresHigh()
{
    XRES_OUTPUT_HIGH;
}

/*******************************************************************************
* Function Name: SetXresLow
********************************************************************************
*
* Summary:
*  Sets the XRES pin low
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  The function definition is the same as the macro definition XRES_OUTPUT_LOW in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
void SetXresLow()
{
    XRES_OUTPUT_LOW;
}

/*******************************************************************************
* Function Name: ReadSwdio
********************************************************************************
*
* Summary:
*  Returns the state of the SWDIO input pin
*
* Parameters:
*  None.
*
* Return:
*  unsigned char (only one of the two values as given below)
*   0x00 - If the SWDIO pin state is low
*   0x01 - If the SWDIO pin state is high
*
* Note:
*  The function definition is the same as the macro definition SWDIO_INPUT_READ in
*  Swd_PhysicalLayer.h.
*
*******************************************************************************/
unsigned char ReadSwdio()
{
    SWDIO_INPUT_READ;
}

/* [] END OF FILE */
