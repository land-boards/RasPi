/*******************************************************************************
* File Name: SCL0.h  
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

#if !defined(CY_PINS_SCL0_H) /* Pins SCL0_H */
#define CY_PINS_SCL0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SCL0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SCL0__PORT == 15 && ((SCL0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SCL0_Write(uint8 value);
void    SCL0_SetDriveMode(uint8 mode);
uint8   SCL0_ReadDataReg(void);
uint8   SCL0_Read(void);
void    SCL0_SetInterruptMode(uint16 position, uint16 mode);
uint8   SCL0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SCL0_SetDriveMode() function.
     *  @{
     */
        #define SCL0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SCL0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SCL0_DM_RES_UP          PIN_DM_RES_UP
        #define SCL0_DM_RES_DWN         PIN_DM_RES_DWN
        #define SCL0_DM_OD_LO           PIN_DM_OD_LO
        #define SCL0_DM_OD_HI           PIN_DM_OD_HI
        #define SCL0_DM_STRONG          PIN_DM_STRONG
        #define SCL0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SCL0_MASK               SCL0__MASK
#define SCL0_SHIFT              SCL0__SHIFT
#define SCL0_WIDTH              1u

/* Interrupt constants */
#if defined(SCL0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SCL0_SetInterruptMode() function.
     *  @{
     */
        #define SCL0_INTR_NONE      (uint16)(0x0000u)
        #define SCL0_INTR_RISING    (uint16)(0x0001u)
        #define SCL0_INTR_FALLING   (uint16)(0x0002u)
        #define SCL0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SCL0_INTR_MASK      (0x01u) 
#endif /* (SCL0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SCL0_PS                     (* (reg8 *) SCL0__PS)
/* Data Register */
#define SCL0_DR                     (* (reg8 *) SCL0__DR)
/* Port Number */
#define SCL0_PRT_NUM                (* (reg8 *) SCL0__PRT) 
/* Connect to Analog Globals */                                                  
#define SCL0_AG                     (* (reg8 *) SCL0__AG)                       
/* Analog MUX bux enable */
#define SCL0_AMUX                   (* (reg8 *) SCL0__AMUX) 
/* Bidirectional Enable */                                                        
#define SCL0_BIE                    (* (reg8 *) SCL0__BIE)
/* Bit-mask for Aliased Register Access */
#define SCL0_BIT_MASK               (* (reg8 *) SCL0__BIT_MASK)
/* Bypass Enable */
#define SCL0_BYP                    (* (reg8 *) SCL0__BYP)
/* Port wide control signals */                                                   
#define SCL0_CTL                    (* (reg8 *) SCL0__CTL)
/* Drive Modes */
#define SCL0_DM0                    (* (reg8 *) SCL0__DM0) 
#define SCL0_DM1                    (* (reg8 *) SCL0__DM1)
#define SCL0_DM2                    (* (reg8 *) SCL0__DM2) 
/* Input Buffer Disable Override */
#define SCL0_INP_DIS                (* (reg8 *) SCL0__INP_DIS)
/* LCD Common or Segment Drive */
#define SCL0_LCD_COM_SEG            (* (reg8 *) SCL0__LCD_COM_SEG)
/* Enable Segment LCD */
#define SCL0_LCD_EN                 (* (reg8 *) SCL0__LCD_EN)
/* Slew Rate Control */
#define SCL0_SLW                    (* (reg8 *) SCL0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SCL0_PRTDSI__CAPS_SEL       (* (reg8 *) SCL0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SCL0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SCL0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SCL0_PRTDSI__OE_SEL0        (* (reg8 *) SCL0__PRTDSI__OE_SEL0) 
#define SCL0_PRTDSI__OE_SEL1        (* (reg8 *) SCL0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SCL0_PRTDSI__OUT_SEL0       (* (reg8 *) SCL0__PRTDSI__OUT_SEL0) 
#define SCL0_PRTDSI__OUT_SEL1       (* (reg8 *) SCL0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SCL0_PRTDSI__SYNC_OUT       (* (reg8 *) SCL0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SCL0__SIO_CFG)
    #define SCL0_SIO_HYST_EN        (* (reg8 *) SCL0__SIO_HYST_EN)
    #define SCL0_SIO_REG_HIFREQ     (* (reg8 *) SCL0__SIO_REG_HIFREQ)
    #define SCL0_SIO_CFG            (* (reg8 *) SCL0__SIO_CFG)
    #define SCL0_SIO_DIFF           (* (reg8 *) SCL0__SIO_DIFF)
#endif /* (SCL0__SIO_CFG) */

/* Interrupt Registers */
#if defined(SCL0__INTSTAT)
    #define SCL0_INTSTAT            (* (reg8 *) SCL0__INTSTAT)
    #define SCL0_SNAP               (* (reg8 *) SCL0__SNAP)
    
	#define SCL0_0_INTTYPE_REG 		(* (reg8 *) SCL0__0__INTTYPE)
#endif /* (SCL0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SCL0_H */


/* [] END OF FILE */
