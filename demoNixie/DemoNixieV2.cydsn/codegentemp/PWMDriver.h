/*******************************************************************************
* File Name: PWMDriver.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the PWMDriver
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(PWMDriver_CY_TCPWM_PWM_PDL_H)
#define PWMDriver_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  PWMDriver_initVar;
extern cy_stc_tcpwm_pwm_config_t const PWMDriver_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void PWMDriver_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t PWMDriver_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void PWMDriver_DeInit(void);
__STATIC_INLINE void PWMDriver_Enable(void);
__STATIC_INLINE void PWMDriver_Disable(void);
__STATIC_INLINE uint32_t PWMDriver_GetStatus(void);
__STATIC_INLINE void PWMDriver_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t PWMDriver_GetCompare0(void);
__STATIC_INLINE void PWMDriver_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t PWMDriver_GetCompare1(void);
__STATIC_INLINE void PWMDriver_EnableCompareSwap(bool enable);
__STATIC_INLINE void PWMDriver_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t PWMDriver_GetCounter(void);
__STATIC_INLINE void PWMDriver_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t PWMDriver_GetPeriod0(void);
__STATIC_INLINE void PWMDriver_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t PWMDriver_GetPeriod1(void);
__STATIC_INLINE void PWMDriver_EnablePeriodSwap(bool enable);
__STATIC_INLINE void PWMDriver_TriggerStart(void);
__STATIC_INLINE void PWMDriver_TriggerReload(void);
__STATIC_INLINE void PWMDriver_TriggerKill(void);
__STATIC_INLINE void PWMDriver_TriggerSwap(void);
__STATIC_INLINE uint32_t PWMDriver_GetInterruptStatus(void);
__STATIC_INLINE void PWMDriver_ClearInterrupt(uint32_t source);
__STATIC_INLINE void PWMDriver_SetInterrupt(uint32_t source);
__STATIC_INLINE void PWMDriver_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t PWMDriver_GetInterruptMask(void);
__STATIC_INLINE uint32_t PWMDriver_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define PWMDriver_HW                 (PWMDriver_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define PWMDriver_CNT_HW             (PWMDriver_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define PWMDriver_CNT_NUM            (PWMDriver_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define PWMDriver_CNT_MASK           (1UL << PWMDriver_CNT_NUM)
/** @} group_macros */

#define PWMDriver_INPUT_MODE_MASK    (0x3U)
#define PWMDriver_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: PWMDriver_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t PWMDriver_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(PWMDriver_HW, PWMDriver_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: PWMDriver_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(PWMDriver_HW, PWMDriver_CNT_NUM, &PWMDriver_config);
}

/*******************************************************************************
* Function Name: PWMDriver_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(PWMDriver_HW, PWMDriver_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWMDriver_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(PWMDriver_HW, PWMDriver_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWMDriver_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(PWMDriver_HW, PWMDriver_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: PWMDriver_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(PWMDriver_HW, PWMDriver_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: PWMDriver_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(PWMDriver_HW, PWMDriver_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: PWMDriver_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(PWMDriver_HW, PWMDriver_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: PWMDriver_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(PWMDriver_HW, PWMDriver_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: PWMDriver_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(PWMDriver_HW, PWMDriver_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: PWMDriver_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(PWMDriver_HW, PWMDriver_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: PWMDriver_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(PWMDriver_HW, PWMDriver_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWMDriver_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(PWMDriver_HW, PWMDriver_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWMDriver_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(PWMDriver_HW, PWMDriver_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWMDriver_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(PWMDriver_HW, PWMDriver_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWMDriver_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(PWMDriver_HW, PWMDriver_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: PWMDriver_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(PWMDriver_HW, PWMDriver_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: PWMDriver_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWMDriver_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(PWMDriver_HW, PWMDriver_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: PWMDriver_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(PWMDriver_HW, PWMDriver_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWMDriver_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWMDriver_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(PWMDriver_HW, PWMDriver_CNT_NUM));
}

#endif /* PWMDriver_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
