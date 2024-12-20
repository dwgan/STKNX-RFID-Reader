/******************************************************************************************
* Right reserved (C 2019) Nanjing Shufan Information Technology Co.
*
* File Name        : buffer.h
*
* File Description : Header file for circle buffer management.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2019.4.1
*
* Modification Rec.:
*   Modify Data    : 2019.4.1
*   Operator       : Danny Cao.
*   Version        : 1.00
*   Action         : Creation.
*
******************************************************************(************************/


#ifndef _BUFFER_H_
#define _BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Attention:The follow definition should be redefined in BoardCtrl.h according to the realistic scenario. */
#ifndef TOTAL_BUFFER_SIZE
    #define TOTAL_BUFFER_SIZE (2048)   /* the total size of buffer pool. */
#endif

/* MCU_SIZE should be defined in hardware.h */
#define DATA_BUF_ADDRESS_ALIGNMENT(x)  ((BYTE*)((((WORDPTR)(x))+MCU_SIZE-1) & (~(MCU_SIZE-1))))  /* align the address of the buffer. */
#define DATA_BUF_SIZE_ALIGNMENT(x)     (((x)+MCU_SIZE-1) & (~(MCU_SIZE-1)))                      /* align the size of the buffer.    */

/* The Max. number of pools. */
#define MAX_BUFFER_POOL_NUM         (16)

/* Pool ID definition. */
#define POOL_ID_NULL              (0)
#define POOL_ID_ERROR             (0xff)
#define SET_POOL_ACLLOC_FLAG      (0x01)    /* set alloc flag.      */
#define CLR_POOL_ACLLOC_FLAG      (0xFE)    /* release aclloc flag. */
#define SET_POOL_FREE_FLAG        (0x02)    /* set free flag.       */
#define CLR_POOL_FREE_FLAG        (0xFD)    /* release free flag.   */
#define SET_POOL_IN_FLAG          (0x04)    /* set input flag.      */
#define CLR_POOL_IN_FLAG          (0xFB)    /* release input flag.  */
#define BUFFER_INIT_FLAG          (0x55)

/* message buffer operation. */
#define GET_MSGBUF_POOL_ID(pucBuffer)             ((T_BUFFER_HEADER*)pucBuffer)->ucPoolId
#define GET_MSGBUF_NEXT(pucBuffer)                ((T_BUFFER_HEADER*)pucBuffer)->pucNext
#define GET_RAW_BUFFER_PAYLOAD(pucBuffer)         ((BYTE*)pucBuffer + sizeof(T_BUFFER_HEADER))

#define GET_MSGBUF_PAYLOAD(pucBuffer)             ((T_MESSAGE_HEADER*)pucBuffer)->pucPayload
#define GET_MSGBUF_LENGTH(pucBuffer)              ((T_MESSAGE_HEADER*)pucBuffer)->wLength
#define GET_MSGBUF_MSG_INFO(pucBuffer)            ((T_MESSAGE_HEADER*)pucBuffer)->ucMessInfo
#define GET_MSGBUF_DEV_NO(pucBuffer)              ((T_MESSAGE_HEADER*)pucBuffer)->ucDevNo
#define GET_MSGBUF_ADD_DATA_POINT(pucBuffer)      ((T_MESSAGE_HEADER*)pucBuffer)->aucAddData

/****************************************************
*   结构名：T_BUFFER_MGM
*   描述：  buffer管理结构
*   参数：  
    BYTE    ucUseFlg;              Bit0:alloc Pool's flag
                                   Bit1:free pool's flag
                                   Bit2:In buffer's flag
    BYTE    *pucPoolHeader;        the current free buffer point
    BYTE    *pucPoolEnd;           the current free buffer end  
    BYTE    *pucBufferIn;          the buffer for input         
    BYTE    *pucBufLastIn;         the last in buffer           
*   作者：       
*   说明:
       (1) buffer frame format is as below:
              |sizeof(WORDPTR)|1 byte for pool ID| data ....|
       (2) buffer size shold be >= (Max. data size + sizeof(WORDPTR) + 1)
       (3) the byte for pool ID in frame is defined as below:
              bit0~bit3:the source pool's ID;
              bit4~bit7:the destination pool's ID;
*   修改记录：
*   2013-7-24         新增结构；
****************************************************/
typedef struct
{
    BYTE    ucUseFlg;              /* Bit0:alloc Pool's flag,
                                      Bit1:free pool's flag,
                                      Bit2:In buffer's flag;         */
    BYTE    *pucPoolHeader;        /* the current free buffer point. */
    BYTE    *pucPoolEnd;           /* the current free buffer end.   */
    BYTE    *pucBufferIn;          /* the buffer for input.          */
    BYTE    *pucBufLastIn;         /* the last in buffer.            */
}T_BUFFER_MGM;

