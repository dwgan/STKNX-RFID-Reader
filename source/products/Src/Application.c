/******************************************************************************
* 版权所有 (C)2013，Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Application.c
* 文件标识：无
* 内容摘要：KNX应用源文件。
* 其他说明：KNX具体应用相关的功能在此实现。在下面各个函数中增加相关功能。
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

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Hardware.h"
#include "Knx_Prop.h"
#include "boardctrl.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "App_Common.h"
#include "Application.h"
#include "Application_Data.h"
#include "Knx_AlApp.h"
#include "demo_app.h"



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
#pragma location = "APP_INTERNAL_SEG"
void App_Data_Init(void)
{
    return;
}


/**************************************************************************
* 函数名称： BOOL Application_Init(void)
* 功能描述： 应用初始化总入口。
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Application_Init(void)
{
    /* add application initicalize data here. */
    App_Data_Init();
    Demo_App_Init();
    
    return TRUE;
}


/**************************************************************************
* 函数名称： BOOL Application_Process(void)
* 功能描述： 应用总入口。
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Application_Process(void)
{
    /* application handler entrance. */
    Demo_App_Run();

    return TRUE;
}

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
#pragma location = "APP_INTERNAL_SEG"
BOOL Application_Save(VOID)
{
    return TRUE;
}

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
#pragma location = "APP_INTERNAL_SEG"
BOOL Application_BusSave(VOID)
{
    /* close all interrupt. */
    asm("CPSID i");
    API_KnxMem_WriteFinished();
    
    return TRUE;
}

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
#pragma location = "APP_INTERNAL_SEG"
BOOL Application_PowerSave(VOID)
{
    return TRUE;
}




/* End of file */

