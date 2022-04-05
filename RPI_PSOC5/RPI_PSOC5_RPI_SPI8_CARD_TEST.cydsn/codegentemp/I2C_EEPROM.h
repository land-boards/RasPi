/*******************************************************************************
* File Name: I2C_EEPROM.h
* Version 3.50
*
* Description:
*  This file provides constants and parameter values for the I2C component.

*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_I2C_EEPROM_H)
#define CY_I2C_I2C_EEPROM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check if required defines such as CY_PSOC5LP are available in cy_boot */
#if !defined (CY_PSOC5LP)
    #error Component I2C_v3_50 requires cy_boot v3.10 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define I2C_EEPROM_IMPLEMENTATION     (1u)
#define I2C_EEPROM_MODE               (2u)
#define I2C_EEPROM_ENABLE_WAKEUP      (0u)
#define I2C_EEPROM_ADDR_DECODE        (1u)
#define I2C_EEPROM_UDB_INTRN_CLOCK    (0u)


/* I2C implementation enum */
#define I2C_EEPROM_UDB    (0x00u)
#define I2C_EEPROM_FF     (0x01u)

#define I2C_EEPROM_FF_IMPLEMENTED     (I2C_EEPROM_FF  == I2C_EEPROM_IMPLEMENTATION)
#define I2C_EEPROM_UDB_IMPLEMENTED    (I2C_EEPROM_UDB == I2C_EEPROM_IMPLEMENTATION)

#define I2C_EEPROM_UDB_INTRN_CLOCK_ENABLED    (I2C_EEPROM_UDB_IMPLEMENTED && \
                                                     (0u != I2C_EEPROM_UDB_INTRN_CLOCK))
/* I2C modes enum */
#define I2C_EEPROM_MODE_SLAVE                 (0x01u)
#define I2C_EEPROM_MODE_MASTER                (0x02u)
#define I2C_EEPROM_MODE_MULTI_MASTER          (0x06u)
#define I2C_EEPROM_MODE_MULTI_MASTER_SLAVE    (0x07u)
#define I2C_EEPROM_MODE_MULTI_MASTER_MASK     (0x04u)

#define I2C_EEPROM_MODE_SLAVE_ENABLED         (0u != (I2C_EEPROM_MODE_SLAVE  & I2C_EEPROM_MODE))
#define I2C_EEPROM_MODE_MASTER_ENABLED        (0u != (I2C_EEPROM_MODE_MASTER & I2C_EEPROM_MODE))
#define I2C_EEPROM_MODE_MULTI_MASTER_ENABLED  (0u != (I2C_EEPROM_MODE_MULTI_MASTER_MASK & \
                                                            I2C_EEPROM_MODE))
#define I2C_EEPROM_MODE_MULTI_MASTER_SLAVE_ENABLED    (I2C_EEPROM_MODE_MULTI_MASTER_SLAVE == \
                                                             I2C_EEPROM_MODE)

/* Address detection enum */
#define I2C_EEPROM_SW_DECODE      (0x00u)
#define I2C_EEPROM_HW_DECODE      (0x01u)

#define I2C_EEPROM_SW_ADRR_DECODE             (I2C_EEPROM_SW_DECODE == I2C_EEPROM_ADDR_DECODE)
#define I2C_EEPROM_HW_ADRR_DECODE             (I2C_EEPROM_HW_DECODE == I2C_EEPROM_ADDR_DECODE)

/* Wakeup enabled */
#define I2C_EEPROM_WAKEUP_ENABLED             (0u != I2C_EEPROM_ENABLE_WAKEUP)

/* Adds bootloader APIs to component */
#define I2C_EEPROM_BOOTLOADER_INTERFACE_ENABLED   (I2C_EEPROM_MODE_SLAVE_ENABLED && \
                                                            ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2C_EEPROM) || \
                                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

/* Timeout functionality */
#define I2C_EEPROM_TIMEOUT_ENABLE             (0u)
#define I2C_EEPROM_TIMEOUT_SCL_TMOUT_ENABLE   (0u)
#define I2C_EEPROM_TIMEOUT_SDA_TMOUT_ENABLE   (0u)
#define I2C_EEPROM_TIMEOUT_PRESCALER_ENABLE   (0u)
#define I2C_EEPROM_TIMEOUT_IMPLEMENTATION     (0u)

/* Convert to boolean */
#define I2C_EEPROM_TIMEOUT_ENABLED            (0u != I2C_EEPROM_TIMEOUT_ENABLE)
#define I2C_EEPROM_TIMEOUT_SCL_TMOUT_ENABLED  (0u != I2C_EEPROM_TIMEOUT_SCL_TMOUT_ENABLE)
#define I2C_EEPROM_TIMEOUT_SDA_TMOUT_ENABLED  (0u != I2C_EEPROM_TIMEOUT_SDA_TMOUT_ENABLE)
#define I2C_EEPROM_TIMEOUT_PRESCALER_ENABLED  (0u != I2C_EEPROM_TIMEOUT_PRESCALER_ENABLE)

/* Timeout implementation enum. */
#define I2C_EEPROM_TIMEOUT_UDB    (0x00u)
#define I2C_EEPROM_TIMEOUT_FF     (0x01u)

#define I2C_EEPROM_TIMEOUT_FF_IMPLEMENTED     (I2C_EEPROM_TIMEOUT_FF  == \
                                                        I2C_EEPROM_TIMEOUT_IMPLEMENTATION)
#define I2C_EEPROM_TIMEOUT_UDB_IMPLEMENTED    (I2C_EEPROM_TIMEOUT_UDB == \
                                                        I2C_EEPROM_TIMEOUT_IMPLEMENTATION)

#define I2C_EEPROM_TIMEOUT_FF_ENABLED         (I2C_EEPROM_TIMEOUT_ENABLED && \
                                                     I2C_EEPROM_TIMEOUT_FF_IMPLEMENTED)

#define I2C_EEPROM_TIMEOUT_UDB_ENABLED        (I2C_EEPROM_TIMEOUT_ENABLED && \
                                                     I2C_EEPROM_TIMEOUT_UDB_IMPLEMENTED)

#define I2C_EEPROM_EXTERN_I2C_INTR_HANDLER    (0u)
#define I2C_EEPROM_EXTERN_TMOUT_INTR_HANDLER  (0u)

#define I2C_EEPROM_INTERN_I2C_INTR_HANDLER    (0u == I2C_EEPROM_EXTERN_I2C_INTR_HANDLER)
#define I2C_EEPROM_INTERN_TMOUT_INTR_HANDLER  (0u == I2C_EEPROM_EXTERN_TMOUT_INTR_HANDLER)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

#if (I2C_EEPROM_FF_IMPLEMENTED)
    uint8 xcfg;
    uint8 cfg;
    uint8 addr;
    uint8 clkDiv1;
    uint8 clkDiv2;
#else
    uint8 control;
#endif /* (I2C_EEPROM_FF_IMPLEMENTED) */

#if (I2C_EEPROM_TIMEOUT_ENABLED)
    uint16 tmoutCfg;
    uint8  tmoutIntr;
#endif /* (I2C_EEPROM_TIMEOUT_ENABLED) */

} I2C_EEPROM_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void I2C_EEPROM_Init(void)                            ;
void I2C_EEPROM_Enable(void)                          ;

void I2C_EEPROM_Start(void)                           ;
void I2C_EEPROM_Stop(void)                            ;

#define I2C_EEPROM_EnableInt()        CyIntEnable      (I2C_EEPROM_ISR_NUMBER)
#define I2C_EEPROM_DisableInt()       CyIntDisable     (I2C_EEPROM_ISR_NUMBER)
#define I2C_EEPROM_ClearPendingInt()  CyIntClearPending(I2C_EEPROM_ISR_NUMBER)
#define I2C_EEPROM_SetPendingInt()    CyIntSetPending  (I2C_EEPROM_ISR_NUMBER)

void I2C_EEPROM_SaveConfig(void)                      ;
void I2C_EEPROM_Sleep(void)                           ;
void I2C_EEPROM_RestoreConfig(void)                   ;
void I2C_EEPROM_Wakeup(void)                          ;

