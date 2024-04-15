/******************************************************************************
* 版权所有 (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：buffer.c
* 文件标识：无
* 内容摘要：缓冲区管理源文件
* 其他说明：
* 当前版本：V1.00
* 作    者：     
* 完成日期：2014年3月18日
*    
* 修改记录1：
*        修改日期：2014年3月18日
*        版 本 号：V1.00
*        修 改 人：     
*        修改内容：创建文件
******************************************************************************/


#include "type_def.h"
#include "Pub.h"
#include "sw_common.h"
#include "boardcfg.h"
#include "Boardctrl.h"       /* it should be included before buffer.h for the TOTAL_BUFFER_SIZE definition. */
#include "buffer.h"
#include "mem_malloc.h"


static BYTE         sg_ucPoolInitFlg = 0;
static BYTE         sg_ucPoolIndex = 0;
static BYTE         sg_BufferPool[DATA_BUF_SIZE_ALIGNMENT(TOTAL_BUFFER_SIZE)];
static BYTE         *sg_pucBufferPool = NULL,*sg_pucFreePool = NULL;
static T_BUFFER_MGM *sg_patBufferMgm[MAX_BUFFER_POOL_NUM] = {NULL,NULL,NULL,NULL};



/**************************************************************************
* 函数名称：VOID Buffer_Pool_Init(VOID)
* 功能描述：初始化buffer池。
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
VOID Buffer_Pool_Init(VOID)
{
    WORD16 wIndex;
    BYTE   *pucData;
    
    sg_ucPoolIndex   = 0;
    sg_pucBufferPool = DATA_BUF_ADDRESS_ALIGNMENT(sg_BufferPool);
    sg_pucFreePool   = sg_pucBufferPool;
    pucData          = sg_pucBufferPool;
    for(wIndex=0;wIndex<TOTAL_BUFFER_SIZE;wIndex++)
    {
        *(pucData+wIndex) = 0;
    }
    sg_ucPoolInitFlg = BUFFER_INIT_FLAG;
    
    return;
}

/**************************************************************************
* 函数名称：BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
* 功能描述：从buffer总池中分配一段buffer子池，子池的大小为buffer长度和个数
            的乘积。
* 输入参数：WORD16 wBufferSize : 一个buffer的大小
            WORD16 wBufferNum  : buffer的个数
* 输出参数：无
* 返 回 值：POOL_ID_NULL  : buffer子池分配失败
                            其他为分配成功后的POOL ID,Pool ID < MAX_BUFFER_POOL_NUM
* 其它说明：wBufferSize > sizeof(WORDPTR) + 1
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
{
    BYTE         *pucPoint;
    WORD16       wMemSize,wIndex;
    T_BUFFER_MGM *ptMgm;
    
    if(BUFFER_INIT_FLAG != sg_ucPoolInitFlg)
    {
        return POOL_ID_NULL;
    }
    
    wMemSize = wBufferSize * wBufferNum;
    if(((sg_pucFreePool + wMemSize) > (sg_pucBufferPool + TOTAL_BUFFER_SIZE))||\
       (sg_ucPoolIndex >= MAX_BUFFER_POOL_NUM)||(wBufferSize <= sizeof(T_BUFFER_HEADER)))
    {
        /* Not enough. */
        return POOL_ID_NULL;
    }
    ptMgm = mem_malloc(sizeof(T_BUFFER_MGM));
    if(NULL==ptMgm)
    {
        return POOL_ID_NULL;
    }
    sg_patBufferMgm[sg_ucPoolIndex] = ptMgm;
    ptMgm->ucUseFlg         = 0;
    ptMgm->pucPoolHeader    = sg_pucFreePool;
    ptMgm->pucBufferIn      = NULL;
    ptMgm->pucBufLastIn     = NULL;
    sg_ucPoolIndex++;
    pucPoint = sg_pucFreePool;
    for(wIndex=0;wIndex < wBufferNum;wIndex++)
    {
        if((wIndex + 1) == wBufferNum)
        {
            ptMgm->pucPoolEnd                      = pucPoint;
            ((T_BUFFER_HEADER *)pucPoint)->pucNext = NULL;                 /* the final one's next is set to NULL. */
        }
        else
        {
            ((T_BUFFER_HEADER *)pucPoint)->pucNext = pucPoint+wBufferSize; /* save the next buffer's address into the buffer's header. */
        }
        ((T_BUFFER_HEADER *)pucPoint)->ucPoolId = sg_ucPoolIndex;            /* save the pool ID. */
        pucPoint += wBufferSize;
    }
    sg_pucFreePool += wMemSize;                                    /* set the pool current free point. */
    
    return sg_ucPoolIndex;
}

