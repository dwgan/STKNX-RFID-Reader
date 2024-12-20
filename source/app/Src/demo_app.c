/******************************************************************************
* ��Ȩ���� (C)2013��**************��˾
*
* �ļ����ƣ�demo_app.c
* �ļ���ʶ����
* ����ժҪ��demo application for education.
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�      
* ������ڣ�2013��7��24��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2013��7��24��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�      
*        �޸����ݣ�������������.
******************************************************************************/

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "app_common.h"
#include "Hardware.h"
#include "Knx_Prop.h"
#include "Rec_Table.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "Application.h"
#include "Knx_AlApp.h"
#include "demo_app.h"
#include "App_Api.h"
#include "boardctrl.h"
#include "demo.h"
#include "SerialProc.h"
#include "main.h"
#include "string.h"
#include "charge_station.h"


T_CHARGER_INFORMATION chargerinformation;
T_CHARGER_STATUSUPDATGE chargerupdateflag;
T_DATATOCHARGERBOARD_UPDATE chargerboardupdateflag;

BYTE uartdataupdatflag;
WORD32 lastuartsendtime;
WORD32 lastchecktime;


UARTINPUT_STATUS chargerinputdata;
int nfc_init_done=0;
uint32_t RefTime = 0;

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
void Demo_App_Init(void)
{
    RefTime = API_KnxTm_GetTimeMs();
}