/* I2C Master functions prototypes */
#if (I2C_EEPROM_MODE_MASTER_ENABLED)
    /* Read and Clear status functions */
    uint8 I2C_EEPROM_MasterStatus(void)                ;
    uint8 I2C_EEPROM_MasterClearStatus(void)           ;

    /* Interrupt based operation functions */
    uint8 I2C_EEPROM_MasterWriteBuf(uint8 slaveAddress, uint8 * wrData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 I2C_EEPROM_MasterReadBuf(uint8 slaveAddress, uint8 * rdData, uint8 cnt, uint8 mode) \
                                                            ;
    uint8 I2C_EEPROM_MasterGetReadBufSize(void)       ;
    uint8 I2C_EEPROM_MasterGetWriteBufSize(void)      ;
    void  I2C_EEPROM_MasterClearReadBuf(void)         ;
    void  I2C_EEPROM_MasterClearWriteBuf(void)        ;

    /* Manual operation functions */
    uint8 I2C_EEPROM_MasterSendStart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 I2C_EEPROM_MasterSendRestart(uint8 slaveAddress, uint8 R_nW) \
                                                            ;
    uint8 I2C_EEPROM_MasterSendStop(void)             ;
    uint8 I2C_EEPROM_MasterWriteByte(uint8 theByte)   ;
    uint8 I2C_EEPROM_MasterReadByte(uint8 acknNak)    ;

#endif /* (I2C_EEPROM_MODE_MASTER_ENABLED) */

/* I2C Slave functions prototypes */
#if (I2C_EEPROM_MODE_SLAVE_ENABLED)
    /* Read and Clear status functions */
    uint8 I2C_EEPROM_SlaveStatus(void)                ;
    uint8 I2C_EEPROM_SlaveClearReadStatus(void)       ;
    uint8 I2C_EEPROM_SlaveClearWriteStatus(void)      ;

    void  I2C_EEPROM_SlaveSetAddress(uint8 address)   ;

    /* Interrupt based operation functions */
    void  I2C_EEPROM_SlaveInitReadBuf(uint8 * rdBuf, uint8 bufSize) \
                                                            ;
    void  I2C_EEPROM_SlaveInitWriteBuf(uint8 * wrBuf, uint8 bufSize) \
                                                            ;
    uint8 I2C_EEPROM_SlaveGetReadBufSize(void)        ;
    uint8 I2C_EEPROM_SlaveGetWriteBufSize(void)       ;
    void  I2C_EEPROM_SlaveClearReadBuf(void)          ;
    void  I2C_EEPROM_SlaveClearWriteBuf(void)         ;

    /* Communication bootloader I2C Slave APIs */
    #if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_EEPROM_BOOTLOADER_INTERFACE_ENABLED)
        /* Physical layer functions */
        void     I2C_EEPROM_CyBtldrCommStart(void) CYSMALL \
                                                            ;
        void     I2C_EEPROM_CyBtldrCommStop(void)  CYSMALL \
                                                            ;
        void     I2C_EEPROM_CyBtldrCommReset(void) CYSMALL \
                                                            ;
        cystatus I2C_EEPROM_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) \
                                                        CYSMALL ;
        cystatus I2C_EEPROM_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)  CYSMALL \
                                                            ;

        #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2C_EEPROM)
            #define CyBtldrCommStart    I2C_EEPROM_CyBtldrCommStart
            #define CyBtldrCommStop     I2C_EEPROM_CyBtldrCommStop
            #define CyBtldrCommReset    I2C_EEPROM_CyBtldrCommReset
            #define CyBtldrCommWrite    I2C_EEPROM_CyBtldrCommWrite
            #define CyBtldrCommRead     I2C_EEPROM_CyBtldrCommRead
        #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_I2C_EEPROM) */

        /* Size of Read/Write buffers for I2C bootloader  */
        #define I2C_EEPROM_BTLDR_SIZEOF_READ_BUFFER   (0x80u)
        #define I2C_EEPROM_BTLDR_SIZEOF_WRITE_BUFFER  (0x80u)
        #define I2C_EEPROM_MIN_UNT16(a, b)            ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
        #define I2C_EEPROM_WAIT_1_MS                  (1u)

    #endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_EEPROM_BOOTLOADER_INTERFACE_ENABLED) */

#endif /* (I2C_EEPROM_MODE_SLAVE_ENABLED) */

/* Component interrupt handlers */
CY_ISR_PROTO(I2C_EEPROM_ISR);
#if ((I2C_EEPROM_FF_IMPLEMENTED) || (I2C_EEPROM_WAKEUP_ENABLED))
    CY_ISR_PROTO(I2C_EEPROM_WAKEUP_ISR);
#endif /* ((I2C_EEPROM_FF_IMPLEMENTED) || (I2C_EEPROM_WAKEUP_ENABLED)) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 I2C_EEPROM_initVar;


/***************************************
*   Initial Parameter Constants
***************************************/

#define I2C_EEPROM_DATA_RATE          (100u)
#define I2C_EEPROM_DEFAULT_ADDR       (8u)
#define I2C_EEPROM_I2C_PAIR_SELECTED  (0u)

/* I2C pair enum */
#define I2C_EEPROM_I2C_PAIR_ANY   (0x01u) /* Any pins for I2C */
#define I2C_EEPROM_I2C_PAIR0      (0x01u) /* I2C0: (SCL = P12[4]) && (SCL = P12[5]) */
#define I2C_EEPROM_I2C_PAIR1      (0x02u) /* I2C1: (SCL = P12[0]) && (SDA = P12[1]) */

#define I2C_EEPROM_I2C1_SIO_PAIR  (I2C_EEPROM_I2C_PAIR1 == I2C_EEPROM_I2C_PAIR_SELECTED)
#define I2C_EEPROM_I2C0_SIO_PAIR  (I2C_EEPROM_I2C_PAIR0 == I2C_EEPROM_I2C_PAIR_SELECTED)


/***************************************
*            API Constants
***************************************/

/* Master/Slave control constants */
#define I2C_EEPROM_READ_XFER_MODE     (0x01u) /* Read */
#define I2C_EEPROM_WRITE_XFER_MODE    (0x00u) /* Write */
#define I2C_EEPROM_ACK_DATA           (0x01u) /* Send ACK */
#define I2C_EEPROM_NAK_DATA           (0x00u) /* Send NAK */
#define I2C_EEPROM_OVERFLOW_RETURN    (0xFFu) /* Send on bus in case of overflow */

#if (I2C_EEPROM_MODE_MASTER_ENABLED)
    /* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
    #define I2C_EEPROM_MODE_COMPLETE_XFER     (0x00u) /* Full transfer with Start and Stop */
    #define I2C_EEPROM_MODE_REPEAT_START      (0x01u) /* Begin with a ReStart instead of a Start */
    #define I2C_EEPROM_MODE_NO_STOP           (0x02u) /* Complete the transfer without a Stop */

    /* Master status */
    #define I2C_EEPROM_MSTAT_CLEAR            (0x00u) /* Clear (initialize) status value */

    #define I2C_EEPROM_MSTAT_RD_CMPLT         (0x01u) /* Read complete */
    #define I2C_EEPROM_MSTAT_WR_CMPLT         (0x02u) /* Write complete */
    #define I2C_EEPROM_MSTAT_XFER_INP         (0x04u) /* Master transfer in progress */
    #define I2C_EEPROM_MSTAT_XFER_HALT        (0x08u) /* Transfer is halted */

    #define I2C_EEPROM_MSTAT_ERR_MASK         (0xF0u) /* Mask for all errors */
    #define I2C_EEPROM_MSTAT_ERR_SHORT_XFER   (0x10u) /* Master NAKed before end of packet */
    #define I2C_EEPROM_MSTAT_ERR_ADDR_NAK     (0x20u) /* Slave did not ACK */
    #define I2C_EEPROM_MSTAT_ERR_ARB_LOST     (0x40u) /* Master lost arbitration during communication */
    #define I2C_EEPROM_MSTAT_ERR_XFER         (0x80u) /* Error during transfer */

    /* Master API returns */
    #define I2C_EEPROM_MSTR_NO_ERROR          (0x00u) /* Function complete without error */
    #define I2C_EEPROM_MSTR_BUS_BUSY          (0x01u) /* Bus is busy, process not started */
    #define I2C_EEPROM_MSTR_NOT_READY         (0x02u) /* Master not Master on the bus or */
                                                            /*  Slave operation in progress */
    #define I2C_EEPROM_MSTR_ERR_LB_NAK        (0x03u) /* Last Byte Naked */
    #define I2C_EEPROM_MSTR_ERR_ARB_LOST      (0x04u) /* Master lost arbitration during communication */
    #define I2C_EEPROM_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave */
                                                               /* was addressed before */

