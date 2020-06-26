/***************************************************************************//**
* \file DBG.h
* \version 2.0
*
*  This file provides constants and parameter values for the UART component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(DBG_CY_SCB_UART_PDL_H)
#define DBG_CY_SCB_UART_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define DBG_DIRECTION  (3U)
#define DBG_ENABLE_RTS (0U)
#define DBG_ENABLE_CTS (0U)

/* UART direction enum */
#define DBG_RX    (0x1U)
#define DBG_TX    (0x2U)

#define DBG_ENABLE_RX  (0UL != (DBG_DIRECTION & DBG_RX))
#define DBG_ENABLE_TX  (0UL != (DBG_DIRECTION & DBG_TX))


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component specific functions. */
void DBG_Start(void);

/* Basic functions */
__STATIC_INLINE cy_en_scb_uart_status_t DBG_Init(cy_stc_scb_uart_config_t const *config);
__STATIC_INLINE void DBG_DeInit(void);
__STATIC_INLINE void DBG_Enable(void);
__STATIC_INLINE void DBG_Disable(void);

/* Register callback. */
__STATIC_INLINE void DBG_RegisterCallback(cy_cb_scb_uart_handle_events_t callback);

/* Configuration change. */
#if (DBG_ENABLE_CTS)
__STATIC_INLINE void DBG_EnableCts(void);
__STATIC_INLINE void DBG_DisableCts(void);
#endif /* (DBG_ENABLE_CTS) */

#if (DBG_ENABLE_RTS)
__STATIC_INLINE void     DBG_SetRtsFifoLevel(uint32_t level);
__STATIC_INLINE uint32_t DBG_GetRtsFifoLevel(void);
#endif /* (DBG_ENABLE_RTS) */

__STATIC_INLINE void DBG_EnableSkipStart(void);
__STATIC_INLINE void DBG_DisableSkipStart(void);

#if (DBG_ENABLE_RX)
/* Low level: Receive direction. */
__STATIC_INLINE uint32_t DBG_Get(void);
__STATIC_INLINE uint32_t DBG_GetArray(void *buffer, uint32_t size);
__STATIC_INLINE void     DBG_GetArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t DBG_GetRxFifoStatus(void);
__STATIC_INLINE void     DBG_ClearRxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t DBG_GetNumInRxFifo(void);
__STATIC_INLINE void     DBG_ClearRxFifo(void);
#endif /* (DBG_ENABLE_RX) */

#if (DBG_ENABLE_TX)
/* Low level: Transmit direction. */
__STATIC_INLINE uint32_t DBG_Put(uint32_t data);
__STATIC_INLINE uint32_t DBG_PutArray(void *buffer, uint32_t size);
__STATIC_INLINE void     DBG_PutArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE void     DBG_PutString(char_t const string[]);
__STATIC_INLINE void     DBG_SendBreakBlocking(uint32_t breakWidth);
__STATIC_INLINE uint32_t DBG_GetTxFifoStatus(void);
__STATIC_INLINE void     DBG_ClearTxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t DBG_GetNumInTxFifo(void);
__STATIC_INLINE bool     DBG_IsTxComplete(void);
__STATIC_INLINE void     DBG_ClearTxFifo(void);
#endif /* (DBG_ENABLE_TX) */

#if (DBG_ENABLE_RX)
/* High level: Ring buffer functions. */
__STATIC_INLINE void     DBG_StartRingBuffer(void *buffer, uint32_t size);
__STATIC_INLINE void     DBG_StopRingBuffer(void);
__STATIC_INLINE void     DBG_ClearRingBuffer(void);
__STATIC_INLINE uint32_t DBG_GetNumInRingBuffer(void);

/* High level: Receive direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t DBG_Receive(void *buffer, uint32_t size);
__STATIC_INLINE void     DBG_AbortReceive(void);
__STATIC_INLINE uint32_t DBG_GetReceiveStatus(void);
__STATIC_INLINE uint32_t DBG_GetNumReceived(void);
#endif /* (DBG_ENABLE_RX) */

#if (DBG_ENABLE_TX)
/* High level: Transmit direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t DBG_Transmit(void *buffer, uint32_t size);
__STATIC_INLINE void     DBG_AbortTransmit(void);
__STATIC_INLINE uint32_t DBG_GetTransmitStatus(void);
__STATIC_INLINE uint32_t DBG_GetNumLeftToTransmit(void);
#endif /* (DBG_ENABLE_TX) */

/* Interrupt handler */
__STATIC_INLINE void DBG_Interrupt(void);
/** @} group_general */


