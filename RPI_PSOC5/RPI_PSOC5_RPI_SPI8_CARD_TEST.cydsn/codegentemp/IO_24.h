/*******************************************************************************
* File Name: IO_24.h  
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

#if !defined(CY_PINS_IO_24_H) /* Pins IO_24_H */
#define CY_PINS_IO_24_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "IO_24_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 IO_24__PORT == 15 && ((IO_24__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    IO_24_Write(uint8 value);
void    IO_24_SetDriveMode(uint8 mode);
uint8   IO_24_ReadDataReg(void);
uint8   IO_24_Read(void);
void    IO_24_SetInterruptMode(uint16 position, uint16 mode);
uint8   IO_24_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the IO_24_SetDriveMode() function.
     *  @{
     */
        #define IO_24_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define IO_24_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define IO_24_DM_RES_UP          PIN_DM_RES_UP
        #define IO_24_DM_RES_DWN         PIN_DM_RES_DWN
        #define IO_24_DM_OD_LO           PIN_DM_OD_LO
        #define IO_24_DM_OD_HI           PIN_DM_OD_HI
        #define IO_24_DM_STRONG          PIN_DM_STRONG
        #define IO_24_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define IO_24_MASK               IO_24__MASK
#define IO_24_SHIFT              IO_24__SHIFT
#define IO_24_WIDTH              1u

/* Interrupt constants */
#if defined(IO_24__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IO_24_SetInterruptMode() function.
     *  @{
     */
        #define IO_24_INTR_NONE      (uint16)(0x0000u)
        #define IO_24_INTR_RISING    (uint16)(0x0001u)
        #define IO_24_INTR_FALLING   (uint16)(0x0002u)
        #define IO_24_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define IO_24_INTR_MASK      (0x01u) 
#endif /* (IO_24__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define IO_24_PS                     (* (reg8 *) IO_24__PS)
/* Data Register */
#define IO_24_DR                     (* (reg8 *) IO_24__DR)
/* Port Number */
#define IO_24_PRT_NUM                (* (reg8 *) IO_24__PRT) 
/* Connect to Analog Globals */                                                  
#define IO_24_AG                     (* (reg8 *) IO_24__AG)                       
/* Analog MUX bux enable */
#define IO_24_AMUX                   (* (reg8 *) IO_24__AMUX) 
/* Bidirectional Enable */                                                        
#define IO_24_BIE                    (* (reg8 *) IO_24__BIE)
/* Bit-mask for Aliased Register Access */
#define IO_24_BIT_MASK               (* (reg8 *) IO_24__BIT_MASK)
/* Bypass Enable */
#define IO_24_BYP                    (* (reg8 *) IO_24__BYP)
/* Port wide control signals */                                                   
#define IO_24_CTL                    (* (reg8 *) IO_24__CTL)
/* Drive Modes */
#define IO_24_DM0                    (* (reg8 *) IO_24__DM0) 
#define IO_24_DM1                    (* (reg8 *) IO_24__DM1)
#define IO_24_DM2                    (* (reg8 *) IO_24__DM2) 
/* Input Buffer Disable Override */
#define IO_24_INP_DIS                (* (reg8 *) IO_24__INP_DIS)
/* LCD Common or Segment Drive */
#define IO_24_LCD_COM_SEG            (* (reg8 *) IO_24__LCD_COM_SEG)
/* Enable Segment LCD */
#define IO_24_LCD_EN                 (* (reg8 *) IO_24__LCD_EN)
/* Slew Rate Control */
#define IO_24_SLW                    (* (reg8 *) IO_24__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define IO_24_PRTDSI__CAPS_SEL       (* (reg8 *) IO_24__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define IO_24_PRTDSI__DBL_SYNC_IN    (* (reg8 *) IO_24__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define IO_24_PRTDSI__OE_SEL0        (* (reg8 *) IO_24__PRTDSI__OE_SEL0) 
#define IO_24_PRTDSI__OE_SEL1        (* (reg8 *) IO_24__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define IO_24_PRTDSI__OUT_SEL0       (* (reg8 *) IO_24__PRTDSI__OUT_SEL0) 
#define IO_24_PRTDSI__OUT_SEL1       (* (reg8 *) IO_24__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define IO_24_PRTDSI__SYNC_OUT       (* (reg8 *) IO_24__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(IO_24__SIO_CFG)
    #define IO_24_SIO_HYST_EN        (* (reg8 *) IO_24__SIO_HYST_EN)
    #define IO_24_SIO_REG_HIFREQ     (* (reg8 *) IO_24__SIO_REG_HIFREQ)
    #define IO_24_SIO_CFG            (* (reg8 *) IO_24__SIO_CFG)
    #define IO_24_SIO_DIFF           (* (reg8 *) IO_24__SIO_DIFF)
#endif /* (IO_24__SIO_CFG) */

/* Interrupt Registers */
#if defined(IO_24__INTSTAT)
    #define IO_24_INTSTAT            (* (reg8 *) IO_24__INTSTAT)
    #define IO_24_SNAP               (* (reg8 *) IO_24__SNAP)
    
	#define IO_24_0_INTTYPE_REG 		(* (reg8 *) IO_24__0__INTTYPE)
#endif /* (IO_24__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_IO_24_H */


/* [] END OF FILE */
