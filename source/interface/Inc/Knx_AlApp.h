/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_AlApp.h
* 文件标识：无
* 内容摘要：knx ip application layer application header file.
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


#ifndef _KNX_ALAPP_H_
#define _KNX_ALAPP_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Value types of communication objects */
#define TYPE_UINT1                   0    /*  1 Bit value  */
#define TYPE_UINT2                   1    /*  2 Bit value  */
#define TYPE_UINT3                   2    /*  3 Bit value  */
#define TYPE_UINT4                   3    /*  4 Bit value  */
#define TYPE_UINT5                   4    /*  5 Bit value  */
#define TYPE_UINT6                   5    /*  6 Bit value  */
#define TYPE_UINT7                   6    /*  7 Bit value  */
#define TYPE_UINT8                   7    /*  1 Byte value */
#define TYPE_UINT16                  8    /*  2 Byte value */
#define TYPE_TIME_DATE               9    /*  3 Byte value */
#define TYPE_FLOAT                  10    /*  4 Byte value */
#define TYPE_DATA6                  11    /*  6 Byte value */
#define TYPE_DOUBLE                 12    /*  8 Byte value */
#define TYPE_DATA10                 13    /* 10 Byte value */
#define TYPE_MAXDATA                14    /* 14 Byte value */

/* Defines for config flags */
#define CO_PRIORITY                0x03    /* Priority class for the object              */
#define CO_COMM_ENABLE             0x04    /* Object in enabled for communication        */
#define CO_READ_ENABLE             0x08    /* Object value can be read via bus           */
#define CO_WRITE_ENABLE            0x10    /* Object value can be written via bus        */
#define CO_COMM_SEG1               0x20    /* Memory offset (only DM0012 & DM0021)       */
#define CO_TRANS_ENABLE            0x40    /* Object is enabled to send                  */
#define CO_UPDATE_ENABLE           0x80    /* Object accepts values from response frames */

/* Abreviations */
#define COM_EN                     0x04    /* Object is enabled for communication        */
#define COM_R                      0x08    /* Object value can be read via bus           */
#define COM_W                      0x10    /* Object value can be written via bus        */
#define COM_T                      0x40    /* Object is enabled to send                  */
#define COM_U                      0x80    /* Object accepts values from response frames */

/* Combinations for config flags */
#define COM_ALL                    COM_EN | COM_R | COM_W | COM_T | COM_U
#define COM_STD                    COM_EN | COM_W | COM_T
#define COM_SND                    COM_EN | COM_T
#define COM_RCV                    COM_EN | COM_W
#define COM_RD                     COM_EN | COM_R | COM_T  

/* Com. Obj. priority. */
#define PRIO_LOW					0x03	/* Priority low    */
#define PRIO_HIGH					0x01	/* Priority high   */
#define PRIO_ALRM					0x02	/* Priority alarm  */
#define PRIO_SYS					0x00	/* Priority system */


/* Defines for RAM-Flags */
#define CO_FLAGS                   0x0F    /* Mask for all used flags */
#define CO_STATUS                  0x03    /* Mask for status flags                       */
#define CO_STATUS_OK               0x00    /* Flag pattern for status ok                  */
#define CO_STATUS_ERROR            0x01    /* Flag pattern for status error               */
#define CO_STATUS_PROGRESS         0x02    /* Flag pattern for status transm. in progress */
#define CO_STATUS_TRANSREQ         0x03    /* Flag pattern for status transm. requested   */

#define CO_READ_REQ                0x04    /* Object has to send a read request    */
#define CO_EXTERNAL_UPDATE         0x08    /* Object has been updated via telegram */
#define CO_FLAG_ERROR              0x0F    /* Used for return value                */


/* Define for telegram rate limitation */
#define TEL_LIMIT_BASE_TIME       17000    /* Base time in ms for telegram limitation */


