/*******************************************************************************
* File Name: PORT5D0.h  
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

#if !defined(CY_PINS_PORT5D0_H) /* Pins PORT5D0_H */
#define CY_PINS_PORT5D0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT5D0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT5D0__PORT == 15 && ((PORT5D0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT5D0_Write(uint8 value);
void    PORT5D0_SetDriveMode(uint8 mode);
uint8   PORT5D0_ReadDataReg(void);
uint8   PORT5D0_Read(void);
void    PORT5D0_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT5D0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT5D0_SetDriveMode() function.
     *  @{
     */
        #define PORT5D0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT5D0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT5D0_DM_RES_UP          PIN_DM_RES_UP
        #define PORT5D0_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT5D0_DM_OD_LO           PIN_DM_OD_LO
        #define PORT5D0_DM_OD_HI           PIN_DM_OD_HI
        #define PORT5D0_DM_STRONG          PIN_DM_STRONG
        #define PORT5D0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT5D0_MASK               PORT5D0__MASK
#define PORT5D0_SHIFT              PORT5D0__SHIFT
#define PORT5D0_WIDTH              1u

/* Interrupt constants */
#if defined(PORT5D0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT5D0_SetInterruptMode() function.
     *  @{
     */
        #define PORT5D0_INTR_NONE      (uint16)(0x0000u)
        #define PORT5D0_INTR_RISING    (uint16)(0x0001u)
        #define PORT5D0_INTR_FALLING   (uint16)(0x0002u)
        #define PORT5D0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT5D0_INTR_MASK      (0x01u) 
#endif /* (PORT5D0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT5D0_PS                     (* (reg8 *) PORT5D0__PS)
/* Data Register */
#define PORT5D0_DR                     (* (reg8 *) PORT5D0__DR)
/* Port Number */
#define PORT5D0_PRT_NUM                (* (reg8 *) PORT5D0__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT5D0_AG                     (* (reg8 *) PORT5D0__AG)                       
/* Analog MUX bux enable */
#define PORT5D0_AMUX                   (* (reg8 *) PORT5D0__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT5D0_BIE                    (* (reg8 *) PORT5D0__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT5D0_BIT_MASK               (* (reg8 *) PORT5D0__BIT_MASK)
/* Bypass Enable */
#define PORT5D0_BYP                    (* (reg8 *) PORT5D0__BYP)
/* Port wide control signals */                                                   
#define PORT5D0_CTL                    (* (reg8 *) PORT5D0__CTL)
/* Drive Modes */
#define PORT5D0_DM0                    (* (reg8 *) PORT5D0__DM0) 
#define PORT5D0_DM1                    (* (reg8 *) PORT5D0__DM1)
#define PORT5D0_DM2                    (* (reg8 *) PORT5D0__DM2) 
/* Input Buffer Disable Override */
#define PORT5D0_INP_DIS                (* (reg8 *) PORT5D0__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT5D0_LCD_COM_SEG            (* (reg8 *) PORT5D0__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT5D0_LCD_EN                 (* (reg8 *) PORT5D0__LCD_EN)
/* Slew Rate Control */
#define PORT5D0_SLW                    (* (reg8 *) PORT5D0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT5D0_PRTDSI__CAPS_SEL       (* (reg8 *) PORT5D0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT5D0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT5D0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT5D0_PRTDSI__OE_SEL0        (* (reg8 *) PORT5D0__PRTDSI__OE_SEL0) 
#define PORT5D0_PRTDSI__OE_SEL1        (* (reg8 *) PORT5D0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT5D0_PRTDSI__OUT_SEL0       (* (reg8 *) PORT5D0__PRTDSI__OUT_SEL0) 
#define PORT5D0_PRTDSI__OUT_SEL1       (* (reg8 *) PORT5D0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT5D0_PRTDSI__SYNC_OUT       (* (reg8 *) PORT5D0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT5D0__SIO_CFG)
    #define PORT5D0_SIO_HYST_EN        (* (reg8 *) PORT5D0__SIO_HYST_EN)
    #define PORT5D0_SIO_REG_HIFREQ     (* (reg8 *) PORT5D0__SIO_REG_HIFREQ)
    #define PORT5D0_SIO_CFG            (* (reg8 *) PORT5D0__SIO_CFG)
    #define PORT5D0_SIO_DIFF           (* (reg8 *) PORT5D0__SIO_DIFF)
#endif /* (PORT5D0__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT5D0__INTSTAT)
    #define PORT5D0_INTSTAT            (* (reg8 *) PORT5D0__INTSTAT)
    #define PORT5D0_SNAP               (* (reg8 *) PORT5D0__SNAP)
    
	#define PORT5D0_0_INTTYPE_REG 		(* (reg8 *) PORT5D0__0__INTTYPE)
#endif /* (PORT5D0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT5D0_H */


/* [] END OF FILE */
