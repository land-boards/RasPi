/*******************************************************************************
* File Name: PORT1D2.h  
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

#if !defined(CY_PINS_PORT1D2_H) /* Pins PORT1D2_H */
#define CY_PINS_PORT1D2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT1D2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT1D2__PORT == 15 && ((PORT1D2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT1D2_Write(uint8 value);
void    PORT1D2_SetDriveMode(uint8 mode);
uint8   PORT1D2_ReadDataReg(void);
uint8   PORT1D2_Read(void);
void    PORT1D2_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT1D2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT1D2_SetDriveMode() function.
     *  @{
     */
        #define PORT1D2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT1D2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT1D2_DM_RES_UP          PIN_DM_RES_UP
        #define PORT1D2_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT1D2_DM_OD_LO           PIN_DM_OD_LO
        #define PORT1D2_DM_OD_HI           PIN_DM_OD_HI
        #define PORT1D2_DM_STRONG          PIN_DM_STRONG
        #define PORT1D2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT1D2_MASK               PORT1D2__MASK
#define PORT1D2_SHIFT              PORT1D2__SHIFT
#define PORT1D2_WIDTH              1u

/* Interrupt constants */
#if defined(PORT1D2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT1D2_SetInterruptMode() function.
     *  @{
     */
        #define PORT1D2_INTR_NONE      (uint16)(0x0000u)
        #define PORT1D2_INTR_RISING    (uint16)(0x0001u)
        #define PORT1D2_INTR_FALLING   (uint16)(0x0002u)
        #define PORT1D2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT1D2_INTR_MASK      (0x01u) 
#endif /* (PORT1D2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT1D2_PS                     (* (reg8 *) PORT1D2__PS)
/* Data Register */
#define PORT1D2_DR                     (* (reg8 *) PORT1D2__DR)
/* Port Number */
#define PORT1D2_PRT_NUM                (* (reg8 *) PORT1D2__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT1D2_AG                     (* (reg8 *) PORT1D2__AG)                       
/* Analog MUX bux enable */
#define PORT1D2_AMUX                   (* (reg8 *) PORT1D2__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT1D2_BIE                    (* (reg8 *) PORT1D2__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT1D2_BIT_MASK               (* (reg8 *) PORT1D2__BIT_MASK)
/* Bypass Enable */
#define PORT1D2_BYP                    (* (reg8 *) PORT1D2__BYP)
/* Port wide control signals */                                                   
#define PORT1D2_CTL                    (* (reg8 *) PORT1D2__CTL)
/* Drive Modes */
#define PORT1D2_DM0                    (* (reg8 *) PORT1D2__DM0) 
#define PORT1D2_DM1                    (* (reg8 *) PORT1D2__DM1)
#define PORT1D2_DM2                    (* (reg8 *) PORT1D2__DM2) 
/* Input Buffer Disable Override */
#define PORT1D2_INP_DIS                (* (reg8 *) PORT1D2__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT1D2_LCD_COM_SEG            (* (reg8 *) PORT1D2__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT1D2_LCD_EN                 (* (reg8 *) PORT1D2__LCD_EN)
/* Slew Rate Control */
#define PORT1D2_SLW                    (* (reg8 *) PORT1D2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT1D2_PRTDSI__CAPS_SEL       (* (reg8 *) PORT1D2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT1D2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT1D2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT1D2_PRTDSI__OE_SEL0        (* (reg8 *) PORT1D2__PRTDSI__OE_SEL0) 
#define PORT1D2_PRTDSI__OE_SEL1        (* (reg8 *) PORT1D2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT1D2_PRTDSI__OUT_SEL0       (* (reg8 *) PORT1D2__PRTDSI__OUT_SEL0) 
#define PORT1D2_PRTDSI__OUT_SEL1       (* (reg8 *) PORT1D2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT1D2_PRTDSI__SYNC_OUT       (* (reg8 *) PORT1D2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT1D2__SIO_CFG)
    #define PORT1D2_SIO_HYST_EN        (* (reg8 *) PORT1D2__SIO_HYST_EN)
    #define PORT1D2_SIO_REG_HIFREQ     (* (reg8 *) PORT1D2__SIO_REG_HIFREQ)
    #define PORT1D2_SIO_CFG            (* (reg8 *) PORT1D2__SIO_CFG)
    #define PORT1D2_SIO_DIFF           (* (reg8 *) PORT1D2__SIO_DIFF)
#endif /* (PORT1D2__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT1D2__INTSTAT)
    #define PORT1D2_INTSTAT            (* (reg8 *) PORT1D2__INTSTAT)
    #define PORT1D2_SNAP               (* (reg8 *) PORT1D2__SNAP)
    
	#define PORT1D2_0_INTTYPE_REG 		(* (reg8 *) PORT1D2__0__INTTYPE)
#endif /* (PORT1D2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT1D2_H */


/* [] END OF FILE */