/****************************************************
*   Structure：T_BUFFER_HEADER
*   Desc.    ：buffer header.
*   Para.    ：BYTE *pucNext : next buffer's address.
               BYTE ucPoolId : buffer's pool ID.
*   Log：
*   2013-7-24  
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE *pucNext;     /* next buffer's address */
    BYTE ucPoolId;     /* buffer's pool ID.     */
}T_BUFFER_HEADER;
#pragma pack()

/****************************************************
*   Structure：T_MESSAGE_HEADER
*   Desc.    ：message buffer header.
*   Para.    ：T_BUFFER_HEADER tBfHeader :    buffer header.
*              BYTE *pucPayload          :    payload address.
*              BYTE ucLength;            :    payload length.
*              BYTE ucMessInfo           :    message information.
*              BYTE ucDevNo              :    device's No.
*              BYTE aucAddData[6]        :    additional data.
*   Log：
*   2013-7-24  Danny.Cao  
****************************************************/
#pragma pack(1)
typedef struct
{
    T_BUFFER_HEADER tBfHeader;             /* buffer header.       */
    WORD16          wLength;               /* payload length.      */
    BYTE            *pucPayload;           /* payload address.     */
    BYTE            ucMessInfo;            /* message information. */
    BYTE            ucDevNo;               /* device's No.         */
    BYTE            aucAddData[6];         /* additional data.     */
}T_MESSAGE_HEADER;
#pragma pack()

/**********************************************************************************************************************
* Func. name       ：VOID Buffer_Pool_Init(VOID)
* Func. description：initialize buffer bool management.
* Input para.      ：None
* Output para.     ：None
* Return           ：None
* Other description：
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18           V1.0                        create  
**********************************************************************************************************************/
VOID Buffer_Pool_Init(VOID);

/**********************************************************************************************************************
* Func. name       ：BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,BYTE ucBufferNum)
* Func. description：it allocates a pool segment according to the input parameters.
* Input para.      ：WORD16 wBufferSize : size of a buffer in byte.
                     WORD16 ucBufferNum : buffer numbers.
* Output para.     ：None
* Return           ：POOL_ID_NULL  : allocating is failed.
                     other number  : the id of a new pool segment.
* Other description：wBufferSize > sizeof(WORDPTR) + 1. the size of pool segment = wBufferSize * ucBufferNum.
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        create  
**********************************************************************************************************************/
BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum);

/**********************************************************************************************************************
* Func. name       ：BYTE* Buffer_Alloc(BYTE ucPoolId)
* Func. description：it allocates a buffer from a poop segment.
* Input para.      ：BYTE ucPoolId : pool segment's Id.
* Output para.     ：None
* Return           ：NULL   : there is no enough buffer.
                     pointer: new buffer's pointer.
* Other description：
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        create  
**********************************************************************************************************************/
BYTE* Buffer_Alloc(BYTE ucPoolId);

/**********************************************************************************************************************
* Func. name       ：BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
* Func. description：it releases a buffer into a pool segment.
* Input para.      ：BYTE ucPoolId  : pool Id.
                     BYTE *pucBuffer: buffer's pointer.
* Output para.     ：None
* Return           ：NULL          : action is failed.
                     buffer pinter : action is successful.
* Other description：
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        create  
**********************************************************************************************************************/
BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer);

/**********************************************************************************************************************
* Func. name       ：BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
* Func. description：it inserts a buffer to the data buffer chain.
* Input para.      ：BYTE ucPoolId   : pool Id.
                     BYTE *pucBuffer : buffer's pointer.
* Output para.     ：None
* Return           ：NULL  : operation is failed.
*                    pinter: operation is successful.
* Other description：
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        create  
**********************************************************************************************************************/
BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer);

/**********************************************************************************************************************
* Func. name       ：BYTE* Buffer_Get(BYTE ucPoolId)
* Func. description：从buffer链中第一个buffer。
* Input para.      ：BYTE ucPoolId : pool Id.
* Output para.     ：None
* Return           ：NULL  : 获取buffer失败
                    获取成功，返回当前buffer。
* Other description：
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        create  
**********************************************************************************************************************/
BYTE* Buffer_Get(BYTE ucPoolId);

/**********************************************************************************************************************
* Func. name       ：BYTE* Msg_Buffer_Alloc(BYTE ucPoolId,BYTE ucHeaderLen)
* Func. description：it allocates a buffer with the message header using for messages.
* Input para.      ：BYTE ucPoolId    : pool Id.
                     BYTE ucHeaderLen : message header lenght in byte.
* Output para.     ：None
* Return           ：NULL   : operation is failed.
*                    pointer: operation is successful.
* Other description：ucHeaderLen + application data length should not exceed the buffer length.
* Modify date        Version     Creator          content
* --------------------------------------------------------------------------------------------------------------------
* 2014/03/18       V1.0         Caoxw          create  
**********************************************************************************************************************/
BYTE* Msg_Buffer_Alloc(BYTE ucPoolId,BYTE ucHeaderLen);

#ifdef __cplusplus
}
#endif

#endif /* _BUFFER_H_ */



/* end of file. */

