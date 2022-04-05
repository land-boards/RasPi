/*******************************************************************************
* File Name: PORT0D6.h  
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

#if !defined(CY_PINS_PORT0D6_H) /* Pins PORT0D6_H */
#define CY_PINS_PORT0D6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT0D6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT0D6__PORT == 15 && ((PORT0D6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT0D6_Write(uint8 value);
void    PORT0D6_SetDriveMode(uint8 mode);
uint8   PORT0D6_ReadDataReg(void);
uint8   PORT0D6_Read(void);
void    PORT0D6_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT0D6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT0D6_SetDriveMode() function.
     *  @{
     */
        #define PORT0D6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT0D6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT0D6_DM_RES_UP          PIN_DM_RES_UP
        #define PORT0D6_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT0D6_DM_OD_LO           PIN_DM_OD_LO
        #define PORT0D6_DM_OD_HI           PIN_DM_OD_HI
        #define PORT0D6_DM_STRONG          PIN_DM_STRONG
        #define PORT0D6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT0D6_MASK               PORT0D6__MASK
#define PORT0D6_SHIFT              PORT0D6__SHIFT
#define PORT0D6_WIDTH              1u

/* Interrupt constants */
#if defined(PORT0D6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT0D6_SetInterruptMode() function.
     *  @{
     */
        #define PORT0D6_INTR_NONE      (uint16)(0x0000u)
        #define PORT0D6_INTR_RISING    (uint16)(0x0001u)
        #define PORT0D6_INTR_FALLING   (uint16)(0x0002u)
        #define PORT0D6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT0D6_INTR_MASK      (0x01u) 
#endif /* (PORT0D6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT0D6_PS                     (* (reg8 *) PORT0D6__PS)
/* Data Register */
#define PORT0D6_DR                     (* (reg8 *) PORT0D6__DR)
/* Port Number */
#define PORT0D6_PRT_NUM                (* (reg8 *) PORT0D6__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT0D6_AG                     (* (reg8 *) PORT0D6__AG)                       
/* Analog MUX bux enable */
#define PORT0D6_AMUX                   (* (reg8 *) PORT0D6__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT0D6_BIE                    (* (reg8 *) PORT0D6__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT0D6_BIT_MASK               (* (reg8 *) PORT0D6__BIT_MASK)
/* Bypass Enable */
#define PORT0D6_BYP                    (* (reg8 *) PORT0D6__BYP)
/* Port wide control signals */                                                   
#define PORT0D6_CTL                    (* (reg8 *) PORT0D6__CTL)
/* Drive Modes */
#define PORT0D6_DM0                    (* (reg8 *) PORT0D6__DM0) 
#define PORT0D6_DM1                    (* (reg8 *) PORT0D6__DM1)
#define PORT0D6_DM2                    (* (reg8 *) PORT0D6__DM2) 
/* Input Buffer Disable Override */
#define PORT0D6_INP_DIS                (* (reg8 *) PORT0D6__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT0D6_LCD_COM_SEG            (* (reg8 *) PORT0D6__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT0D6_LCD_EN                 (* (reg8 *) PORT0D6__LCD_EN)
/* Slew Rate Control */
#define PORT0D6_SLW                    (* (reg8 *) PORT0D6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT0D6_PRTDSI__CAPS_SEL       (* (reg8 *) PORT0D6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT0D6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT0D6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT0D6_PRTDSI__OE_SEL0        (* (reg8 *) PORT0D6__PRTDSI__OE_SEL0) 
#define PORT0D6_PRTDSI__OE_SEL1        (* (reg8 *) PORT0D6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT0D6_PRTDSI__OUT_SEL0       (* (reg8 *) PORT0D6__PRTDSI__OUT_SEL0) 
#define PORT0D6_PRTDSI__OUT_SEL1       (* (reg8 *) PORT0D6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT0D6_PRTDSI__SYNC_OUT       (* (reg8 *) PORT0D6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT0D6__SIO_CFG)
    #define PORT0D6_SIO_HYST_EN        (* (reg8 *) PORT0D6__SIO_HYST_EN)
    #define PORT0D6_SIO_REG_HIFREQ     (* (reg8 *) PORT0D6__SIO_REG_HIFREQ)
    #define PORT0D6_SIO_CFG            (* (reg8 *) PORT0D6__SIO_CFG)
    #define PORT0D6_SIO_DIFF           (* (reg8 *) PORT0D6__SIO_DIFF)
#endif /* (PORT0D6__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT0D6__INTSTAT)
    #define PORT0D6_INTSTAT            (* (reg8 *) PORT0D6__INTSTAT)
    #define PORT0D6_SNAP               (* (reg8 *) PORT0D6__SNAP)
    
	#define PORT0D6_0_INTTYPE_REG 		(* (reg8 *) PORT0D6__0__INTTYPE)
#endif /* (PORT0D6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT0D6_H */


/* [] END OF FILE */