/**************************************************************************
* �������ƣ� VOID Demo_App_Forced_Run(BYTE ucInputNo)
* ���������� handle the force function happening on the input channel.
* ��������� BYTE ucInputNo : the NO. of the input channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Forced_Run(BYTE ucInputNo)
{
    ;
}

/**************************************************************************
* �������ƣ� VOID Demo_App_Scene_Run(BYTE ucInputNo)
* ���������� handle the scene function happening on the input channel.
* ��������� BYTE ucInputNo : the NO. of the input channel.z
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Scene_Run(BYTE ucInputNo)
{
    ;
}

/**************************************************************************
* �������ƣ� VOID Demo_App_Switch_Run(BYTE ucInputNo)
* ���������� handle key input function.
* ��������� BYTE ucInputNo : the NO. of the input channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Switch_Run(BYTE ucInputNo)
{
    ;
}

/**************************************************************************
* �������ƣ� void Demo_App_Out_Run(BYTE ucOutputNo)
* ���������� handle output function.
* ��������� BYTE ucOutputNo : the NO. of the output channel.
* ��������� no.      
* �� �� ֵ�� no.
* ����˵���� no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Out_Run(BYTE ucOutputNo)
{
    ;
}

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
uint16_t int32_to_custom_float16(int32_t int32) ;
void ChargerStatus_FromRFID_Update( SCAN_NFCInfo *tag_global);
uint8_t NFCTagUpdateflag;
static KNX_NFCInfo RFID_Msg_Out;
BYTE is_prgm_mode;
void Demo_App_Run(void)
{
    BYTE ucData;
    static BYTE KNX_Msg_In[14];
    static WORD32 TimesMsRef;
    static WORD32 TimesMsRef1;
    WORD16 crcchecksum;
    BYTE sendvalue[2];
    
    if ( API_KnxTm_GetDelayMs( RefTime ) >= 0 && nfc_init_done== 0 && is_prgm_mode == 0)
    {
        nfc_app_init();
        nfc_init_done= 1;
    }
    
    if (is_prgm_mode)
    {
        if (nfc_init_done)
        {
            demoDeini(  );
            nfc_init_done=0;
            RefTime = API_KnxTm_GetTimeMs();
        }
    }
    
    
    if(uartdataupdatflag == 1)
    {
        uartdataupdatflag = 0;
        serialProc_Routine(&chargerinputdata);
    }
    
    if(chargerinputdata.ReceivedFlag == 1)
    {
        ChargerDataReceviedProcess(&chargerinputdata.ReceivedMessages[0]);
        
        crcchecksum = calculate_crc(&chargerinputdata.ReceivedMessages[0],6);
        
        sendvalue[0] = crcchecksum & 0xff;
        sendvalue[1] = (crcchecksum >> 8) & 0xff;
        
        USART_SendStringData(&sendvalue[0],2);
        
        chargerinputdata.ReceivedFlag = 0;
    }
    
    // from NFC process
    if (nfc_init_done)
    {
        if ( API_KnxTm_GetDelayMs( TimesMsRef ) >= 200 )
        {
            demoCycle(true);
            nfcTagID_process((KNX_NFCInfo*)&chargerinformation.chargerid, &local_info);
            TimesMsRef = API_KnxTm_GetTimeMs();
        }
        else
        {
            demoCycle(false);
        }
    }
    //    // from NFC process
    //    ChargerStatus_FromRFID_Update(&tag_global);
    
    // from KNX bus process
    ChargerStatus_FromKNXBus_Update();
    
    // to KNX bus process
    ChargerStatus_ToKNXBus_Update();
    
//    // to Charge board process
//    ChargerStatus_ToChargerBoard_Update();
    
    if((API_KnxTm_GetTimeMs() - lastuartsendtime) >= 300)
    {
        ChargerStatus_ToChargerBoard_Update();	
    }
    
    if(((API_KnxTm_GetTimeMs() - lastchecktime) >= 2000)&&((API_KnxTm_GetTimeMs() - lastuartsendtime) >= 300)
       &&(chargerboardupdateflag.chargerstatussetting == 0)&&(chargerboardupdateflag.maximumchargingpower == 0)
           &&(chargerboardupdateflag.maximumchargingtime == 0))
    {
        lastchecktime = API_KnxTm_GetTimeMs();
        ChargerStatus_FromChargerBoard_Update();
    }
}

void ChargerDataReceviedProcess(BYTE *pData)
{
    WORD16 crcchecksum;
    BYTE functioncode;
    BYTE datalength;
    BYTE testdata[2];
    
    functioncode = pData[1];
    switch(functioncode)
    {
    case MB_READINPUTREGISTERS:
        {
            datalength = pData[2];
            crcchecksum = calculate_crc(pData,datalength+3);
            testdata[0] = crcchecksum & 0xff;
            testdata[1] = ((crcchecksum >> 8) & 0xff);
            if((pData[datalength+3] == (crcchecksum & 0xff ))&&(pData[datalength+4] == ((crcchecksum >> 8) & 0xff)))
            {
                chargerinformation.chargerworkingstatus = pData[4];
                chargerinformation.connectionstatus  =    pData[6];
                chargerinformation.energy_totalvalue[0] = pData[7];
                chargerinformation.energy_totalvalue[1] = pData[8];
                chargerinformation.energy_totalvalue[2] = pData[9];
                chargerinformation.energy_totalvalue[3] = pData[10];
                chargerinformation.energy_lastvalue[0]  = pData[11];
                chargerinformation.energy_lastvalue[1]  = pData[12];
                chargerinformation.energy_lastvalue[2]  = pData[13];
                chargerinformation.energy_lastvalue[3]  = pData[14];
                chargerinformation.chargedtime[0]	    = pData[15];
                chargerinformation.chargedtime[1]	    = pData[16];
                chargerinformation.chargingvoltage[0]   = pData[17];
                chargerinformation.chargingvoltage[1]	= pData[18];
                chargerinformation.chargingcurrent[0]	= pData[19];
                chargerinformation.chargingcurrent[1]	= pData[20];
                chargerinformation.chargingpower[0]		= pData[21];
                chargerinformation.chargingpower[1]		= pData[22];
                chargerinformation.faultnumber[0] 	    = pData[23];
                chargerinformation.faultnumber[1] 	    = pData[24];
                
                if(chargerinformation.chargerworkingstatus != chargerinformation.chargerworkingstatus_previous)
                {
                    chargerinformation.chargerworkingstatus_previous = chargerinformation.chargerworkingstatus;
                    chargerupdateflag.chargerworkingstatusupdate = 1;
                    
                }
                if(chargerinformation.connectionstatus != chargerinformation.connectionstatus_previous)
                {
                    chargerinformation.connectionstatus_previous = chargerinformation.connectionstatus;
                    chargerupdateflag.connectionstatusupdate = 1;
                    
                }
                if((chargerinformation.energy_totalvalue[0] != chargerinformation.energy_totalvalue_previous[0])
                   ||(chargerinformation.energy_totalvalue[1] != chargerinformation.energy_totalvalue_previous[1])
                       ||(chargerinformation.energy_totalvalue[2] != chargerinformation.energy_totalvalue_previous[2])
                           ||(chargerinformation.energy_totalvalue[3] != chargerinformation.energy_totalvalue_previous[3]))
                {
                    chargerinformation.energy_totalvalue_previous[0] = chargerinformation.energy_totalvalue[0];					
                    chargerinformation.energy_totalvalue_previous[1] = chargerinformation.energy_totalvalue[1];
                    chargerinformation.energy_totalvalue_previous[2] = chargerinformation.energy_totalvalue[2];
                    chargerinformation.energy_totalvalue_previous[3] = chargerinformation.energy_totalvalue[3];
                    chargerupdateflag.energytotalvalueupdate = 1;
                    
                }
                if((chargerinformation.energy_lastvalue[0] != chargerinformation.energy_lastvalue_previous[0])
                   ||(chargerinformation.energy_lastvalue[1] != chargerinformation.energy_lastvalue_previous[1])
                       ||(chargerinformation.energy_lastvalue[2] != chargerinformation.energy_lastvalue_previous[2])
                           ||(chargerinformation.energy_lastvalue[3] != chargerinformation.energy_lastvalue_previous[3]))
                {
                    chargerinformation.energy_lastvalue_previous[0] = chargerinformation.energy_lastvalue[0];					
                    chargerinformation.energy_lastvalue_previous[1] = chargerinformation.energy_lastvalue[1];
                    chargerinformation.energy_lastvalue_previous[2] = chargerinformation.energy_lastvalue[2];
                    chargerinformation.energy_lastvalue_previous[3] = chargerinformation.energy_lastvalue[3];
                    chargerupdateflag.energy_lastvalueupdate = 1;
                }
                
                if((chargerinformation.chargedtime[0] != chargerinformation.chargedtime_previous[0])
                   ||(chargerinformation.chargedtime[1] != chargerinformation.chargedtime_previous[1]))
                {
                    chargerinformation.chargedtime_previous[0] = chargerinformation.chargedtime[0];					
                    chargerinformation.chargedtime_previous[1] = chargerinformation.chargedtime[1];
                    chargerupdateflag.chargedtimeupdate = 1;
                }
                
                if((chargerinformation.chargingvoltage[0] != chargerinformation.chargingvoltage_previous[0])
                   ||(chargerinformation.chargingvoltage[1] != chargerinformation.chargingvoltage_previous[1]))
                {
                    chargerinformation.chargingvoltage_previous[0] = chargerinformation.chargingvoltage[0];					
                    chargerinformation.chargingvoltage_previous[1] = chargerinformation.chargingvoltage[1];
                    chargerupdateflag.chargingvoltageupdate = 1;
                }
                
                if((chargerinformation.chargingpower[0] != chargerinformation.chargingpower_previous[0])
                   ||(chargerinformation.chargingpower[1] != chargerinformation.chargingpower_previous[1]))
                {
                    chargerinformation.chargingpower_previous[0] = chargerinformation.chargingpower[0];					
                    chargerinformation.chargingpower_previous[1] = chargerinformation.chargingpower[1];
                    chargerupdateflag.chargingpowerupdate = 1;
                }
                
                if((chargerinformation.chargingcurrent[0] != chargerinformation.chargingcurrent_previous[0])
                   ||(chargerinformation.chargingcurrent[1] != chargerinformation.chargingcurrent_previous[1]))
                {
                    chargerinformation.chargingcurrent_previous[0] = chargerinformation.chargingcurrent[0];					
                    chargerinformation.chargingcurrent_previous[1] = chargerinformation.chargingcurrent[1];
                    chargerupdateflag.chargingcurrentupdate = 1;
                }
                
                if((chargerinformation.faultnumber[0] != chargerinformation.faultnumber_previous[0])
                   ||(chargerinformation.faultnumber[1] != chargerinformation.faultnumber_previous[1]))
                {
                    chargerinformation.faultnumber_previous[0] = chargerinformation.faultnumber[0];				 
                    chargerinformation.faultnumber_previous[1] = chargerinformation.faultnumber[1];
                    chargerupdateflag.faultnumberupdate = 0;
                }
                
#ifdef DEBUG_TEST
                chargerupdateflag.chargerworkingstatusupdate = 1;
                chargerupdateflag.connectionstatusupdate = 1;
                chargerupdateflag.energytotalvalueupdate = 1;
                chargerupdateflag.energy_lastvalueupdate = 1;
                chargerupdateflag.chargedtimeupdate = 1;
                chargerupdateflag.chargingvoltageupdate = 1;
                chargerupdateflag.chargingpowerupdate = 1;
                chargerupdateflag.chargingcurrentupdate = 1;			
                chargerupdateflag.maximumchargingpower = 1;
                chargerupdateflag.maximumchargingtime = 1;
                chargerupdateflag.faultnumberupdate = 1;
                chargerupdateflag.temperaturevalueupdate = 1;	
                
#endif			  
                
            }		   
        }
        break;
        
        
    case MB_READHOLDINGREGISTERS:
        
        break;
        
        
    default:
        break;
        
    }
    
}


void ChargerStatus_ToKNXBus_Update(void)
{
    BYTE sendvalue[16],ucData;
    WORD16 tempvalue;
    BYTE tempconvertdata[4];
    
    
    if(chargerupdateflag.chargerworkingstatusupdate == 1)
    {
        ucData = chargerinformation.chargerworkingstatus;			 
        API_KnxAl_SetCoValue(CHARGER_WORKING_STATUS_CO,&ucData);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGER_WORKING_STATUS_CO);	  
        chargerupdateflag.chargerworkingstatusupdate = 0;
    }
    else if(chargerupdateflag.connectionstatusupdate == 1)
    {
        ucData = chargerinformation.connectionstatus;			 
        API_KnxAl_SetCoValue(CHARGER_CONNECT_STATUS_CO,&ucData);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGER_CONNECT_STATUS_CO);	  
        chargerupdateflag.connectionstatusupdate = 0;
    }
    else if(chargerupdateflag.energytotalvalueupdate == 1)
    {
        sendvalue[0] = chargerinformation.energy_totalvalue[0];		
        sendvalue[1] = chargerinformation.energy_totalvalue[1];
        sendvalue[2] = chargerinformation.energy_totalvalue[2];
        sendvalue[3] = chargerinformation.energy_totalvalue[3];
        
        
        API_KnxAl_SetCoValue(CHARGING_ENERGY_TOTAL_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_ENERGY_TOTAL_CO);   
        chargerupdateflag.energytotalvalueupdate = 0;
    }
    else if(chargerupdateflag.energy_lastvalueupdate == 1)
    {
        sendvalue[0] = chargerinformation.energy_lastvalue[0];		
        sendvalue[1] = chargerinformation.energy_lastvalue[1];
        sendvalue[2] = chargerinformation.energy_lastvalue[2];
        sendvalue[3] = chargerinformation.energy_lastvalue[3];	
        
        
        API_KnxAl_SetCoValue(CHARGING_ENERGY_LAST_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_ENERGY_LAST_CO);	  
        chargerupdateflag.energy_lastvalueupdate = 0;
    }
    else if(chargerupdateflag.chargedtimeupdate == 1)
    {
        sendvalue[0] = chargerinformation.chargedtime[0];		
        sendvalue[1] = chargerinformation.chargedtime[1];		 	
        
        API_KnxAl_SetCoValue(CHARGED_TIME_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGED_TIME_CO);	  
        chargerupdateflag.chargedtimeupdate = 0;
    }
    else if(chargerupdateflag.chargingvoltageupdate == 1)
    {
        tempvalue = chargerinformation.chargingvoltage[0];
        tempvalue = ((tempvalue << 8) + chargerinformation.chargingvoltage[1]);
        tempvalue = tempvalue /10;
        
        tempconvertdata[0] = tempvalue & 0x0ff;	
        tempconvertdata[1] = (tempvalue >> 8) & 0xff;
        tempconvertdata[2] = 0;
        tempconvertdata[3] = 0;
        
        //   chargerinformation.chargingvoltage[3] = 0;
        //	 chargerinformation.chargingvoltage[2] = 0;
        //     chargerinformation.chargingvoltage[1] = (tempvalue >> 8) & 0xff;
        //	 chargerinformation.chargingvoltage[0] = tempvalue & 0x0ff;		 
        
        Int_to_float32(&tempconvertdata[0],&sendvalue[0]);
        
        ucData = sendvalue[0];
        sendvalue[0] = sendvalue[3];
        sendvalue[3] = ucData;
        ucData = sendvalue[1];
        sendvalue[1] = sendvalue[2];
        sendvalue[2] = ucData;
        
        API_KnxAl_SetCoValue(CHARGING_VOLTAGE_VALUE_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_VOLTAGE_VALUE_CO);	  
        chargerupdateflag.chargingvoltageupdate = 0;
    }
    else if(chargerupdateflag.chargingpowerupdate == 1)
    {
        tempvalue = chargerinformation.chargingpower[0];
        tempvalue = ((tempvalue << 8) + chargerinformation.chargingpower[1]);
        tempvalue = tempvalue *100;
        
        tempconvertdata[0] = tempvalue & 0x0ff;	
        tempconvertdata[1] = (tempvalue >> 8) & 0xff;
        tempconvertdata[2] = 0;
        tempconvertdata[3] = 0;
        
        Int_to_float32(&tempconvertdata[0],&sendvalue[0]);
        
        ucData = sendvalue[0];
        sendvalue[0] = sendvalue[3];
        sendvalue[3] = ucData;
        ucData = sendvalue[1];
        sendvalue[1] = sendvalue[2];
        sendvalue[2] = ucData;
        
        API_KnxAl_SetCoValue(CHARGING_POWER_VALUE_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_POWER_VALUE_CO);	  
        chargerupdateflag.chargingpowerupdate = 0;
    }
    else if(chargerupdateflag.chargingcurrentupdate == 1)
    {
        tempvalue = chargerinformation.chargingcurrent[0];
        tempvalue = ((tempvalue << 8) + chargerinformation.chargingcurrent[1]);
        tempvalue = tempvalue *100;
        
        sendvalue[1] = tempvalue & 0x0ff;	
        sendvalue[0] = (tempvalue >> 8) & 0xff;
        
        API_KnxAl_SetCoValue(CHARGING_CURRENT_VALUE_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_CURRENT_VALUE_CO);	  
        chargerupdateflag.chargingcurrentupdate = 0;
    }
    else if(chargerupdateflag.maximumchargingpower == 1)
    {
        tempvalue = chargerinformation.maximumchargingpower[0];
        tempvalue = ((tempvalue << 8) + chargerinformation.maximumchargingpower[1]);
        tempvalue = tempvalue *100;
        
        tempconvertdata[0] = tempvalue & 0x0ff;	
        tempconvertdata[1] = (tempvalue >> 8) & 0xff;
        tempconvertdata[2] = 0;
        tempconvertdata[3] = 0;
        
        Int_to_float32(&tempconvertdata[0],&sendvalue[0]);
        
        ucData = sendvalue[0];
        sendvalue[0] = sendvalue[3];
        sendvalue[3] = ucData;
        ucData = sendvalue[1];
        sendvalue[1] = sendvalue[2];
        sendvalue[2] = ucData;
        
        API_KnxAl_SetCoValue(CHARGING_POWER_MAXIMUM_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_POWER_MAXIMUM_CO);	  
        chargerupdateflag.maximumchargingpower = 0;
    }
    else if(chargerupdateflag.maximumchargingtime == 1)
    {
        sendvalue[0] = chargerinformation.maximumchargingtime[0];		
        sendvalue[1] = chargerinformation.maximumchargingtime[1];
        API_KnxAl_SetCoValue(CHARGING_TIME_MAXIMUM_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_TIME_MAXIMUM_CO);   
        chargerupdateflag.maximumchargingtime = 0;
    }
    else if(chargerupdateflag.faultnumberupdate == 1)
    {
        ucData = chargerinformation.faultnumber[0];			 
        API_KnxAl_SetCoValue(CHARGING_FAULT_ID_CO,&ucData);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGING_FAULT_ID_CO);   
        chargerupdateflag.faultnumberupdate = 0;
    }
    else if(chargerupdateflag.temperaturevalueupdate == 1)
    {
        sendvalue[0] = chargerinformation.temperaturevalue[0];	// high part
        sendvalue[1] = chargerinformation.temperaturevalue[1];	// low part 
        
        DataConvert_IntToFloat(&sendvalue[0]);
        API_KnxAl_SetCoValue(CHARGER_TEMPERATURE_OBJ_CO,&sendvalue[0]);
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGER_TEMPERATURE_OBJ_CO); 
        chargerupdateflag.temperaturevalueupdate = 0;
    }	
    else if(chargerupdateflag.chargerdatetime == 1)
    {
        sendvalue[0] = chargerinformation.chargedtime[0];		
        sendvalue[1] = chargerinformation.chargedtime[1];
        API_KnxAl_SetCoValue(CHARGE_DATE_TIME_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGE_DATE_TIME_CO);	  
        chargerupdateflag.chargerdatetime = 0;
    }
    else if(chargerupdateflag.chargeridupdate == 1)
    {
        memcpy(sendvalue, (BYTE*)&chargerinformation.chargerid, sizeof(KNX_NFCInfo));
        
        API_KnxAl_SetCoValue(CHARGE_ID_CO,&sendvalue[0]);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGE_ID_CO);   
        chargerupdateflag.chargeridupdate = 0;
    }
    else if(chargerupdateflag.chargercontrolupdate == 1)
    {
        ucData = chargerinformation.chargersetting;			 
        API_KnxAl_SetCoValue(CHARGER_STATUS_SETTING_CO,&ucData);
        /* send the CURTAIN_CLOSE co-obj's data. */
        API_KnxAl_RequestValueWrite(CHARGER_STATUS_SETTING_CO);	  
        chargerupdateflag.chargercontrolupdate = 0;
    }
}