/**************************************************************************************************************
* 函数名称：VOID Knx_AlAppUp(BYTE **pucUpFrame)
* 功能描述：KNX application layer up frames handle。
* 输入参数：BYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：if we handle over the frames,we set the length of the buffer to clear it.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxAl_AppUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* 函数名称：BYTE KnxAl_GetCoInfoLength(BYTE ucCoNo)
* 功能描述：This function retrieves the buffer length used by the given communication object.
* 输入参数：BYTE ucCoNo :communication object No.
* 输出参数：no.
* 返 回 值：buffer length.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxAl_GetCoBufferLength(BYTE ucCoNo);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* 功能描述：This function is used by application to retrieve the value of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :frame's payload pointer.
* 输出参数：BYTE *pucBuffer :communication object data.
* 返 回 值：TRUE / FALSE.
* 其它说明：This function will be a API function used by the application.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* 功能描述：This function is used by application to set the value of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :frame's payload pointer.
* 输出参数：BYTE *pucBuffer :communication object data.
* 返 回 值：TRUE / FALSE.
* 其它说明：(1)This function will be a API function used by the application.
            (2)To initiate a transmission of the new value KnxAl_RequestValueWrite(para) has to be called in addition.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_GetUpdatedCo(BYTE *pucCoNo)
* 功能描述：This function is used by the application to retrieve the number of the next communication object
            updated by external event.
* 输入参数：BYTE *pucCoNo:Co.objet No pointer.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_GetUpdatedCo(BYTE *pucCoNo);

/**************************************************************************************************************
* 函数名称：BYTE KnxAl_GetRamFlags(BYTE ucCoNo)
* 功能描述：This function is used by application to retrieve the status of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
* 输出参数：no.
* 返 回 值：BYTE : the status of the communication object.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxAl_GetRamFlags(BYTE ucCoNo);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags)
* 功能描述：This function is used by application to set the status of the given communication object.
* 输入参数：BYTE ucCoNo     :communication object No.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_RequestValueWrite(BYTE ucCoNo)
* 功能描述：This function initiates a value write request on the given communication object.
* 输入参数：BYTE ucCoNo:Co.objet No.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：The system will transmitts the current value of the given communication object.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_RequestValueWrite(BYTE ucCoNo);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_RequestValueRead(BYTE ucCoNo)
* 功能描述：This function initiates a value read request on the given communication object.
* 输入参数：BYTE ucCoNo:Co.objet No.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：Attention: The response by remote device can only be received if the "Update on response" flag is set
            for this communication object.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_RequestValueRead(BYTE ucCoNo);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_Init(VOID)
* 功能描述：KNX application layer management initialize。
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_Init(VOID);

/**************************************************************************************************************
* 函数名称：VOID KnxAl_IncTelRateCredits(VOID)
* 功能描述：This function updates the telegram limitation credits.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：(1)The telegram limitation is enabled if the limit rate is not equal 0x00.
            (2)each ms of runtime is a "send credit".in order to send a telegram,we should have enough send credits.
               when we send a telegram,we will subtract Telegram-limitation-base-time/limitation.We can not have more 
               credits than the base time.
            (3)to decrement credit when ucEnSub = TURE.
            (4)to increment the credit KnxAl_UpdateTelRateCredit() must be called during each cycle.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxAl_UpdateTelRateCredit(VOID);

/**************************************************************************************************************
* 函数名称：BYTE *KnxAl_GetDownFrame(VOID)
* 功能描述：This function is called to build a new request to be sent to the bus.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：BYTE *:down buffer.
* 其它说明：if we handle over the frames,we set the length of the buffer to clear it.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE *KnxAl_GetDownFrame(VOID);

/**************************************************************************************************************
* 函数名称：BOOL KnxAl_Close(void)
* 功能描述：close the application.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAl_Close(void);







#ifdef __cplusplus
}
#endif

#endif /* _KNX_ALAPP_H_ */



/* end of file. */


