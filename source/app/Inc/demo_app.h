/******************************************************************************
* 版权所有 (C)2013，南京******************** 有限公司。
*
* 文件名称：demo_app.h
* 文件标识：无
* 内容摘要：demo app header file.
* 其他说明：
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

#ifndef _DEMO_APP_H_
#define _DEMO_APP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

  
#define OUTPUT_FLASH_TIME          500 /* 500 ms. */
#define INPUT_CHECK_TIME           50  /* 50ms    */
#define OUTPUT_FLASH_START         1
#define OUTPUT_FLASH_STOP          0


typedef struct
{
    BOOL   ucForced;               /* channel is in forced status. */
    BYTE   ucOldCoData;            /* previous data of co-obj.       */
    WORD32 dwStartTime;            /* input start time.            */
}T_INPUT_STATUS;

typedef struct
{
    BYTE    ucSwtCoNo;                   /* switch function com. NO. */
    BYTE    ucForceCoNo;                 /* force function com. No.  */
    BYTE    ucSceneCoNo;                 /* scene function  com. No. */
    T_INPUT_STATUS *pdwChnlParaRef;      /* channel ram data variable's address. */
    WORDPTR pdwSwtTypeRef;               /* switch type set address.   */
    WORDPTR pdwForceCtrlRef;             /* force control set address. */
    WORDPTR pdwSceneCtrlRef;             /* scene control set address. */
    WORDPTR pdwSceneDataRef;             /* scene data address.        */
}T_INPUT_CHANNEL;

typedef struct
{
    BYTE    ucOutCoNo;           /* output function com. NO. */
    BYTE    ucOutStCoNo;         /* output status com. NO.   */
    WORDPTR pdwOutTypeRef;       /* output type set address com. NO. */
}T_OUTPUT_CHANNEL;

typedef struct
{
    BYTE   ucOldSt;               /* the old status of output. */
    BYTE   ucFlashCtl;            /* control flash stop or  start. */
    WORD32 dwStartTime;           /* the action start time(ms). */
}T_OUTPUT_STATUS;



typedef struct
{
    BYTE   ReceivedFlag;
    WORD32 ReceivedTime;
    BYTE   ReceivedMessages[7];
}KEYINPUT_STATUS;

/**************************************************************************
* 函数名称： App_Data_Init(void)
* 功能描述： Initialize the demo application data.
* 输入参数： no.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Init(void);

/**************************************************************************
* 函数名称： App_Data_Init(void)
* 功能描述： Initialize the demo application data.
* 输入参数： no.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Run(void);
void DataConvert_FloatToInt(BYTE *pData);
void DataConvert_IntToFloat(BYTE *pData);
void swapEndian(void* data, size_t size);
void DataConvert_Int32ToFloat( BYTE *pData );
u32_t GetSystemTime_ms(void);
void SystemDelay_ms(u32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* _DEMO_APP_H_ */






/* end of file. */