void ChargerStatus_FromKNXBus_Update(void)
{
    BYTE ucData;
    
    /* get charger setting update flag. */
    ucData = API_KnxAl_GetRamFlags(CHARGER_STATUS_SETTING_CO);
    /* check whether this co-obj's data was renewed. */
    if(ucData & CO_EXTERNAL_UPDATE)
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        API_KnxAl_GetCoValue(CHARGER_STATUS_SETTING_CO,&chargerinformation.chargersetting);	
        chargerboardupdateflag.chargerstatussetting = 1;
    }
    
    /* get charger MAXIMUM charging power update flag. */
    ucData = API_KnxAl_GetRamFlags(CHARGING_POWER_MAXIMUM_CO);
    /* check whether this co-obj's data was renewed. */
    if(ucData & CO_EXTERNAL_UPDATE)
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        API_KnxAl_GetCoValue(CHARGING_POWER_MAXIMUM_CO,&chargerinformation.maximumchargingpower[0]);
        chargerboardupdateflag.maximumchargingpower = 1;
    }
    
    /* get charger MAXIMUM charging time update flag. */
    ucData = API_KnxAl_GetRamFlags(CHARGING_TIME_MAXIMUM_CO);
    /* check whether this co-obj's data was renewed. */
    if(ucData & CO_EXTERNAL_UPDATE)
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        API_KnxAl_GetCoValue(CHARGING_TIME_MAXIMUM_CO,&chargerinformation.maximumchargingtime[0]);	
        
        chargerboardupdateflag.maximumchargingtime = 1;
    }
    
    /* get charger MAXIMUM date time update flag. */
    ucData = API_KnxAl_GetRamFlags(CHARGE_DATE_TIME_CO);
    /* check whether this co-obj's data was renewed. */
    if(ucData & CO_EXTERNAL_UPDATE)
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        API_KnxAl_GetCoValue(CHARGE_DATE_TIME_CO,&chargerinformation.datatime[0]);		
        
        chargerboardupdateflag.chargerdatetime = 1;
    }
    
    /* get charger ID update flag. */
    ucData = API_KnxAl_GetRamFlags(CHARGE_ID_CO);
    /* check whether this co-obj's data was renewed. */
    if(ucData & CO_EXTERNAL_UPDATE)
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        API_KnxAl_GetCoValue(CHARGE_ID_CO,&chargerinformation.chargerid[0]);
        
        chargerboardupdateflag.chargeridupdate = 1;
    }
    
}


