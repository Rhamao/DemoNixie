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

char writeState = 0;

struct s_data12{
    uint16 data:12;
    uint16 unused:4;
};

#define TESTDATALENGHT 33

struct s_data12 testData[TESTDATALENGHT];
int8 dataIndex = 0;
uint16 octetIndex = 0;

uint8 writing = 0;
char msg[20];




#define TIME_ATTRIB 0x15
#define TIME_VAL_LENGHT 3
#define TIME_EEPROM_LOCATION    3

#define ANIM_ATTRIB 0x12
#define ANIM_VAL_LENGHT 22

int yolo = 0;


char timeValue[TIME_VAL_LENGHT] = {0, 0, 0};
char animValue[ANIM_VAL_LENGHT];

uint8 dataAnimChanged = 0;

struct s_color{
    uint8 r;
    uint8 g;
    uint8 b;
};
struct s_anim_data{
    uint8 animMode;
    struct s_color color0;
    uint32 time0;
    struct s_color color1;
    uint32 time1;
    struct s_color color2;
    uint32 time2;
} animStruct;

void setOffHeure()
{
    memset(testData, 0, 64);
    
}

#define driver2Offset 32
#define driver3Offset 64
#define driver4Offset 96
void setDriverValue(uint8 value, uint8 offset)
{
    switch (value)
    {
     case 0:
        testData[13 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[14 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[15 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 1:
        testData[10 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[11 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[12 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 2:
        testData[7 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[8 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[9 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 3:
        testData[4 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[5 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[6 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 4:
        testData[1 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[2 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[3 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 5:
        testData[29 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[30 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[31 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 6:
        testData[26 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[27 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[28 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 7:
        testData[23 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[24 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[25 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 8:
        testData[20 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[21 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[22 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
     case 9:
        testData[17 + offset].data = (uint16)animStruct.color0.r<<4u;
        testData[18 + offset].data = (uint16)animStruct.color0.g<<4u;
        testData[19 + offset].data = (uint16)animStruct.color0.b<<4u;
        break;
        
    }
}

void setDigitHeure(){
    uint8 heure = timeValue[0];
    setDriverValue(heure/10, 0);
    setDriverValue(heure%10, driver2Offset);    
}
void setDigitMinute(){
    uint8 minute = timeValue[1];
    setDriverValue(minute/10, 0);
    setDriverValue(minute%10, driver2Offset);    
}

void setDataStruct()
{
    animStruct.animMode = animValue[0];
    animStruct.color0.r = animValue[1];
    animStruct.color0.g = animValue[2];
    animStruct.color0.b = animValue[3];
    animStruct.time0 = animValue[7] + (animValue[6] << 8u) + (animValue[5] << 16u) + (animValue[4] << 24u);
    animStruct.color1.r = animValue[8];
    animStruct.color1.g = animValue[9];
    animStruct.color1.b = animValue[10];
    animStruct.time1 = animValue[14] + (animValue[13] << 8u) + (animValue[12] << 16u) + (animValue[11] << 24u);
    animStruct.color2.r = animValue[15];
    animStruct.color2.g = animValue[16];
    animStruct.color2.b = animValue[17];
    animStruct.time2 = animValue[21] + (animValue[20] << 8u) + (animValue[19] << 16u) + (animValue[18] << 24u);
    dataAnimChanged = 1;
}


static cy_stc_ble_conn_handle_t appConnHandle;

char dbgMessage[200];


inline uint8 getBitValue(struct s_data12 data12, uint8 index)
{
        return data12.data & (1u<<index);
}


void GeneralEventHandler(uint32 event, void * eventParam)
{
/* Structure to store data written by Client */
    char str[20];
    uint32_t i = 0;
    sprintf(str,"receive event 0x%x\n", event);
    DBG_PutString(str);
    cy_en_ble_api_result_t apiResult;
    cy_stc_ble_gatts_write_cmd_req_param_t *data;
    uint8 *dataR;
    uint8 *dataW;
    cy_stc_ble_gatt_handle_value_pair_t dataHandle;

    
    static cy_stc_ble_gap_sec_key_info_t keyInfo =
    {
        .localKeysFlag    = CY_BLE_GAP_SMP_INIT_ENC_KEY_DIST | 
                            CY_BLE_GAP_SMP_INIT_IRK_KEY_DIST | 
                            CY_BLE_GAP_SMP_INIT_CSRK_KEY_DIST,
        .exchangeKeysFlag = CY_BLE_GAP_SMP_INIT_ENC_KEY_DIST | 
                            CY_BLE_GAP_SMP_INIT_IRK_KEY_DIST | 
                            CY_BLE_GAP_SMP_INIT_CSRK_KEY_DIST |
                            CY_BLE_GAP_SMP_RESP_ENC_KEY_DIST |
                            CY_BLE_GAP_SMP_RESP_IRK_KEY_DIST |
                            CY_BLE_GAP_SMP_RESP_CSRK_KEY_DIST,
    };
    
        switch (event)
    {
        
        /**********************************************************
        *                       General Events
        ***********************************************************/
        case CY_BLE_EVT_STACK_ON: /* This event is received when the component is Started */
            sprintf(dbgMessage,"*CY_BLE_EVT_STACK_ON, StartAdvertisement \r\n");
            DBG_PutString(dbgMessage);   
            
            /* Enter into discoverable mode so that remote can find it. */
            apiResult = Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            if(apiResult != CY_BLE_SUCCESS)
            {
                sprintf(dbgMessage,"-> Cy_BLE_GAPP_StartAdvertisement API Error: 0x%x \r\n", apiResult);
                DBG_PutString(dbgMessage);   
            }
            
            /* Generates the security keys */
            apiResult = Cy_BLE_GAP_GenerateKeys(&keyInfo);
            if(apiResult != CY_BLE_SUCCESS)
            {
                sprintf(dbgMessage,"-> Cy_BLE_GAP_GenerateKeys API Error: 0x%x \r\n", apiResult);
                DBG_PutString(dbgMessage);
            }
            break;
            
            case CY_BLE_EVT_TIMEOUT: /* 0x01 -> GAP limited discoverable mode timeout. */
                                 /* 0x02 -> GAP pairing process timeout. */
                                 /* 0x03 -> GATT response timeout. */
                DBG_PutString("*CY_BLE_EVT_TIMEOUT \r\n");
            break;
            
            
        case CY_BLE_EVT_SET_TX_PWR_COMPLETE:
//            sprintf(dbgMessage,);
            DBG_PutString("*CY_BLE_EVT_SET_TX_PWR_COMPLETE \r\n");
            break;
            
        case CY_BLE_EVT_LE_SET_EVENT_MASK_COMPLETE:
            DBG_PutString("*CY_BLE_EVT_LE_SET_EVENT_MASK_COMPLETE \r\n");
            break;
        break;
            
        case CY_BLE_EVT_SET_DEVICE_ADDR_COMPLETE:
            DBG_PutString("*CY_BLE_EVT_SET_DEVICE_ADDR_COMPLETE \r\n");
            
            /* Reads the BD device address from BLE Controller's memory */
            apiResult = Cy_BLE_GAP_GetBdAddress();
            if(apiResult != CY_BLE_SUCCESS)
            {   
                sprintf(dbgMessage,"-> Cy_BLE_GAP_GetBdAddress API Error: 0x%x \r\n", apiResult);
                DBG_PutString(dbgMessage);
            }
            break;
            
        case CY_BLE_EVT_GET_DEVICE_ADDR_COMPLETE:
            DBG_PutString("*CY_BLE_EVT_GET_DEVICE_ADDR_COMPLETE: ");
            for(i = CY_BLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
            {
                
                sprintf(dbgMessage,"%2.2x", ((cy_stc_ble_bd_addrs_t *)
                                    ((cy_stc_ble_events_param_generic_t *)eventParam)->eventParams)->publicBdAddr[i-1]);
                DBG_PutString(dbgMessage);
            }
            DBG_PutString("\r\n");
            break;
            
        case CY_BLE_EVT_STACK_SHUTDOWN_COMPLETE:
            DBG_PutString("CY_BLE_EVT_STACK_SHUTDOWN_COMPLETE \r\n");
            /* Hibernate */
            Cy_SysPm_Hibernate();
            break;   
            
            
        case CY_BLE_EVT_HARDWARE_ERROR:    /* This event indicates that some internal HW error has occurred. */
            DBG_PutString("Hardware Error \r\n");
            break;
            
        /* This event will be triggered by host stack if BLE stack is busy or not busy.
         *  Parameter corresponding to this event will be the state of BLE stack.
         *  BLE stack busy = CY_BLE_STACK_STATE_BUSY,
         *  BLE stack not busy = CY_BLE_STACK_STATE_FREE 
         */
        case CY_BLE_EVT_STACK_BUSY_STATUS:
            sprintf(dbgMessage,"CY_BLE_EVT_STACK_BUSY_STATUS: %x\r\n", *(uint8_t *)eventParam);
            DBG_PutString(dbgMessage);
            break;

            
            
        /**********************************************************
        *                       GAP Events
        ***********************************************************/
            
        case CY_BLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            sprintf(dbgMessage, "*CY_BLE_EVT_GAPP_ADVERTISEMENT_START_STOP, state: %d \r\n", Cy_BLE_GetAdvertisementState());
            DBG_PutString(dbgMessage);
            
            if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_STOPPED)
            {   
                /* Fast and slow advertising period complete, go to low power  
                 * mode (Hibernate) and wait for an external
                 * user event to wake up the device again */
                DBG_PutString("-> BLE Stopped\n");
                Cy_BLE_Stop();
            }
            else if (Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADV_INITIATED)
            {
                 DBG_PutString("-> BLE ADV started\n");
   
            }
            else if (Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADVERTISING)
            {
                 DBG_PutString("-> BLE currently ADV\n");
   
            }
            break;
            
        case CY_BLE_EVT_GAP_DEVICE_CONNECTED:
            
            sprintf(dbgMessage,"CY_BLE_EVT_GAP_DEVICE_CONNECTED: connIntv = %d ms \r\n", 
                       ((cy_stc_ble_gap_connected_param_t *)eventParam)->connIntv * 5u /4u);
            DBG_PutString(dbgMessage);
            
            keyInfo.SecKeyParam.bdHandle = (*(cy_stc_ble_gap_connected_param_t *)eventParam).bdHandle;
            apiResult = Cy_BLE_GAP_SetSecurityKeys(&keyInfo);
            if(apiResult != CY_BLE_SUCCESS)
            {
                sprintf(dbgMessage,"-> Cy_BLE_GAP_SetSecurityKeys API Error: 0x%x \r\n", apiResult);
                DBG_PutString(dbgMessage);
            }
            break;
            
            
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            // !!!
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: bdHandle=%x, reason=%x, status=%x\r\n",
                (*(cy_stc_ble_gap_disconnect_param_t *)eventParam).bdHandle, 
                (*(cy_stc_ble_gap_disconnect_param_t *)eventParam).reason, 
                (*(cy_stc_ble_gap_disconnect_param_t *)eventParam).status);
            DBG_PutString(dbgMessage);
            /* Put the device into discoverable mode so that a remote can search it. */
            apiResult = Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            if(apiResult != CY_BLE_SUCCESS)
            {
                sprintf(dbgMessage, "StartAdvertisement API Error: 0x%x \r\n", apiResult);
                DBG_PutString(dbgMessage);
            }
            break;
            
        case CY_BLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE:   
            sprintf(dbgMessage, "*CY_BLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE: connIntv = %d ms \r\n", /* in milliseconds / 1.25ms */
                        ((cy_stc_ble_gap_conn_param_updated_in_controller_t *)eventParam)->connIntv * 5u /4u);
            DBG_PutString(dbgMessage);
            break;
            
            case CY_BLE_EVT_GAP_AUTH_REQ:
            /* This event is received by Peripheral and Central devices. When it is received by a peripheral, 
             * that peripheral must Call Cy_BLE_GAPP_AuthReqReply() to reply to the authentication request
             * from Central. */
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_AUTH_REQ: bdHandle=%x, security=%x, bonding=%x, ekeySize=%x, err=%x \r\n", 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bdHandle, (*(cy_stc_ble_gap_auth_info_t *)eventParam).security, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bonding, (*(cy_stc_ble_gap_auth_info_t *)eventParam).ekeySize, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).authErr);
            DBG_PutString(dbgMessage);
            
            if(cy_ble_configPtr->authInfo[CY_BLE_SECURITY_CONFIGURATION_0_INDEX].security == 
                (CY_BLE_GAP_SEC_MODE_1 | CY_BLE_GAP_SEC_LEVEL_1))
            {
                cy_ble_configPtr->authInfo[CY_BLE_SECURITY_CONFIGURATION_0_INDEX].authErr = 
                    CY_BLE_GAP_AUTH_ERROR_PAIRING_NOT_SUPPORTED;
            }    
            
            cy_ble_configPtr->authInfo[CY_BLE_SECURITY_CONFIGURATION_0_INDEX].bdHandle = 
                ((cy_stc_ble_gap_auth_info_t *)eventParam)->bdHandle;

            /* Pass security information for authentication in reply to an authentication request 
             * from the master device */
            apiResult = Cy_BLE_GAPP_AuthReqReply(&cy_ble_configPtr->authInfo[CY_BLE_SECURITY_CONFIGURATION_0_INDEX]);            
            if(apiResult != CY_BLE_SUCCESS)
            {
                Cy_BLE_GAP_RemoveOldestDeviceFromBondedList();
                apiResult = Cy_BLE_GAPP_AuthReqReply(&cy_ble_configPtr->authInfo[CY_BLE_SECURITY_CONFIGURATION_0_INDEX]);            
                if(apiResult != CY_BLE_SUCCESS)
                {
                    sprintf(dbgMessage, "-> Cy_BLE_GAPP_AuthReqReply API Error: 0x%x \r\n", apiResult);
                    DBG_PutString(dbgMessage);
                }
            }
            break;
        
        case CY_BLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
            DBG_PutString("CY_BLE_EVT_GAP_PASSKEY_ENTRY_REQUEST\r\n");
            DBG_PutString("Please enter the passkey displayed on the peer device:\r\n");
            break;
            
        case CY_BLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST: %6.6d\r\n", *(uint32_t *)eventParam);
            DBG_PutString(dbgMessage);
            break;
            
        case CY_BLE_EVT_GAP_NUMERIC_COMPARISON_REQUEST:
            sprintf(dbgMessage, "Compare this passkey with the one displayed in your peer device and press 'y' or 'n':"
                       " %6.6u \r\n", *(uint32_t *)eventParam);
            DBG_PutString(dbgMessage);
            break;    
            
        case CY_BLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
            DBG_PutString("CY_BLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT \r\n");
            break;
            
        case CY_BLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO:
           sprintf(dbgMessage, "CY_BLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO:" 
                       " bdHandle=%x, security=%x, bonding=%x, ekeySize=%x, err=%x \r\n", 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bdHandle, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).security, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bonding, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).ekeySize, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).authErr);
            DBG_PutString(dbgMessage);
            break;
        
        case CY_BLE_EVT_GAP_AUTH_COMPLETE:
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_AUTH_COMPLETE: bdHandle=%x, security=%x, bonding=%x, ekeySize=%x, err=%x \r\n", 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bdHandle, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).security, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bonding, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).ekeySize, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).authErr);
            DBG_PutString(dbgMessage);
            break;
         
        case CY_BLE_EVT_GAP_AUTH_FAILED:
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_AUTH_FAILED: bdHandle=%x, authErr=%x\r\n", 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).bdHandle, 
                (*(cy_stc_ble_gap_auth_info_t *)eventParam).authErr);
            DBG_PutString(dbgMessage);
            break;    
         
            
        case CY_BLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
            sprintf(dbgMessage, "CY_BLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP, result = %d\r\n", 
                (*(cy_stc_ble_l2cap_conn_update_rsp_param_t *)eventParam).result);
            DBG_PutString(dbgMessage);
            break; 
            
        case CY_BLE_EVT_GAP_KEYS_GEN_COMPLETE:
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_KEYS_GEN_COMPLETE \r\n");
            DBG_PutString(dbgMessage);
            keyInfo.SecKeyParam = (*(cy_stc_ble_gap_sec_key_param_t *)eventParam);
            Cy_BLE_GAP_SetIdAddress(&cy_ble_deviceAddress);
            
            break;
            
        case CY_BLE_EVT_GAP_ENCRYPT_CHANGE:
            sprintf(dbgMessage, "CY_BLE_EVT_GAP_ENCRYPT_CHANGE: %x \r\n", *(uint8_t *)eventParam);
            DBG_PutString(dbgMessage);
            break;
            
        /**********************************************************
        *                       GATT Events
        ***********************************************************/
            
        case CY_BLE_EVT_GATT_CONNECT_IND:
            appConnHandle = *(cy_stc_ble_conn_handle_t *)eventParam;
            sprintf(dbgMessage, "* CY_BLE_EVT_GATT_CONNECT_IND: %x, %x \r\n", 
                (*(cy_stc_ble_conn_handle_t *)eventParam).attId, 
                (*(cy_stc_ble_conn_handle_t *)eventParam).bdHandle);
            DBG_PutString(dbgMessage);
            break;
            
        case CY_BLE_EVT_GATT_DISCONNECT_IND:
            sprintf(dbgMessage, "CY_BLE_EVT_GATT_DISCONNECT_IND: %x, %x \r\n", 
                (*(cy_stc_ble_conn_handle_t *)eventParam).attId, 
                (*(cy_stc_ble_conn_handle_t *)eventParam).bdHandle);
            DBG_PutString(dbgMessage);
            break;
            
        case CY_BLE_EVT_GATTS_XCNHG_MTU_REQ:
            { 
                cy_stc_ble_gatt_xchg_mtu_param_t mtu = 
                {
                    .connHandle = ((cy_stc_ble_gatt_xchg_mtu_param_t *)eventParam)->connHandle
                };
                Cy_BLE_GATT_GetMtuSize(&mtu);
                sprintf(dbgMessage, "*CY_BLE_EVT_GATTS_XCNHG_MTU_REQ %x, %x, final mtu= %d \r\n", mtu.connHandle.attId,
                            mtu.connHandle.bdHandle, mtu.mtu);
                DBG_PutString(dbgMessage);
            }
            break;
            
        case CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
            /* Triggered on server side when client sends read request and when
            * characteristic has CY_BLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set.
            * This event could be ignored by application unless it need to response
            * by error response which needs to be set in gattErrorCode field of
            * event parameter. */
            sprintf(dbgMessage, "*CY_BLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ: handle: %x \r\n", 
                ((cy_stc_ble_gatts_char_val_read_req_t *)eventParam)->attrHandle);
            DBG_PutString(dbgMessage);
            break;
            
        /**********************************************************
        *                       Other Events
        ***********************************************************/
        case CY_BLE_EVT_PENDING_FLASH_WRITE:
            /* Inform application that flash write is pending. Stack internal data 
            * structures are modified and require to be stored in Flash using 
            * Cy_BLE_StoreBondingData() */
            DBG_PutString("CY_BLE_EVT_PENDING_FLASH_WRITE\r\n");
            break;
            
            
        case    CY_BLE_EVT_GATTS_WRITE_CMD_REQ:
            data = eventParam;
            DBG_PutString("CY_BLE_EVT_GATTS_WRITE_CMD_REQ\r\n");
                
            dataW = data->handleValPair.value.val;
            if (data->handleValPair.attrHandle == TIME_ATTRIB)
            {

                DBG_PutString("-->receive TIME");
                dataHandle.attrHandle = TIME_ATTRIB;
                memcpy(timeValue, dataW, TIME_VAL_LENGHT);
                sprintf(dbgMessage, "---> time : %d:%d::%d \r\n", timeValue[0], timeValue[1], timeValue[2]);
                DBG_PutString(dbgMessage);
                
            }
            else if (data->handleValPair.attrHandle == ANIM_ATTRIB)
            {
                DBG_PutString("-->receive Color");
                
                
                dataHandle.attrHandle = ANIM_ATTRIB;
                memcpy(animValue, dataW, ANIM_VAL_LENGHT);
                setDataStruct();
                
                
            }
            
            
        break;
            
        /**********************************************************
        *                       BAS Events
        ***********************************************************/
        case    CY_BLE_EVT_GATTS_INDICATION_ENABLED:
            DBG_PutString("CY_BLE_EVT_GATTS_INDICATION_ENABLED\r\n");
        break;
        case    CY_BLE_EVT_GATTS_INDICATION_DISABLED:
            DBG_PutString("CY_BLE_EVT_GATTS_INDICATION_DISABLED\r\n");
        break;
        case    CY_BLE_EVT_GATTS_EVT_CCCD_CORRUPT:
            DBG_PutString("CY_BLE_EVT_GATTS_EVT_CCCD_CORRUPT\r\n");
        break;
            
        default:
            if (event >= 0x10000)
                DBG_PutString("unhandled BAS event\n");
            else
                DBG_PutString("unhandled STACK event\n");
        break;
            
    }
    
}

void itHandle()
{
//   LedDriverSdaOut
    Cy_TCPWM_ClearInterrupt(PWM_COM_HW, PWM_COM_CNT_NUM, CY_TCPWM_INT_ON_TC);
    if (writeState)
    {
        writing = 1;
        if (testData[octetIndex].data & (1u<<dataIndex))
        {
            Cy_GPIO_Write(LedDriverSdaOut_PORT, LedDriverSdaOut_NUM,1);
        }
        else
        {
            Cy_GPIO_Write(LedDriverSdaOut_PORT, LedDriverSdaOut_NUM,0);
        }
        dataIndex--;
        if (dataIndex < 0)
        {
            dataIndex = 11;
            octetIndex++;
            if (octetIndex == TESTDATALENGHT)
                writeState = 0;
        }
        else if (octetIndex == TESTDATALENGHT -1 && dataIndex < 10)
        {
            writeState = 0;
            dataIndex = 11;
            
        }
           

    }
    else
    {
        Cy_GPIO_Write(LedDriverLatchOut_PORT, LedDriverLatchOut_NUM, 0);
        PWM_COM_Disable();
        Cy_GPIO_Write(LedDriverSdaOut_PORT, LedDriverSdaOut_NUM,0);
        if (writing)
        {
            writing = 0;
            yolo = 1;
            Cy_GPIO_Write(LedDriverLatchOut_PORT, LedDriverLatchOut_NUM, 1);
            CyDelayUs(2);
            Cy_GPIO_Write(LedDriverLatchOut_PORT, LedDriverLatchOut_NUM, 0);
            
        }
    }
}
    

void eventLoop()
{
//   LedDriverSdaOut
    if (yolo)
    {
     //return;   
    }
    writeState = 1;
    //sprintf(msg,"%d\n", testData.data12.data);
    //DBG_PutString(msg);
    dataIndex = 11;
    
    static int j = 0;
    
    j = !j;
    
    if (j)
    {
        testData[TESTDATALENGHT - 1].data = 0xc00;
    }
    else
    {
        testData[TESTDATALENGHT - 1].data = 0xc00;
    }
    if (testData[0].data & (1u<<dataIndex))
    {
        Cy_GPIO_Write(LedDriverSdaOut_PORT, LedDriverSdaOut_NUM,1);
    }
    else
    {
        Cy_GPIO_Write(LedDriverSdaOut_PORT, LedDriverSdaOut_NUM,0);
    }
    
    dataIndex = 10;
    octetIndex = 0;
    Cy_GPIO_Write(LedDriverLatchOut_PORT, LedDriverLatchOut_NUM, 0);
    Cy_TCPWM_ClearInterrupt(TIMER_HW, TIMER_CNT_NUM, CY_TCPWM_INT_ON_TC);
    PWM_COM_Enable();
    PWM_COM_Start();
    

    //Cy_GPIO_Inv(LedDriverSdaOut_PORT, LedDriverSdaOut_NUM);
}



int main(void)
{
    cy_en_ble_api_result_t apiResult;
    
    int i = 0;
    while(i<TESTDATALENGHT -1)
    {
        if (i < 10)
            testData[i].data = 0xc00;
        else
            testData[i].data = 0xc00;
        
        i++;
    }
    testData[i].data = 0Xc00;
    /*
    testData[i].data = (0b100000000000);
    testData[3].data = (0b100000000000);
    */
    
    memset(animValue, 0, ANIM_VAL_LENGHT);
    Cy_SysLib_Delay(5000);
    Cy_SysInt_Init(&dataIsr_cfg, itHandle);
    Cy_SysInt_Init(&Timer_ISR_cfg, eventLoop);
    NVIC_EnableIRQ(dataIsr_cfg.intrSrc); /* Enable the core interrupt */
    NVIC_EnableIRQ(Timer_ISR_cfg.intrSrc); /* Enable the core interrupt */
    __enable_irq(); /* Enable global interrupts. */
    
    //EEPROM_config.userFlashStartAddr = (uint32_t)EEPROM_em_EepromStorage;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    //Cy_GPIO_Pin_Init(LedDriverSdaOut_0_PORT, LedDriverSdaOut_0_NUM, LedDriverSdaOut_0_cfg);    
//    Cy_TCPWM_Counter_Init(PWM_COM_HW, PWM_COM_CNT_NUM, &PWM_COM_config); 
    Cy_SysLib_Delay(100);
    //Cy_GPIO_Write(LedDriverSdaOut_0_PORT, LedDriverSdaOut_0_NUM,0);
    
    //Cy_TCPWM_TriggerStart(PWM_COM_HW, PWM_COM_CNT_MASK); 
    PWM_COM_Start();
    PWMDriver_Start();
    TIMER_Start();
    
        DBG_Start();
    apiResult = Cy_BLE_Start(GeneralEventHandler);  
    DBG_PutString("UART Started\n");
    if(apiResult != CY_BLE_SUCCESS)
    {   
        sprintf(dbgMessage,"Cy_BLE_Start API Error: 0x%x \r\n", apiResult);
        DBG_PutString(dbgMessage);
        
    }
    //sprintf(dbgMessage, "Cy_BLE_GAP_GetBdAddress API Error: 0x%x \r\n", apiResult)
    DBG_PutString("BLE Started\n");
    
	//NVIC_ClearPendingIRQ(dataIsr_cfg.intrSrc);
	//NVIC_EnableIRQ(dataIsr_cfg.intrSrc);
    for(;;)
    {
        Cy_BLE_ProcessEvents();
        if (dataAnimChanged)
        {
            
            dataAnimChanged = 0;
        }
        Cy_SysLib_Delay(10);
    
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
