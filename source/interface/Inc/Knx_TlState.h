/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_TlState.h
* 文件标识：无
* 内容摘要：knx transport layer state machine header file.
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


#ifndef _KNX_TLSTATE_H_
#define _KNX_TLSTATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* define the tl style.1/2/3 */
#define KNX_TL_STYLE               3
#define TL_STYLE1                  1
#define TL_STYLE2                  2
#define TL_STYLE3                  3

/* TL state machine definition. */
#define KNX_TL_CNECT_CLOSED        0    /* there is no connection.                 */
#define KNX_TL_CNECT_IDLE          1    /* there is a connection open and idle.    */
#define KNX_TL_CNECT_WAIT          2    /* Waiting for a T_ACK after sending data. */
#define KNX_TL_CNECT_CNECTING      3    /* Only for client.                        */

#define KNX_TL_REPT_MAX_CUNT       3    /* max. count for TL repititions. */

#define KNX_TL_SEQ_ADD_1           0x04   /* sequence No. + 1.    */
#define KNX_TL_SEQ_MASK            0x3C   /* sequence No.'s Mask. */

#define KNX_TL_REP_FLAG            0x8000 /* repeat send flag.                  */
#define KNX_TL_ACK_OVERTIME        3000   /* 3000ms-3s for ack overtime.        */
#define KNX_TL_CNECT_OVERTIME      6000   /* 6000ms-3s for connection overtime. */

/****************************************************
*   结构名：T_KNXTL_ATTR
*   描述：  transport parameter connection parameter.
*   参数：  see below.
*   作者：  Jackson
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE   ucDevInfo;                                /* Bit0-3:the source device flag&No.Bit4-7:the destination device flag&No. */
    BYTE   ucMsgInfo;                                /* bit6-7:layer type.bit4-5:PortNo,bit0-3:connect channel No.              */
    BYTE   ucPoolId;                                 /* buffer pool used for connection frames. */
    BYTE   ucState;                                  /* connection's state.Closed/IDEL/Wait.    */
    BYTE   ucRxSeq;                                  /* receive sequence No.                    */
    BYTE   ucTxSeq;                                  /* transmit sequence No.                   */
    BYTE   ucRepCunt;                                /* the counter of repetition.              */
    WORD16 wParterAddr;                              /* remote device's address.                */
    WORD32 wTimeCnect;                               /* connection time for over time.          */
    WORD32 wTimeAck;                                 /* start time for waiting ACK.             */
    BYTE   *pucTlCtlUp;                              /* buffer for Tl control up frames.        */
    BYTE   *pucTlCtlDwn;                             /* buffer for Tl control down frames.      */
    BYTE   *pucTlData;                               /* buffer for down frames.                 */
}T_KNXTL_CNECT_ATTR;


/**************************************************************************************************************
* 函数名称：BOOL Knx_TlStatInit(BYTE ucPoolId)
* 功能描述：KNX transport layer state initiation.
* 输入参数：BYTE ucPoolId:pool for TL.
* 输出参数：no.
* 返 回 值：TRUE or FLASE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_TlStatInit(VOID);

/**************************************************************************************************************
* 函数名称：VOID Knx_TlCnect_Data(**pucUpFrame)
* 功能描述：Connection data frames handling.
* 输入参数：BYTE **pucUpFrame:frame buffer's pointer's pointer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：we will clear the buffer length if the buffer is not need to be handled anymore.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_TlCnect_Data(BYTE **pucUpFrame);

/**************************************************************************************************************
* 函数名称：VOID Knx_TlCnect_Ctrl(**pucUpFrame)
* 功能描述：Connection command handling.
* 输入参数：BYTE **pucUpFrame:frame buffer's pointer's pointer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：we will clear the buffer length if the buffer is not need to be handled anymore.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_TlCnect_Ctrl(BYTE **pucUpFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxTlCnect_Ack(**pucUpFrame)
* 功能描述：Connection ACK handling.
* 输入参数：BYTE **pucUpFrame:frame buffer's pointer's pointer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：we will clear the buffer length if the buffer is not need to be handled anymore.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxTlCnect_Ack(BYTE **pucUpFrame);

/**************************************************************************************************************
* 函数名称：BYTE *KnxTl_GetStUpFrame(VOID)
* 功能描述：Getting the KNX TL state management up frames.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：NULL    :no return buffer;
            Not Null:up frames buffer pointer.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE *KnxTl_GetStUpFrame(VOID);

/**************************************************************************************************************
* 函数名称：VOID KnxTl_GetStDwnFrame(VOID)
* 功能描述：Getting the KNX TL state management up frames.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxTl_GetStDwnFrame(VOID);

/**************************************************************************************************************
* 函数名称：BYTE KnxTl_GetTlState(VOID)
* 功能描述：Getting the KNX TL state.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：   KNX_TL_CNECT_CLOSED
                             KNX_TL_CNECT_IDLE
                             KNX_TL_CNECT_WAIT
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxTl_GetTlState(VOID);

/**************************************************************************************************************
* 函数名称：BOOL KnxTl_IsWaiting(VOID)
* 功能描述：KNX TL is in waiting.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE:TL is in waiting;
            FALSE:TL is not in waiting.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxTl_IsWaiting(VOID);

/**************************************************************************************************************
* 函数名称：BOOL KnxTl_Evt15Action(BYTE *pucBuffer)
* 功能描述：Action of Knx Tl Event15.
* 输入参数：BYTE *pucBuffer:frame buffer's pointer.
* 输出参数：no.
* 返 回 值：TRUE or FLASE.
* 其它说明：case ucstate == CLOSED,we do action0;
            case ucstate == IDLE,we do action7,ucstate = WAIT;
            case ucstate == WAIT,we do action11(do nothing).
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxTl_Evt15Action(BYTE *pucBuffer);









#ifdef __cplusplus
}
#endif

#endif /* _KNX_TLSTATE_H_ */



/* end of file. */