void ChargerStatus_ToChargerBoard_Update(void)
{
    BYTE sendvalue[20];
    WORD16 crcchecksum;
    BYTE convertdata[4];
    
    if(chargerboardupdateflag.chargerstatussetting == 1)
    {
        chargerboardupdateflag.chargerstatussetting = 0;
        
        //      ucData =  chargerinformation.chargersetting;
        
        sendvalue[0] = 0x01;  //address
        sendvalue[1] = 0x06; // function code
        sendvalue[2] = 0x60; // high byte of register		
        sendvalue[3] = 0x01; // high byte of register
        sendvalue[4] = 0x00; // high byte of data
        if(chargerinformation.chargersetting == 1)
        {
            sendvalue[5] = 0x55; // start charging
        }
        else
        {
            sendvalue[5] = 0xAA; // stop charging
        }
        crcchecksum = calculate_crc(&sendvalue[0],6);
        sendvalue[6] = crcchecksum & 0xff;
        sendvalue[7] = (crcchecksum >> 8) & 0xff;
        
        USART_SendStringData(&sendvalue[0],8);
        
    }
    else if((chargerboardupdateflag.maximumchargingpower == 1)||(chargerboardupdateflag.maximumchargingtime == 1))
    {
        chargerboardupdateflag.maximumchargingpower = 0;
        chargerboardupdateflag.maximumchargingtime = 0;
        
        //ucData =  chargerinformation.chargersetting;
        
        sendvalue[0] = 0x01;  //address
        sendvalue[1] = 0x10; // function code
        sendvalue[2] = 0x10; // high byte of register		
        sendvalue[3] = 0x01; // low byte of register
        sendvalue[4] = 0x00; // high byte of quantity register		
        sendvalue[5] = 0x03; // low byte of quantity register	
        sendvalue[6] = 0x06; // byte count
        sendvalue[7] = 0x00; //  register1 value of Hi	
        sendvalue[8] = 0x01; // register1 value of Lo	
        
        float_to_int_bytes(chargerinformation.maximumchargingpower, convertdata);
        
        sendvalue[9] = convertdata[1]; //  register2 value of Hi	
        sendvalue[10] = convertdata[0]; // register2 value of Lo	
        
        sendvalue[11] = chargerinformation.maximumchargingtime[0]; //  register3 value of Hi	
        sendvalue[12] = chargerinformation.maximumchargingtime[1]; // register3 value of Lo	
        
        crcchecksum = calculate_crc(&sendvalue[0],13);
        sendvalue[13] = crcchecksum & 0xff;
        sendvalue[14] = (crcchecksum >> 8) & 0xff;
        
        USART_SendStringData(&sendvalue[0],15);
        
    }
    else if(chargerboardupdateflag.chargerdatetime == 1)
    {
        ;
    }
}


