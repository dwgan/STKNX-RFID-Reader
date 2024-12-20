/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：App_Api.c
* 文件标识：无
* 内容摘要：Knx application API file.
* 其他说明：
* 当前版本：V1.00
* 作    者：      
* 完成日期：2013年7月24日
*    
* 修改记录1：
*        修改日期：2013年7月24日
*        版 本 号：V1.00
*        修 改 人：      
*        修改内容：新增公共定义.
******************************************************************************/


#include "type_def.h"
#include "pub.h"
#include "Sw_common.h"
#include "Buffer.h"
#include "Hardware.h"
#include "Knx_Mem.h"
#include "Knx_Prop.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "mem_malloc.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "Knx_InternalData.h"
#include "Knx_InternalApp.h"
#include "Knx_Timer.h"
#include "Knx_AlApp.h"
#include "Knx_AlMgm.h"
#include "Knx_Program.h"
#include "knx_chip.h"
#include "Knx_M0705_Ll.h"
#include "Knx_Auth.h"
#include "Knx_LoadCtrl.h"
#include "Knx_Run.h"
#include "Knx_Msg.h"
#include "Mem_malloc.h"


/* we should allocate an 512 bytes ROM area for below API. */

/*****************************************************************************************************************
* 函数名称：VOID API_Knx_UserAppHandler_Set(VOID *pfHandler,BYTE ucHandlerType)
* 功能描述：application set handler relate to the device design.
* 输入参数：APP_HANDLER pfHandler:application handler.
            BYTE ucHandlerType   :handler type.
                 APP_HANDLER_MAIN            0x01           application entry
                 APP_HANDLER_INIT            0x02           application initialize entry.
                 APP_HANDLER_SAVE            0x03           application save handling entry.
                 APP_HANDLER_BUS_SAVE        0x04           application save handling when bus voltage down.
                 APP_HANDLER_POWER_SAVE      0x05           application save handling when power supply down.
                 APP_HANDLER_WDG_RESET       0x06           application reset watchdog entry.
                 APP_HANDLER_RESET_CPU       0x07           CPU reset entry.
                 APP_HANDLER_PRGM_LED_OFF    0x08           OFF program LED entry.
                 APP_HANDLER_PRGM_LED_ON     0x09           light program LED entry.
                 APP_HANDLER_PRGM_KEY        0x0a           program key check entry.
                 APP_HANDLER_BUS_POWER_CHECK 0x0b           bus power check entry.
                 APP_HANDLER_ADC_OP          0x0c           adc operation entry. 
* 输出参数：no.
* 返 回 值：no.
* 其它说明：application realize the design in self source files.these handler will be used by KNX protocol
            stack internally.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                  创建
********************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 0*MCU_SIZE)
__root VOID (*const API_Knx_UserAppHandler_Set)(VOID *pfHandler,BYTE ucHandlerType) = Knx_UserAppHandler_Set;

/****************************************/
/**************** Knx time op. ************/
/****************************************/

