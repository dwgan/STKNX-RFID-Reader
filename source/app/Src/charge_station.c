#include "nfc_app.h"
#include "charge_station.h"

ChargingInfo_t ChargingInfo;

void ChargeStatus_Init()
{
    ChargingInfo.status=CONNECTED;
}

void SendStatusToChargingStation( SCAN_NFCInfo *tag_global)
{
    switch (ChargingInfo.status)
    {
    case DISCONNECTED/* constant-expression */:
        /* code */
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_0);
        LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_1);
        break;

    case CONNECTED/* constant-expression */:
        /* code */
        LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_0);
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_1);
        if (tag_global->mem_index != 0xff)
        {
            ChargingInfo.status = RUNNING;
    //        switch (tagArray.tags[tag_global->id_index].vipLevel)
    //        {
    //        case HIGH/* constant-expression */:
    //        LL_GPIO_SetOutputPin(GPIOD, 0);
    //            /* code */
    //            break;
    //        case MEDIUM/* constant-expression */:
    //        LL_GPIO_SetOutputPin(GPIOD, 0);
    //            /* code */
    //            break;
    //        case LOW/* constant-expression */:
    //        LL_GPIO_SetOutputPin(GPIOD, 0);
    //            /* code */
    //            break;
    //        
    //        default:
    //            break;
    //        }
            tag_global->mem_index = 0xff;
        }
        break;

    case RUNNING/* constant-expression */:
        /* code */
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_0);
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_1);
        if (tag_global->mem_index != 0xff)
        {
            ChargingInfo.status = CONNECTED;
            tag_global->mem_index = 0xff;
        }
        break;
    
    default:
        break;
    }
}

// call this func to get the status of charge station and save it
void GetChargingStationStatus()
{
//    ChargingInfo.status = DISCONNECTED;
}

void ChargeStation_Process()
{
    static bool init_done = false;
    if (!init_done)
    {
        ChargeStatus_Init();
        init_done = true;
    }
    
    GetChargingStationStatus();
    SendStatusToChargingStation(&local_info);
}