/******************************************************************/
// the following function was used to read data from ev charger control board

/******************************************************************/

void ChargerStatus_FromChargerBoard_Update(void)
{
    WORD16 crcchecksum;
    BYTE sendvalue[8];
    
    sendvalue[0] = 0x01;  //address
    sendvalue[1] = 0x04; // function code read input register
    sendvalue[2] = 0x40; // high byte of register address		
    sendvalue[3] = 0x01; // low byte of register address
    sendvalue[4] = 0x00; // high byte of quantity register		
    sendvalue[5] = 0x0b; // low byte of quantity register		
    
    crcchecksum = calculate_crc(&sendvalue[0],6);
    sendvalue[6] = crcchecksum & 0xff;
    sendvalue[7] = (crcchecksum >> 8) & 0xff;
    
    USART_SendStringData(&sendvalue[0],8);
    
    
}

void ChargerStatus_FromRFID_Update( SCAN_NFCInfo *tag_global)
{
//    if (tag_global->id_index != -1)
//    {
//        chargerboardupdateflag.chargerstatussetting = 1;
//        if (chargerinformation.chargersetting == 1)
//        {
//            chargerinformation.chargersetting = 0;
//        }
//        else
//        {
//            chargerinformation.chargersetting = 1;
//        }
//        tag_global->id_index = -1;
//    }
}

