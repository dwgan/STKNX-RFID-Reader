/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Rec_Table.h
* 文件标识：无
* 内容摘要：record table header file.
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


#ifndef _REC_TABLE_H_
#define _REC_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif


/* record's status define. */
#define ID_RECORD_FREE                0xffff    /* Record is free and ready to be used      */
#define ID_RECORD_VALID               0x5555    /* The data that record contains is valid   */
#define ID_RECORD_INVALID             0xaaaa    /* The data that record contains is invalid */
#define ID_RCD_FREE_DATA              0xff
#define ID_RCD_INVALID_DATA           0xaa
#define ID_RCD_VALID_DATA             0x55

#define RCD_INVALID_INDEX             0
#define RCD_INVALID_ST_OFFSET         16

#define RCD_VALID_INDEX               8
#define RCD_VALID_ST_OFFSET           24

#define RCD_DATA_INDEX                0
#define RCD_DATA_OFFSET               8
#define RCD_ST_LENG                   16

/* system relating record type define. */
#define ID_REC_SYS                    0x01    /* One byte record used by system */
#define ID_REC_FLASH                  0x02    /* one byte used for flash status. */
/* application relatint record define. */
#define ID_REC_APP                    0x06    /* One byte Record used by application */

/* record table virtual space.1K bytes,8 bytes per record. */
#define RECORD_TABLE_BEG             VIR_BEG_REC_EE
#define RECTBL_FIRST_RECORD          RECORD_TABLE_BEG

#define RECORD_TABLE_END                   VIR_END_REC_EE
#define RECTBL_RECORD_LEN                  8
#define RECTBL_LAST_RECORD                 (RECORD_TABLE_END - RECTBL_RECORD_LEN + 1)
#define RECTBL_RECORD_CUNT                 ((RECORD_TABLE_END - RECORD_TABLE_BEG + 1)/RECTBL_RECORD_LEN)
#define BUILD_RECORD_ID(ucMainId,ucSubId)  (((ucMainId & 0x0F)<<8) | ucSubId)

#define GET_RECORD_MAIN_ID(ptRecord)   (((T_RECORD*)ptRecord)->ucMainId)
#define GET_RECORD_SUB_ID(ptRecord)    (((T_RECORD*)ptRecord)->ucSubId)
#define GET_RECORD_ID(ptRecord)        ((((T_RECORD*)ptRecord)->ucMainId << 8) + ((T_RECORD*)ptRecord)->ucSubId)

/****************************************************
*   结构名：T_RECORD
*   描述：  record structure define of record table.
            every record has 6 data.
*   参数：  
            BYTE ucMainId:4;           The main ID of record   
            BYTE ucReserved_0:4;       Only used by word record
            BYTE ucSubId;              The sub ID of record    
            BYTE aucResv[6];           reserve space.
            BYTE aucData[8];           Data bytes
            BYTE aucStatus[16];        The status of record,0-1 invalid,2-3 valid
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE ucMainId:4;                     /* The main ID of record    */
    BYTE ucReserved_0:4;                 /* Only used by word record */
    BYTE ucSubId;                        /* The sub ID of record     */
    BYTE aucResv[6];                     /* reserve space.           */
    BYTE aucData[8];                     /* Data bytes               */
    BYTE aucStatus[RCD_ST_LENG];         /* The status of record     */
}T_RECORD;
#pragma pack()

/**************************************************************************
* 函数名称：VOID *RecTable_GetRecord(WORD16 wRecordId)
* 功能说明：This function searches the requested control record in the 
            record table.
* 输入参数：WORD16 wRecordId : record id.
* 输出参数：no.
* 返 回 值: record pointer.
* 其它说明：Attention:the return pointer is physicall address.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
VOID *RecTable_GetRecord(WORD16 wRecordId);

/**************************************************************************
* 函数名称：BOOL RecTable_SetRecord(VOID *ptRec2Write)
* 功能说明：This function searches the record with the given ID 
            in the record table.If possible (only 1->0 to write)
            overwrite this record.else mark found record as invalid
            and use the next free record.
* 输入参数：VOID *ptRec2Write : record.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_SetRecord(VOID *ptRec2Write);

/**************************************************************************
* 函数名称：BOOL RecTable_DeleteRecord(WORD16 wRecordId)
* 功能说明：This function searches the requested control record in the 
            record table and mark it as invalid.
* 输入参数：WORD16 wRecordId : record id.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_DeleteRecord(WORD16 wRecordId);

/**************************************************************************
* 函数名称：BOOL RecTable_DeleteAppRecords(void)
* 功能说明：This function searches all control records used by the application
            process in the record table and mark them as invalid.
* 输入参数：no.
* 输出参数：no.
* 返 回 值: TRUE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_DeleteAppRecords(void);

/**************************************************************************
* 函数名称：BYTE RecTable_GetByteIndex(BYTE ucBytePlace)
* 功能说明：This function retrieves the byte index in a byte record for a 
            given ucBytePlace bit pattern.
* 输入参数：BYTE ucBytePlace : data saving pattern.
* 输出参数：no.
* 返 回 值: saving data index.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BYTE RecTable_GetByteIndex(BYTE ucBytePlace);

/**************************************************************************
* 函数名称：BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData)
* 功能说明：reading one data byte to pucData from a record's data area.
* 输入参数：WORD16 wRecordID : record ID.
            BYTE *pucData    : return data's pointer.
* 输出参数：BYTE *pucData    : return data.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData);

/**************************************************************************
* 函数名称：BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData)
* 功能说明：This function writes one data byte ucData to OneByteRecord with 
            wRecordID. modify it, else it creates new record.
* 输入参数：WORD16 wRecordID : record ID.
            BYTE ucData      : input data byte.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData);

/**************************************************************************
* 函数名称：BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord)
* 功能说明：This function is used by cleanup to free dirty memory in one 
            byte and one word records.
* 输入参数：T_RECORD *ptRecord : record.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：we only use byte mode to save the data.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord);

/**************************************************************************
* 函数名称：BOOL RecTable_CleanUpTable(VOID)
* 功能说明：This function copys all valid records to RAM, erases Record table 
            write back the valid records.
* 输入参数：no.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：This function can not be called during running.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_CleanUpTable(VOID);

/**************************************************************************
* 函数名称：BOOL RecTable_ClearTable(void)
* 功能说明：This function erases the complete record table.
* 输入参数：no.
* 输出参数：no.
* 返 回 值: TRUE / FALSE.
* 其它说明：This function can not be called during running.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL RecTable_ClearTable(void);

/**************************************************************************
* 函数名称：VOID RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize)
* 功能说明：init recorder table operation.
* 输入参数：BYTE ucDevNo     : data saving pattern.
*           BYTE ucWrtSize   : flash programing size of byte.  1.2.4.8
* 输出参数：no.
* 返 回 值: no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
VOID RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize);






#ifdef __cplusplus
}
#endif

#endif /* _REC_TABLE_H_ */

/* end of file. */
