/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Nl.h
* 文件标识：无
* 内容摘要：knx ip network layer header file.
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


#ifndef _KNX_NL_H_
#define _KNX_NL_H_

#ifdef __cplusplus
extern "C" {
#endif


#define NPDU_CLR_HOP_COUNT        0x8F           /* clear the hop count.        */
#define NPDU_MAX_HOP_COUNT        0x60           /* Max. hop count.             */
#define NPDU_ESC_HOP_COUNT        0x70           /* No blocking hop count.      */
#define NPDU_HOP_COUNT_MASK       0x70           /* Mask for getting hop count. */


/**************************************************************************************************************
* 函数名称：VOID Knx_NlUp(BYTE **pucUpFrame)
* 功能描述：KNX network up frame handle。
* 输入参数：BYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：if there is a wrong in the buffer,we set the length to 0.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_NlUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* 函数名称：VOID Knx_NlDown(BYTE **pucDownFrame)
* 功能描述：KNX network down frame handle。
* 输入参数：BYTE **pucDownFrame:down frame buffer's pointer,*pucDownFrame points to the header of buffer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：if there is a wrong in the buffer,we set the length to 0.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID Knx_NlDown(BYTE **pucDownFrame);











#ifdef __cplusplus
}
#endif

#endif /* _KNX_NL_H_ */



/* end of file. */