/******************************************************************
The following function was used to convert 2 bytes float data to short
currently only processed postive date

*******************************************************************/
void DataConvert_FloatToInt(BYTE *pData)
{
    WORD16 converrvalue;
    BYTE indexnumer;
    
    indexnumer = ((pData[0] & 0x78)>>3);
    converrvalue = ((pData[0] & 0x07)<<8) + pData[1] ;
    
    for(;indexnumer>=1;indexnumer--)
    {
        converrvalue = converrvalue * 2;
    }
    pData[1] = (BYTE)(converrvalue & 0xff);
    pData[0] = (BYTE)((converrvalue >>8) & 0xff);
}


/******************************************************************
The following function was used to convert short to 2 bytes float data 
currently only processed postive date

*******************************************************************/
void DataConvert_IntToFloat(BYTE *pData)
{
    WORD16 converrvalue;
    BYTE indexnumer;
    
    converrvalue = (pData[0] <<8) + pData[1] ;
    indexnumer = 0;
    
    
    for(;converrvalue> 0x7ff;)
    {
        converrvalue = converrvalue /2;
        indexnumer++;
    }
    pData[1] = (BYTE)(converrvalue & 0xff);
    pData[0] = (BYTE)(((converrvalue >>8) & 0xff)|(indexnumer << 3));
}

