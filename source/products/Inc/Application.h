/******************************************************************************
* 版权所有 (C)2013，Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Application.h
* 文件标识：无
* 内容摘要：KNX应用头文件。
* 其他说明：KNX应用功能相关的头文件。
* 当前版本：V1.00
* 作    者：    
* 完成日期：2014年7月8日
*    
* 修改记录1：
*        修改日期：2014年7月8日
*        版 本 号：V1.00
*        修 改 人：    
*        修改内容：新增公共定义.
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
* 函数名称： BOOL Application_Init(void)
* 功能描述： 应用初始化总入口。
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
BOOL Application_Init(void);

/**************************************************************************
* 函数名称： BOOL Application_Process(void)
* 功能描述： 应用总入口。
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
BOOL Application_Process(void);

/**************************************************************************
* 函数名称： App_Data_Init(void)
* 功能描述： 读取输入参数功能，分配数据结构地址并读取ETS参数，通讯对象编号
             和IO读取/输出操作函数。
* 输入参数： 无
* 输出参数： 无      
* 返 回 值： 无
* 其它说明： 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
void App_Data_Init(void);

/**************************************************************************
* 函数名称：BOOL Application_Save(VOID)
* 功能描述：application save entry used for saving user data in running halt.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
BOOL Application_Save(VOID);

/**************************************************************************
* 函数名称：BOOL Application_BusSave(VOID)
* 功能描述：application save entry used for saving user data when bus voltage
            is abnormal.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
BOOL Application_BusSave(VOID);

/**************************************************************************
* 函数名称：BOOL Application_PowerSave(VOID)
* 功能描述：application save entry used for saving user data in power down.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
BOOL Application_PowerSave(VOID);






#ifdef __cplusplus
}
#endif

#endif /* _APPLICATION_H_ */
