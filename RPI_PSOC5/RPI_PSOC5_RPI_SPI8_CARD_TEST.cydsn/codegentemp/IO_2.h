/*******************************************************************************
* File Name: IO_2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IO_2_H) /* Pins IO_2_H */
#define CY_PINS_IO_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_2__PORT == 15 && ((IO_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_2_Write(uint8 value);
void    IO_2_SetDriveMode(uint8 mode);
uint8   IO_2_ReadDataReg(void);
uint8   IO_2_Read(void);
void    IO_2_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_2_SetDriveMode() function.
     *  @{
     */
        #define IO_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_2_DM_RES_UP          PIN_DM_RES_UP
        #define IO_2_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_2_DM_OD_LO           PIN_DM_OD_LO
        #define IO_2_DM_OD_HI           PIN_DM_OD_HI
        #define IO_2_DM_STRONG          PIN_DM_STRONG
        #define IO_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_2_MASK               IO_2__MASK
#define IO_2_SHIFT              IO_2__SHIFT
#define IO_2_WIDTH              1u

/* Interrupt constants */
#if defined(IO_2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_2_SetInterruptMode() function.
     *  @{
     */
        #define IO_2_INTR_NONE      (uint16)(0x0000u)
        #define IO_2_INTR_RISING    (uint16)(0x0001u)
        #define IO_2_INTR_FALLING   (uint16)(0x0002u)
        #define IO_2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_2_INTR_MASK      (0x01u) 
#endif /* (IO_2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_2_PS                     (* (reg8 *) IO_2__PS)
/* Data Register */
#define IO_2_DR                     (* (reg8 *) IO_2__DR)
/* Port Number */
#define IO_2_PRT_NUM                (* (reg8 *) IO_2__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_2_AG                     (* (reg8 *) IO_2__AG)                       
/* Analog MUX bux enable */
#define IO_2_AMUX                   (* (reg8 *) IO_2__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_2_BIE                    (* (reg8 *) IO_2__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_2_BIT_MASK               (* (reg8 *) IO_2__BIT_MASK)
/* Bypass Enable */
#define IO_2_BYP                    (* (reg8 *) IO_2__BYP)
/* Port wide control signals */                                                   
#define IO_2_CTL                    (* (reg8 *) IO_2__CTL)
/* Drive Modes */
#define IO_2_DM0                    (* (reg8 *) IO_2__DM0) 
#define IO_2_DM1                    (* (reg8 *) IO_2__DM1)
#define IO_2_DM2                    (* (reg8 *) IO_2__DM2) 
/* Input Buffer Disable Override */
#define IO_2_INP_DIS                (* (reg8 *) IO_2__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_2_LCD_COM_SEG            (* (reg8 *) IO_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_2_LCD_EN                 (* (reg8 *) IO_2__LCD_EN)
/* Slew Rate Control */
#define IO_2_SLW                    (* (reg8 *) IO_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_2_PRTDSI__CAPS_SEL       (* (reg8 *) IO_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_2_PRTDSI__OE_SEL0        (* (reg8 *) IO_2__PRTDSI__OE_SEL0) 
#define IO_2_PRTDSI__OE_SEL1        (* (reg8 *) IO_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_2_PRTDSI__OUT_SEL0       (* (reg8 *) IO_2__PRTDSI__OUT_SEL0) 
#define IO_2_PRTDSI__OUT_SEL1       (* (reg8 *) IO_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_2_PRTDSI__SYNC_OUT       (* (reg8 *) IO_2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_2__SIO_CFG)
    #define IO_2_SIO_HYST_EN        (* (reg8 *) IO_2__SIO_HYST_EN)
    #define IO_2_SIO_REG_HIFREQ     (* (reg8 *) IO_2__SIO_REG_HIFREQ)
    #define IO_2_SIO_CFG            (* (reg8 *) IO_2__SIO_CFG)
    #define IO_2_SIO_DIFF           (* (reg8 *) IO_2__SIO_DIFF)
#endif /* (IO_2__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_2__INTSTAT)
    #define IO_2_INTSTAT            (* (reg8 *) IO_2__INTSTAT)
    #define IO_2_SNAP               (* (reg8 *) IO_2__SNAP)
    
	#define IO_2_0_INTTYPE_REG 		(* (reg8 *) IO_2__0__INTTYPE)
#endif /* (IO_2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_2_H */


/* [] END OF FILE */
