/*******************************************************************************
* File Name: TIMER.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the TIMER
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(TIMER_CY_TCPWM_PWM_PDL_H)
#define TIMER_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  TIMER_initVar;
extern cy_stc_tcpwm_pwm_config_t const TIMER_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void TIMER_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t TIMER_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void TIMER_DeInit(void);
__STATIC_INLINE void TIMER_Enable(void);
__STATIC_INLINE void TIMER_Disable(void);
__STATIC_INLINE uint32_t TIMER_GetStatus(void);
__STATIC_INLINE void TIMER_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t TIMER_GetCompare0(void);
__STATIC_INLINE void TIMER_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t TIMER_GetCompare1(void);
__STATIC_INLINE void TIMER_EnableCompareSwap(bool enable);
__STATIC_INLINE void TIMER_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t TIMER_GetCounter(void);
__STATIC_INLINE void TIMER_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t TIMER_GetPeriod0(void);
__STATIC_INLINE void TIMER_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t TIMER_GetPeriod1(void);
__STATIC_INLINE void TIMER_EnablePeriodSwap(bool enable);
__STATIC_INLINE void TIMER_TriggerStart(void);
__STATIC_INLINE void TIMER_TriggerReload(void);
__STATIC_INLINE void TIMER_TriggerKill(void);
__STATIC_INLINE void TIMER_TriggerSwap(void);
__STATIC_INLINE uint32_t TIMER_GetInterruptStatus(void);
__STATIC_INLINE void TIMER_ClearInterrupt(uint32_t source);
__STATIC_INLINE void TIMER_SetInterrupt(uint32_t source);
__STATIC_INLINE void TIMER_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t TIMER_GetInterruptMask(void);
__STATIC_INLINE uint32_t TIMER_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define TIMER_HW                 (TIMER_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define TIMER_CNT_HW             (TIMER_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define TIMER_CNT_NUM            (TIMER_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define TIMER_CNT_MASK           (1UL << TIMER_CNT_NUM)
/** @} group_macros */

#define TIMER_INPUT_MODE_MASK    (0x3U)
#define TIMER_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: TIMER_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t TIMER_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(TIMER_HW, TIMER_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: TIMER_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(TIMER_HW, TIMER_CNT_NUM, &TIMER_config);
}

/*******************************************************************************
* Function Name: TIMER_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(TIMER_HW, TIMER_CNT_MASK);
}


/*******************************************************************************
* Function Name: TIMER_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(TIMER_HW, TIMER_CNT_MASK);
}


/*******************************************************************************
* Function Name: TIMER_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(TIMER_HW, TIMER_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: TIMER_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(TIMER_HW, TIMER_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: TIMER_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(TIMER_HW, TIMER_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: TIMER_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(TIMER_HW, TIMER_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: TIMER_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(TIMER_HW, TIMER_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: TIMER_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(TIMER_HW, TIMER_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: TIMER_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(TIMER_HW, TIMER_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: TIMER_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(TIMER_HW, TIMER_CNT_MASK);
}


/*******************************************************************************
* Function Name: TIMER_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(TIMER_HW, TIMER_CNT_MASK);
}


/*******************************************************************************
* Function Name: TIMER_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(TIMER_HW, TIMER_CNT_MASK);
}


/*******************************************************************************
* Function Name: TIMER_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(TIMER_HW, TIMER_CNT_MASK);
}


/*******************************************************************************
* Function Name: TIMER_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(TIMER_HW, TIMER_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: TIMER_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(TIMER_HW, TIMER_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: TIMER_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void TIMER_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(TIMER_HW, TIMER_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: TIMER_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(TIMER_HW, TIMER_CNT_NUM));
}


/*******************************************************************************
* Function Name: TIMER_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t TIMER_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(TIMER_HW, TIMER_CNT_NUM));
}

#endif /* TIMER_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
