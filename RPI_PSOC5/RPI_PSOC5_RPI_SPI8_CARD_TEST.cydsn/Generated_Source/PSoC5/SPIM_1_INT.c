/*******************************************************************************
* File Name: SPIM_1_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_1_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START SPIM_1_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPIM_1_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPIM_1_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPIM_1_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPIM_1_txBuffer[SPIM_1_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIM_1_TX_ISR)
{
    #if(SPIM_1_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SPIM_1_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPIM_1_TX_ISR_ENTRY_CALLBACK
        SPIM_1_TX_ISR_EntryCallback();
    #endif /* SPIM_1_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPIM_1_TX_ISR_START` */

    /* `#END` */
    
    #if(SPIM_1_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(SPIM_1_txBufferRead != SPIM_1_txBufferWrite)
        {
            tmpStatus = SPIM_1_GET_STATUS_TX(SPIM_1_swStatusTx);
            SPIM_1_swStatusTx = tmpStatus;

            if(0u != (SPIM_1_swStatusTx & SPIM_1_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == SPIM_1_txBufferFull)
                {
                   SPIM_1_txBufferRead++;

                    if(SPIM_1_txBufferRead >= SPIM_1_TX_BUFFER_SIZE)
                    {
                        SPIM_1_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPIM_1_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG16(SPIM_1_TXDATA_PTR, 
                                             SPIM_1_txBuffer[SPIM_1_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(SPIM_1_txBufferRead == SPIM_1_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            SPIM_1_TX_STATUS_MASK_REG &= ((uint8) ~SPIM_1_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (SPIM_1_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIM_1_TX_ISR_END` */

    /* `#END` */
    
    #ifdef SPIM_1_TX_ISR_EXIT_CALLBACK
        SPIM_1_TX_ISR_ExitCallback();
    #endif /* SPIM_1_TX_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: SPIM_1_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPIM_1_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPIM_1_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPIM_1_rxBuffer[SPIM_1_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIM_1_RX_ISR)
{
    #if(SPIM_1_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint16 rxData;
    #endif /* (SPIM_1_RX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPIM_1_RX_ISR_ENTRY_CALLBACK
        SPIM_1_RX_ISR_EntryCallback();
    #endif /* SPIM_1_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPIM_1_RX_ISR_START` */

    /* `#END` */
    
    #if(SPIM_1_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = SPIM_1_GET_STATUS_RX(SPIM_1_swStatusRx);
        SPIM_1_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (SPIM_1_swStatusRx & SPIM_1_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG16(SPIM_1_RXDATA_PTR);

            /* Set next pointer. */
            SPIM_1_rxBufferWrite++;
            if(SPIM_1_rxBufferWrite >= SPIM_1_RX_BUFFER_SIZE)
            {
                SPIM_1_rxBufferWrite = 0u;
            }

            if(SPIM_1_rxBufferWrite == SPIM_1_rxBufferRead)
            {
                SPIM_1_rxBufferRead++;
                if(SPIM_1_rxBufferRead >= SPIM_1_RX_BUFFER_SIZE)
                {
                    SPIM_1_rxBufferRead = 0u;
                }

                SPIM_1_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPIM_1_rxBuffer[SPIM_1_rxBufferWrite] = rxData;

            tmpStatus = SPIM_1_GET_STATUS_RX(SPIM_1_swStatusRx);
            SPIM_1_swStatusRx = tmpStatus;
        }

    #endif /* (SPIM_1_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIM_1_RX_ISR_END` */

    /* `#END` */
    
    #ifdef SPIM_1_RX_ISR_EXIT_CALLBACK
        SPIM_1_RX_ISR_ExitCallback();
    #endif /* SPIM_1_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
