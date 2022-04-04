/*******************************************************************************
* File Name: IO_16.h  
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

#if !defined(CY_PINS_IO_16_H) /* Pins IO_16_H */
#define CY_PINS_IO_16_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_16_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_16__PORT == 15 && ((IO_16__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_16_Write(uint8 value);
void    IO_16_SetDriveMode(uint8 mode);
uint8   IO_16_ReadDataReg(void);
uint8   IO_16_Read(void);
void    IO_16_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_16_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_16_SetDriveMode() function.
     *  @{
     */
        #define IO_16_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_16_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_16_DM_RES_UP          PIN_DM_RES_UP
        #define IO_16_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_16_DM_OD_LO           PIN_DM_OD_LO
        #define IO_16_DM_OD_HI           PIN_DM_OD_HI
        #define IO_16_DM_STRONG          PIN_DM_STRONG
        #define IO_16_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_16_MASK               IO_16__MASK
#define IO_16_SHIFT              IO_16__SHIFT
#define IO_16_WIDTH              1u

/* Interrupt constants */
#if defined(IO_16__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_16_SetInterruptMode() function.
     *  @{
     */
        #define IO_16_INTR_NONE      (uint16)(0x0000u)
        #define IO_16_INTR_RISING    (uint16)(0x0001u)
        #define IO_16_INTR_FALLING   (uint16)(0x0002u)
        #define IO_16_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_16_INTR_MASK      (0x01u) 
#endif /* (IO_16__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_16_PS                     (* (reg8 *) IO_16__PS)
/* Data Register */
#define IO_16_DR                     (* (reg8 *) IO_16__DR)
/* Port Number */
#define IO_16_PRT_NUM                (* (reg8 *) IO_16__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_16_AG                     (* (reg8 *) IO_16__AG)                       
/* Analog MUX bux enable */
#define IO_16_AMUX                   (* (reg8 *) IO_16__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_16_BIE                    (* (reg8 *) IO_16__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_16_BIT_MASK               (* (reg8 *) IO_16__BIT_MASK)
/* Bypass Enable */
#define IO_16_BYP                    (* (reg8 *) IO_16__BYP)
/* Port wide control signals */                                                   
#define IO_16_CTL                    (* (reg8 *) IO_16__CTL)
/* Drive Modes */
#define IO_16_DM0                    (* (reg8 *) IO_16__DM0) 
#define IO_16_DM1                    (* (reg8 *) IO_16__DM1)
#define IO_16_DM2                    (* (reg8 *) IO_16__DM2) 
/* Input Buffer Disable Override */
#define IO_16_INP_DIS                (* (reg8 *) IO_16__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_16_LCD_COM_SEG            (* (reg8 *) IO_16__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_16_LCD_EN                 (* (reg8 *) IO_16__LCD_EN)
/* Slew Rate Control */
#define IO_16_SLW                    (* (reg8 *) IO_16__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_16_PRTDSI__CAPS_SEL       (* (reg8 *) IO_16__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_16_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_16__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_16_PRTDSI__OE_SEL0        (* (reg8 *) IO_16__PRTDSI__OE_SEL0) 
#define IO_16_PRTDSI__OE_SEL1        (* (reg8 *) IO_16__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_16_PRTDSI__OUT_SEL0       (* (reg8 *) IO_16__PRTDSI__OUT_SEL0) 
#define IO_16_PRTDSI__OUT_SEL1       (* (reg8 *) IO_16__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_16_PRTDSI__SYNC_OUT       (* (reg8 *) IO_16__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_16__SIO_CFG)
    #define IO_16_SIO_HYST_EN        (* (reg8 *) IO_16__SIO_HYST_EN)
    #define IO_16_SIO_REG_HIFREQ     (* (reg8 *) IO_16__SIO_REG_HIFREQ)
    #define IO_16_SIO_CFG            (* (reg8 *) IO_16__SIO_CFG)
    #define IO_16_SIO_DIFF           (* (reg8 *) IO_16__SIO_DIFF)
#endif /* (IO_16__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_16__INTSTAT)
    #define IO_16_INTSTAT            (* (reg8 *) IO_16__INTSTAT)
    #define IO_16_SNAP               (* (reg8 *) IO_16__SNAP)
    
	#define IO_16_0_INTTYPE_REG 		(* (reg8 *) IO_16__0__INTTYPE)
#endif /* (IO_16__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_16_H */


/* [] END OF FILE */
