/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：boardctrl.h
* 文件标识：无
* 内容摘要：本文件为产品单板描述控制头文件。
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

#ifndef _BOARDCTRL_H_
#define _BOARDCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEFINE_AUTO_SER_SERIAL_NUMBER         0
  
/* do not modify the name of the follow macro. */
#define CLK0_FREQ_HZ                          16000000
#define STM32G070_MCUID_START                 (0x1FFF7590)

#ifndef MCU_SIZE
    #define MCU_SIZE 4                        /* 4 bytes */
#endif

#ifndef FLASH_PAGE_SIZE
    #define FLASH_PAGE_SIZE                   2048
#endif

#ifdef FLASH_WRT_SIZE
    #undef  FLASH_WRT_SIZE
    #define FLASH_WRT_SIZE                    8
#else
    #define FLASH_WRT_SIZE                    8
#endif

/* redefine  the RxTx buffer pool size. */
#ifdef TOTAL_BUFFER_SIZE
    #undef  TOTAL_BUFFER_SIZE
#endif
#define TOTAL_BUFFER_SIZE               1288                                        /* 5 rx buffer,5 tx buffer.256 bytes for rx,128 bytes for tx. */
#define RX_BUFFER_NUMBER                5                                           /* rx buffer number. */
#define TX_BUFFER_NUMBER                5                                           /* tx buffer number. */
#define TX_PHY_BUFFER_SIZE              32                                          /* physical data buffer size. */

#define DEV_KEY_ON                      0
#define DEV_KEY_DEBOUNC_TIM             100
#define DEV_KEY_LONG_PRESS_TIM          300
  
/* Pin state define */
#define PIN_LOW_STATE                   0       /* Pin is Low voltage  */
#define PIN_HIGH_STATE                  1       /* Pin is High voltage */

/* key press state machine. */
#define KEY_PRESS_NONE  0x00
#define KEY_PRESS_ST    0x01
#define KEY_PRESS_CONF  0x02
#define KEY_PRESS_REL   0x03

#define KEY1_ST_MASK    0xfc
#define KEY2_ST_MASK    0xf3
#define KEY3_ST_MASK    0xcf
#define KEY4_ST_MASK    0x3f

/* KNX power check. */
#define PIN_SAVE_SIGNAL                 (0 == GET_GPIO_PORT_DATA(C,13))              /* power down. */
/* KNX programming key */
#define KNX_KEY_PORT                    (0 == GET_GPIO_PORT_DATA(B,10))             /* knx programming key. */
/* KNX programming led */
#define SET_KNX_LED_ON                  SET_GPIO_PORT(B,12)                          /* Switch LED off */
#define SET_KNX_LED_OFF                 CLR_GPIO_PORT(B,12)                          /* Switch LED on  */  

#define SET_RUN_LED_ON                 SET_GPIO_PORT(A,5)
#define SET_RUN_LED_OFF                  CLR_GPIO_PORT(A,5)

#define MASTER_RESET_TIME               3000                                        /* do master reset time.default 3s. */
/* device no define. */
#define AD_LOGIC_NO                     0                                           /* AD's logical No. */
#define AD_PHYSICAL_NO                  0                                           /* AD's physical No. */
#define TIMER_LOGIC_NO                  0                                           /* Timer logical No.  */
#define TIMER_PHYSICAL_NO               0                                           /* Timer physical No. */
#define FLASH_LOGIC_NO                  0                                           /* Flash logical No.  */
#define FLASH_PHYSICAL_NO               0                                           /* Flash physical No. */
#define KNX_CHIP_LOGIC_NO               0
#define KNX_CHIP_PH_NO                  0


/*************************************************************************
* 函数名称：VOID BoardCtrl_Init(VOID) 
* 功能说明：设备描述初始化。
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
VOID BoardCtrl_Init(VOID);

/*************************************************************************
* 函数名称：BOOL Board_PrgmLed_On(VOID)
* 功能说明：编程指示灯亮
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL Board_PrgmLed_On(VOID);

/*************************************************************************
* 函数名称：BOOL Board_PrgmLed_Off(VOID)
* 功能说明：编程指示灯灭
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL Board_PrgmLed_Off(VOID);

/*************************************************************************
* 函数名称：BOOL Board_PrgmKey_Handle(VOID)
* 功能说明：编程按钮状态判断
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL Board_PrgmKey_Handle(VOID);

/*************************************************************************
* 函数名称：BOOL Board_SavePin_Check(VOID)
* 功能说明：判断总线掉电管脚是否有掉电。
* 输入参数：无
* 输出参数：无
* 返 回 值：TRUE:出现总线掉电
                          FALSE:没有总线掉电
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL Board_SavePin_Check(VOID);

/*************************************************************************
* 函数名称：BOOL Board_CheckMasterReset(VOID)
* 功能说明：检查是否需要进行上电恢复默认设置。
* 输入参数：无
* 输出参数：无
* 返 回 值：TRUE:要恢复
                          FALSE:不要恢复
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL Board_CheckMasterReset(VOID);

/*****************************************************************************************************
* Function        : VOID BrdCtrl_KeyCheck(VOID)
* Description     : check the key input.
* Input parameter : No.
* Output parameter: No.
* Return          : No.
* Other description:
*             K1	PIO0_0     0 is pressed. 1 is released.
*             K2	PIO0_1
*             K15	PIO0_15
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
VOID BrdCtrl_KeyCheck(VOID);

/**************************************************************************
* 函数名称： Set_Output(BYTE ucChnlNo, BYTE ucOnOff)
* 功能描述： 设置输出的管脚状态。
* 输入参数： BYTE ucChnlNo           输出通道号，从1开始
                                     OUTPUT_CHANNLE_1
                                     OUTPUT_CHANNLE_2
                                     OUTPUT_CHANNLE_3
             BYTE ucOnOff            开关指令
                                     OUTPUT_LED_OFF  LED灯灭
                                     OUTPUT_LED_ON   LED灯亮
* 输出参数： 无      
* 返 回 值： 无
* 其它说明： LED亮灭状态根据硬件设计进行修改
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   创建
**************************************************************************/
void Set_Output(BYTE ucChnlNo, BYTE ucOnOff);

/***************************************************************************************
* 函数名称：BOOL VOID BoardCtrl_Set(VOID)
* 功能说明：set device working parameters.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* --------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
****************************************************************************************/
VOID BoardCtrl_Set(VOID);

/*****************************************************************************************************
* Function        : BYTE Get_Input(BYTE ucChnlNo)
* Description     : return key status.
* Input parameter : BYTE ucChnlNo : channel No.
* Output parameter: No.
* Return          : key status.
* Other description:
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
BYTE Get_Input(BYTE ucChnlNo);

#ifdef __cplusplus
}
#endif

#endif /* _BOARDCTRL_H_ */




