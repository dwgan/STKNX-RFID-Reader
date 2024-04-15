/******************************************************************************
* 版权所有 (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：dma.h
* 文件标识：无
* 内容摘要：本文件为嵌入式系统软件公共定义。
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


#ifndef _COMMON_DRIVER_H_
#define _COMMON_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SW_COMMON_DEV_MAX_NUM      4

/**************************************************************************
* 函数名称：WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* 功能描述： 通用设备控制。
* 输入参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 输出参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 返 回 值： SW_OK： 成功
             SW_ERR：失败
* 其它说明： 
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建 
**************************************************************************/
WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara);

/**************************************************************************
* 函数名称： void API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* 功能描述： 通用驱动层的设备注册入口。
* 输入参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 输出参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 返 回 值： SW_ERR:注册失败
             SW_OK :注册成功
  其它说明： 调用中间层的注册函数将SPI模块注册到中间层。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
WORD32 API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* 函数名称： WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
* 功能描述： 通用驱动层的初始化接口。
* 输入参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 输出参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 返 回 值： SW_OK :初始化成功
             SW_ERR:初始化失败
 其它说明：  设计思路上，要先注册资源、设备后，再调用该接口。
             该接口通过调用各个设备注册的接口再将各个驱动设
             备初始化。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建
**************************************************************************/
WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);



#endif /* _COMMON_DRIVER_H_ */

/* End of common_driver.h */