/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t DBG_initVar;
extern cy_stc_scb_uart_config_t const DBG_config;
extern cy_stc_scb_uart_context_t DBG_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the hardware */
#define DBG_HW     ((CySCB_Type *) DBG_SCB__HW)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: DBG_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t DBG_Init(cy_stc_scb_uart_config_t const *config)
{
   return Cy_SCB_UART_Init(DBG_HW, config, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_DeInit(void)
{
    Cy_SCB_UART_DeInit(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_Enable(void)
{
    Cy_SCB_UART_Enable(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_Disable(void)
{
    Cy_SCB_UART_Disable(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_RegisterCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_RegisterCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_RegisterCallback(cy_cb_scb_uart_handle_events_t callback)
{
    Cy_SCB_UART_RegisterCallback(DBG_HW, callback, &DBG_context);
}


#if (DBG_ENABLE_CTS)
/*******************************************************************************
* Function Name: DBG_EnableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_EnableCts(void)
{
    Cy_SCB_UART_EnableCts(DBG_HW);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_DisableCts(void)
{
    Cy_SCB_UART_DisableCts(DBG_HW);
}
#endif /* (DBG_ENABLE_CTS) */


#if (DBG_ENABLE_RTS)
/*******************************************************************************
* Function Name: DBG_SetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_SetRtsFifoLevel(uint32_t level)
{
    Cy_SCB_UART_SetRtsFifoLevel(DBG_HW, level);
}


/*******************************************************************************
* Function Name: DBG_GetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetRtsFifoLevel(void)
{
    return Cy_SCB_UART_GetRtsFifoLevel(DBG_HW);
}
#endif /* (DBG_ENABLE_RTS) */


/*******************************************************************************
* Function Name: DBG_EnableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_EnableSkipStart(void)
{
    Cy_SCB_UART_EnableSkipStart(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_DisableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_DisableSkipStart(void)
{
    Cy_SCB_UART_DisableSkipStart(DBG_HW);
}


#if (DBG_ENABLE_RX)
/*******************************************************************************
* Function Name: DBG_Get
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Get() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_Get(void)
{
    return Cy_SCB_UART_Get(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_GetArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_GetArray(DBG_HW, buffer, size);
}


/*******************************************************************************
* Function Name: DBG_GetArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_GetArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_GetArrayBlocking(DBG_HW, buffer, size);
}


/*******************************************************************************
* Function Name: DBG_GetRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetRxFifoStatus(void)
{
    return Cy_SCB_UART_GetRxFifoStatus(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_ClearRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_ClearRxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearRxFifoStatus(DBG_HW, clearMask);
}


/*******************************************************************************
* Function Name: DBG_GetNumInRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetNumInRxFifo(void)
{
    return Cy_SCB_UART_GetNumInRxFifo(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_ClearRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_ClearRxFifo(void)
{
    Cy_SCB_UART_ClearRxFifo(DBG_HW);
}
#endif /* (DBG_ENABLE_RX) */


#if (DBG_ENABLE_TX)
/*******************************************************************************
* Function Name: DBG_Put
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Put() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_Put(uint32_t data)
{
    return Cy_SCB_UART_Put(DBG_HW,data);
}


/*******************************************************************************
* Function Name: DBG_PutArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_PutArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_PutArray(DBG_HW, buffer, size);
}


/*******************************************************************************
* Function Name: DBG_PutArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_PutArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_PutArrayBlocking(DBG_HW, buffer, size);
}


/*******************************************************************************
* Function Name: DBG_PutString
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutString() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_PutString(char_t const string[])
{
    Cy_SCB_UART_PutString(DBG_HW, string);
}


/*******************************************************************************
* Function Name: DBG_SendBreakBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SendBreakBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_SendBreakBlocking(uint32_t breakWidth)
{
    Cy_SCB_UART_SendBreakBlocking(DBG_HW, breakWidth);
}


/*******************************************************************************
* Function Name: DBG_GetTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetTxFifoStatus(void)
{
    return Cy_SCB_UART_GetTxFifoStatus(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_ClearTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_ClearTxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearTxFifoStatus(DBG_HW, clearMask);
}


/*******************************************************************************
* Function Name: DBG_GetNumInTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetNumInTxFifo(void)
{
    return Cy_SCB_UART_GetNumInTxFifo(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_IsTxComplete
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_IsTxComplete() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool DBG_IsTxComplete(void)
{
    return Cy_SCB_UART_IsTxComplete(DBG_HW);
}


/*******************************************************************************
* Function Name: DBG_ClearTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_ClearTxFifo(void)
{
    Cy_SCB_UART_ClearTxFifo(DBG_HW);
}
#endif /* (DBG_ENABLE_TX) */


#if (DBG_ENABLE_RX)
/*******************************************************************************
* Function Name: DBG_StartRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StartRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_StartRingBuffer(void *buffer, uint32_t size)
{
    Cy_SCB_UART_StartRingBuffer(DBG_HW, buffer, size, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_StopRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StopRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_StopRingBuffer(void)
{
    Cy_SCB_UART_StopRingBuffer(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_ClearRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_ClearRingBuffer(void)
{
    Cy_SCB_UART_ClearRingBuffer(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_GetNumInRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetNumInRingBuffer(void)
{
    return Cy_SCB_UART_GetNumInRingBuffer(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_Receive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Receive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t DBG_Receive(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Receive(DBG_HW, buffer, size, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_GetReceiveStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetReceiveStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetReceiveStatus(void)
{
    return Cy_SCB_UART_GetReceiveStatus(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_AbortReceive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortReceive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_AbortReceive(void)
{
    Cy_SCB_UART_AbortReceive(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_GetNumReceived
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumReceived() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetNumReceived(void)
{
    return Cy_SCB_UART_GetNumReceived(DBG_HW, &DBG_context);
}
#endif /* (DBG_ENABLE_RX) */


#if (DBG_ENABLE_TX)
/*******************************************************************************
* Function Name: DBG_Transmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Transmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t DBG_Transmit(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Transmit(DBG_HW, buffer, size, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_GetTransmitStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTransmitStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetTransmitStatus(void)
{
    return Cy_SCB_UART_GetTransmitStatus(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_AbortTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_AbortTransmit(void)
{
    Cy_SCB_UART_AbortTransmit(DBG_HW, &DBG_context);
}


/*******************************************************************************
* Function Name: DBG_GetNumLeftToTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumLeftToTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t DBG_GetNumLeftToTransmit(void)
{
    return Cy_SCB_UART_GetNumLeftToTransmit(DBG_HW, &DBG_context);
}
#endif /* (DBG_ENABLE_TX) */


/*******************************************************************************
* Function Name: DBG_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void DBG_Interrupt(void)
{
    Cy_SCB_UART_Interrupt(DBG_HW, &DBG_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* DBG_CY_SCB_UART_PDL_H */


/* [] END OF FILE */
