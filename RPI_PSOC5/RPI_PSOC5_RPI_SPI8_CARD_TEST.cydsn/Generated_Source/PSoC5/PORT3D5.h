/*******************************************************************************
* File Name: PORT3D5.h  
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

#if !defined(CY_PINS_PORT3D5_H) /* Pins PORT3D5_H */
#define CY_PINS_PORT3D5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PORT3D5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PORT3D5__PORT == 15 && ((PORT3D5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PORT3D5_Write(uint8 value);
void    PORT3D5_SetDriveMode(uint8 mode);
uint8   PORT3D5_ReadDataReg(void);
uint8   PORT3D5_Read(void);
void    PORT3D5_SetInterruptMode(uint16 position, uint16 mode);
uint8   PORT3D5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PORT3D5_SetDriveMode() function.
     *  @{
     */
        #define PORT3D5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PORT3D5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PORT3D5_DM_RES_UP          PIN_DM_RES_UP
        #define PORT3D5_DM_RES_DWN         PIN_DM_RES_DWN
        #define PORT3D5_DM_OD_LO           PIN_DM_OD_LO
        #define PORT3D5_DM_OD_HI           PIN_DM_OD_HI
        #define PORT3D5_DM_STRONG          PIN_DM_STRONG
        #define PORT3D5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PORT3D5_MASK               PORT3D5__MASK
#define PORT3D5_SHIFT              PORT3D5__SHIFT
#define PORT3D5_WIDTH              1u

/* Interrupt constants */
#if defined(PORT3D5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PORT3D5_SetInterruptMode() function.
     *  @{
     */
        #define PORT3D5_INTR_NONE      (uint16)(0x0000u)
        #define PORT3D5_INTR_RISING    (uint16)(0x0001u)
        #define PORT3D5_INTR_FALLING   (uint16)(0x0002u)
        #define PORT3D5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PORT3D5_INTR_MASK      (0x01u) 
#endif /* (PORT3D5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PORT3D5_PS                     (* (reg8 *) PORT3D5__PS)
/* Data Register */
#define PORT3D5_DR                     (* (reg8 *) PORT3D5__DR)
/* Port Number */
#define PORT3D5_PRT_NUM                (* (reg8 *) PORT3D5__PRT) 
/* Connect to Analog Globals */                                                  
#define PORT3D5_AG                     (* (reg8 *) PORT3D5__AG)                       
/* Analog MUX bux enable */
#define PORT3D5_AMUX                   (* (reg8 *) PORT3D5__AMUX) 
/* Bidirectional Enable */                                                        
#define PORT3D5_BIE                    (* (reg8 *) PORT3D5__BIE)
/* Bit-mask for Aliased Register Access */
#define PORT3D5_BIT_MASK               (* (reg8 *) PORT3D5__BIT_MASK)
/* Bypass Enable */
#define PORT3D5_BYP                    (* (reg8 *) PORT3D5__BYP)
/* Port wide control signals */                                                   
#define PORT3D5_CTL                    (* (reg8 *) PORT3D5__CTL)
/* Drive Modes */
#define PORT3D5_DM0                    (* (reg8 *) PORT3D5__DM0) 
#define PORT3D5_DM1                    (* (reg8 *) PORT3D5__DM1)
#define PORT3D5_DM2                    (* (reg8 *) PORT3D5__DM2) 
/* Input Buffer Disable Override */
#define PORT3D5_INP_DIS                (* (reg8 *) PORT3D5__INP_DIS)
/* LCD Common or Segment Drive */
#define PORT3D5_LCD_COM_SEG            (* (reg8 *) PORT3D5__LCD_COM_SEG)
/* Enable Segment LCD */
#define PORT3D5_LCD_EN                 (* (reg8 *) PORT3D5__LCD_EN)
/* Slew Rate Control */
#define PORT3D5_SLW                    (* (reg8 *) PORT3D5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PORT3D5_PRTDSI__CAPS_SEL       (* (reg8 *) PORT3D5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PORT3D5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PORT3D5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PORT3D5_PRTDSI__OE_SEL0        (* (reg8 *) PORT3D5__PRTDSI__OE_SEL0) 
#define PORT3D5_PRTDSI__OE_SEL1        (* (reg8 *) PORT3D5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PORT3D5_PRTDSI__OUT_SEL0       (* (reg8 *) PORT3D5__PRTDSI__OUT_SEL0) 
#define PORT3D5_PRTDSI__OUT_SEL1       (* (reg8 *) PORT3D5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PORT3D5_PRTDSI__SYNC_OUT       (* (reg8 *) PORT3D5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PORT3D5__SIO_CFG)
    #define PORT3D5_SIO_HYST_EN        (* (reg8 *) PORT3D5__SIO_HYST_EN)
    #define PORT3D5_SIO_REG_HIFREQ     (* (reg8 *) PORT3D5__SIO_REG_HIFREQ)
    #define PORT3D5_SIO_CFG            (* (reg8 *) PORT3D5__SIO_CFG)
    #define PORT3D5_SIO_DIFF           (* (reg8 *) PORT3D5__SIO_DIFF)
#endif /* (PORT3D5__SIO_CFG) */

/* Interrupt Registers */
#if defined(PORT3D5__INTSTAT)
    #define PORT3D5_INTSTAT            (* (reg8 *) PORT3D5__INTSTAT)
    #define PORT3D5_SNAP               (* (reg8 *) PORT3D5__SNAP)
    
	#define PORT3D5_0_INTTYPE_REG 		(* (reg8 *) PORT3D5__0__INTTYPE)
#endif /* (PORT3D5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PORT3D5_H */


/* [] END OF FILE */