#endif /* (I2C_EEPROM_MODE_MASTER_ENABLED) */

#if (I2C_EEPROM_MODE_SLAVE_ENABLED)
    /* Slave Status Constants */
    #define I2C_EEPROM_SSTAT_RD_CMPLT     (0x01u) /* Read transfer complete */
    #define I2C_EEPROM_SSTAT_RD_BUSY      (0x02u) /* Read transfer in progress */
    #define I2C_EEPROM_SSTAT_RD_ERR_OVFL  (0x04u) /* Read overflow Error */
    #define I2C_EEPROM_SSTAT_RD_MASK      (0x0Fu) /* Read Status Mask */
    #define I2C_EEPROM_SSTAT_RD_NO_ERR    (0x00u) /* Read no Error */

    #define I2C_EEPROM_SSTAT_WR_CMPLT     (0x10u) /* Write transfer complete */
    #define I2C_EEPROM_SSTAT_WR_BUSY      (0x20u) /* Write transfer in progress */
    #define I2C_EEPROM_SSTAT_WR_ERR_OVFL  (0x40u) /* Write overflow Error */
    #define I2C_EEPROM_SSTAT_WR_MASK      (0xF0u) /* Write Status Mask  */
    #define I2C_EEPROM_SSTAT_WR_NO_ERR    (0x00u) /* Write no Error */

    #define I2C_EEPROM_SSTAT_RD_CLEAR     (0x0Du) /* Read Status clear */
    #define I2C_EEPROM_SSTAT_WR_CLEAR     (0xD0u) /* Write Status Clear */

#endif /* (I2C_EEPROM_MODE_SLAVE_ENABLED) */


/***************************************
*       I2C state machine constants
***************************************/

/* Default slave address states */
#define  I2C_EEPROM_SM_IDLE           (0x10u) /* Default state - IDLE */
#define  I2C_EEPROM_SM_EXIT_IDLE      (0x00u) /* Pass master and slave processing and go to IDLE */

/* Slave mode states */
#define  I2C_EEPROM_SM_SLAVE          (I2C_EEPROM_SM_IDLE) /* Any Slave state */
#define  I2C_EEPROM_SM_SL_WR_DATA     (0x11u) /* Master writes data to slave  */
#define  I2C_EEPROM_SM_SL_RD_DATA     (0x12u) /* Master reads data from slave */

/* Master mode states */
#define  I2C_EEPROM_SM_MASTER         (0x40u) /* Any master state */

#define  I2C_EEPROM_SM_MSTR_RD        (0x08u) /* Any master read state          */
#define  I2C_EEPROM_SM_MSTR_RD_ADDR   (0x49u) /* Master sends address with read */
#define  I2C_EEPROM_SM_MSTR_RD_DATA   (0x4Au) /* Master reads data              */

#define  I2C_EEPROM_SM_MSTR_WR        (0x04u) /* Any master read state           */
#define  I2C_EEPROM_SM_MSTR_WR_ADDR   (0x45u) /* Master sends address with write */
#define  I2C_EEPROM_SM_MSTR_WR_DATA   (0x46u) /* Master writes data              */

#define  I2C_EEPROM_SM_MSTR_HALT      (0x60u) /* Master waits for ReStart */

#define I2C_EEPROM_CHECK_SM_MASTER    (0u != (I2C_EEPROM_SM_MASTER & I2C_EEPROM_state))
#define I2C_EEPROM_CHECK_SM_SLAVE     (0u != (I2C_EEPROM_SM_SLAVE  & I2C_EEPROM_state))


/***************************************
*              Registers
***************************************/

#if (I2C_EEPROM_FF_IMPLEMENTED)
    /* Fixed Function registers */
    #define I2C_EEPROM_XCFG_REG           (*(reg8 *) I2C_EEPROM_I2C_FF__XCFG)
    #define I2C_EEPROM_XCFG_PTR           ( (reg8 *) I2C_EEPROM_I2C_FF__XCFG)

    #define I2C_EEPROM_ADDR_REG           (*(reg8 *) I2C_EEPROM_I2C_FF__ADR)
    #define I2C_EEPROM_ADDR_PTR           ( (reg8 *) I2C_EEPROM_I2C_FF__ADR)

    #define I2C_EEPROM_CFG_REG            (*(reg8 *) I2C_EEPROM_I2C_FF__CFG)
    #define I2C_EEPROM_CFG_PTR            ( (reg8 *) I2C_EEPROM_I2C_FF__CFG)

    #define I2C_EEPROM_CSR_REG            (*(reg8 *) I2C_EEPROM_I2C_FF__CSR)
    #define I2C_EEPROM_CSR_PTR            ( (reg8 *) I2C_EEPROM_I2C_FF__CSR)

    #define I2C_EEPROM_DATA_REG           (*(reg8 *) I2C_EEPROM_I2C_FF__D)
    #define I2C_EEPROM_DATA_PTR           ( (reg8 *) I2C_EEPROM_I2C_FF__D)

    #define I2C_EEPROM_MCSR_REG           (*(reg8 *) I2C_EEPROM_I2C_FF__MCSR)
    #define I2C_EEPROM_MCSR_PTR           ( (reg8 *) I2C_EEPROM_I2C_FF__MCSR)

    #define I2C_EEPROM_ACT_PWRMGR_REG     (*(reg8 *) I2C_EEPROM_I2C_FF__PM_ACT_CFG)
    #define I2C_EEPROM_ACT_PWRMGR_PTR     ( (reg8 *) I2C_EEPROM_I2C_FF__PM_ACT_CFG)
    #define I2C_EEPROM_ACT_PWR_EN         ( (uint8)  I2C_EEPROM_I2C_FF__PM_ACT_MSK)

    #define I2C_EEPROM_STBY_PWRMGR_REG    (*(reg8 *) I2C_EEPROM_I2C_FF__PM_STBY_CFG)
    #define I2C_EEPROM_STBY_PWRMGR_PTR    ( (reg8 *) I2C_EEPROM_I2C_FF__PM_STBY_CFG)
    #define I2C_EEPROM_STBY_PWR_EN        ( (uint8)  I2C_EEPROM_I2C_FF__PM_STBY_MSK)

    #define I2C_EEPROM_PWRSYS_CR1_REG     (*(reg8 *) CYREG_PWRSYS_CR1)
    #define I2C_EEPROM_PWRSYS_CR1_PTR     ( (reg8 *) CYREG_PWRSYS_CR1)

    #define I2C_EEPROM_CLKDIV1_REG    (*(reg8 *) I2C_EEPROM_I2C_FF__CLK_DIV1)
    #define I2C_EEPROM_CLKDIV1_PTR    ( (reg8 *) I2C_EEPROM_I2C_FF__CLK_DIV1)

    #define I2C_EEPROM_CLKDIV2_REG    (*(reg8 *) I2C_EEPROM_I2C_FF__CLK_DIV2)
    #define I2C_EEPROM_CLKDIV2_PTR    ( (reg8 *) I2C_EEPROM_I2C_FF__CLK_DIV2)

