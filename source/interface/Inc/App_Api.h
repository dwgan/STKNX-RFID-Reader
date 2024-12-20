/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：App_Api.h
* 文件标识：无
* 内容摘要：Knx application API header file.
* 其他说明：
* 当前版本：V1.00
* 作    者：Jackson
* 完成日期：2014年3月18日
*    
* 修改记录1：
*        修改日期：2014年3月18日
*        版 本 号：V1.00
*        修 改 人：Jackson
*        修改内容：创建文件
******************************************************************************/


#ifndef _APP_API_H_
#define _APP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define KNX_API_START_VIR_ADDR         0x0800FE80
#include "Rec_Table.h"

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
extern VOID (*const API_Knx_UserAppHandler_Set)(VOID *pfHandler,BYTE ucHandlerType);

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
extern VOID (*const API_KnxTm_TimerInit)(BYTE ucDevNo);

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
extern WORD32 (*const API_KnxTm_GetTimeMs)(VOID);

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
extern WORD32 (*const API_KnxTm_GetDelayMs)(WORD32 dwOldTime);

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
extern VOID (*const API_KnxTm_UpdateCycle)(VOID);

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
extern WORD32 (*const API_KnxTm_GetCycleTimeMs)(VOID);

/**************************************************************************
* 函数名称：WORD32 API_KnxTm_GetCycleCount(VOID)
* 功能描述： 获取循环周期次数。
* 输入参数： 无。
* 输出参数： 无。
* 返 回 值： 循环次数（0~0xFFFF）
* 其它说明： 需要在循环中调用KnxTm_UpdateCycle函数更新计数。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    创建
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetCycleCount)(VOID);


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
extern BYTE (*const API_KnxAl_GetCoBufferLength)(BYTE ucCoNo);

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
extern BOOL (*const API_KnxAl_GetCoValue)(BYTE ucCoNo,BYTE *pucBuffer);

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
extern BOOL (*const API_KnxAl_SetCoValue)(BYTE ucCoNo,BYTE *pucBuffer);

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
extern BOOL (*const API_KnxAl_GetUpdatedCo)(BYTE *pucCoNo);

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
extern BYTE (*const API_KnxAl_GetRamFlags)(BYTE ucCoNo);

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
extern BOOL (*const API_KnxAl_SetRamFlags)(BYTE ucCoNo, BYTE ucFlags);

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
extern BOOL (*const API_KnxAl_RequestValueWrite)(BYTE ucCoNo);

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
extern BOOL (*const API_KnxAl_RequestValueRead)(BYTE ucCoNo);

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
extern VOID (*const API_Knx_AlMgmInit)(VOID);

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
extern VOID (*const API_KnxMem_Init)(VOID);

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
extern BYTE (*const API_KnxMem_GetByte)(WORDPTR dwAddr);

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
extern WORD16 (*const API_KnxMem_GetWord)(WORDPTR dwAddrHi);

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
extern BOOL (*const API_KnxMem_ReadByte)(WORDPTR dwAddr, BYTE *pucData);

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
extern BOOL (*const API_KnxMem_WriteByte)(WORDPTR dwAddr,BYTE ucData);

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
extern BOOL (*const API_KnxMem_WriteWord)(WORDPTR dwAddrHi, WORD16 wData);

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
extern BOOL (*const API_KnxMem_WriteData)(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount);

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
extern BOOL (*const API_KnxMem_WriteFinished)(VOID);

/**********************************************************************************
* 函数名称：BYTE API_KnxMem_GetCoCount(VOID)
* 功能描述：This function returns the number of communication objects.
* 输入参数：WORD16 wPhysAddr : physical address.
* 输出参数：no.
* 返 回 值：BYTE :communication object number.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
extern BYTE (*const API_KnxMem_GetCoCount)(VOID);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* 功能描述：This function writes the checksum for the given memory block.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern BOOL (*const API_KnxMem_SetChecksum)(BYTE ucObjIndex);

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
extern BOOL (*const API_KnxMem_SetParam)(BYTE ucItem, BYTE ucValue);

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
extern VOID (*const API_KnxMem_MediaRecoveDefault)(VOID);

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
extern WORDPTR (*const API_KnxMem_GetCoValueRef)(BYTE ucCoNo);

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
extern BYTE (*const API_KnxMem_GetCoValueType)(BYTE ucCoNo);

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
extern BYTE (*const API_KnxAl_GetCoBufLength)(BYTE ucCoNo);

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
extern BYTE (*const API_KnxMem_GetCoConfigByte)(BYTE ucCoNo);

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
extern BOOL (*const API_KnxMem_InitMedia)(BYTE ucDevNo);

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
extern BOOL (*const API_KnxMem_VirRamInit)(VOID);


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
extern VOID (*const API_Knx_GetProgKey)(VOID);

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
extern BYTE (*const API_Knx_GetPrgLedState)(VOID);

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
extern VOID (*const API_Knx_SetPrgLed)(VOID);


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
extern VOID (*const API_Knx_SetPrgLedState)(BYTE ucState);

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
extern VOID *(*const API_RecTable_GetRecord)(WORD16 wRecordId);

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
extern BOOL (*const API_RecTable_SetRecord)(VOID *ptRec2Write);

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
extern BOOL (*const API_RecTable_DeleteRecord)(WORD16 wRecordId);

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
extern BOOL (*const API_RecTable_DeleteAppRecords)(void);

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
extern VOID (*const API_RecTable_OpInit)(BYTE ucDevNo,BYTE ucWrtSize);

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
extern BOOL (*const API_RecTable_GetByte)(WORD16 wRecordID, BYTE *pucData);

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
extern BOOL (*const API_RecTable_SetByte)(WORD16 wRecordID, BYTE ucData);

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
extern BOOL (*const API_RecTable_CleanUpRecord)(T_RECORD *ptRecord);

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
extern BOOL (*const API_RecTable_CleanUpTable)(VOID);

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
extern BOOL (*const API_RecTable_ClearTable)(void);

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
extern VOID (*const API_Knx_SetRunState)(BYTE ucControl);

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
extern BYTE (*const API_Knx_GetRunStateEx)(VOID);

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
extern VOID (*const API_Knx_RunProcess)(VOID);

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
extern WORD32 (*const API_KnxLl_DevReg)(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum);

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
extern VOID (*const API_Knx_MsgInit)(VOID);

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
extern VOID (*const API_Knx_MsgProcess)(VOID);

/**************************************************************************
* 函数名称： WORD32 KnxLl_Init(BYTE ucBufferNum,BYTE ucBufferSize)
* 功能描述： initialize the link device.
* 输入参数： 
* 输出参数： 
* 返 回 值： SW_OK ：操作成功
             SW_ERR：操作失败
* 其它说明： 
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 (*const API_KnxLl_Init)(BYTE ucBufferNum,BYTE ucBufferSize);


/****************************************/
/*********** system memory op. **********/
/****************************************/

extern VOID *(*const API_malloc)(unsigned short wLen);

extern VOID (*const API_free)(void *p);

extern VOID *(*const API_realloc)(void *p,unsigned short wLen);

extern VOID (*const API_memset)(void *p,unsigned char byte,unsigned short wLen);






#ifdef __cplusplus
}
#endif

#endif /* _APP_API_H_ */

/* end of file. */

