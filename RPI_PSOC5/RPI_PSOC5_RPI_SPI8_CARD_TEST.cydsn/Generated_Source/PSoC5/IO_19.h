/*******************************************************************************
* File Name: IO_19.h  
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

#if !defined(CY_PINS_IO_19_H) /* Pins IO_19_H */
#define CY_PINS_IO_19_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_19_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_19__PORT == 15 && ((IO_19__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_19_Write(uint8 value);
void    IO_19_SetDriveMode(uint8 mode);
uint8   IO_19_ReadDataReg(void);
uint8   IO_19_Read(void);
void    IO_19_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_19_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_19_SetDriveMode() function.
     *  @{
     */
        #define IO_19_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_19_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_19_DM_RES_UP          PIN_DM_RES_UP
        #define IO_19_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_19_DM_OD_LO           PIN_DM_OD_LO
        #define IO_19_DM_OD_HI           PIN_DM_OD_HI
        #define IO_19_DM_STRONG          PIN_DM_STRONG
        #define IO_19_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_19_MASK               IO_19__MASK
#define IO_19_SHIFT              IO_19__SHIFT
#define IO_19_WIDTH              1u

/* Interrupt constants */
#if defined(IO_19__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_19_SetInterruptMode() function.
     *  @{
     */
        #define IO_19_INTR_NONE      (uint16)(0x0000u)
        #define IO_19_INTR_RISING    (uint16)(0x0001u)
        #define IO_19_INTR_FALLING   (uint16)(0x0002u)
        #define IO_19_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_19_INTR_MASK      (0x01u) 
#endif /* (IO_19__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_19_PS                     (* (reg8 *) IO_19__PS)
/* Data Register */
#define IO_19_DR                     (* (reg8 *) IO_19__DR)
/* Port Number */
#define IO_19_PRT_NUM                (* (reg8 *) IO_19__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_19_AG                     (* (reg8 *) IO_19__AG)                       
/* Analog MUX bux enable */
#define IO_19_AMUX                   (* (reg8 *) IO_19__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_19_BIE                    (* (reg8 *) IO_19__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_19_BIT_MASK               (* (reg8 *) IO_19__BIT_MASK)
/* Bypass Enable */
#define IO_19_BYP                    (* (reg8 *) IO_19__BYP)
/* Port wide control signals */                                                   
#define IO_19_CTL                    (* (reg8 *) IO_19__CTL)
/* Drive Modes */
#define IO_19_DM0                    (* (reg8 *) IO_19__DM0) 
#define IO_19_DM1                    (* (reg8 *) IO_19__DM1)
#define IO_19_DM2                    (* (reg8 *) IO_19__DM2) 
/* Input Buffer Disable Override */
#define IO_19_INP_DIS                (* (reg8 *) IO_19__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_19_LCD_COM_SEG            (* (reg8 *) IO_19__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_19_LCD_EN                 (* (reg8 *) IO_19__LCD_EN)
/* Slew Rate Control */
#define IO_19_SLW                    (* (reg8 *) IO_19__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_19_PRTDSI__CAPS_SEL       (* (reg8 *) IO_19__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_19_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_19__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_19_PRTDSI__OE_SEL0        (* (reg8 *) IO_19__PRTDSI__OE_SEL0) 
#define IO_19_PRTDSI__OE_SEL1        (* (reg8 *) IO_19__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_19_PRTDSI__OUT_SEL0       (* (reg8 *) IO_19__PRTDSI__OUT_SEL0) 
#define IO_19_PRTDSI__OUT_SEL1       (* (reg8 *) IO_19__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_19_PRTDSI__SYNC_OUT       (* (reg8 *) IO_19__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_19__SIO_CFG)
    #define IO_19_SIO_HYST_EN        (* (reg8 *) IO_19__SIO_HYST_EN)
    #define IO_19_SIO_REG_HIFREQ     (* (reg8 *) IO_19__SIO_REG_HIFREQ)
    #define IO_19_SIO_CFG            (* (reg8 *) IO_19__SIO_CFG)
    #define IO_19_SIO_DIFF           (* (reg8 *) IO_19__SIO_DIFF)
#endif /* (IO_19__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_19__INTSTAT)
    #define IO_19_INTSTAT            (* (reg8 *) IO_19__INTSTAT)
    #define IO_19_SNAP               (* (reg8 *) IO_19__SNAP)
    
	#define IO_19_0_INTTYPE_REG 		(* (reg8 *) IO_19__0__INTTYPE)
#endif /* (IO_19__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_19_H */


/* [] END OF FILE */