void DataConvert_Int32ToFloat( BYTE *pData )
{
    WORD32 converrvalue;
    BYTE indexnumer;
    
    converrvalue = ( pData[3] << 24 ) + ( pData[2] << 16 ) + ( pData[1] << 8 ) + pData[0];
    indexnumer = 0;
    
    
    for( ; converrvalue > 0x7ff; )
    {
        converrvalue = converrvalue / 2;
        indexnumer++;
    }
    pData[1] = ( BYTE )( converrvalue & 0xff );
    pData[0] = ( BYTE )( ( ( converrvalue >> 8 ) & 0xff ) | ( indexnumer << 3 ) );
}

/**
* @description: swap big-endian or little-endian to another type
* @param {none} 
* @return: none
* @date 2023/9/2
* example: swapEndian(&value16, sizeof(value16));
*/
void swapEndian(void* data, size_t size)
{
    uint8_t* byteData = (uint8_t*)data;
    uint8_t temp;
    
    for (size_t i = 0; i < size / 2; ++i)
    {
        temp = byteData[i];
        byteData[i] = byteData[size - 1 - i];
        byteData[size - 1 - i] = temp;
    }
}

/******************************************************************
The following function was used to convert 4 bytes int data to float32 

*******************************************************************/
void Int_to_float32(BYTE *intBytes, BYTE *floatBytes)
{
    WORD32 inValue;
    float floatValue;

    memcpy(&inValue,intBytes,4);
  
    floatValue = (float)inValue;
	
 //   floatValue = *((float *)&inValue);

	memcpy(floatBytes,&floatValue,4);
}
uint16_t int32_to_custom_float16(int32_t int32) {
    uint16_t f16 = 0;
    uint32_t absVal, tempVal;
    int32_t exp = 0;
    uint32_t sign = 0;
    
    // ������λ����ȡ����ֵ
    if (int32 < 0) {
        sign = 1;
        absVal = -int32; // ����Ǹ�����ȡ����1�õ�����ֵ
    } else {
        absVal = int32;
    }
    
    // ������������������0��ֱ�ӷ���0
    if (absVal == 0) return 0;
    
    // ����ָ����β��
    tempVal = absVal;
    while (tempVal > 0) {
        tempVal >>= 1;
        exp++;
    }
    
    // ����β������Ӧ11λ�ռ�
    // exp-1��Ϊָ���Ǵ����λ1��ʼ����ģ��������absVal��1����2^0����expӦ����0
    int shiftAmount = exp - 12;
    uint32_t mantissa = (shiftAmount > 0) ? (absVal >> shiftAmount) : (absVal << -shiftAmount);
    
    // ��ϳ�16λ������
    // ����ָ����Χ������Ӧ4λָ��λ
    if (exp > 15) {
        exp = 15;
    } else if (exp < 1) {
        exp = 1; // ����ֵ����Сָ��
    }
    
    f16 = (sign << 15) | ((exp & 0xF) << 11) | (mantissa & 0x7FF);
    
    return f16;
}

/******************************************************************
The following function was used to convert 4 bytes float data to short
 currently only processed postive date

*******************************************************************/

void float_to_int_bytes(BYTE float_bytes[4],BYTE int_bytes[4])
{
    float value;
	BYTE testdata[4];

    testdata[0] = float_bytes[3];
	testdata[1] = float_bytes[2];	 
	testdata[2] = float_bytes[1];
	testdata[3] = float_bytes[0];
	
	memcpy(&value,&testdata[0],4);

	WORD32 int_value = (WORD32)value;
	
	memcpy(int_bytes,&int_value,4);

}

u32_t GetSystemTime_ms(void)
{
    
    return(API_KnxTm_GetTimeMs());
}

void SystemDelay_ms(u32_t ms)
{
    u32_t start = API_KnxTm_GetTimeMs();
    while(API_KnxTm_GetTimeMs() - start < ms);
}

/* end of file. */