#else
    /* UDB implementation registers */
    #define I2C_EEPROM_CFG_REG \
            (*(reg8 *) I2C_EEPROM_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)
    #define I2C_EEPROM_CFG_PTR \
            ( (reg8 *) I2C_EEPROM_bI2C_UDB_SyncCtl_CtrlReg__CONTROL_REG)

    #define I2C_EEPROM_CSR_REG        (*(reg8 *) I2C_EEPROM_bI2C_UDB_StsReg__STATUS_REG)
    #define I2C_EEPROM_CSR_PTR        ( (reg8 *) I2C_EEPROM_bI2C_UDB_StsReg__STATUS_REG)

    #define I2C_EEPROM_INT_MASK_REG   (*(reg8 *) I2C_EEPROM_bI2C_UDB_StsReg__MASK_REG)
    #define I2C_EEPROM_INT_MASK_PTR   ( (reg8 *) I2C_EEPROM_bI2C_UDB_StsReg__MASK_REG)

    #define I2C_EEPROM_INT_ENABLE_REG (*(reg8 *) I2C_EEPROM_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)
    #define I2C_EEPROM_INT_ENABLE_PTR ( (reg8 *) I2C_EEPROM_bI2C_UDB_StsReg__STATUS_AUX_CTL_REG)

    #define I2C_EEPROM_DATA_REG       (*(reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__A0_REG)
    #define I2C_EEPROM_DATA_PTR       ( (reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__A0_REG)

    #define I2C_EEPROM_GO_REG         (*(reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__F1_REG)
    #define I2C_EEPROM_GO_PTR         ( (reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__F1_REG)

    #define I2C_EEPROM_GO_DONE_REG    (*(reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__A1_REG)
    #define I2C_EEPROM_GO_DONE_PTR    ( (reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__A1_REG)

    #define I2C_EEPROM_MCLK_PRD_REG   (*(reg8 *) I2C_EEPROM_bI2C_UDB_Master_ClkGen_u0__D0_REG)
    #define I2C_EEPROM_MCLK_PRD_PTR   ( (reg8 *) I2C_EEPROM_bI2C_UDB_Master_ClkGen_u0__D0_REG)

    #define I2C_EEPROM_MCLK_CMP_REG   (*(reg8 *) I2C_EEPROM_bI2C_UDB_Master_ClkGen_u0__D1_REG)
    #define I2C_EEPROM_MCLK_CMP_PTR   ( (reg8 *) I2C_EEPROM_bI2C_UDB_Master_ClkGen_u0__D1_REG)

    #if (I2C_EEPROM_MODE_SLAVE_ENABLED)
        #define I2C_EEPROM_ADDR_REG       (*(reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__D0_REG)
        #define I2C_EEPROM_ADDR_PTR       ( (reg8 *) I2C_EEPROM_bI2C_UDB_Shifter_u0__D0_REG)

        #define I2C_EEPROM_PERIOD_REG     (*(reg8 *) I2C_EEPROM_bI2C_UDB_Slave_BitCounter__PERIOD_REG)
        #define I2C_EEPROM_PERIOD_PTR     ( (reg8 *) I2C_EEPROM_bI2C_UDB_Slave_BitCounter__PERIOD_REG)

        #define I2C_EEPROM_COUNTER_REG    (*(reg8 *) I2C_EEPROM_bI2C_UDB_Slave_BitCounter__COUNT_REG)
        #define I2C_EEPROM_COUNTER_PTR    ( (reg8 *) I2C_EEPROM_bI2C_UDB_Slave_BitCounter__COUNT_REG)

        #define I2C_EEPROM_COUNTER_AUX_CTL_REG \
                                    (*(reg8 *) I2C_EEPROM_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)
        #define I2C_EEPROM_COUNTER_AUX_CTL_PTR \
                                    ( (reg8 *) I2C_EEPROM_bI2C_UDB_Slave_BitCounter__CONTROL_AUX_CTL_REG)

    #endif /* (I2C_EEPROM_MODE_SLAVE_ENABLED) */

#endif /* (I2C_EEPROM_FF_IMPLEMENTED) */


/***************************************
*        Registers Constants
***************************************/

/* I2C_EEPROM_I2C_IRQ */
#define I2C_EEPROM_ISR_NUMBER     ((uint8) I2C_EEPROM_I2C_IRQ__INTC_NUMBER)
#define I2C_EEPROM_ISR_PRIORITY   ((uint8) I2C_EEPROM_I2C_IRQ__INTC_PRIOR_NUM)

/* I2C Slave Data Register */
#define I2C_EEPROM_SLAVE_ADDR_MASK    (0x7Fu)
#define I2C_EEPROM_SLAVE_ADDR_SHIFT   (0x01u)
#define I2C_EEPROM_DATA_MASK          (0xFFu)
#define I2C_EEPROM_READ_FLAG          (0x01u)

/* Block reset constants */
#define I2C_EEPROM_CLEAR_REG          (0x00u)
#define I2C_EEPROM_BLOCK_RESET_DELAY  (2u)
#define I2C_EEPROM_FF_RESET_DELAY     (I2C_EEPROM_BLOCK_RESET_DELAY)
#define I2C_EEPROM_RESTORE_TIMEOUT    (255u)

#if (I2C_EEPROM_FF_IMPLEMENTED)
    /* XCFG I2C Extended Configuration Register */
    #define I2C_EEPROM_XCFG_CLK_EN        (0x80u) /* Enable gated clock to block */
    #define I2C_EEPROM_XCFG_I2C_ON        (0x40u) /* Enable I2C as wake up source*/
    #define I2C_EEPROM_XCFG_RDY_TO_SLEEP  (0x20u) /* I2C ready go to sleep */
    #define I2C_EEPROM_XCFG_FORCE_NACK    (0x10u) /* Force NACK all incoming transactions */
    #define I2C_EEPROM_XCFG_NO_BC_INT     (0x08u) /* No interrupt on byte complete */
    #define I2C_EEPROM_XCFG_BUF_MODE      (0x02u) /* Enable buffer mode */
    #define I2C_EEPROM_XCFG_HDWR_ADDR_EN  (0x01u) /* Enable Hardware address match */

    /* CFG I2C Configuration Register */
    #define I2C_EEPROM_CFG_SIO_SELECT     (0x80u) /* Pin Select for SCL/SDA lines */
    #define I2C_EEPROM_CFG_PSELECT        (0x40u) /* Pin Select */
    #define I2C_EEPROM_CFG_BUS_ERR_IE     (0x20u) /* Bus Error Interrupt Enable */
    #define I2C_EEPROM_CFG_STOP_IE        (0x10u) /* Enable Interrupt on STOP condition */
    #define I2C_EEPROM_CFG_CLK_RATE_MSK   (0x0Cu) /* Clock rate select */
    #define I2C_EEPROM_CFG_CLK_RATE_100   (0x00u) /* Clock rate select 100K */
    #define I2C_EEPROM_CFG_CLK_RATE_400   (0x04u) /* Clock rate select 400K */
    #define I2C_EEPROM_CFG_CLK_RATE_050   (0x08u) /* Clock rate select 50K  */
    #define I2C_EEPROM_CFG_CLK_RATE_RSVD  (0x0Cu) /* Clock rate select Invalid */
    #define I2C_EEPROM_CFG_EN_MSTR        (0x02u) /* Enable Master operation */
    #define I2C_EEPROM_CFG_EN_SLAVE       (0x01u) /* Enable Slave operation */

    #define I2C_EEPROM_CFG_CLK_RATE_LESS_EQUAL_50 (0x04u) /* Clock rate select <= 50kHz */
    #define I2C_EEPROM_CFG_CLK_RATE_GRATER_50     (0x00u) /* Clock rate select > 50kHz */

    /* CSR I2C Control and Status Register */
    #define I2C_EEPROM_CSR_BUS_ERROR      (0x80u) /* Active high when bus error has occurred */
    #define I2C_EEPROM_CSR_LOST_ARB       (0x40u) /* Set to 1 if lost arbitration in host mode */
    #define I2C_EEPROM_CSR_STOP_STATUS    (0x20u) /* Set if Stop has been detected */
    #define I2C_EEPROM_CSR_ACK            (0x10u) /* ACK response */
    #define I2C_EEPROM_CSR_NAK            (0x00u) /* NAK response */
    #define I2C_EEPROM_CSR_ADDRESS        (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
    #define I2C_EEPROM_CSR_TRANSMIT       (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
    #define I2C_EEPROM_CSR_LRB            (0x02u) /* Last received bit */
    #define I2C_EEPROM_CSR_LRB_ACK        (0x00u) /* Last received bit was an ACK */
    #define I2C_EEPROM_CSR_LRB_NAK        (0x02u) /* Last received bit was an NAK */
    #define I2C_EEPROM_CSR_BYTE_COMPLETE  (0x01u) /* Informs that last byte has been sent */
    #define I2C_EEPROM_CSR_STOP_GEN       (0x00u) /* Generate a stop condition */
    #define I2C_EEPROM_CSR_RDY_TO_RD      (0x00u) /* Set to receive mode */

    /* MCSR I2C Master Control and Status Register */
    #define I2C_EEPROM_MCSR_STOP_GEN      (0x10u) /* Firmware sets this bit to initiate a Stop condition */
    #define I2C_EEPROM_MCSR_BUS_BUSY      (0x08u) /* Status bit, Set at Start and cleared at Stop condition */
    #define I2C_EEPROM_MCSR_MSTR_MODE     (0x04u) /* Status bit, Set at Start and cleared at Stop condition */
    #define I2C_EEPROM_MCSR_RESTART_GEN   (0x02u) /* Firmware sets this bit to initiate a ReStart condition */
    #define I2C_EEPROM_MCSR_START_GEN     (0x01u) /* Firmware sets this bit to initiate a Start condition */

    /* PWRSYS_CR1 to handle Sleep */
    #define I2C_EEPROM_PWRSYS_CR1_I2C_REG_BACKUP  (0x04u) /* Enables, power to I2C regs while sleep */