/**************************************************************************
* 函数名称：VOID API_KnxTm_TimerInit(BYTE ucDevNo)
* 功能描述：KNX定时器初始化接口，定时器1ms。
* 输入参数：BYTE ucDevNo:device logical number.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：通过api提供给外部使用。定时器驱动通过注册方式注册到KNX定时器处理
            进行工作。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      创建 
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 1*MCU_SIZE)
__root VOID (*const API_KnxTm_TimerInit)(BYTE ucDevNo) = KnxTm_TimerInit;

/**************************************************************************
* 函数名称：WORD32 API_KnxTm_GetTimeMs(VOID)
* 功能描述：获取当前计时毫秒数。
* 输入参数： 无。
* 输出参数： 无。
* 返 回 值： 当前毫秒数：0-0xFFFFFFFF。
* 其它说明： 无
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      创建 
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 2*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetTimeMs)(VOID) = KnxTm_GetTimeMs;

/**************************************************************************
* 函数名称：WORD32 API_KnxTm_GetDelayMs(WORD32 dwOldTime)
* 功能描述：获取给定时间跟当前时间的时差（毫秒）。
* 输入参数： WORD16 wOldTime：给定老时间。
* 输出参数： 无。
* 返 回 值： 时差，毫秒：0-0xFFFF。
* 其它说明： 无
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    创建 
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 3*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetDelayMs)(WORD32 dwOldTime) = KnxTm_GetDelayMs;

/**************************************************************************
* 函数名称：VOID API_KnxTm_UpdateCycle(VOID)
* 功能描述： 更新周期时间和计数。
* 输入参数： 无。
* 输出参数： 无。
* 返 回 值： 无。
* 其它说明： 无。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 4*MCU_SIZE)
__root VOID (*const API_KnxTm_UpdateCycle)(VOID) = KnxTm_UpdateCycle;

/**************************************************************************
* 函数名称：WORD16 API_KnxTm_GetCycleTimeMs(VOID)
* 功能描述： 获取循环周期时间（毫秒）。
* 输入参数： 无。
* 输出参数： 无。
* 返 回 值： 时间值（毫秒，0~0xFFFF）
* 其它说明： 需要在循环中调用KnxTm_UpdateCycle函数更新时间。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 5*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetCycleTimeMs)(VOID) = KnxTm_GetCycleTimeMs;

/**************************************************************************
* 函数名称：WORD32 API_KnxTm_GetCycleCount(VOID)
* 功能描述： 获取循环周期次数。
* 输入参数： 无。
* 输出参数： 无。
* 返 回 值： 循环次数（0~0xFFFFFFFF）
* 其它说明： 需要在循环中调用KnxTm_UpdateCycle函数更新计数。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 6*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetCycleCount)(VOID) = KnxTm_GetCycleCount;


/****************************************/
/**************** Knx co. op. ************/
/****************************************/

/**************************************************************************************************************
* 函数名称：BYTE API_KnxAl_GetCoBufferLength(BYTE ucCoNo)
* 功能描述：This function retrieves the buffer length used by the given communication object.
* 输入参数：BYTE ucCoNo :communication object No.
* 输出参数：no.
* 返 回 值：buffer length.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 7*MCU_SIZE)
__root BYTE (*const API_KnxAl_GetCoBufLength)(BYTE ucCoNo) = KnxAl_GetCoBufferLength;

/**************************************************************************************************************
* 函数名称：BOOL API_KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* 功能描述：This function is used by application to retrieve the value of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :data buffer pointer.
* 输出参数：BYTE *pucBuffer :communication object data.
* 返 回 值：TRUE / FALSE.
* 其它说明：This function will be a API function used by the application.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 8*MCU_SIZE)
__root BOOL (*const API_KnxAl_GetCoValue)(BYTE ucCoNo,BYTE *pucBuffer) = KnxAl_GetCoValue;

/**************************************************************************************************************
* 函数名称：BOOL API_KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* 功能描述：This function is used by application to set the value of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :data buffer pointer.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：(1)This function will be a API function used by the application.
            (2)To initiate a transmission of the new value KnxAl_RequestValueWrite(para) has to be called in addition.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 9*MCU_SIZE)
__root BOOL (*const API_KnxAl_SetCoValue)(BYTE ucCoNo,BYTE *pucBuffer) = KnxAl_SetCoValue;

/**************************************************************************************************************
* 函数名称：BOOL API_KnxAl_GetUpdatedCo(BYTE *pucCoNo)
* 功能描述：This function is used by the application to retrieve the number of the next communication object
            updated by external event.
* 输入参数：BYTE *pucCoNo:Co.objet No pointer.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 10*MCU_SIZE)
__root BOOL (*const API_KnxAl_GetUpdatedCo)(BYTE *pucCoNo) = KnxAl_GetUpdatedCo;

/**************************************************************************************************************
* 函数名称：BYTE API_KnxAl_GetRamFlags(BYTE ucCoNo)
* 功能描述：This function is used by application to retrieve the status of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
* 输出参数：no.
* 返 回 值：BYTE : the status of the communication object.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 11*MCU_SIZE)
__root BYTE (*const API_KnxAl_GetRamFlags)(BYTE ucCoNo) = KnxAl_GetRamFlags;

/**************************************************************************************************************
* 函数名称：BOOL API_KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags)
* 功能描述：This function is used by application to set the status of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 12*MCU_SIZE)
__root BOOL (*const API_KnxAl_SetRamFlags)(BYTE ucCoNo, BYTE ucFlags) = KnxAl_SetRamFlags;

/**************************************************************************************************************
* 函数名称：BOOL API_KnxAl_RequestValueWrite(BYTE ucCoNo)
* 功能描述：This function initiates a value write request on the given communication object.
* 输入参数：BYTE ucCoNo:Co.objet No.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：The system will transmitts the current value of the given communication object.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 13*MCU_SIZE)
__root BOOL (*const API_KnxAl_RequestValueWrite)(BYTE ucCoNo) = KnxAl_RequestValueWrite;

/**************************************************************************************************************
* 函数名称：BOOL API_KnxAl_RequestValueRead(BYTE ucCoNo)
* 功能描述：This function initiates a value read request on the given communication object.
* 输入参数：BYTE ucCoNo:Co.objet No.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：Attention: The response by remote device can only be received if the "Update on response" flag is set
            for this communication object.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 14*MCU_SIZE)
__root BOOL (*const API_KnxAl_RequestValueRead)(BYTE ucCoNo) = KnxAl_RequestValueRead;

/**************************************************************************************************************
* 函数名称：VOID Knx_AlMgmInit(VOID)
* 功能描述：KNX application layer management initialize。
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 15*MCU_SIZE)
__root VOID (*const API_Knx_AlMgmInit)(VOID) = Knx_AlMgmInit;

/****************************************/
/*********** Knx memory data op. **********/
/****************************************/

