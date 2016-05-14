/*******************************************************************************
* File Name: TimeoutCalc.h
* Version 3.0
*
* Description:
*  This header file contains the definitions for the timeout parameters, declaration 
*  of the functions used for calculating the the timeout parameters.
*
* Note:
*  The timeout values given below are applicable for a PSoC 5LP Host processor with the CPU
*  operating at a clock frequency of 63 MHz. A test pin defined as TESTPIN
*  is used to arrive at these timeout values by toggling the pin, and measuring the low 
*  pulse width of the square wave on the test pin using an oscilloscope.
*******************************************************************************/
#ifndef __TIMEOUTCALC_H
#define __TIMEOUTCALC_H

/***************************** USER ATTENTION REQUIRED **************************
***************************** HOST PROCESSOR SPECIFIC ***************************
***************************** Timeout parameter definitions *********************
*
* The below four timeout values namely: XRES_PULSE_100US, TIME_WINDOW_68US, DEVICE_ACQUIRE_TIMEOUT,
* and SPC_POLLING_TIMEOUT should be calculated by calling the corresponding functions 
* in the for loop of the main() function  and measuring the low pulse width
* of the square wave signal on the TESTPIN. Refer to the procedure given for calculating each
* of the parameters below.
* The default definitions below are for a PSoC 5LP host programmer operating at a frequency of 66 MHZ.
*
* Modify these values as required for your host processor. 

********************************************************************************/

/*********************Calculating XRES_PULSE_100US *******************************************
1.) Call ONLY the function TestDelayHundredUs(), defined in TimeoutCalc.c, in the for loop of the main code
2.) Note down the LOW PULSE WIDTH (Tlow) of the square wave on the pin TEST_PIN
3.) Tune the value of the definition XRES_PULSE_100US below till the low pulse width (Tlow)
    is JUST GREATER than 100uS 
4.) For example, for a PSoC 5LP host programmer operating at 66 MHz, defining the 
    XRES_PULSE_100US as 630 gave a low pulse width of ~105 uS. This was used in the HSSP code.
5.) This parameter is referred to as TRESET in the programming specifications document.
6840 = 93.6 uS
*********************************************************************************/
#define XRES_PULSE_100US  7100

/*********************Calculating TIME_WINDOW_68US *******************************************
1.) Call ONLY the function TestSwdck(), defined in TimeoutCalc.c, in the for loop of the main code
2.) Note down the LOW PULSE WIDTH (Tlow) of the square wave on the pin TEST_PIN
3.) Tune the value of the definition TIME_WINDOW_68US below till the low pulse width (Tlow)
    is JUST GREATER than 68 uS (range of 70 us - 75 us would be sufficient)
4.) For example, for a PSoC 5LP host programmer operating at 66 MHz, defining the 
    TIME_WINDOW_68US as 125 gave a low pulse width of ~71 uS. This was used in the HSSP code.
5.) This parameter is referred to as TBOOT in the programming specifications document.

*********************************************************************************/
#define TIME_WINDOW_68US 125


/*********************Calculating DEVICE_ACQUIRE_TIMEOUT *******************************************
1.) Call ONLY the function TestAcquirePacket(), defined in TimeoutCalc.c, in the for loop of the main code
2.) Note down the LOW PULSE WIDTH (Tlow in us) of the square wave on the pin TEST_PIN
3.) DEVICE_ACQUIRE_TIMEOUT = (327 us)/(Tlow), rounded off to the next higher integer
4.) For example, for a PSoC 5LP host programmer operating at 66 MHz, Tlow was 47 uS.
    So, DEVICE_ACQUIRE_TIMEOUT = (327 us)/(47 us) = 6.9 = 7. This value was used in the HSSP code.
5.) The value 327us is derived from the programming specifications document
    based on the difference of Ttestmode(min) and Tboot. 395us - 68us = 327us.
6.) An important factor to consider is that this value should be greater than or equal to 4 to program
    target PSoC 3 / PSoC 5LP. Because a maximum of 4 SWD packets are required to acquire target PSoC 3 / PSoC 5LP device. If this value is 
    less than 4, optimize the acquire code so that Tlow duration is reduced, and the value is >= 4.
*********************************************************************************/
#define DEVICE_ACQUIRE_TIMEOUT 7

/*********************Calculating SPC_POLLING_TIMEOUT *******************************************
1.) Call ONLY the function TestSwdReadPacket(), defined in TimeoutCalc.c, in the for loop of the main code
2.) Note down the LOW PULSE WIDTH (Tlow in us) of the square wave on the pin TEST_PIN
3.) SPC_POLLING_TIMEOUT = (1000000 us)/(Tlow), rounded off to the next higher integer
4.) For example, for a PSoC 5LP host programmer operating at 66 MHz, Tlow was 72 uS.
    So, SPC_POLLING_TIMEOUT = (1000000 us)/(72 us) = 13889. This value was used in the HSSP code.
5.) The value 1000000 us (1 second) is derived from the programming specifications document
    based on the SPC polling timeout duration whoch is 1 second.
*********************************************************************************/
#define SPC_POLLING_TIMEOUT 13889

/********************************************************************************
*   Function Prototypes
********************************************************************************/
void TestDelayHundredUs(void);
void TestSwdck(void);
void TestSwdReadPacket(void);
void TestAcquirePacket(void);

#endif /* __TIMEOUTCALC_H */
//[] END OF FILE
