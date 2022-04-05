/*******************************************************************************
* File Name: P74.h  
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

#if !defined(CY_PINS_P74_H) /* Pins P74_H */
#define CY_PINS_P74_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P74_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P74__PORT == 15 && ((P74__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P74_Write(uint8 value);
void    P74_SetDriveMode(uint8 mode);
uint8   P74_ReadDataReg(void);
uint8   P74_Read(void);
void    P74_SetInterruptMode(uint16 position, uint16 mode);
uint8   P74_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P74_SetDriveMode() function.
     *  @{
     */
        #define P74_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P74_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P74_DM_RES_UP          PIN_DM_RES_UP
        #define P74_DM_RES_DWN         PIN_DM_RES_DWN
        #define P74_DM_OD_LO           PIN_DM_OD_LO
        #define P74_DM_OD_HI           PIN_DM_OD_HI
        #define P74_DM_STRONG          PIN_DM_STRONG
        #define P74_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P74_MASK               P74__MASK
#define P74_SHIFT              P74__SHIFT
#define P74_WIDTH              1u

/* Interrupt constants */
#if defined(P74__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P74_SetInterruptMode() function.
     *  @{
     */
        #define P74_INTR_NONE      (uint16)(0x0000u)
        #define P74_INTR_RISING    (uint16)(0x0001u)
        #define P74_INTR_FALLING   (uint16)(0x0002u)
        #define P74_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P74_INTR_MASK      (0x01u) 
#endif /* (P74__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P74_PS                     (* (reg8 *) P74__PS)
/* Data Register */
#define P74_DR                     (* (reg8 *) P74__DR)
/* Port Number */
#define P74_PRT_NUM                (* (reg8 *) P74__PRT) 
/* Connect to Analog Globals */                                                  
#define P74_AG                     (* (reg8 *) P74__AG)                       
/* Analog MUX bux enable */
#define P74_AMUX                   (* (reg8 *) P74__AMUX) 
/* Bidirectional Enable */                                                        
#define P74_BIE                    (* (reg8 *) P74__BIE)
/* Bit-mask for Aliased Register Access */
#define P74_BIT_MASK               (* (reg8 *) P74__BIT_MASK)
/* Bypass Enable */
#define P74_BYP                    (* (reg8 *) P74__BYP)
/* Port wide control signals */                                                   
#define P74_CTL                    (* (reg8 *) P74__CTL)
/* Drive Modes */
#define P74_DM0                    (* (reg8 *) P74__DM0) 
#define P74_DM1                    (* (reg8 *) P74__DM1)
#define P74_DM2                    (* (reg8 *) P74__DM2) 
/* Input Buffer Disable Override */
#define P74_INP_DIS                (* (reg8 *) P74__INP_DIS)
/* LCD Common or Segment Drive */
#define P74_LCD_COM_SEG            (* (reg8 *) P74__LCD_COM_SEG)
/* Enable Segment LCD */
#define P74_LCD_EN                 (* (reg8 *) P74__LCD_EN)
/* Slew Rate Control */
#define P74_SLW                    (* (reg8 *) P74__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P74_PRTDSI__CAPS_SEL       (* (reg8 *) P74__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P74_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P74__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P74_PRTDSI__OE_SEL0        (* (reg8 *) P74__PRTDSI__OE_SEL0) 
#define P74_PRTDSI__OE_SEL1        (* (reg8 *) P74__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P74_PRTDSI__OUT_SEL0       (* (reg8 *) P74__PRTDSI__OUT_SEL0) 
#define P74_PRTDSI__OUT_SEL1       (* (reg8 *) P74__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P74_PRTDSI__SYNC_OUT       (* (reg8 *) P74__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P74__SIO_CFG)
    #define P74_SIO_HYST_EN        (* (reg8 *) P74__SIO_HYST_EN)
    #define P74_SIO_REG_HIFREQ     (* (reg8 *) P74__SIO_REG_HIFREQ)
    #define P74_SIO_CFG            (* (reg8 *) P74__SIO_CFG)
    #define P74_SIO_DIFF           (* (reg8 *) P74__SIO_DIFF)
#endif /* (P74__SIO_CFG) */

/* Interrupt Registers */
#if defined(P74__INTSTAT)
    #define P74_INTSTAT            (* (reg8 *) P74__INTSTAT)
    #define P74_SNAP               (* (reg8 *) P74__SNAP)
    
	#define P74_0_INTTYPE_REG 		(* (reg8 *) P74__0__INTTYPE)
#endif /* (P74__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P74_H */


/* [] END OF FILE */