/**************************************************************************************************************
* 函数名称：VOID KnxMem_Init(VOID)
* 功能描述：This function does the initialisation of the internal variables.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 16*MCU_SIZE)
__root VOID (*const API_KnxMem_Init)(VOID) = KnxMem_Init;

/**************************************************************************
* 函数名称：BYTE API_KnxMem_GetByte(WORDPTR dwAddr)
* 功能描述：get a byte data from the given virtual address.
* 输入参数：WORDPTR dwAddr:source address.
* 输出参数：no.
* 返 回 值：memory data.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 17*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetByte)(WORDPTR dwAddr) = KnxMem_GetByte;

/**************************************************************************
* 函数名称：WORD16 API_KnxMem_GetWord(WORDPTR dwAddrHi)
* 功能描述：This function reads one word from virtual memory area.
* 输入参数：WORDPTR dwAddr:source address.
* 输出参数：no.
* 返 回 值：memory data.
* 其它说明：The requested word in virtual memory is assumed to have the 
            hibyte at address dwAddrHi and the lobyte at dwAddrHi+1
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 18*MCU_SIZE)
__root WORD16 (*const API_KnxMem_GetWord)(WORDPTR dwAddrHi) = KnxMem_GetWord;

/**************************************************************************
* 函数名称：BOOL API_KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
* 功能描述：get a byte data from the given virtual address.
* 输入参数：WORDPTR dwAddr:source address.
            BYTE *pucData : destination address.
* 输出参数：BYTE *pucData : destination data.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 19*MCU_SIZE)
__root BOOL (*const API_KnxMem_ReadByte)(WORDPTR dwAddr, BYTE *pucData) = KnxMem_ReadByte;

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
* 功能描述：This function writes one byte to virtual memory area.
* 输入参数：WORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 20*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteByte)(WORDPTR dwAddr,BYTE ucData) = KnxMem_WriteByte;

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
* 功能描述：This function writes one word to virtual memory area.
* 输入参数：WORDPTR dwAddrHi:destination high address.
            WORD16 wData    :source data.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 21*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteWord)(WORDPTR dwAddrHi, WORD16 wData) = KnxMem_WriteWord;

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
* 功能描述：This function writes ucCount bytes to virtual memory area.
* 输入参数：WORDPTR dwAddr:destination high address.
            BYTE *pucData :source data.
            BYTE ucCount  :byte count.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 22*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteData)(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount) = KnxMem_WriteData;

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteFinished(VOID)
* 功能描述：This function is called to force writing data to the flash.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 23*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteFinished)(VOID) = KnxMem_WriteFinished;

/**********************************************************************************
* 函数名称：BYTE API_KnxMem_GetCoCount(VOID)
* 功能描述：This function returns the number of communication objects.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：BYTE :communication object number.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 24*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetCoCount)(VOID) = KnxMem_GetCoCount;

/**************************************************************************
* 函数名称：BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* 功能描述：This function writes the checksum for the given memory block.
* 输入参数：ucObjIndex:interface object
                          OBJECT_ADDR_TABLE_ID
                          OBJECT_ASSOC_TABLE_ID
                          OBJECT_APPLICATION_ID
* 输出参数：no.
* 返 回 值：TREU/FLASE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 25*MCU_SIZE)
__root BOOL (*const API_KnxMem_SetChecksum)(BYTE ucObjIndex) = KnxMem_SetChecksum;

/**********************************************************************************
* 函数名称：BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
* 功能描述：This function may be called by application to set some system parameters.
* 输入参数：BYTE ucItem : system parameter id.
                          PARID_RESTART_COUNT
                          PARID_ROUTING_COUNT
                          PARID_DEL_USER_MSG
                          PARID_TELRATE_LIMIT
            BYTE ucValue: 
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 26*MCU_SIZE)
__root BOOL (*const API_KnxMem_SetParam)(BYTE ucItem, BYTE ucValue) = KnxMem_SetParam;

/**************************************************************************
* 函数名称：VOID KnxMem_MediaRecoveDefault(VOID)
* 功能描述：This function sets the parameter area in flash to the default.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：this function will be called at the start.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 27*MCU_SIZE)
__root VOID (*const API_KnxMem_MediaRecoveDefault)(VOID) = KnxMem_MediaRecoveDefault;

/**********************************************************************************
* 函数名称：WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
* 功能描述：This function retrieves the virtual address of the buffer of the given 
            communication object.
* 输入参数：BYTE ucCoNo : number of communication object.
* 输出参数：no.
* 返 回 值：WORDPTR :communication object's value reference(Virtual).
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 28*MCU_SIZE)
__root WORDPTR (*const API_KnxMem_GetCoValueRef)(BYTE ucCoNo) = KnxMem_GetCoValueRef;

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetCoValueType(BYTE nCoNo)
* 功能描述：This function returns the value type of the given communication object.
* 输入参数：BYTE ucCoNo : number of communication object.
* 输出参数：no.
* 返 回 值：BYTE :communication object's value type.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 29*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetCoValueType)(BYTE ucCoNo) = KnxMem_GetCoValueType;

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo)
* 功能描述：returns the configuration flags of the given communication object.
* 输入参数：BYTE ucCoNo : number of communication object.
* 输出参数：no.
* 返 回 值：BYTE :communication object's configuration.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 30*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetCoConfigByte)(BYTE ucCoNo) = KnxMem_GetCoConfigByte;

/**************************************************************************
* 函数名称：BOOL KnxMem_InitMedia(VOID)
* 功能描述：This function is called by main at the begin.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 31*MCU_SIZE)
__root BOOL (*const API_KnxMem_InitMedia)(BYTE ucDevNo) = KnxMem_InitMedia;

/**************************************************************************************************************
* 函数名称：BOOL KnxMem_VirRamInit(VOID)
* 功能描述：This function initialize the virtual RAM.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 32*MCU_SIZE)
__root BOOL (*const API_KnxMem_VirRamInit)(VOID) = KnxMem_VirRamInit;


/****************************************/
/*********** Knx program led&key op. **********/
/****************************************/

