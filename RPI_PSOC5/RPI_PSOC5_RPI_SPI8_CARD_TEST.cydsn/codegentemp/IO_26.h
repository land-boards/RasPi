/*******************************************************************************
* File Name: IO_26.h  
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

#if !defined(CY_PINS_IO_26_H) /* Pins IO_26_H */
#define CY_PINS_IO_26_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_26_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_26__PORT == 15 && ((IO_26__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_26_Write(uint8 value);
void    IO_26_SetDriveMode(uint8 mode);
uint8   IO_26_ReadDataReg(void);
uint8   IO_26_Read(void);
void    IO_26_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_26_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_26_SetDriveMode() function.
     *  @{
     */
        #define IO_26_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_26_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_26_DM_RES_UP          PIN_DM_RES_UP
        #define IO_26_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_26_DM_OD_LO           PIN_DM_OD_LO
        #define IO_26_DM_OD_HI           PIN_DM_OD_HI
        #define IO_26_DM_STRONG          PIN_DM_STRONG
        #define IO_26_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_26_MASK               IO_26__MASK
#define IO_26_SHIFT              IO_26__SHIFT
#define IO_26_WIDTH              1u

/* Interrupt constants */
#if defined(IO_26__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_26_SetInterruptMode() function.
     *  @{
     */
        #define IO_26_INTR_NONE      (uint16)(0x0000u)
        #define IO_26_INTR_RISING    (uint16)(0x0001u)
        #define IO_26_INTR_FALLING   (uint16)(0x0002u)
        #define IO_26_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_26_INTR_MASK      (0x01u) 
#endif /* (IO_26__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_26_PS                     (* (reg8 *) IO_26__PS)
/* Data Register */
#define IO_26_DR                     (* (reg8 *) IO_26__DR)
/* Port Number */
#define IO_26_PRT_NUM                (* (reg8 *) IO_26__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_26_AG                     (* (reg8 *) IO_26__AG)                       
/* Analog MUX bux enable */
#define IO_26_AMUX                   (* (reg8 *) IO_26__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_26_BIE                    (* (reg8 *) IO_26__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_26_BIT_MASK               (* (reg8 *) IO_26__BIT_MASK)
/* Bypass Enable */
#define IO_26_BYP                    (* (reg8 *) IO_26__BYP)
/* Port wide control signals */                                                   
#define IO_26_CTL                    (* (reg8 *) IO_26__CTL)
/* Drive Modes */
#define IO_26_DM0                    (* (reg8 *) IO_26__DM0) 
#define IO_26_DM1                    (* (reg8 *) IO_26__DM1)
#define IO_26_DM2                    (* (reg8 *) IO_26__DM2) 
/* Input Buffer Disable Override */
#define IO_26_INP_DIS                (* (reg8 *) IO_26__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_26_LCD_COM_SEG            (* (reg8 *) IO_26__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_26_LCD_EN                 (* (reg8 *) IO_26__LCD_EN)
/* Slew Rate Control */
#define IO_26_SLW                    (* (reg8 *) IO_26__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_26_PRTDSI__CAPS_SEL       (* (reg8 *) IO_26__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_26_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_26__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_26_PRTDSI__OE_SEL0        (* (reg8 *) IO_26__PRTDSI__OE_SEL0) 
#define IO_26_PRTDSI__OE_SEL1        (* (reg8 *) IO_26__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_26_PRTDSI__OUT_SEL0       (* (reg8 *) IO_26__PRTDSI__OUT_SEL0) 
#define IO_26_PRTDSI__OUT_SEL1       (* (reg8 *) IO_26__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_26_PRTDSI__SYNC_OUT       (* (reg8 *) IO_26__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_26__SIO_CFG)
    #define IO_26_SIO_HYST_EN        (* (reg8 *) IO_26__SIO_HYST_EN)
    #define IO_26_SIO_REG_HIFREQ     (* (reg8 *) IO_26__SIO_REG_HIFREQ)
    #define IO_26_SIO_CFG            (* (reg8 *) IO_26__SIO_CFG)
    #define IO_26_SIO_DIFF           (* (reg8 *) IO_26__SIO_DIFF)
#endif /* (IO_26__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_26__INTSTAT)
    #define IO_26_INTSTAT            (* (reg8 *) IO_26__INTSTAT)
    #define IO_26_SNAP               (* (reg8 *) IO_26__SNAP)
    
	#define IO_26_0_INTTYPE_REG 		(* (reg8 *) IO_26__0__INTTYPE)
#endif /* (IO_26__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_26_H */


/* [] END OF FILE */
