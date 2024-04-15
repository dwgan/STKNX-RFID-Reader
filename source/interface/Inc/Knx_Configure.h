/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Configure.h
* 文件标识：无
* 内容摘要：lnx protocol configure data header file.
* 其他说明：
* 当前版本：V1.00
* 作    者：
* 完成日期：2014年5月5日
*    
* 修改记录1：
*        修改日期：2014年5月5日
*        版 本 号：V1.00
*        修 改 人：
*        修改内容：新增公共定义.
******************************************************************************/

#ifndef _KNX_CONFIGURE_H_
#define _KNX_CONFIGURE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*  */
#define APP_PEI_TYPE        PEI_TYPE_0                                /* No adapter           */
#define PEI_SW_TYPE         {0x00, 0x00, 0x00, 0x00, 0x00}            /* No PEI program       */
#define API_VERSION         {0x00, 0x00, 0x01, VALUE_FIRMWARE_VER}    /* Version of firmware  */



/* retransmission counters define */
#define REPEAT_COUNTER_BUSY        3        /* repeat counts in busy. */
#define REPEAT_COUNTER_NACK        3        /* repeat counts in NAck. */

/* routing hop count define. */
#define NL_ROUTING_COUNT           6

/* frame rate control define. */
#define AL_DEL_MESSAGE             1
#define AL_TEL_RATE_LIMIT          0        /* Telegram limitation. Frames/17s,0=off. */



#ifdef __cplusplus
}
#endif

#endif /* _KNX_CONFIGURE_H_ */