#else
    /* CONTROL REG bits location */
    #define I2C_EEPROM_CTRL_START_SHIFT           (7u)
    #define I2C_EEPROM_CTRL_STOP_SHIFT            (6u)
    #define I2C_EEPROM_CTRL_RESTART_SHIFT         (5u)
    #define I2C_EEPROM_CTRL_NACK_SHIFT            (4u)
    #define I2C_EEPROM_CTRL_ANY_ADDRESS_SHIFT     (3u)
    #define I2C_EEPROM_CTRL_TRANSMIT_SHIFT        (2u)
    #define I2C_EEPROM_CTRL_ENABLE_MASTER_SHIFT   (1u)
    #define I2C_EEPROM_CTRL_ENABLE_SLAVE_SHIFT    (0u)
    #define I2C_EEPROM_CTRL_START_MASK            ((uint8) (0x01u << I2C_EEPROM_CTRL_START_SHIFT))
    #define I2C_EEPROM_CTRL_STOP_MASK             ((uint8) (0x01u << I2C_EEPROM_CTRL_STOP_SHIFT))
    #define I2C_EEPROM_CTRL_RESTART_MASK          ((uint8) (0x01u << I2C_EEPROM_CTRL_RESTART_SHIFT))
    #define I2C_EEPROM_CTRL_NACK_MASK             ((uint8) (0x01u << I2C_EEPROM_CTRL_NACK_SHIFT))
    #define I2C_EEPROM_CTRL_ANY_ADDRESS_MASK      ((uint8) (0x01u << I2C_EEPROM_CTRL_ANY_ADDRESS_SHIFT))
    #define I2C_EEPROM_CTRL_TRANSMIT_MASK         ((uint8) (0x01u << I2C_EEPROM_CTRL_TRANSMIT_SHIFT))
    #define I2C_EEPROM_CTRL_ENABLE_MASTER_MASK    ((uint8) (0x01u << I2C_EEPROM_CTRL_ENABLE_MASTER_SHIFT))
    #define I2C_EEPROM_CTRL_ENABLE_SLAVE_MASK     ((uint8) (0x01u << I2C_EEPROM_CTRL_ENABLE_SLAVE_SHIFT))

    /* STATUS REG bits location */
    #define I2C_EEPROM_STS_LOST_ARB_SHIFT         (6u)
    #define I2C_EEPROM_STS_STOP_SHIFT             (5u)
    #define I2C_EEPROM_STS_BUSY_SHIFT             (4u)
    #define I2C_EEPROM_STS_ADDR_SHIFT             (3u)
    #define I2C_EEPROM_STS_MASTER_MODE_SHIFT      (2u)
    #define I2C_EEPROM_STS_LRB_SHIFT              (1u)
    #define I2C_EEPROM_STS_BYTE_COMPLETE_SHIFT    (0u)
    #define I2C_EEPROM_STS_LOST_ARB_MASK          ((uint8) (0x01u << I2C_EEPROM_STS_LOST_ARB_SHIFT))
    #define I2C_EEPROM_STS_STOP_MASK              ((uint8) (0x01u << I2C_EEPROM_STS_STOP_SHIFT))
    #define I2C_EEPROM_STS_BUSY_MASK              ((uint8) (0x01u << I2C_EEPROM_STS_BUSY_SHIFT))
    #define I2C_EEPROM_STS_ADDR_MASK              ((uint8) (0x01u << I2C_EEPROM_STS_ADDR_SHIFT))
    #define I2C_EEPROM_STS_MASTER_MODE_MASK       ((uint8) (0x01u << I2C_EEPROM_STS_MASTER_MODE_SHIFT))
    #define I2C_EEPROM_STS_LRB_MASK               ((uint8) (0x01u << I2C_EEPROM_STS_LRB_SHIFT))
    #define I2C_EEPROM_STS_BYTE_COMPLETE_MASK     ((uint8) (0x01u << I2C_EEPROM_STS_BYTE_COMPLETE_SHIFT))

    /* AUX_CTL bits definition */
    #define I2C_EEPROM_COUNTER_ENABLE_MASK        (0x20u) /* Enable 7-bit counter */
    #define I2C_EEPROM_INT_ENABLE_MASK            (0x10u) /* Enable interrupt from status register */
    #define I2C_EEPROM_CNT7_ENABLE                (I2C_EEPROM_COUNTER_ENABLE_MASK)
    #define I2C_EEPROM_INTR_ENABLE                (I2C_EEPROM_INT_ENABLE_MASK)

#endif /* (I2C_EEPROM_FF_IMPLEMENTED) */


/***************************************
*        Marco
***************************************/

/* ACK and NACK for data and address checks */
#define I2C_EEPROM_CHECK_ADDR_ACK(csr)    ((I2C_EEPROM_CSR_LRB_ACK | I2C_EEPROM_CSR_ADDRESS) == \
                                                 ((I2C_EEPROM_CSR_LRB    | I2C_EEPROM_CSR_ADDRESS) &  \
                                                  (csr)))


#define I2C_EEPROM_CHECK_ADDR_NAK(csr)    ((I2C_EEPROM_CSR_LRB_NAK | I2C_EEPROM_CSR_ADDRESS) == \
                                                 ((I2C_EEPROM_CSR_LRB    | I2C_EEPROM_CSR_ADDRESS) &  \
                                                  (csr)))

#define I2C_EEPROM_CHECK_DATA_ACK(csr)    (0u == ((csr) & I2C_EEPROM_CSR_LRB_NAK))

/* MCSR conditions check */
#define I2C_EEPROM_CHECK_BUS_FREE(mcsr)       (0u == ((mcsr) & I2C_EEPROM_MCSR_BUS_BUSY))
#define I2C_EEPROM_CHECK_MASTER_MODE(mcsr)    (0u != ((mcsr) & I2C_EEPROM_MCSR_MSTR_MODE))

/* CSR conditions check */
#define I2C_EEPROM_WAIT_BYTE_COMPLETE(csr)    (0u == ((csr) & I2C_EEPROM_CSR_BYTE_COMPLETE))
#define I2C_EEPROM_WAIT_STOP_COMPLETE(csr)    (0u == ((csr) & (I2C_EEPROM_CSR_BYTE_COMPLETE | \
                                                                     I2C_EEPROM_CSR_STOP_STATUS)))
#define I2C_EEPROM_CHECK_BYTE_COMPLETE(csr)   (0u != ((csr) & I2C_EEPROM_CSR_BYTE_COMPLETE))
#define I2C_EEPROM_CHECK_STOP_STS(csr)        (0u != ((csr) & I2C_EEPROM_CSR_STOP_STATUS))
#define I2C_EEPROM_CHECK_LOST_ARB(csr)        (0u != ((csr) & I2C_EEPROM_CSR_LOST_ARB))
#define I2C_EEPROM_CHECK_ADDRESS_STS(csr)     (0u != ((csr) & I2C_EEPROM_CSR_ADDRESS))

