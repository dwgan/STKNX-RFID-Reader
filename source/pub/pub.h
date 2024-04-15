/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：pub.h
* 文件标识：无
* 内容摘要：本文件为嵌入式系统软件公共定义。
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


#ifndef _PUB_H_
#define _PUB_H_

#ifdef __cplusplus
extern "C" {
#endif




    
/****************************** 应用类型定义 *************************************************/
#define SW_APP_KNX             (0x01)        /* KNX应用    */
#define SW_APP_KNX_IP          (0x02)        /* KNX IP     */
#define SW_APP_MODBUS          (0x03)        /* MODBUS应用 */
#define SW_APP_DLT645          (0x04)        /* Dlt645应用 */
#define SW_APP_SAVE_MEDIA      (0x05)        /* 存储应用   */


/****************************** 软件框架层定义 ***********************************************/
#define SW_INTERFACE_LAYER_NUM (0x06)        /* 接口层总数，后续增加新接口层，需要更改次定义。*/
#define SW_NA_INTERFACE        (0x00)        /* 无用层     */
#define SW_SAVE_INTERFACE      (0x01)        /* 存储层     */
#define SW_COMM_INTERFACE      (0x02)        /* 通讯层     */
#define SW_MATH_INTERFACE      (0x03)        /* 运算层     */
#define SW_CONTROL_INTERFACE   (0x04)        /* 控制层     */
#define SW_DISPLAY_INTERFACE   (0x05)        /* 显示层     */
#define SW_COMMON_DRIVER_LAYER (0x06)        /* 公共驱动层 */

/****************************** 接口层服务操作模式 ********************************************/
#define SW_SVR_READ            (0x01)        /* 数据读取   */
#define SW_SVR_WRITE           (0x02)        /* 数据写入   */

/************************* 通用错误码定义 *******************************/

#define SW_ERRCODE_BASE           ( 0x00000000 )                                    /* 错误码基码       */
#define SW_APP_ERRCODE_BASE       ( SW_ERRCODE_BASE + (0x01<<24) )                    /* 应用层错误码基码 */
#define SW_INTERFACE_ERRCODE_BASE ( SW_ERRCODE_BASE + (0x02<<24) )                    /* 接口层错误码基码 */
#define SW_DRIVER_ERRCODE_BASE    ( SW_ERRCODE_BASE + (0x03<<24) )                    /* 驱动层错误码基码 */

/************************* 应用层错误码定义 ****************************/
                          /* 应用层电能处理错误码 */
#define SW_APP_ENERGY_ERRCODE_BASE      ( SW_APP_ERRCODE_BASE + (1<<16) )            /* 应用层电能量处理错误基码 */
        #define SW_APP_ENERGY_DATA_ERR  ( SW_APP_ENERGY_ERRCODE_BASE + 1 )          /* 电能数据出错             */
        
                          /* 应用层通讯处理错误码 */
#define SW_APP_COMM_ERRCODE_BASE        ( SW_APP_ERRCODE_BASE + (2<<16) )            /* 应用层通讯处理错误基码   */
        #define SW_APP_COMM_CHECK_ERR   ( SW_APP_COMM_ERRCODE_BASE + 1 )            /* 通讯数据检查失败         */

/******* 后续错误码定义，在上述定义中按序添加 **************************/

/************************** 通用返回码定义 ********************************/
#define SW_OK               ((WORD32)0x00000000)  /* 操作成功 */
#define SW_ERR              ((WORD32)0xffffffff)  /* 操作失败 */
#define SW_INVALID_PARA     ((WORD32)0xfffffffe)  /* 非法参数 */
#define SW_NOT_SUPPORT      ((WORD32)0xfffffffd)  /* 非法操作 */

/******************************* 通用数据结构定义 ***************************/








#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H_ */

/* End-of-file */


