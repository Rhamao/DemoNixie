/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LOGICAL_EEPROM_SIZE     25u
#define LOGICAL_EEPROM_START    0u




#define TIME_ATTRIB 0x15
#define TIME_VAL_LENGHT 3
#define TIME_EEPROM_LOCATION    3

#define ANIM_ATTRIB 0x12
#define ANIM_VAL_LENGHT 22


char timeValue[TIME_VAL_LENGHT] = {0, 0, 0};
char animValue[ANIM_VAL_LENGHT];

static cy_stc_ble_conn_handle_t appConnHandle;


int main(void)
{
    cy_en_ble_api_result_t apiResult;
    __enable_irq(); /* Enable global interrupts. */
    Cy_RTC_Init(&RTC_1_config);
//    Cy_i
    /* Set Start Address to work flash */
    //EEPROM_config.userFlashStartAddr = (uint32_t)EEPROM_em_EepromStorage;
     
    
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 
    
    
    memset(animValue, 0, ANIM_VAL_LENGHT);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    /*
    apiResult = Cy_BLE_Start(GeneralEventHandler);
    DBG_Start();
   
    DBG_PutString("UART Started\n");
    if(apiResult != CY_BLE_SUCCESS)
    {   
        sprintf(dbgMessage,"Cy_BLE_Start API Error: 0x%x \r\n", apiResult);
        DBG_PutString(dbgMessage);
        
    }
    //sprintf(dbgMessage, "Cy_BLE_GAP_GetBdAddress API Error: 0x%x \r\n", apiResult)
    DBG_PutString("BLE Started\n");
    */
    //Cy_SysInt_Init(&dataIsr_cfg, itHandle);
    for(;;)
    {
       // Cy_BLE_ProcessEvents();
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