/* Software start and end of transaction check */
#define I2C_EEPROM_CHECK_RESTART(mstrCtrl)    (0u != ((mstrCtrl) & I2C_EEPROM_MODE_REPEAT_START))
#define I2C_EEPROM_CHECK_NO_STOP(mstrCtrl)    (0u != ((mstrCtrl) & I2C_EEPROM_MODE_NO_STOP))

/* Send read or write completion depends on state */
#define I2C_EEPROM_GET_MSTAT_CMPLT ((0u != (I2C_EEPROM_state & I2C_EEPROM_SM_MSTR_RD)) ? \
                                                 (I2C_EEPROM_MSTAT_RD_CMPLT) : (I2C_EEPROM_MSTAT_WR_CMPLT))

/* Returns 7-bit slave address */
#define I2C_EEPROM_GET_SLAVE_ADDR(dataReg)   (((dataReg) >> I2C_EEPROM_SLAVE_ADDR_SHIFT) & \
                                                                  I2C_EEPROM_SLAVE_ADDR_MASK)

#if (I2C_EEPROM_FF_IMPLEMENTED)
    /* Check enable of module */
    #define I2C_EEPROM_I2C_ENABLE_REG     (I2C_EEPROM_ACT_PWRMGR_REG)
    #define I2C_EEPROM_IS_I2C_ENABLE(reg) (0u != ((reg) & I2C_EEPROM_ACT_PWR_EN))
    #define I2C_EEPROM_IS_ENABLED         (0u != (I2C_EEPROM_ACT_PWRMGR_REG & I2C_EEPROM_ACT_PWR_EN))

    #define I2C_EEPROM_CHECK_PWRSYS_I2C_BACKUP    (0u != (I2C_EEPROM_PWRSYS_CR1_I2C_REG_BACKUP & \
                                                                I2C_EEPROM_PWRSYS_CR1_REG))

    /* Check start condition generation */
    #define I2C_EEPROM_CHECK_START_GEN(mcsr)  ((0u != ((mcsr) & I2C_EEPROM_MCSR_START_GEN)) && \
                                                     (0u == ((mcsr) & I2C_EEPROM_MCSR_MSTR_MODE)))

    #define I2C_EEPROM_CLEAR_START_GEN        do{ \
                                                        I2C_EEPROM_MCSR_REG &=                                   \
                                                                           ((uint8) ~I2C_EEPROM_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define I2C_EEPROM_ENABLE_INT_ON_STOP     do{ \
                                                        I2C_EEPROM_CFG_REG |= I2C_EEPROM_CFG_STOP_IE; \
                                                    }while(0)

    #define I2C_EEPROM_DISABLE_INT_ON_STOP    do{ \
                                                        I2C_EEPROM_CFG_REG &=                                 \
                                                                           ((uint8) ~I2C_EEPROM_CFG_STOP_IE); \
                                                    }while(0)

    /* Transmit data */
    #define I2C_EEPROM_TRANSMIT_DATA          do{ \
                                                        I2C_EEPROM_CSR_REG = I2C_EEPROM_CSR_TRANSMIT; \
                                                    }while(0)

    #define I2C_EEPROM_ACK_AND_TRANSMIT       do{ \
                                                        I2C_EEPROM_CSR_REG = (I2C_EEPROM_CSR_ACK |      \
                                                                                    I2C_EEPROM_CSR_TRANSMIT); \
                                                    }while(0)

    #define I2C_EEPROM_NAK_AND_TRANSMIT       do{ \
                                                        I2C_EEPROM_CSR_REG = I2C_EEPROM_CSR_NAK; \
                                                    }while(0)

    /* Special case: udb needs to ack, ff needs to nak */
    #define I2C_EEPROM_ACKNAK_AND_TRANSMIT    do{ \
                                                        I2C_EEPROM_CSR_REG  = (I2C_EEPROM_CSR_NAK |      \
                                                                                     I2C_EEPROM_CSR_TRANSMIT); \
                                                    }while(0)
    /* Receive data */
    #define I2C_EEPROM_ACK_AND_RECEIVE        do{ \
                                                        I2C_EEPROM_CSR_REG = I2C_EEPROM_CSR_ACK; \
                                                    }while(0)

    #define I2C_EEPROM_NAK_AND_RECEIVE        do{ \
                                                        I2C_EEPROM_CSR_REG = I2C_EEPROM_CSR_NAK; \
                                                    }while(0)

    #define I2C_EEPROM_READY_TO_READ          do{ \
                                                        I2C_EEPROM_CSR_REG = I2C_EEPROM_CSR_RDY_TO_RD; \
                                                    }while(0)

    /* Release bus after lost arbitration */
    #define I2C_EEPROM_BUS_RELEASE    I2C_EEPROM_READY_TO_READ

    /* Master Start/ReStart/Stop conditions generation */
    #define I2C_EEPROM_GENERATE_START         do{ \
                                                        I2C_EEPROM_MCSR_REG = I2C_EEPROM_MCSR_START_GEN; \
                                                    }while(0)

    #define I2C_EEPROM_GENERATE_RESTART \
                    do{                       \
                        I2C_EEPROM_MCSR_REG = (I2C_EEPROM_MCSR_RESTART_GEN | \
                                                     I2C_EEPROM_MCSR_STOP_GEN);    \
                        I2C_EEPROM_CSR_REG  = I2C_EEPROM_CSR_TRANSMIT;       \
                    }while(0)

    #define I2C_EEPROM_GENERATE_STOP \
                    do{                    \
                        I2C_EEPROM_MCSR_REG = I2C_EEPROM_MCSR_STOP_GEN; \
                        I2C_EEPROM_CSR_REG  = I2C_EEPROM_CSR_TRANSMIT;  \
                    }while(0)

    /* Master manual APIs compatible defines */
    #define I2C_EEPROM_GENERATE_START_MANUAL      I2C_EEPROM_GENERATE_START
    #define I2C_EEPROM_GENERATE_RESTART_MANUAL    I2C_EEPROM_GENERATE_RESTART
    #define I2C_EEPROM_GENERATE_STOP_MANUAL       I2C_EEPROM_GENERATE_STOP
    #define I2C_EEPROM_TRANSMIT_DATA_MANUAL       I2C_EEPROM_TRANSMIT_DATA
    #define I2C_EEPROM_READY_TO_READ_MANUAL       I2C_EEPROM_READY_TO_READ
    #define I2C_EEPROM_ACK_AND_RECEIVE_MANUAL     I2C_EEPROM_ACK_AND_RECEIVE
    #define I2C_EEPROM_BUS_RELEASE_MANUAL         I2C_EEPROM_BUS_RELEASE

