/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Run.h
* 文件标识：无
* 内容摘要：本文件为KNX协议栈状态处理头文件。
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



#ifndef _KNX_RUN_H_
#define _KNX_RUN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Run status machine define */
#define RUNSTATE_HALTED             0x00    /* The application is halted (e.g. no app loaded) */
#define RUNSTATE_RUNNING            0x01    /* The application is running                     */
#define RUNSTATE_READY              0x02    /* The application is ready to start (after reset)*/
#define RUNSTATE_TERMINATED         0x03    /* The application is stopped by external request */

/* Not extern (via property read) because only the low byte will be returned */
#define RUNSTATE_FLAG_SAVE_SUPPLY    0x40    /* A comming up power fail has been detected */
#define RUNSTATE_FLAG_SAVE_BUS       0x80    /* A comming up power fail has been detected */
#define RUNSTATE_MASK_EXT            0x0F    /* Mask to get the external run state  */
#define RUNSTATE_MASK_SAVE           0xF0    /* Mask to get the save flags in state */

/* Defines for run control commands (defined by KNX) */
#define RUNCONTROL_NO_OPERATION       0x00    /* No operation */
#define RUNCONTROL_RESTART            0x01    /* Request to start application */
#define RUNCONTROL_STOP               0x02    /* Request to stop application  */
/* Defines for run control commands (only used internally) */
#define RUNCONTROL_HALT               0xFF    /* Request to halt application */

/* Definitions for start delay */
#define START_DELAY_CONST            1700    /* Time constant in ms for application start   */
#define START_DELAY_MULT                5    /* Time mulitplier in ms for application start */
#define RUN_RESET_FLG                0x55
#define RUN_RESET_WAIT_TIM           40




/**************************************************************************************************************
* 函数名称：BOOL Knx_StartRunApplication(VOID)
* 功能描述：This function initializes the application.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_StartRunApplication(VOID);

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
VOID Knx_SetRunState(BYTE ucControl);

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
BYTE Knx_GetRunStateEx(VOID);

/**************************************************************************************************************
* 函数名称：BYTE Knx_GetRunState(VOID)
* 功能描述：This function get the run state(without save flags).
* 输入参数：no.
* 输出参数：no.
* 返 回 值：run state without save flags.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE Knx_GetRunState(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_CallAppFunction(BYTE ucFunctionId,BYTE* pucBuffer,BYTE *pucDwBuf);
* 功能描述：calling a function in application.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_CallAppFunction(BYTE ucFunctionId,BYTE* pucBuffer,BYTE *pucDwBuf);

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
VOID Knx_RunProcess(VOID);

/**************************************************************************************************************
* 函数名称：BOOL Knx_CheckRunConditions(VOID)
* 功能描述：Checking whether the system is ready to start the application program.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_CheckRunConditions(VOID);

/**************************************************************************************************************
* 函数名称：VOID Knx_RunOnBusPowerFail(VOID)
* 功能描述：if bus power failed this function will be called.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_RunOnBusPowerFail(VOID);

/**************************************************************************************************************
* 函数名称：VOID Knx_RunOnSupplyPowerFail(VOID)
* 功能描述：supply power failed should call this function.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_RunOnSupplyPowerFail(VOID);

/****************************************************************************************************************
* Function: VOID KnxRun_SetResetCmd(VOID)
* Descrip.: reset device.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxRun_SetResetCmd(VOID);






#ifdef __cplusplus
}
#endif

#endif /* _KNX_RUN_H_ */



/* end of file. */



