/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Tl.h
* 文件标识：无
* 内容摘要：knx ip transport layer header file.
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


#ifndef _KNX_TL_H_
#define _KNX_TL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* define TPDU type. */
#define KNX_TPDU_TYPE_MASK        0xC0   /* TPDU type mask.                     */
#define KNX_TPDU_TYPE_DATA        0x00   /* TPDU data type,P2P-cntless/Brd/Grp. */
#define KNX_TPDU_TYPE_CDATA       0x40   /* T_Connect_Data.                     */
#define KNX_TPDU_TYPE_CMD         0x80   /* Cnt/DisCnt command.                 */
#define KNX_TPDU_TYPE_ACK         0xC0   /* connection ACK.                     */
#define KNX_TPDU_TYPE_SEQU_NO     0xFC

/* define connection command. */
#define KNX_TPDU_CNECT_CMD        0x80   /* establish a connection command. */
#define KNX_TPDU_DISCNT_CMD       0x81   /* release a connection command.   */

/* define connection ACK. */
#define KNX_TPDU_ACK              0xC2   /* Positive connection ACK. */
#define KNX_TPDU_NACK             0xC3   /* Negative connection ACK. */

/* connection sequence mask. */
#define KNX_TPDU_SEQ_MASK         0x3C   /* connection sequence mask. */


/**************************************************************************************************************
* 函数名称：VOID Knx_TlUp(BYTE **pucUpFrame)
* 功能描述：KNX transport up frame handle。
* 输入参数：BYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：if there is a wrong in the buffer,we set the length to 0.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_TlUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* 函数名称：VOID Knx_TlDown(BYTE **pucDownFrame)
* 功能描述：KNX transport down frame handle。
* 输入参数：BYTE **pucDownFrame:down frame buffer's pointer,*pucDownFrame points to the header of buffer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：if there is a wrong in the buffer,we set the length to 0.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_TlDown(BYTE **pucDownFrame);











#ifdef __cplusplus
}
#endif

#endif /* _KNX_TL_H_ */



/* end of file. */


