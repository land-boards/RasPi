/*******************************************************************************
* File Name: IO_20.h  
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

#if !defined(CY_PINS_IO_20_H) /* Pins IO_20_H */
#define CY_PINS_IO_20_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_20_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_20__PORT == 15 && ((IO_20__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_20_Write(uint8 value);
void    IO_20_SetDriveMode(uint8 mode);
uint8   IO_20_ReadDataReg(void);
uint8   IO_20_Read(void);
void    IO_20_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_20_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_20_SetDriveMode() function.
     *  @{
     */
        #define IO_20_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_20_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_20_DM_RES_UP          PIN_DM_RES_UP
        #define IO_20_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_20_DM_OD_LO           PIN_DM_OD_LO
        #define IO_20_DM_OD_HI           PIN_DM_OD_HI
        #define IO_20_DM_STRONG          PIN_DM_STRONG
        #define IO_20_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_20_MASK               IO_20__MASK
#define IO_20_SHIFT              IO_20__SHIFT
#define IO_20_WIDTH              1u

/* Interrupt constants */
#if defined(IO_20__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_20_SetInterruptMode() function.
     *  @{
     */
        #define IO_20_INTR_NONE      (uint16)(0x0000u)
        #define IO_20_INTR_RISING    (uint16)(0x0001u)
        #define IO_20_INTR_FALLING   (uint16)(0x0002u)
        #define IO_20_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_20_INTR_MASK      (0x01u) 
#endif /* (IO_20__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_20_PS                     (* (reg8 *) IO_20__PS)
/* Data Register */
#define IO_20_DR                     (* (reg8 *) IO_20__DR)
/* Port Number */
#define IO_20_PRT_NUM                (* (reg8 *) IO_20__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_20_AG                     (* (reg8 *) IO_20__AG)                       
/* Analog MUX bux enable */
#define IO_20_AMUX                   (* (reg8 *) IO_20__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_20_BIE                    (* (reg8 *) IO_20__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_20_BIT_MASK               (* (reg8 *) IO_20__BIT_MASK)
/* Bypass Enable */
#define IO_20_BYP                    (* (reg8 *) IO_20__BYP)
/* Port wide control signals */                                                   
#define IO_20_CTL                    (* (reg8 *) IO_20__CTL)
/* Drive Modes */
#define IO_20_DM0                    (* (reg8 *) IO_20__DM0) 
#define IO_20_DM1                    (* (reg8 *) IO_20__DM1)
#define IO_20_DM2                    (* (reg8 *) IO_20__DM2) 
/* Input Buffer Disable Override */
#define IO_20_INP_DIS                (* (reg8 *) IO_20__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_20_LCD_COM_SEG            (* (reg8 *) IO_20__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_20_LCD_EN                 (* (reg8 *) IO_20__LCD_EN)
/* Slew Rate Control */
#define IO_20_SLW                    (* (reg8 *) IO_20__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_20_PRTDSI__CAPS_SEL       (* (reg8 *) IO_20__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_20_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_20__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_20_PRTDSI__OE_SEL0        (* (reg8 *) IO_20__PRTDSI__OE_SEL0) 
#define IO_20_PRTDSI__OE_SEL1        (* (reg8 *) IO_20__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_20_PRTDSI__OUT_SEL0       (* (reg8 *) IO_20__PRTDSI__OUT_SEL0) 
#define IO_20_PRTDSI__OUT_SEL1       (* (reg8 *) IO_20__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_20_PRTDSI__SYNC_OUT       (* (reg8 *) IO_20__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_20__SIO_CFG)
    #define IO_20_SIO_HYST_EN        (* (reg8 *) IO_20__SIO_HYST_EN)
    #define IO_20_SIO_REG_HIFREQ     (* (reg8 *) IO_20__SIO_REG_HIFREQ)
    #define IO_20_SIO_CFG            (* (reg8 *) IO_20__SIO_CFG)
    #define IO_20_SIO_DIFF           (* (reg8 *) IO_20__SIO_DIFF)
#endif /* (IO_20__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_20__INTSTAT)
    #define IO_20_INTSTAT            (* (reg8 *) IO_20__INTSTAT)
    #define IO_20_SNAP               (* (reg8 *) IO_20__SNAP)
    
	#define IO_20_0_INTTYPE_REG 		(* (reg8 *) IO_20__0__INTTYPE)
#endif /* (IO_20__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_20_H */


/* [] END OF FILE */
