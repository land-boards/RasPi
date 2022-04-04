/*******************************************************************************
* File Name: PORT2D7.h  
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

#if !defined(CY_PINS_PORT2D7_H) /* Pins PORT2D7_H */
#define CY_PINS_PORT2D7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT2D7_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT2D7__PORT == 15 && ((PORT2D7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT2D7_Write(uint8 value);
void    PORT2D7_SetDriveMode(uint8 mode);
uint8   PORT2D7_ReadDataReg(void);
uint8   PORT2D7_Read(void);
void    PORT2D7_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT2D7_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT2D7_SetDriveMode() function.
     *  @{
     */
        #define PORT2D7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT2D7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT2D7_DM_RES_UP          PIN_DM_RES_UP
        #define PORT2D7_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT2D7_DM_OD_LO           PIN_DM_OD_LO
        #define PORT2D7_DM_OD_HI           PIN_DM_OD_HI
        #define PORT2D7_DM_STRONG          PIN_DM_STRONG
        #define PORT2D7_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT2D7_MASK               PORT2D7__MASK
#define PORT2D7_SHIFT              PORT2D7__SHIFT
#define PORT2D7_WIDTH              1u

/* Interrupt constants */
#if defined(PORT2D7__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT2D7_SetInterruptMode() function.
     *  @{
     */
        #define PORT2D7_INTR_NONE      (uint16)(0x0000u)
        #define PORT2D7_INTR_RISING    (uint16)(0x0001u)
        #define PORT2D7_INTR_FALLING   (uint16)(0x0002u)
        #define PORT2D7_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT2D7_INTR_MASK      (0x01u) 
#endif /* (PORT2D7__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT2D7_PS                     (* (reg8 *) PORT2D7__PS)
/* Data Register */
#define PORT2D7_DR                     (* (reg8 *) PORT2D7__DR)
/* Port Number */
#define PORT2D7_PRT_NUM                (* (reg8 *) PORT2D7__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT2D7_AG                     (* (reg8 *) PORT2D7__AG)                       
/* Analog MUX bux enable */
#define PORT2D7_AMUX                   (* (reg8 *) PORT2D7__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT2D7_BIE                    (* (reg8 *) PORT2D7__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT2D7_BIT_MASK               (* (reg8 *) PORT2D7__BIT_MASK)
/* Bypass Enable */
#define PORT2D7_BYP                    (* (reg8 *) PORT2D7__BYP)
/* Port wide control signals */                                                   
#define PORT2D7_CTL                    (* (reg8 *) PORT2D7__CTL)
/* Drive Modes */
#define PORT2D7_DM0                    (* (reg8 *) PORT2D7__DM0) 
#define PORT2D7_DM1                    (* (reg8 *) PORT2D7__DM1)
#define PORT2D7_DM2                    (* (reg8 *) PORT2D7__DM2) 
/* Input Buffer Disable Override */
#define PORT2D7_INP_DIS                (* (reg8 *) PORT2D7__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT2D7_LCD_COM_SEG            (* (reg8 *) PORT2D7__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT2D7_LCD_EN                 (* (reg8 *) PORT2D7__LCD_EN)
/* Slew Rate Control */
#define PORT2D7_SLW                    (* (reg8 *) PORT2D7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT2D7_PRTDSI__CAPS_SEL       (* (reg8 *) PORT2D7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT2D7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT2D7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT2D7_PRTDSI__OE_SEL0        (* (reg8 *) PORT2D7__PRTDSI__OE_SEL0) 
#define PORT2D7_PRTDSI__OE_SEL1        (* (reg8 *) PORT2D7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT2D7_PRTDSI__OUT_SEL0       (* (reg8 *) PORT2D7__PRTDSI__OUT_SEL0) 
#define PORT2D7_PRTDSI__OUT_SEL1       (* (reg8 *) PORT2D7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT2D7_PRTDSI__SYNC_OUT       (* (reg8 *) PORT2D7__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT2D7__SIO_CFG)
    #define PORT2D7_SIO_HYST_EN        (* (reg8 *) PORT2D7__SIO_HYST_EN)
    #define PORT2D7_SIO_REG_HIFREQ     (* (reg8 *) PORT2D7__SIO_REG_HIFREQ)
    #define PORT2D7_SIO_CFG            (* (reg8 *) PORT2D7__SIO_CFG)
    #define PORT2D7_SIO_DIFF           (* (reg8 *) PORT2D7__SIO_DIFF)
#endif /* (PORT2D7__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT2D7__INTSTAT)
    #define PORT2D7_INTSTAT            (* (reg8 *) PORT2D7__INTSTAT)
    #define PORT2D7_SNAP               (* (reg8 *) PORT2D7__SNAP)
    
	#define PORT2D7_0_INTTYPE_REG 		(* (reg8 *) PORT2D7__0__INTTYPE)
#endif /* (PORT2D7__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT2D7_H */


/* [] END OF FILE */