/**************************************************************************************************************
* 函数名称：VOID Knx_GetProgKey(VOID)
* 功能描述：checks the KNX key state and stores it.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：it should be called periodically.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 33*MCU_SIZE)
__root VOID (*const API_Knx_GetProgKey)(VOID) = Knx_GetProgKey;

/**************************************************************************************************************
* 函数名称：BYTE API_Knx_GetPrgLedState(VOID)
* 功能描述：retrieves the current state of the programming LED.
* 输入参数：no.
* 输出参数：BYTE ucState.
* 返 回 值：KNX_PRGLED_OFF / KNX_PRGLED_ON
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 34*MCU_SIZE)
__root BYTE (*const API_Knx_GetPrgLedState)(VOID) = Knx_GetPrgLedState;

/**************************************************************************************************************
* 函数名称：VOID Knx_SetPrgLed(VOID)
* 功能描述：sets the state of the KNX programing LED according to the state in g_ucProgramState.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：it should be called periodically.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 35*MCU_SIZE)
__root VOID (*const API_Knx_SetPrgLed)(VOID) = Knx_SetPrgLed;


/**************************************************************************************************************
* 函数名称：VOID API_Knx_SetPrgLedState(BYTE ucState)
* 功能描述：set the program LED state to g_ucProgramState.
* 输入参数：BYTE ucState.
                                     KNX_PRGLED_OFF
                                     KNX_PRGLED_ON
                                     KNX_PRGLED_BLINK_SLOW
                                     KNX_PRGLED_BLINK_FAST
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 36*MCU_SIZE)
__root VOID (*const API_Knx_SetPrgLedState)(BYTE ucState) = Knx_SetPrgLedState;

/**************************************************************************
* 函数名称：VOID *RecTable_GetRecord(WORD16 wRecordId)
* 功能说明：This function searches the requested control record in the 
            record table.
* 输入参数：WORD16 wRecordId : record id.
* 输出参数：no.
* 返 回 值: record pointer.
* 其它说明：Attention:the return pointer is physicall address.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 39*MCU_SIZE)
__root VOID *(*const API_RecTable_GetRecord)(WORD16 wRecordId) = RecTable_GetRecord;

/**************************************************************************
* 函数名称：BOOL RecTable_SetRecord(VOID *ptRec2Write)
* 功能说明：This function searches the record with the given ID 
            in the record table.If possible (only 1->0 to write)
            overwrite this record.else mark found record as invalid
            and use the next free record.
* 输入参数：VOID *ptRec2Write : record.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 40*MCU_SIZE)
__root BOOL (*const API_RecTable_SetRecord)(VOID *ptRec2Write) = RecTable_SetRecord;

/**************************************************************************
* 函数名称：BOOL RecTable_DeleteRecord(WORD16 wRecordId)
* 功能说明：This function searches the requested control record in the 
            record table and mark it as invalid.
* 输入参数：WORD16 wRecordId : record id.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 41*MCU_SIZE)
__root BOOL (*const API_RecTable_DeleteRecord)(WORD16 wRecordId) = RecTable_DeleteRecord;

/**************************************************************************
* 函数名称：BOOL RecTable_DeleteAppRecords(void)
* 功能说明：This function searches all control records used by the application
            process in the record table and mark them as invalid.
* 输入参数：no.
* 输出参数：no.
* 返 回 值: TRUE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 42*MCU_SIZE)
__root BOOL (*const API_RecTable_DeleteAppRecords)(void) = RecTable_DeleteAppRecords;

/**************************************************************************
* 函数名称：BYTE RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize)
* 功能说明：This function initializes rectalbe.
* 输入参数：BYTE ucBytePlace : data saving pattern.
*           BYTE ucWrtSize   : flash programing size of byte.  1.2.4.8
* 输出参数：no.
* 返 回 值: saving data index.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 43*MCU_SIZE)
__root VOID (*const API_RecTable_OpInit)(BYTE ucDevNo,BYTE ucWrtSize) = RecTable_OpInit;

/**************************************************************************
* 函数名称：BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData)
* 功能说明：reading one data byte to pucData from a record's data area.
* 输入参数：WORD16 wRecordID : record ID.
            BYTE *pucData    : return data's pointer.
* 输出参数：BYTE *pucData    : return data.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 44*MCU_SIZE)
__root BOOL (*const API_RecTable_GetByte)(WORD16 wRecordID, BYTE *pucData) = RecTable_GetByte;

/**************************************************************************
* 函数名称：BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData)
* 功能说明：This function writes one data byte ucData to OneByteRecord with 
            wRecordID. modify it, else it creates new record.
* 输入参数：WORD16 wRecordID : record ID.
            BYTE ucData      : input data byte.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 45*MCU_SIZE)
__root BOOL (*const API_RecTable_SetByte)(WORD16 wRecordID, BYTE ucData) = RecTable_SetByte;

/**************************************************************************
* 函数名称：BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord)
* 功能说明：This function is used by cleanup to free dirty memory in one 
            byte and one word records.
* 输入参数：T_RECORD *ptRecord : record.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：we only use byte mode to save the data.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 46*MCU_SIZE)
__root BOOL (*const API_RecTable_CleanUpRecord)(T_RECORD *ptRecord) = RecTable_CleanUpRecord;

/**************************************************************************
* 函数名称：BOOL RecTable_CleanUpTable(VOID)
* 功能说明：This function copys all valid records to RAM, erases Record table 
            write back the valid records.
* 输入参数：no.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：This function can not be called during running.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 47*MCU_SIZE)
__root BOOL (*const API_RecTable_CleanUpTable)(VOID) = RecTable_CleanUpTable;

/**************************************************************************
* 函数名称：BOOL RecTable_ClearTable(void)
* 功能说明：This function erases the complete record table.
* 输入参数：no.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：This function can not be called during running.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 48*MCU_SIZE)
__root BOOL (*const API_RecTable_ClearTable)(void) = RecTable_ClearTable;

/**************************************************************************************************************
* 函数名称：VOID Knx_SetRunState(BYTE ucControl)
* 功能描述：This function set the run state.
* 输入参数：BYTE ucControl:run control byte.
                 RUNCONTROL_NO_OPERATION
                 RUNCONTROL_RESTART
                 RUNCONTROL_STOP
                 RUNCONTROL_HALT
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 49*MCU_SIZE)
__root VOID (*const API_Knx_SetRunState)(BYTE ucControl) = Knx_SetRunState;

/**************************************************************************************************************
* 函数名称：BYTE Knx_GetRunStateEx(VOID)
* 功能描述：This function get the run state(with save flags).
* 输入参数：no.
* 输出参数：no.
* 返 回 值：run state with save flags.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 50*MCU_SIZE)
__root BYTE (*const API_Knx_GetRunStateEx)(VOID) = Knx_GetRunStateEx;

/**************************************************************************************************************
* 函数名称：VOID Knx_RunProcess(VOID)
* 功能描述：managing the application precess.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：It will be called periodically.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 51*MCU_SIZE)
__root VOID (*const API_Knx_RunProcess)(VOID) = Knx_RunProcess;

/*******************************************************************************************
* 函数名称：WORD32 KnxLl_DevReg(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum)
* 功能描述：向链路层注册设备，设备逻辑号从0开始，按序进行注册。
* 输入参数：BYTE ucLogNo:device's logical No.
            BYTE ucPhyNo:device's physical No.
            WORD16 wRxBufNum:buffer count for receiving.it should be bigger than 0.
            WORD16 wTxBufNum:buffer count for transmitting.it should be bigger than 0.
* 输出参数：
* 返 回 值：SW_OK ：注册成功；
            SW_ERR：注册失败；
* 其它说明：(1)the device logical No. should begin with 0.
            (2)the device should be registered in sequence.
            (3)wBufferNum should set according to the resource of CPU.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
*********************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 52*MCU_SIZE)
__root WORD32 (*const API_KnxLl_DevReg)(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum) = KnxLl_DevReg;

/**************************************************************************************************************
* 函数名称：VOID Knx_MsgInit(VOID)
* 功能描述：KNX message handler initialization.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 53*MCU_SIZE)
__root VOID (*const API_Knx_MsgInit)(VOID) = Knx_MsgInit;

/**************************************************************************************************************
* 函数名称：VOID Knx_MsgProcess(VOID)
* 功能描述：KNX消息处理总入口。
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 54*MCU_SIZE)
__root VOID (*const API_Knx_MsgProcess)(VOID) = Knx_MsgProcess;

/**************************************************************************************************************
* 函数名称： WORD32 KnxLl_Init(WORD16 *pwKnxBitTimArry,BYTE ucBufferNum,BYTE ucBufferSize)
* 功能描述： initialize the link device.
* 输入参数： 
* 输出参数： 
* 返 回 值： SW_OK ：操作成功
             SW_ERR：操作失败
* 其它说明： 
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 55*MCU_SIZE)
__root WORD32 (*const API_KnxLl_Init)(BYTE ucBufferNum,BYTE ucBufferSize) = KnxLl_Init;


/****************************************/
/*********** system memory op. **********/
/****************************************/

#pragma location = (KNX_API_START_VIR_ADDR + 64*MCU_SIZE)
__root VOID *(*const API_malloc)(unsigned short wLen) = mem_malloc;

#pragma location = (KNX_API_START_VIR_ADDR + 65*MCU_SIZE)
__root VOID (*const API_free)(void *p) = mem_free;

#pragma location = (KNX_API_START_VIR_ADDR + 66*MCU_SIZE)
__root VOID *(*const API_realloc)(void *p,unsigned short wLen) = mem_realloc;

#pragma location = (KNX_API_START_VIR_ADDR + 67*MCU_SIZE)
__root VOID (*const API_memset)(void *p,unsigned char byte,unsigned short wLen) = mem_memset;


/* end of file. */

