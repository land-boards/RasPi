/*******************************************************************************
* File Name: IO_6.h  
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

#if !defined(CY_PINS_IO_6_H) /* Pins IO_6_H */
#define CY_PINS_IO_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_6__PORT == 15 && ((IO_6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_6_Write(uint8 value);
void    IO_6_SetDriveMode(uint8 mode);
uint8   IO_6_ReadDataReg(void);
uint8   IO_6_Read(void);
void    IO_6_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_6_SetDriveMode() function.
     *  @{
     */
        #define IO_6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_6_DM_RES_UP          PIN_DM_RES_UP
        #define IO_6_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_6_DM_OD_LO           PIN_DM_OD_LO
        #define IO_6_DM_OD_HI           PIN_DM_OD_HI
        #define IO_6_DM_STRONG          PIN_DM_STRONG
        #define IO_6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_6_MASK               IO_6__MASK
#define IO_6_SHIFT              IO_6__SHIFT
#define IO_6_WIDTH              1u

/* Interrupt constants */
#if defined(IO_6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_6_SetInterruptMode() function.
     *  @{
     */
        #define IO_6_INTR_NONE      (uint16)(0x0000u)
        #define IO_6_INTR_RISING    (uint16)(0x0001u)
        #define IO_6_INTR_FALLING   (uint16)(0x0002u)
        #define IO_6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_6_INTR_MASK      (0x01u) 
#endif /* (IO_6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_6_PS                     (* (reg8 *) IO_6__PS)
/* Data Register */
#define IO_6_DR                     (* (reg8 *) IO_6__DR)
/* Port Number */
#define IO_6_PRT_NUM                (* (reg8 *) IO_6__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_6_AG                     (* (reg8 *) IO_6__AG)                       
/* Analog MUX bux enable */
#define IO_6_AMUX                   (* (reg8 *) IO_6__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_6_BIE                    (* (reg8 *) IO_6__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_6_BIT_MASK               (* (reg8 *) IO_6__BIT_MASK)
/* Bypass Enable */
#define IO_6_BYP                    (* (reg8 *) IO_6__BYP)
/* Port wide control signals */                                                   
#define IO_6_CTL                    (* (reg8 *) IO_6__CTL)
/* Drive Modes */
#define IO_6_DM0                    (* (reg8 *) IO_6__DM0) 
#define IO_6_DM1                    (* (reg8 *) IO_6__DM1)
#define IO_6_DM2                    (* (reg8 *) IO_6__DM2) 
/* Input Buffer Disable Override */
#define IO_6_INP_DIS                (* (reg8 *) IO_6__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_6_LCD_COM_SEG            (* (reg8 *) IO_6__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_6_LCD_EN                 (* (reg8 *) IO_6__LCD_EN)
/* Slew Rate Control */
#define IO_6_SLW                    (* (reg8 *) IO_6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_6_PRTDSI__CAPS_SEL       (* (reg8 *) IO_6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_6_PRTDSI__OE_SEL0        (* (reg8 *) IO_6__PRTDSI__OE_SEL0) 
#define IO_6_PRTDSI__OE_SEL1        (* (reg8 *) IO_6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_6_PRTDSI__OUT_SEL0       (* (reg8 *) IO_6__PRTDSI__OUT_SEL0) 
#define IO_6_PRTDSI__OUT_SEL1       (* (reg8 *) IO_6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_6_PRTDSI__SYNC_OUT       (* (reg8 *) IO_6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_6__SIO_CFG)
    #define IO_6_SIO_HYST_EN        (* (reg8 *) IO_6__SIO_HYST_EN)
    #define IO_6_SIO_REG_HIFREQ     (* (reg8 *) IO_6__SIO_REG_HIFREQ)
    #define IO_6_SIO_CFG            (* (reg8 *) IO_6__SIO_CFG)
    #define IO_6_SIO_DIFF           (* (reg8 *) IO_6__SIO_DIFF)
#endif /* (IO_6__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_6__INTSTAT)
    #define IO_6_INTSTAT            (* (reg8 *) IO_6__INTSTAT)
    #define IO_6_SNAP               (* (reg8 *) IO_6__SNAP)
    
	#define IO_6_0_INTTYPE_REG 		(* (reg8 *) IO_6__0__INTTYPE)
#endif /* (IO_6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_6_H */


/* [] END OF FILE */
