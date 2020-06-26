/*******************************************************************************
* File Name: TIMER.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the TIMER
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TIMER.h"

/** Indicates whether or not the TIMER has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  TIMER_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the TIMER_Start() routine.
*/
uint8_t TIMER_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated TIMER_Init() function.
*/ 
cy_stc_tcpwm_pwm_config_t const TIMER_config =
{
    .pwmMode = 4UL,
    .clockPrescaler = 0UL,
    .pwmAlignment = 0UL,
    .deadTimeClocks = 0UL,
    .runMode = 0UL,
    .period0 = 1UL,
    .period1 = 32768UL,
    .enablePeriodSwap = false,
    .compare0 = 1UL,
    .compare1 = 16384UL,
    .enableCompareSwap = false,
    .interruptSources = 1UL,
    .invertPWMOut = 0UL,
    .invertPWMOutN = 0UL,
    .killMode = 2UL,
    .swapInputMode = 3UL,
    .swapInput = CY_TCPWM_INPUT_CREATOR,
    .reloadInputMode = 3UL,
    .reloadInput = CY_TCPWM_INPUT_CREATOR,
    .startInputMode = 3UL,
    .startInput = CY_TCPWM_INPUT_CREATOR,
    .killInputMode = 3UL,
    .killInput = CY_TCPWM_INPUT_CREATOR,
    .countInputMode = 3UL,
    .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: TIMER_Start
****************************************************************************//**
*
*  Calls the TIMER_Init() when called the first time and enables 
*  the TIMER. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref TIMER_initVar
*
*******************************************************************************/
void TIMER_Start(void)
{
    if (0U == TIMER_initVar)
    {
        (void) Cy_TCPWM_PWM_Init(TIMER_HW, TIMER_CNT_NUM, &TIMER_config);

        TIMER_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(TIMER_HW, TIMER_CNT_MASK);
    
    #if (TIMER_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(TIMER_HW, TIMER_CNT_MASK);
    #endif /* (TIMER_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
