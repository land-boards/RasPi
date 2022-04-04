/*******************************************************************************
* File Name: PORT4D1.h  
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

#if !defined(CY_PINS_PORT4D1_H) /* Pins PORT4D1_H */
#define CY_PINS_PORT4D1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT4D1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT4D1__PORT == 15 && ((PORT4D1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT4D1_Write(uint8 value);
void    PORT4D1_SetDriveMode(uint8 mode);
uint8   PORT4D1_ReadDataReg(void);
uint8   PORT4D1_Read(void);
void    PORT4D1_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT4D1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT4D1_SetDriveMode() function.
     *  @{
     */
        #define PORT4D1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT4D1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT4D1_DM_RES_UP          PIN_DM_RES_UP
        #define PORT4D1_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT4D1_DM_OD_LO           PIN_DM_OD_LO
        #define PORT4D1_DM_OD_HI           PIN_DM_OD_HI
        #define PORT4D1_DM_STRONG          PIN_DM_STRONG
        #define PORT4D1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT4D1_MASK               PORT4D1__MASK
#define PORT4D1_SHIFT              PORT4D1__SHIFT
#define PORT4D1_WIDTH              1u

/* Interrupt constants */
#if defined(PORT4D1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT4D1_SetInterruptMode() function.
     *  @{
     */
        #define PORT4D1_INTR_NONE      (uint16)(0x0000u)
        #define PORT4D1_INTR_RISING    (uint16)(0x0001u)
        #define PORT4D1_INTR_FALLING   (uint16)(0x0002u)
        #define PORT4D1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT4D1_INTR_MASK      (0x01u) 
#endif /* (PORT4D1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT4D1_PS                     (* (reg8 *) PORT4D1__PS)
/* Data Register */
#define PORT4D1_DR                     (* (reg8 *) PORT4D1__DR)
/* Port Number */
#define PORT4D1_PRT_NUM                (* (reg8 *) PORT4D1__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT4D1_AG                     (* (reg8 *) PORT4D1__AG)                       
/* Analog MUX bux enable */
#define PORT4D1_AMUX                   (* (reg8 *) PORT4D1__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT4D1_BIE                    (* (reg8 *) PORT4D1__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT4D1_BIT_MASK               (* (reg8 *) PORT4D1__BIT_MASK)
/* Bypass Enable */
#define PORT4D1_BYP                    (* (reg8 *) PORT4D1__BYP)
/* Port wide control signals */                                                   
#define PORT4D1_CTL                    (* (reg8 *) PORT4D1__CTL)
/* Drive Modes */
#define PORT4D1_DM0                    (* (reg8 *) PORT4D1__DM0) 
#define PORT4D1_DM1                    (* (reg8 *) PORT4D1__DM1)
#define PORT4D1_DM2                    (* (reg8 *) PORT4D1__DM2) 
/* Input Buffer Disable Override */
#define PORT4D1_INP_DIS                (* (reg8 *) PORT4D1__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT4D1_LCD_COM_SEG            (* (reg8 *) PORT4D1__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT4D1_LCD_EN                 (* (reg8 *) PORT4D1__LCD_EN)
/* Slew Rate Control */
#define PORT4D1_SLW                    (* (reg8 *) PORT4D1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT4D1_PRTDSI__CAPS_SEL       (* (reg8 *) PORT4D1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT4D1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT4D1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT4D1_PRTDSI__OE_SEL0        (* (reg8 *) PORT4D1__PRTDSI__OE_SEL0) 
#define PORT4D1_PRTDSI__OE_SEL1        (* (reg8 *) PORT4D1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT4D1_PRTDSI__OUT_SEL0       (* (reg8 *) PORT4D1__PRTDSI__OUT_SEL0) 
#define PORT4D1_PRTDSI__OUT_SEL1       (* (reg8 *) PORT4D1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT4D1_PRTDSI__SYNC_OUT       (* (reg8 *) PORT4D1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT4D1__SIO_CFG)
    #define PORT4D1_SIO_HYST_EN        (* (reg8 *) PORT4D1__SIO_HYST_EN)
    #define PORT4D1_SIO_REG_HIFREQ     (* (reg8 *) PORT4D1__SIO_REG_HIFREQ)
    #define PORT4D1_SIO_CFG            (* (reg8 *) PORT4D1__SIO_CFG)
    #define PORT4D1_SIO_DIFF           (* (reg8 *) PORT4D1__SIO_DIFF)
#endif /* (PORT4D1__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT4D1__INTSTAT)
    #define PORT4D1_INTSTAT            (* (reg8 *) PORT4D1__INTSTAT)
    #define PORT4D1_SNAP               (* (reg8 *) PORT4D1__SNAP)
    
	#define PORT4D1_0_INTTYPE_REG 		(* (reg8 *) PORT4D1__0__INTTYPE)
#endif /* (PORT4D1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT4D1_H */


/* [] END OF FILE */