/**************************************************************************
* 函数名称：BYTE* Buffer_Alloc(BYTE ucPoolId)
* 功能描述：从buffer子池中分配一个buffer。
* 输入参数：BYTE ucPoolId : pool Id.
* 输出参数：无
* 返 回 值：NULL  : buffer子池分配失败
                    其他，成功的buffer指针
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
BYTE* Buffer_Alloc(BYTE ucPoolId)
{
    BYTE         *pucBuffer;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0 == ucPoolId))
    {
        return NULL;
    }

    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL == ptMgm->pucPoolHeader)
    {
        /* There is no buffer in pool. */
        return NULL;
    }

#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
    pucBuffer            = ptMgm->pucPoolHeader;
    ptMgm->pucPoolHeader = ((T_BUFFER_HEADER *)pucBuffer)->pucNext;
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif

    /* clear the buffer next chain link. */
    ((T_BUFFER_HEADER *)pucBuffer)->pucNext = NULL;

    return pucBuffer;
}

/**************************************************************************
* 函数名称：BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
* 功能描述：释放一个buffer回pool中。
* 输入参数：BYTE ucPoolId : pool Id.
            BYTE *pucBuffer:待释放buffer.
* 输出参数：无
* 返 回 值：NULL  : buffer子池释放失败
                    释放成功，返回子池首buffer
* 其它说明：存在函数重入的情况下，返回值不能作为buffer池的首地址进行计算。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
{
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId)||(NULL==pucBuffer))
    {
        return NULL;
    }

    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    ((T_BUFFER_HEADER *)pucBuffer)->pucNext = NULL;
    
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
    if(NULL == ptMgm->pucPoolHeader)
    {
        ptMgm->pucPoolHeader = pucBuffer;
    }
    else
    {
        ((T_BUFFER_HEADER *)ptMgm->pucPoolEnd)->pucNext = pucBuffer;
    }
    ptMgm->pucPoolEnd = pucBuffer;
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif

    return ptMgm->pucPoolHeader;
}

/**************************************************************************
* 函数名称：BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
* 功能描述：向buffer链中插入一个buffer。
* 输入参数：BYTE ucPoolId : pool Id.
            BYTE *pucBuffer:insert buffer.
* 输出参数：无
* 返 回 值：NULL  : 插入buffer失败
                    插入成功，返回当前buffer池首buffer。
* 其它说明：存在函数重入的情况下，返回值不能作为buffer链的首地址进行计算。
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
{
    BYTE *pucBufEnd;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId)||(NULL==pucBuffer))
    {
        return NULL;
    }
    
    /* we get the input buffer chain's end. */
    pucBufEnd = pucBuffer;
    while(((T_BUFFER_HEADER *)pucBufEnd)->pucNext != NULL)
    {
        /* it is a buffer chain. */
        pucBufEnd = ((T_BUFFER_HEADER *)pucBufEnd)->pucNext;
    }
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
    if(NULL == ptMgm->pucBufferIn)
    {
        ptMgm->pucBufferIn  = pucBuffer;
        ptMgm->pucBufLastIn = pucBufEnd;
    }
    /* we use first in first out mode. */
    else
    {
        ((T_BUFFER_HEADER *)(ptMgm->pucBufLastIn))->pucNext = pucBuffer;
        ptMgm->pucBufLastIn                                 = pucBufEnd;
    }
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif

    return ptMgm->pucBufferIn;
}

/**************************************************************************
* 函数名称：BYTE* Buffer_Get(BYTE ucPoolId)
* 功能描述：从buffer链中第一个buffer。
* 输入参数：BYTE ucPoolId : pool Id.
* 输出参数：无
* 返 回 值：NULL  : 获取buffer失败
                    获取成功，返回当前buffer。
* 其它说明：
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
BYTE* Buffer_Get(BYTE ucPoolId)
{
    BYTE *pucResult = NULL;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId))
    {
        return NULL;
    }
    
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL != ptMgm->pucBufferIn)
    {
        pucResult = ptMgm->pucBufferIn;
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
    __asm
    {
        CPSID i
    }
#endif
        ptMgm->pucBufferIn = ((T_BUFFER_HEADER *)(ptMgm->pucBufferIn))->pucNext;
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
    __asm
    {
        CPSIE i
    }
#endif
        ((T_BUFFER_HEADER *)pucResult)->pucNext = NULL;
    }

    return pucResult;
}



/* end of file. */

