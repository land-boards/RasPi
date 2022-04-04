/*******************************************************************************
* File Name: P71.h  
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

#if !defined(CY_PINS_P71_H) /* Pins P71_H */
#define CY_PINS_P71_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P71_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P71__PORT == 15 && ((P71__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P71_Write(uint8 value);
void    P71_SetDriveMode(uint8 mode);
uint8   P71_ReadDataReg(void);
uint8   P71_Read(void);
void    P71_SetInterruptMode(uint16 position, uint16 mode);
uint8   P71_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P71_SetDriveMode() function.
     *  @{
     */
        #define P71_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P71_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P71_DM_RES_UP          PIN_DM_RES_UP
        #define P71_DM_RES_DWN         PIN_DM_RES_DWN
        #define P71_DM_OD_LO           PIN_DM_OD_LO
        #define P71_DM_OD_HI           PIN_DM_OD_HI
        #define P71_DM_STRONG          PIN_DM_STRONG
        #define P71_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P71_MASK               P71__MASK
#define P71_SHIFT              P71__SHIFT
#define P71_WIDTH              1u

/* Interrupt constants */
#if defined(P71__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P71_SetInterruptMode() function.
     *  @{
     */
        #define P71_INTR_NONE      (uint16)(0x0000u)
        #define P71_INTR_RISING    (uint16)(0x0001u)
        #define P71_INTR_FALLING   (uint16)(0x0002u)
        #define P71_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P71_INTR_MASK      (0x01u) 
#endif /* (P71__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P71_PS                     (* (reg8 *) P71__PS)
/* Data Register */
#define P71_DR                     (* (reg8 *) P71__DR)
/* Port Number */
#define P71_PRT_NUM                (* (reg8 *) P71__PRT) 
/* Connect to Analog Globals */                                                  
#define P71_AG                     (* (reg8 *) P71__AG)                       
/* Analog MUX bux enable */
#define P71_AMUX                   (* (reg8 *) P71__AMUX) 
/* Bidirectional Enable */                                                        
#define P71_BIE                    (* (reg8 *) P71__BIE)
/* Bit-mask for Aliased Register Access */
#define P71_BIT_MASK               (* (reg8 *) P71__BIT_MASK)
/* Bypass Enable */
#define P71_BYP                    (* (reg8 *) P71__BYP)
/* Port wide control signals */                                                   
#define P71_CTL                    (* (reg8 *) P71__CTL)
/* Drive Modes */
#define P71_DM0                    (* (reg8 *) P71__DM0) 
#define P71_DM1                    (* (reg8 *) P71__DM1)
#define P71_DM2                    (* (reg8 *) P71__DM2) 
/* Input Buffer Disable Override */
#define P71_INP_DIS                (* (reg8 *) P71__INP_DIS)
/* LCD Common or Segment Drive */
#define P71_LCD_COM_SEG            (* (reg8 *) P71__LCD_COM_SEG)
/* Enable Segment LCD */
#define P71_LCD_EN                 (* (reg8 *) P71__LCD_EN)
/* Slew Rate Control */
#define P71_SLW                    (* (reg8 *) P71__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P71_PRTDSI__CAPS_SEL       (* (reg8 *) P71__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P71_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P71__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P71_PRTDSI__OE_SEL0        (* (reg8 *) P71__PRTDSI__OE_SEL0) 
#define P71_PRTDSI__OE_SEL1        (* (reg8 *) P71__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P71_PRTDSI__OUT_SEL0       (* (reg8 *) P71__PRTDSI__OUT_SEL0) 
#define P71_PRTDSI__OUT_SEL1       (* (reg8 *) P71__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P71_PRTDSI__SYNC_OUT       (* (reg8 *) P71__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P71__SIO_CFG)
    #define P71_SIO_HYST_EN        (* (reg8 *) P71__SIO_HYST_EN)
    #define P71_SIO_REG_HIFREQ     (* (reg8 *) P71__SIO_REG_HIFREQ)
    #define P71_SIO_CFG            (* (reg8 *) P71__SIO_CFG)
    #define P71_SIO_DIFF           (* (reg8 *) P71__SIO_DIFF)
#endif /* (P71__SIO_CFG) */

/* Interrupt Registers */
#if defined(P71__INTSTAT)
    #define P71_INTSTAT            (* (reg8 *) P71__INTSTAT)
    #define P71_SNAP               (* (reg8 *) P71__SNAP)
    
	#define P71_0_INTTYPE_REG 		(* (reg8 *) P71__0__INTTYPE)
#endif /* (P71__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P71_H */


/* [] END OF FILE */
