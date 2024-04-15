/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Prop.h
* 文件标识：无
* 内容摘要：本文件为KNX编程状态定义。
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



#ifndef _KNX_PROGRAM_H_
#define _KNX_PROGRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* KNX programming key */
#define    KNX_PRG_KEY_OFF                    0x00                /* Key was not pressed            */
#define    KNX_PRG_KEY_NEW                    0x10                /* Key was just pressed           */
#define    KNX_PRG_KEY_ON                     0x20                /* Key was pressed long enough    */
#define    KNX_PRG_KEY_PRESSED                0x80                /* Key actually pressed           */
#define    KNX_PRG_KEY_MASK                   0x30                /* Key state without pressed flag */
#define    KNX_PRG_KEY_MASK_EX                0xF0                /* Key state with pressed flag    */

#define    KNX_KEY_TIME                       50                  /* Debounce time before pressed short */

/* KNX programming led  */
#define    KNX_PRGLED_OFF                     0x00                /* LED is switched off      */
#define    KNX_PRGLED_ON                      0x01                /* LED is switched on       */
#define    KNX_PRGLED_BLINK_SLOW              0x02                /* LED is blinking slow     */
#define    KNX_PRGLED_BLINK_FAST              0x03                /* LED is blinking fast     */
#define    KNX_PRGLED_MASK                    0x03                /* Mask to access LED flags */

#define    TIME_EXP_BLINK_SLOW                9                   /* Blinking time is 2^exp: here 512 ms */
#define    TIME_EXP_BLINK_FAST                6                   /* Blinking time is 2^exp: here  64 ms */



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
VOID Knx_GetProgKey(VOID);

/**************************************************************************************************************
* 函数名称：VOID Knx_SetPrgLed(VOID)
* 功能描述：sets the state of the KNX learning LED according to the state in g_ucProgramState.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：it should be called periodically.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_SetPrgLed(VOID);

/**************************************************************************************************************
* 函数名称：BYTE Knx_GetPrgLedState(VOID)
* 功能描述：retrieves the current state of the programming LED.
* 输入参数：BYTE ucState.
* 输出参数：no.
* 返 回 值：KNX_PRGLED_OFF / KNX_PRGLED_ON
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE Knx_GetPrgLedState(VOID);

/**************************************************************************************************************
* 函数名称：VOID Knx_SetPrgLedState(BYTE ucState)
* 功能描述：set the program LED state.
* 输入参数：BYTE ucState.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_SetPrgLedState(BYTE ucState);













#ifdef __cplusplus
}
#endif

#endif /* _KNX_PROGRAM_H_ */



/* End of file. */