#else

    /* Masks to enable interrupts from Status register */
    #define I2C_EEPROM_STOP_IE_MASK           (I2C_EEPROM_STS_STOP_MASK)
    #define I2C_EEPROM_BYTE_COMPLETE_IE_MASK  (I2C_EEPROM_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: CSR register bit-fields */
    #define I2C_EEPROM_CSR_LOST_ARB       (I2C_EEPROM_STS_LOST_ARB_MASK)
    #define I2C_EEPROM_CSR_STOP_STATUS    (I2C_EEPROM_STS_STOP_MASK)
    #define I2C_EEPROM_CSR_BUS_ERROR      (0x00u)
    #define I2C_EEPROM_CSR_ADDRESS        (I2C_EEPROM_STS_ADDR_MASK)
    #define I2C_EEPROM_CSR_TRANSMIT       (I2C_EEPROM_CTRL_TRANSMIT_MASK)
    #define I2C_EEPROM_CSR_LRB            (I2C_EEPROM_STS_LRB_MASK)
    #define I2C_EEPROM_CSR_LRB_NAK        (I2C_EEPROM_STS_LRB_MASK)
    #define I2C_EEPROM_CSR_LRB_ACK        (0x00u)
    #define I2C_EEPROM_CSR_BYTE_COMPLETE  (I2C_EEPROM_STS_BYTE_COMPLETE_MASK)

    /* FF compatibility: MCSR registers bit-fields */
    #define I2C_EEPROM_MCSR_REG           (I2C_EEPROM_CSR_REG)  /* UDB incorporates master and slave regs */
    #define I2C_EEPROM_MCSR_BUS_BUSY      (I2C_EEPROM_STS_BUSY_MASK)      /* Is bus is busy               */
    #define I2C_EEPROM_MCSR_START_GEN     (I2C_EEPROM_CTRL_START_MASK)    /* Generate Start condition     */
    #define I2C_EEPROM_MCSR_RESTART_GEN   (I2C_EEPROM_CTRL_RESTART_MASK)  /* Generates RESTART condition  */
    #define I2C_EEPROM_MCSR_MSTR_MODE     (I2C_EEPROM_STS_MASTER_MODE_MASK)/* Define if active Master     */

    /* Data to write into TX FIFO to release FSM */
    #define I2C_EEPROM_PREPARE_TO_RELEASE (0xFFu)
    #define I2C_EEPROM_RELEASE_FSM        (0x00u)

    /* Define release command done: history of byte complete status is cleared */
    #define I2C_EEPROM_WAIT_RELEASE_CMD_DONE  (I2C_EEPROM_RELEASE_FSM != I2C_EEPROM_GO_DONE_REG)

    /* Check enable of module */
    #define I2C_EEPROM_I2C_ENABLE_REG     (I2C_EEPROM_CFG_REG)
    #define I2C_EEPROM_IS_I2C_ENABLE(reg) ((0u != ((reg) & I2C_EEPROM_ENABLE_MASTER)) || \
                                                 (0u != ((reg) & I2C_EEPROM_ENABLE_SLAVE)))

    #define I2C_EEPROM_IS_ENABLED         (0u != (I2C_EEPROM_CFG_REG & I2C_EEPROM_ENABLE_MS))

    /* Check start condition generation */
    #define I2C_EEPROM_CHECK_START_GEN(mcsr)  ((0u != (I2C_EEPROM_CFG_REG &        \
                                                             I2C_EEPROM_MCSR_START_GEN)) \
                                                    &&                                         \
                                                    (0u == ((mcsr) & I2C_EEPROM_MCSR_MSTR_MODE)))

    #define I2C_EEPROM_CLEAR_START_GEN        do{ \
                                                        I2C_EEPROM_CFG_REG &=                 \
                                                        ((uint8) ~I2C_EEPROM_MCSR_START_GEN); \
                                                    }while(0)

    /* Stop interrupt */
    #define I2C_EEPROM_ENABLE_INT_ON_STOP     do{ \
                                                       I2C_EEPROM_INT_MASK_REG |= I2C_EEPROM_STOP_IE_MASK; \
                                                    }while(0)

    #define I2C_EEPROM_DISABLE_INT_ON_STOP    do{ \
                                                        I2C_EEPROM_INT_MASK_REG &=                               \
                                                                             ((uint8) ~I2C_EEPROM_STOP_IE_MASK); \
                                                    }while(0)

    /* Transmit data */
    #define I2C_EEPROM_TRANSMIT_DATA \
                                    do{    \
                                        I2C_EEPROM_CFG_REG     = (I2C_EEPROM_CTRL_TRANSMIT_MASK | \
                                                                       I2C_EEPROM_CTRL_DEFAULT);        \
                                        I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE;   \
                                        I2C_EEPROM_GO_REG      = I2C_EEPROM_RELEASE_FSM;          \
                                    }while(0)

    #define I2C_EEPROM_ACK_AND_TRANSMIT   I2C_EEPROM_TRANSMIT_DATA

    #define I2C_EEPROM_NAK_AND_TRANSMIT \
                                        do{   \
                                            I2C_EEPROM_CFG_REG     = (I2C_EEPROM_CTRL_NACK_MASK     | \
                                                                            I2C_EEPROM_CTRL_TRANSMIT_MASK | \
                                                                            I2C_EEPROM_CTRL_DEFAULT);       \
                                            I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE;   \
                                            I2C_EEPROM_GO_REG      = I2C_EEPROM_RELEASE_FSM;          \
                                        }while(0)

    /* Receive data */
    #define I2C_EEPROM_READY_TO_READ  \
                                        do{ \
                                            I2C_EEPROM_CFG_REG     = I2C_EEPROM_CTRL_DEFAULT;       \
                                            I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE; \
                                            I2C_EEPROM_GO_REG      = I2C_EEPROM_RELEASE_FSM;       \
                                        }while(0)

    #define I2C_EEPROM_ACK_AND_RECEIVE    I2C_EEPROM_READY_TO_READ

    /* Release bus after arbitration is lost */
    #define I2C_EEPROM_BUS_RELEASE    I2C_EEPROM_READY_TO_READ

    #define I2C_EEPROM_NAK_AND_RECEIVE \
                                        do{  \
                                            I2C_EEPROM_CFG_REG     = (I2C_EEPROM_CTRL_NACK_MASK |   \
                                                                            I2C_EEPROM_CTRL_DEFAULT);     \
                                            I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE; \
                                            I2C_EEPROM_GO_REG      = I2C_EEPROM_RELEASE_FSM;       \
                                        }while(0)

    /* Master condition generation */
    #define I2C_EEPROM_GENERATE_START \
                                        do{ \
                                            I2C_EEPROM_CFG_REG     = (I2C_EEPROM_CTRL_START_MASK |  \
                                                                            I2C_EEPROM_CTRL_DEFAULT);     \
                                            I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE; \
                                            I2C_EEPROM_GO_REG      = I2C_EEPROM_RELEASE_FSM;       \
                                        }while(0)

    #define I2C_EEPROM_GENERATE_RESTART \
                                        do{   \
                                            I2C_EEPROM_CFG_REG     = (I2C_EEPROM_CTRL_RESTART_MASK | \
                                                                            I2C_EEPROM_CTRL_NACK_MASK    | \
                                                                            I2C_EEPROM_CTRL_DEFAULT);      \
                                            I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE;  \
                                            I2C_EEPROM_GO_REG  =     I2C_EEPROM_RELEASE_FSM;         \
                                        }while(0)

    #define I2C_EEPROM_GENERATE_STOP  \
                                        do{ \
                                            I2C_EEPROM_CFG_REG    = (I2C_EEPROM_CTRL_NACK_MASK |    \
                                                                           I2C_EEPROM_CTRL_STOP_MASK |    \
                                                                           I2C_EEPROM_CTRL_DEFAULT);      \
                                            I2C_EEPROM_GO_DONE_REG = I2C_EEPROM_PREPARE_TO_RELEASE; \
                                            I2C_EEPROM_GO_REG      = I2C_EEPROM_RELEASE_FSM;        \
                                        }while(0)

    /* Master manual APIs compatible macros */
    /* These macros wait until byte complete history is cleared after command issued */
    #define I2C_EEPROM_GENERATE_START_MANUAL \
                                        do{ \
                                            I2C_EEPROM_GENERATE_START;                  \
                                            /* Wait until byte complete history is cleared */ \
                                            while(I2C_EEPROM_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)
                                        
    #define I2C_EEPROM_GENERATE_RESTART_MANUAL \
                                        do{          \
                                            I2C_EEPROM_GENERATE_RESTART;                \
                                            /* Wait until byte complete history is cleared */ \
                                            while(I2C_EEPROM_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define I2C_EEPROM_GENERATE_STOP_MANUAL \
                                        do{       \
                                            I2C_EEPROM_GENERATE_STOP;                   \
                                            /* Wait until byte complete history is cleared */ \
                                            while(I2C_EEPROM_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define I2C_EEPROM_TRANSMIT_DATA_MANUAL \
                                        do{       \
                                            I2C_EEPROM_TRANSMIT_DATA;                   \
                                            /* Wait until byte complete history is cleared */ \
                                            while(I2C_EEPROM_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define I2C_EEPROM_READY_TO_READ_MANUAL \
                                        do{       \
                                            I2C_EEPROM_READY_TO_READ;                   \
                                            /* Wait until byte complete history is cleared */ \
                                            while(I2C_EEPROM_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define I2C_EEPROM_ACK_AND_RECEIVE_MANUAL \
                                        do{         \
                                            I2C_EEPROM_ACK_AND_RECEIVE;                 \
                                            /* Wait until byte complete history is cleared */ \
                                            while(I2C_EEPROM_WAIT_RELEASE_CMD_DONE)     \
                                            {                                                 \
                                            }                                                 \
                                        }while(0)

    #define I2C_EEPROM_BUS_RELEASE_MANUAL I2C_EEPROM_READY_TO_READ_MANUAL

#endif /* (I2C_EEPROM_FF_IMPLEMENTED) */


/***************************************
*     Default register init constants
***************************************/

#define I2C_EEPROM_DISABLE    (0u)
#define I2C_EEPROM_ENABLE     (1u)

#if (I2C_EEPROM_FF_IMPLEMENTED)
    /* I2C_EEPROM_XCFG_REG: bits definition */
    #define I2C_EEPROM_DEFAULT_XCFG_HW_ADDR_EN ((I2C_EEPROM_HW_ADRR_DECODE) ? \
                                                        (I2C_EEPROM_XCFG_HDWR_ADDR_EN) : (0u))

    #define I2C_EEPROM_DEFAULT_XCFG_I2C_ON    ((I2C_EEPROM_WAKEUP_ENABLED) ? \
                                                        (I2C_EEPROM_XCFG_I2C_ON) : (0u))


    #define I2C_EEPROM_DEFAULT_CFG_SIO_SELECT ((I2C_EEPROM_I2C1_SIO_PAIR) ? \
                                                        (I2C_EEPROM_CFG_SIO_SELECT) : (0u))


    /* I2C_EEPROM_CFG_REG: bits definition */
    #define I2C_EEPROM_DEFAULT_CFG_PSELECT    ((I2C_EEPROM_WAKEUP_ENABLED) ? \
                                                        (I2C_EEPROM_CFG_PSELECT) : (0u))

    #define I2C_EEPROM_DEFAULT_CLK_RATE0  ((I2C_EEPROM_DATA_RATE <= 50u) ?        \
                                                    (I2C_EEPROM_CFG_CLK_RATE_050) :     \
                                                    ((I2C_EEPROM_DATA_RATE <= 100u) ?   \
                                                        (I2C_EEPROM_CFG_CLK_RATE_100) : \
                                                        (I2C_EEPROM_CFG_CLK_RATE_400)))

    #define I2C_EEPROM_DEFAULT_CLK_RATE1  ((I2C_EEPROM_DATA_RATE <= 50u) ?           \
                                                 (I2C_EEPROM_CFG_CLK_RATE_LESS_EQUAL_50) : \
                                                 (I2C_EEPROM_CFG_CLK_RATE_GRATER_50))

    #define I2C_EEPROM_DEFAULT_CLK_RATE   (I2C_EEPROM_DEFAULT_CLK_RATE1)


    #define I2C_EEPROM_ENABLE_MASTER      ((I2C_EEPROM_MODE_MASTER_ENABLED) ? \
                                                 (I2C_EEPROM_CFG_EN_MSTR) : (0u))

    #define I2C_EEPROM_ENABLE_SLAVE       ((I2C_EEPROM_MODE_SLAVE_ENABLED) ? \
                                                 (I2C_EEPROM_CFG_EN_SLAVE) : (0u))

    #define I2C_EEPROM_ENABLE_MS      (I2C_EEPROM_ENABLE_MASTER | I2C_EEPROM_ENABLE_SLAVE)


    /* I2C_EEPROM_DEFAULT_XCFG_REG */
    #define I2C_EEPROM_DEFAULT_XCFG   (I2C_EEPROM_XCFG_CLK_EN         | \
                                             I2C_EEPROM_DEFAULT_XCFG_I2C_ON | \
                                             I2C_EEPROM_DEFAULT_XCFG_HW_ADDR_EN)

    /* I2C_EEPROM_DEFAULT_CFG_REG */
    #define I2C_EEPROM_DEFAULT_CFG    (I2C_EEPROM_DEFAULT_CFG_SIO_SELECT | \
                                             I2C_EEPROM_DEFAULT_CFG_PSELECT    | \
                                             I2C_EEPROM_DEFAULT_CLK_RATE       | \
                                             I2C_EEPROM_ENABLE_MASTER          | \
                                             I2C_EEPROM_ENABLE_SLAVE)

    /*I2C_EEPROM_DEFAULT_DIVIDE_FACTOR_REG */
    #define I2C_EEPROM_DEFAULT_DIVIDE_FACTOR  ((uint16) 40u)

