#ifndef _CHARGE_STATION_H_
#define _CHARGE_STATION_H_

typedef enum {
    DISCONNECTED=0,
    CONNECTED=1,
    RUNNING=2
} ChargingStatus;

typedef struct {
    ChargingStatus status;
} ChargingInfo_t;

extern T_CHARGER_INFORMATION chargerinformation;
void SendStatusToChargingStation( SCAN_NFCInfo *tag_global);

#endif