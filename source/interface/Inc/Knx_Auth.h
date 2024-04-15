/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Auth.h
* 文件标识：无
* 内容摘要：本文件为KNX协议栈授权处理头文件。
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



#ifndef _KNX_AUTH_H_
#define _KNX_AUTH_H_

#ifdef __cplusplus
extern "C" {
#endif


/* define access level */
#define ACC_SYS          0x02    /* Access to application program.           */
#define ACC_TABLE        0x02    /* Access to address and association table. */
#define ACC_PARAM        0x03    /* Access to application parameters.        */
#define ACC_FREE         0x0F    /* Free access.    */
#define ACC_ERROR        0xFF    /* Error detected. */



/**************************************************************************************************************
* 函数名称：BYTE KnxAuth_SetLevel(BYTE* pucKey)
* 功能描述：Setting the actual access level according to the given key.
* 输入参数：BYTE *pucKey:key data pointer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxAuth_SetLevel(BYTE* pucKey);

/**************************************************************************************************************
* 函数名称：BYTE KnxAuth_GetLevel(VOID)
* 功能描述：Getting the actual access level.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：access level.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxAuth_GetLevel(VOID);

/**************************************************************************************************************
* 函数名称：BOOL KnxAuth_GetKey(BYTE ucLevel, BYTE *pucKey)
* 功能描述：Getting a key by the level.
* 输入参数：BYTE ucLevel : input level.
            BYTE *pucKey : the output buffer's pointer.
* 输出参数：BYTE *pucKey : the output key data.
* 返 回 值：TRUE / FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAuth_GetKey(BYTE ucLevel, BYTE *pucKey);

/**************************************************************************************************************
* 函数名称：BOOL KnxAuth_SetKey(BYTE ucLevel, BYTE *pucKey)
* 功能描述：Setting a key by the level.
* 输入参数：BYTE ucLevel : input level.
            BYTE *pucKey : the input buffer's pointer.
* 输出参数：no.
* 返 回 值：TRUE / FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxAuth_SetKey(BYTE ucLevel, BYTE *pucKey);












#ifdef __cplusplus
}
#endif

#endif /* _KNX_AUTH_H_ */

/* End of _KNX_AUTH_H_ */