#else
    /* I2C_EEPROM_CFG_REG: bits definition  */
    #define I2C_EEPROM_ENABLE_MASTER  ((I2C_EEPROM_MODE_MASTER_ENABLED) ? \
                                             (I2C_EEPROM_CTRL_ENABLE_MASTER_MASK) : (0u))

    #define I2C_EEPROM_ENABLE_SLAVE   ((I2C_EEPROM_MODE_SLAVE_ENABLED) ? \
                                             (I2C_EEPROM_CTRL_ENABLE_SLAVE_MASK) : (0u))

    #define I2C_EEPROM_ENABLE_MS      (I2C_EEPROM_ENABLE_MASTER | I2C_EEPROM_ENABLE_SLAVE)


    #define I2C_EEPROM_DEFAULT_CTRL_ANY_ADDR   ((I2C_EEPROM_HW_ADRR_DECODE) ? \
                                                      (0u) : (I2C_EEPROM_CTRL_ANY_ADDRESS_MASK))

    /* I2C_EEPROM_DEFAULT_CFG_REG */
    #define I2C_EEPROM_DEFAULT_CFG    (I2C_EEPROM_DEFAULT_CTRL_ANY_ADDR)

    /* All CTRL default bits to be used in macro */
    #define I2C_EEPROM_CTRL_DEFAULT   (I2C_EEPROM_DEFAULT_CTRL_ANY_ADDR | I2C_EEPROM_ENABLE_MS)

    /* Master clock generator: d0 and d1 */
    #define I2C_EEPROM_MCLK_PERIOD_VALUE  (0x0Fu)
    #define I2C_EEPROM_MCLK_COMPARE_VALUE (0x08u)

    /* Slave bit-counter: control period */
    #define I2C_EEPROM_PERIOD_VALUE       (0x07u)

    /* I2C_EEPROM_DEFAULT_INT_MASK */
    #define I2C_EEPROM_DEFAULT_INT_MASK   (I2C_EEPROM_BYTE_COMPLETE_IE_MASK)

    /* I2C_EEPROM_DEFAULT_MCLK_PRD_REG */
    #define I2C_EEPROM_DEFAULT_MCLK_PRD   (I2C_EEPROM_MCLK_PERIOD_VALUE)

    /* I2C_EEPROM_DEFAULT_MCLK_CMP_REG */
    #define I2C_EEPROM_DEFAULT_MCLK_CMP   (I2C_EEPROM_MCLK_COMPARE_VALUE)

    /* I2C_EEPROM_DEFAULT_PERIOD_REG */
    #define I2C_EEPROM_DEFAULT_PERIOD     (I2C_EEPROM_PERIOD_VALUE)

#endif /* (I2C_EEPROM_FF_IMPLEMENTED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define I2C_EEPROM_SSTAT_RD_ERR       (0x08u)
#define I2C_EEPROM_SSTAT_WR_ERR       (0x80u)
#define I2C_EEPROM_MSTR_SLAVE_BUSY    (I2C_EEPROM_MSTR_NOT_READY)
#define I2C_EEPROM_MSTAT_ERR_BUF_OVFL (0x80u)
#define I2C_EEPROM_SSTAT_RD_CMPT      (I2C_EEPROM_SSTAT_RD_CMPLT)
#define I2C_EEPROM_SSTAT_WR_CMPT      (I2C_EEPROM_SSTAT_WR_CMPLT)
#define I2C_EEPROM_MODE_MULTI_MASTER_ENABLE    (I2C_EEPROM_MODE_MULTI_MASTER_MASK)
#define I2C_EEPROM_DATA_RATE_50       (50u)
#define I2C_EEPROM_DATA_RATE_100      (100u)
#define I2C_EEPROM_DEV_MASK           (0xF0u)
#define I2C_EEPROM_SM_SL_STOP         (0x14u)
#define I2C_EEPROM_SM_MASTER_IDLE     (0x40u)
#define I2C_EEPROM_HDWR_DECODE        (0x01u)

#endif /* CY_I2C_I2C_EEPROM_H */


/* [] END OF FILE */
