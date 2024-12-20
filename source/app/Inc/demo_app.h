/******************************************************************************
* ��Ȩ���� (C)2013���Ͼ�******************** ���޹�˾��
*
* �ļ����ƣ�demo_app.h
* �ļ���ʶ����
* ����ժҪ��demo app header file.
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�    
* ������ڣ�2014��7��8��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2014��7��8��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�    
*        �޸����ݣ�������������.
******************************************************************************/

#ifndef _DEMO_APP_H_
#define _DEMO_APP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

//#define DEBUG_TEST

#define OBJECT_SENDOUT_INTERVAL    350  /*350ms */

#define OUTPUT_FLASH_TIME          500 /* 500 ms. */
#define INPUT_CHECK_TIME           50  /* 50ms    */
#define OUTPUT_FLASH_START         1
#define OUTPUT_FLASH_STOP          0

#define  MB_READHOLDINGREGISTERS   0X03
#define  MB_READINPUTREGISTERS     0X04
#define  MB_WRITESINGLEREGISTERS   0x06
#define  MB_WRITEMULTIPLEREGISTERS 0X10

typedef struct
{
	
	BYTE chargerworkingstatus;
	BYTE chargerworkingstatus_previous;
	BYTE connectionstatus;
	BYTE connectionstatus_previous;
	BYTE energy_totalvalue[4];
	BYTE energy_totalvalue_previous[4];
	BYTE energy_lastvalue[4];	
	BYTE energy_lastvalue_previous[4];
	BYTE chargedtime[2];
	BYTE chargedtime_previous[2];
	BYTE chargingvoltage[4];
	BYTE chargingvoltage_previous[2];	
	BYTE chargingpower[4];
	BYTE chargingpower_previous[2];	
	BYTE chargingcurrent[2];
	BYTE chargingcurrent_previous[2];	
	BYTE maximumchargingpower[4];
	BYTE maximumchargingtime[2];
	BYTE faultnumber[2];	
	BYTE faultnumber_previous[2];
	BYTE temperaturevalue[2];
	BYTE datatime[8];
	BYTE chargerid[16];
	BYTE chargersetting;
}T_CHARGER_INFORMATION;


typedef struct
{
	
	BYTE chargerworkingstatusupdate;
	BYTE connectionstatusupdate;
	BYTE energytotalvalueupdate;
	BYTE energy_lastvalueupdate;
	BYTE chargedtimeupdate;
	BYTE chargingvoltageupdate;
	BYTE chargingpowerupdate;
	BYTE chargingcurrentupdate;
	BYTE maximumchargingpower;
	BYTE maximumchargingtime;
	BYTE faultnumberupdate;	
	BYTE temperaturevalueupdate;
	BYTE chargerdatetime;
	BYTE chargeridupdate;
	BYTE chargercontrolupdate;
}T_CHARGER_STATUSUPDATGE;


typedef struct
{
	BYTE maximumchargingpower;
	BYTE maximumchargingtime;
	BYTE chargerdatetime;
	BYTE chargeridupdate;
	BYTE chargerstatussetting;
}T_DATATOCHARGERBOARD_UPDATE;


typedef struct
{
    BYTE    ucSwtCoNo;                   /* switch function com. NO. */
    BYTE    ucForceCoNo;                 /* force function com. No.  */
    BYTE    ucSceneCoNo;                 /* scene function  com. No. */
    WORDPTR pdwSwtTypeRef;               /* switch type set address.   */
    WORDPTR pdwForceCtrlRef;             /* force control set address. */
    WORDPTR pdwSceneCtrlRef;             /* scene control set address. */
    WORDPTR pdwSceneDataRef;             /* scene data address.        */
}T_INPUT_CHANNEL;

typedef struct
{
    BYTE    ucOutCoNo;           /* output function com. NO. */
    BYTE    ucOutStCoNo;         /* output status com. NO.   */
    WORDPTR pdwOutTypeRef;       /* output type set address com. NO. */
}T_OUTPUT_CHANNEL;

typedef struct
{
    BYTE   ucOldSt;               /* the old status of output. */
    BYTE   ucFlashCtl;            /* control flash stop or  start. */
    WORD32 dwStartTime;           /* the action start time(ms). */
}T_OUTPUT_STATUS;



typedef struct
{
    BYTE   ReceivedFlag;
    WORD32 ReceivedTime;
    BYTE   ReceivedMessages[30];
}UARTINPUT_STATUS;

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� Initialize the demo application data.
* ��������� no.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Init(void);

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� Initialize the demo application data.
* ��������� no.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Run(void);
void DataConvert_FloatToInt(BYTE *pData);
void DataConvert_IntToFloat(BYTE *pData);
void float_to_int_bytes(BYTE float_bytes[4],BYTE int_bytes[4]);
void Int_to_float32(BYTE *intBytes, BYTE *floatBytes);
void swapEndian(void* data, size_t size);
void DataConvert_Int32ToFloat( BYTE *pData );
u32_t GetSystemTime_ms(void);
void SystemDelay_ms(u32_t ms);
void ChargerStatus_ToKNXBus_Update(void);
void ChargerStatus_FromKNXBus_Update(void);
void ChargerStatus_ToChargerBoard_Update(void);	 	
void ChargerStatus_FromChargerBoard_Update(void); 
void ChargerDataReceviedProcess(BYTE *pData);

#ifdef __cplusplus
}
#endif

#endif /* _DEMO_APP_H_ */






/* end of file. */
