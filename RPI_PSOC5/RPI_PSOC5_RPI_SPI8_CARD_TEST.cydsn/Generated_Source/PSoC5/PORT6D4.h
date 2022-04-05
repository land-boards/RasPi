/*******************************************************************************
* File Name: PORT6D4.h  
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

#if !defined(CY_PINS_PORT6D4_H) /* Pins PORT6D4_H */
#define CY_PINS_PORT6D4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT6D4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT6D4__PORT == 15 && ((PORT6D4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT6D4_Write(uint8 value);
void    PORT6D4_SetDriveMode(uint8 mode);
uint8   PORT6D4_ReadDataReg(void);
uint8   PORT6D4_Read(void);
void    PORT6D4_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT6D4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT6D4_SetDriveMode() function.
     *  @{
     */
        #define PORT6D4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT6D4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT6D4_DM_RES_UP          PIN_DM_RES_UP
        #define PORT6D4_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT6D4_DM_OD_LO           PIN_DM_OD_LO
        #define PORT6D4_DM_OD_HI           PIN_DM_OD_HI
        #define PORT6D4_DM_STRONG          PIN_DM_STRONG
        #define PORT6D4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT6D4_MASK               PORT6D4__MASK
#define PORT6D4_SHIFT              PORT6D4__SHIFT
#define PORT6D4_WIDTH              1u

/* Interrupt constants */
#if defined(PORT6D4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT6D4_SetInterruptMode() function.
     *  @{
     */
        #define PORT6D4_INTR_NONE      (uint16)(0x0000u)
        #define PORT6D4_INTR_RISING    (uint16)(0x0001u)
        #define PORT6D4_INTR_FALLING   (uint16)(0x0002u)
        #define PORT6D4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT6D4_INTR_MASK      (0x01u) 
#endif /* (PORT6D4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT6D4_PS                     (* (reg8 *) PORT6D4__PS)
/* Data Register */
#define PORT6D4_DR                     (* (reg8 *) PORT6D4__DR)
/* Port Number */
#define PORT6D4_PRT_NUM                (* (reg8 *) PORT6D4__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT6D4_AG                     (* (reg8 *) PORT6D4__AG)                       
/* Analog MUX bux enable */
#define PORT6D4_AMUX                   (* (reg8 *) PORT6D4__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT6D4_BIE                    (* (reg8 *) PORT6D4__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT6D4_BIT_MASK               (* (reg8 *) PORT6D4__BIT_MASK)
/* Bypass Enable */
#define PORT6D4_BYP                    (* (reg8 *) PORT6D4__BYP)
/* Port wide control signals */                                                   
#define PORT6D4_CTL                    (* (reg8 *) PORT6D4__CTL)
/* Drive Modes */
#define PORT6D4_DM0                    (* (reg8 *) PORT6D4__DM0) 
#define PORT6D4_DM1                    (* (reg8 *) PORT6D4__DM1)
#define PORT6D4_DM2                    (* (reg8 *) PORT6D4__DM2) 
/* Input Buffer Disable Override */
#define PORT6D4_INP_DIS                (* (reg8 *) PORT6D4__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT6D4_LCD_COM_SEG            (* (reg8 *) PORT6D4__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT6D4_LCD_EN                 (* (reg8 *) PORT6D4__LCD_EN)
/* Slew Rate Control */
#define PORT6D4_SLW                    (* (reg8 *) PORT6D4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT6D4_PRTDSI__CAPS_SEL       (* (reg8 *) PORT6D4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT6D4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT6D4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT6D4_PRTDSI__OE_SEL0        (* (reg8 *) PORT6D4__PRTDSI__OE_SEL0) 
#define PORT6D4_PRTDSI__OE_SEL1        (* (reg8 *) PORT6D4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT6D4_PRTDSI__OUT_SEL0       (* (reg8 *) PORT6D4__PRTDSI__OUT_SEL0) 
#define PORT6D4_PRTDSI__OUT_SEL1       (* (reg8 *) PORT6D4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT6D4_PRTDSI__SYNC_OUT       (* (reg8 *) PORT6D4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT6D4__SIO_CFG)
    #define PORT6D4_SIO_HYST_EN        (* (reg8 *) PORT6D4__SIO_HYST_EN)
    #define PORT6D4_SIO_REG_HIFREQ     (* (reg8 *) PORT6D4__SIO_REG_HIFREQ)
    #define PORT6D4_SIO_CFG            (* (reg8 *) PORT6D4__SIO_CFG)
    #define PORT6D4_SIO_DIFF           (* (reg8 *) PORT6D4__SIO_DIFF)
#endif /* (PORT6D4__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT6D4__INTSTAT)
    #define PORT6D4_INTSTAT            (* (reg8 *) PORT6D4__INTSTAT)
    #define PORT6D4_SNAP               (* (reg8 *) PORT6D4__SNAP)
    
	#define PORT6D4_0_INTTYPE_REG 		(* (reg8 *) PORT6D4__0__INTTYPE)
#endif /* (PORT6D4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT6D4_H */


/* [] END OF FILE */
