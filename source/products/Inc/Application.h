/******************************************************************************
* ��Ȩ���� (C)2013��Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Application.h
* �ļ���ʶ����
* ����ժҪ��KNXӦ��ͷ�ļ���
* ����˵����KNXӦ�ù�����ص�ͷ�ļ���
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

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------Define for application------------------------------*/



/* communication object No. define. */

/* input channel Co. define. */
#define CHARGER_WORKING_STATUS_CO               0   /* charge point running status 1byte */
#define CHARGER_CONNECT_STATUS_CO               1   /* charge point connection status 1bit  */
#define CHARGING_ENERGY_TOTAL_CO                2   /* charge energy for all */
#define CHARGING_ENERGY_LAST_CO                 3   /* charging energy for last time */
#define CHARGED_TIME_CO                         4   /* charged time */
#define CHARGING_VOLTAGE_VALUE_CO               5   /* charging voltage */
#define CHARGING_POWER_VALUE_CO                 6   /* charging power */
#define CHARGING_CURRENT_VALUE_CO               7   /* charging current */
#define CHARGING_POWER_MAXIMUM_CO               8   /* MAXIMUM CHARING POWER**/
#define CHARGING_TIME_MAXIMUM_CO                9   /* MAXIMUM CHARGING time*/
#define CHARGING_FAULT_ID_CO                    10   /* FAULT ID*/
#define CHARGER_TEMPERATURE_OBJ_CO              11  /*Temperature Co No*//* 2bytes */
#define CHARGE_DATE_TIME_CO                     12  /* charging point DATE TIME */
#define CHARGE_ID_CO                            13  /* charging point ID */
#define CHARGER_STATUS_SETTING_CO               14   /* SETTING CHARGER WORKING STATUS IDEL&CHARGING */




/*-------------------------Declaration of functions---------------------------*/
/**************************************************************************
* �������ƣ� BOOL Application_Init(void)
* ���������� Ӧ�ó�ʼ������ڡ�
* ��������� ��
* ��������� ��
* �� �� ֵ�� ��
* ����˵���� 
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
BOOL Application_Init(void);

/**************************************************************************
* �������ƣ� BOOL Application_Process(void)
* ���������� Ӧ������ڡ�
* ��������� ��
* ��������� ��
* �� �� ֵ�� ��
* ����˵���� 
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
BOOL Application_Process(void);

/**************************************************************************
* �������ƣ� App_Data_Init(void)
* ���������� ��ȡ����������ܣ��������ݽṹ��ַ����ȡETS������ͨѶ������
             ��IO��ȡ/�������������
* ��������� ��
* ��������� ��      
* �� �� ֵ�� ��
* ����˵���� ��
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
void App_Data_Init(void);

/**************************************************************************
* �������ƣ�BOOL Application_Save(VOID)
* ����������application save entry used for saving user data in running halt.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
BOOL Application_Save(VOID);

/**************************************************************************
* �������ƣ�BOOL Application_BusSave(VOID)
* ����������application save entry used for saving user data when bus voltage
            is abnormal.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
BOOL Application_BusSave(VOID);

/**************************************************************************
* �������ƣ�BOOL Application_PowerSave(VOID)
* ����������application save entry used for saving user data in power down.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����no.
* �޸�����     �汾��     �޸���      �޸�����
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   ����
**************************************************************************/
BOOL Application_PowerSave(VOID);






#ifdef __cplusplus
}
#endif

#endif /* _APPLICATION_H_ */
