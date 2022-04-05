/*******************************************************************************
* File Name: SDA1.h  
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

#if !defined(CY_PINS_SDA1_H) /* Pins SDA1_H */
#define CY_PINS_SDA1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SDA1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SDA1__PORT == 15 && ((SDA1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SDA1_Write(uint8 value);
void    SDA1_SetDriveMode(uint8 mode);
uint8   SDA1_ReadDataReg(void);
uint8   SDA1_Read(void);
void    SDA1_SetInterruptMode(uint16 position, uint16 mode);
uint8   SDA1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SDA1_SetDriveMode() function.
     *  @{
     */
        #define SDA1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SDA1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SDA1_DM_RES_UP          PIN_DM_RES_UP
        #define SDA1_DM_RES_DWN         PIN_DM_RES_DWN
        #define SDA1_DM_OD_LO           PIN_DM_OD_LO
        #define SDA1_DM_OD_HI           PIN_DM_OD_HI
        #define SDA1_DM_STRONG          PIN_DM_STRONG
        #define SDA1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SDA1_MASK               SDA1__MASK
#define SDA1_SHIFT              SDA1__SHIFT
#define SDA1_WIDTH              1u

/* Interrupt constants */
#if defined(SDA1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SDA1_SetInterruptMode() function.
     *  @{
     */
        #define SDA1_INTR_NONE      (uint16)(0x0000u)
        #define SDA1_INTR_RISING    (uint16)(0x0001u)
        #define SDA1_INTR_FALLING   (uint16)(0x0002u)
        #define SDA1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SDA1_INTR_MASK      (0x01u) 
#endif /* (SDA1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SDA1_PS                     (* (reg8 *) SDA1__PS)
/* Data Register */
#define SDA1_DR                     (* (reg8 *) SDA1__DR)
/* Port Number */
#define SDA1_PRT_NUM                (* (reg8 *) SDA1__PRT) 
/* Connect to Analog Globals */                                                  
#define SDA1_AG                     (* (reg8 *) SDA1__AG)                       
/* Analog MUX bux enable */
#define SDA1_AMUX                   (* (reg8 *) SDA1__AMUX) 
/* Bidirectional Enable */                                                        
#define SDA1_BIE                    (* (reg8 *) SDA1__BIE)
/* Bit-mask for Aliased Register Access */
#define SDA1_BIT_MASK               (* (reg8 *) SDA1__BIT_MASK)
/* Bypass Enable */
#define SDA1_BYP                    (* (reg8 *) SDA1__BYP)
/* Port wide control signals */                                                   
#define SDA1_CTL                    (* (reg8 *) SDA1__CTL)
/* Drive Modes */
#define SDA1_DM0                    (* (reg8 *) SDA1__DM0) 
#define SDA1_DM1                    (* (reg8 *) SDA1__DM1)
#define SDA1_DM2                    (* (reg8 *) SDA1__DM2) 
/* Input Buffer Disable Override */
#define SDA1_INP_DIS                (* (reg8 *) SDA1__INP_DIS)
/* LCD Common or Segment Drive */
#define SDA1_LCD_COM_SEG            (* (reg8 *) SDA1__LCD_COM_SEG)
/* Enable Segment LCD */
#define SDA1_LCD_EN                 (* (reg8 *) SDA1__LCD_EN)
/* Slew Rate Control */
#define SDA1_SLW                    (* (reg8 *) SDA1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SDA1_PRTDSI__CAPS_SEL       (* (reg8 *) SDA1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SDA1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SDA1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SDA1_PRTDSI__OE_SEL0        (* (reg8 *) SDA1__PRTDSI__OE_SEL0) 
#define SDA1_PRTDSI__OE_SEL1        (* (reg8 *) SDA1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SDA1_PRTDSI__OUT_SEL0       (* (reg8 *) SDA1__PRTDSI__OUT_SEL0) 
#define SDA1_PRTDSI__OUT_SEL1       (* (reg8 *) SDA1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SDA1_PRTDSI__SYNC_OUT       (* (reg8 *) SDA1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SDA1__SIO_CFG)
    #define SDA1_SIO_HYST_EN        (* (reg8 *) SDA1__SIO_HYST_EN)
    #define SDA1_SIO_REG_HIFREQ     (* (reg8 *) SDA1__SIO_REG_HIFREQ)
    #define SDA1_SIO_CFG            (* (reg8 *) SDA1__SIO_CFG)
    #define SDA1_SIO_DIFF           (* (reg8 *) SDA1__SIO_DIFF)
#endif /* (SDA1__SIO_CFG) */

/* Interrupt Registers */
#if defined(SDA1__INTSTAT)
    #define SDA1_INTSTAT            (* (reg8 *) SDA1__INTSTAT)
    #define SDA1_SNAP               (* (reg8 *) SDA1__SNAP)
    
	#define SDA1_0_INTTYPE_REG 		(* (reg8 *) SDA1__0__INTTYPE)
#endif /* (SDA1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SDA1_H */


/* [] END OF FILE */
