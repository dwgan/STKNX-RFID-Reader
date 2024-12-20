/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：ctrl_service.h
* 文件标识：无
* 内容摘要：本文件为控制接口层公共头文件定义。
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

#ifndef _CTRL_SERVICE_H_
#define _CTRL_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


/***************TIMER define***********************/
#define SW_TIMER_MAX_NUM                    20       /* max. number of timer. */
/* working mode define. */
#define SW_TIMER_TM_MODE                    0        /* timer working mode.   */
#define SW_TIMER_COUNT_MODE                 1        /* counter working mode. */
#define SW_TIMER_PWM_MODE                   2        /* PWM working mode.     */
/* control the timer. */
#define SW_TIMER_STOP                       0        /* stop the timer.  */
#define SW_TIMER_START                      1        /* start the timer. */
#define SW_DISABLE_TIMER_INT                2        /* disable the interrupt of timer. */
#define SW_ENABLE_TIMER_INT                 3        /* enable the interrupt of timer.  */
/* time scale. */
#define SW_TIMER_MS                         0        /* timer is running in ms scale. */
#define SW_TIMER_US                         1        /* timer is running is us scale. */

/********************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA结构用于Timer初始化/配置时的参数定义。
* 参数列表：
           参数名       数据类型    取值范围                 含义   
  ------------------------------------------------------------------------------------------------------------------
  Input  pIntCallBackHandler                               回调函数。
  Input  ucPara[0]      BYTE      1-                       设备ID。
  Input  ucPara[1]      BYTE      0-                       物理设备号
  Input  ucPara[2]      BYTE      0-4                      工作模式
  Input                           SW_TIMER_TM_MODE
  Input                           SW_TIMER_COUNT_MODE
  Input                           SW_TIMER_PWM_MODE
  Input  ucPara[3]      BYTE      1-                       定时器时间长度(ms/us)
  Input  ucPara[4]      BYTE      SW_TIMER_MS/SW_TIMER_US
 -------------------------------------------------------------------------------------------------
  Output no.
*******************************************************************************************************************/





/**********************函数原型定义******************************/

/**************************************************************************
* 函数名称：WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* 功能描述：定时器设备注册。
* 输入参数：T_REGISTED_DEVICE *ptRegDev：见结构定义。
* 输出参数：无。
* 返 回 值：SW_OK   ：注册成功；
            SW_ERROR：注册失败；
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* 函数名称：WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData)
* 功能说明：定时器计数器读取接口。
* 输入参数：ucLogNo:device logical no.
            WORD32 *pdwData:pointer of return data.
* 输出参数：WORD32 *pdwData:timer data.
* 返 回 值：SW_OK    ：successfully.
            SW_ERROR ：failed.
* 其它说明：获取物理定时器的计数器数据。
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData);

/**************************************************************************
* 函数名称：WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData)
* 功能说明：定时器数据写接口。
* 输入参数：ucLogNo:device logical no.
            WORD32 dwData:pointer of return data.
* 输出参数：无
* 返 回 值: SW_OK   ：成功
            SW_ERROR：失败
* 其它说明：写定时器的计数器值。
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData);

/**************************************************************************
* 函数名称：WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* 功能说明：定时器设备控制接口。
* 输入参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara.
*              ucPara[0]      BYTE      SW_PERIPHERAL_TIMER      Timer type.  
*              ucPara[1]      BYTE      1                        timer logical number.
*              ucPara[2]      BYTE      control command.         timer control command.  
* 输出参数：device dependent.
* 返 回 值: SW_OK   ：successfully.
            SW_ERROR：failed.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* 函数名称：WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* 功能说明：通讯层设备初始化接口。
* 输入参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->pIntCallBackHandler:callback function,if no,should set NULL.
                                    ->ucPara[0]:device ID
                                    ->ucPara[1]:logical device No.
                                    ->ucPara[2]:working mode.
                                                SW_TIMER_TM_MODE
                                                SW_TIMER_COUNT_MODE
                                                SW_TIMER_PWM_MODE
* 输出参数：no.
* 返 回 值: SW_OK   ：successfully.
            SW_ERROR：failed.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);


#ifdef __cplusplus
}
#endif

#endif /* _CTRL_SERVICE_H_ */




