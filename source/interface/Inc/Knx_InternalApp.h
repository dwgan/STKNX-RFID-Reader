/****************************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_InternalApp.h
* 文件标识：无
* 内容摘要：knx internal application source file header file.
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
*******************************************************************************************/


#ifndef _KNX_INTERNALAPP_H_
#define _KNX_INTERNALAPP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define APP_MAIN_FUNC               0xFA           /* application main function ID        */
#define APP_MAIN_INIT_FUNC          0xFB           /* application main init. function ID  */
#define APP_SAVE_FUNC               0xFC           /* application save function ID.       */

#define APP_HANDLER_MAIN            0x01           /* application entry */
#define APP_HANDLER_INIT            0x02           /* application initialize entry.    */
#define APP_HANDLER_SAVE            0x03           /* application save handling entry. */
#define APP_HANDLER_BUS_SAVE        0x04           /* application save handling when bus voltage down.  */
#define APP_HANDLER_POWER_SAVE      0x05           /* application save handling when power supply down. */
#define APP_HANDLER_WDG_RESET       0x06           /* application reset watchdog entry. */
#define APP_HANDLER_RESET_CPU       0x07           /* CPU reset entry.         */
#define APP_HANDLER_PRGM_LED_OFF    0x08           /* OFF program LED entry.   */
#define APP_HANDLER_PRGM_LED_ON     0x09           /* light program LED entry. */
#define APP_HANDLER_PRGM_KEY        0x0a           /* program key check entry. */
#define APP_HANDLER_BUS_POWER_CHECK 0x0b           /* bus power check entry.   */
#define APP_HANDLER_ADC_OP          0x0c           /* adc operation entry. */



/*****************************************************************************************************************
* 函数名称：VOID Knx_UserAppHandler_Set(APP_HANDLER pfHandler,BYTE ucHandlerType)
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
* 输出参数：no.
* 返 回 值：no.
* 其它说明：application realize the design in self source files.these handler will be used by KNX protocol
            stack internally.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                  创建
********************************************************************************************************************/
VOID Knx_UserAppHandler_Set(VOID *pfHandler,BYTE ucHandlerType);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_BusSave(VOID)
* 功能描述：the internal bus save entry used for calling user extenal bus save function when bus voltage down.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_BusSave(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_SupplySave(VOID)
* 功能描述：the internal supply save entry used for calling user extenal supply save function when supply down.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_SupplySave(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_InteralApp_Main(VOID)
* 功能描述：internal application entry,used to call the user registering extenal application entry.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_InteralApp_Main(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_InternalApp_Init(VOID)
* 功能描述：the internal app init. entry used for calling user's application initializing function.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_InternalApp_Init(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_ResetDog(VOID)
* 功能描述：the internal dog handle entry used for calling user's dog handler.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_ResetDog(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_ResetDev(VOID)
* 功能描述：the internal device reset entry used for calling user's device reset function.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_ResetDev(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_PrgmLedOff(VOID)
* 功能描述：the internal entry for switching off the program LED.it will call the user's program led handler.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_PrgmLedOff(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_PrgmLedOn(VOID)
* 功能描述：the internal entry for switching on the program LED.it will call the user's program led handler.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_PrgmLedOn(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_PrgmKey(VOID)
* 功能描述：the internal entry for check the program key.it will call the user's program key handler.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_PrgmKey(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_Internal_BusPowerCheck(VOID)
* 功能描述：the internal entry for checking the bus power.it will call the user's bus power handler.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_Internal_BusPowerCheck(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_InternalApp_Save(VOID)
* 功能描述：the internal entry for application save.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_InternalApp_Save(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_InternalApp_Entry(BYTE ucFuncId)
* 功能描述：the internal application entry used to call different internal function.
* 输入参数：BYTE ucFuncId:internal function ID.
                 APP_MAIN_FUNC      : internal application main function.
                 APP_MAIN_INIT_FUNC : internal application initializing function.
                 APP_SAVE_FUNC      : internal application save function.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_InternalApp_Entry(BYTE ucFuncId);

/**************************************************************************************************************
* 函数名称：BOOL Knx_InternalApp_Adc(BYTE ucLogDevNo,BYTE ucLogChnl,BYTE ucCunt,WORD16 *pwData)
* 功能描述：the internal ADC operation entry for application.
* 输入参数：BYTE ucChnl:channel no.
            BYTE ucCunt:sample count.
            WORD16 *pwData:return data pointer.
* 输出参数：WORD16 *pwData:return data.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_InternalApp_Adc(BYTE ucLogDevNo,BYTE ucLogChnl,BYTE ucCunt,WORD16 *pwData);




#ifdef __cplusplus
}
#endif

#endif /* _KNX_INTERNALAPP_H_ */



/* end of file. */

