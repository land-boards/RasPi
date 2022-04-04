/*******************************************************************************
* File Name: P72.h  
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

#if !defined(CY_PINS_P72_H) /* Pins P72_H */
#define CY_PINS_P72_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P72_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P72__PORT == 15 && ((P72__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P72_Write(uint8 value);
void    P72_SetDriveMode(uint8 mode);
uint8   P72_ReadDataReg(void);
uint8   P72_Read(void);
void    P72_SetInterruptMode(uint16 position, uint16 mode);
uint8   P72_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P72_SetDriveMode() function.
     *  @{
     */
        #define P72_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P72_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P72_DM_RES_UP          PIN_DM_RES_UP
        #define P72_DM_RES_DWN         PIN_DM_RES_DWN
        #define P72_DM_OD_LO           PIN_DM_OD_LO
        #define P72_DM_OD_HI           PIN_DM_OD_HI
        #define P72_DM_STRONG          PIN_DM_STRONG
        #define P72_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P72_MASK               P72__MASK
#define P72_SHIFT              P72__SHIFT
#define P72_WIDTH              1u

/* Interrupt constants */
#if defined(P72__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P72_SetInterruptMode() function.
     *  @{
     */
        #define P72_INTR_NONE      (uint16)(0x0000u)
        #define P72_INTR_RISING    (uint16)(0x0001u)
        #define P72_INTR_FALLING   (uint16)(0x0002u)
        #define P72_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P72_INTR_MASK      (0x01u) 
#endif /* (P72__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P72_PS                     (* (reg8 *) P72__PS)
/* Data Register */
#define P72_DR                     (* (reg8 *) P72__DR)
/* Port Number */
#define P72_PRT_NUM                (* (reg8 *) P72__PRT) 
/* Connect to Analog Globals */                                                  
#define P72_AG                     (* (reg8 *) P72__AG)                       
/* Analog MUX bux enable */
#define P72_AMUX                   (* (reg8 *) P72__AMUX) 
/* Bidirectional Enable */                                                        
#define P72_BIE                    (* (reg8 *) P72__BIE)
/* Bit-mask for Aliased Register Access */
#define P72_BIT_MASK               (* (reg8 *) P72__BIT_MASK)
/* Bypass Enable */
#define P72_BYP                    (* (reg8 *) P72__BYP)
/* Port wide control signals */                                                   
#define P72_CTL                    (* (reg8 *) P72__CTL)
/* Drive Modes */
#define P72_DM0                    (* (reg8 *) P72__DM0) 
#define P72_DM1                    (* (reg8 *) P72__DM1)
#define P72_DM2                    (* (reg8 *) P72__DM2) 
/* Input Buffer Disable Override */
#define P72_INP_DIS                (* (reg8 *) P72__INP_DIS)
/* LCD Common or Segment Drive */
#define P72_LCD_COM_SEG            (* (reg8 *) P72__LCD_COM_SEG)
/* Enable Segment LCD */
#define P72_LCD_EN                 (* (reg8 *) P72__LCD_EN)
/* Slew Rate Control */
#define P72_SLW                    (* (reg8 *) P72__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P72_PRTDSI__CAPS_SEL       (* (reg8 *) P72__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P72_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P72__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P72_PRTDSI__OE_SEL0        (* (reg8 *) P72__PRTDSI__OE_SEL0) 
#define P72_PRTDSI__OE_SEL1        (* (reg8 *) P72__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P72_PRTDSI__OUT_SEL0       (* (reg8 *) P72__PRTDSI__OUT_SEL0) 
#define P72_PRTDSI__OUT_SEL1       (* (reg8 *) P72__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P72_PRTDSI__SYNC_OUT       (* (reg8 *) P72__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P72__SIO_CFG)
    #define P72_SIO_HYST_EN        (* (reg8 *) P72__SIO_HYST_EN)
    #define P72_SIO_REG_HIFREQ     (* (reg8 *) P72__SIO_REG_HIFREQ)
    #define P72_SIO_CFG            (* (reg8 *) P72__SIO_CFG)
    #define P72_SIO_DIFF           (* (reg8 *) P72__SIO_DIFF)
#endif /* (P72__SIO_CFG) */

/* Interrupt Registers */
#if defined(P72__INTSTAT)
    #define P72_INTSTAT            (* (reg8 *) P72__INTSTAT)
    #define P72_SNAP               (* (reg8 *) P72__SNAP)
    
	#define P72_0_INTTYPE_REG 		(* (reg8 *) P72__0__INTTYPE)
#endif /* (P72__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P72_H */


/* [] END OF FILE */
