/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Filter.h
* 文件标识：无
* 内容摘要：KNX地址过滤处理头文件。
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


#ifndef _KNX_FILTER_H_
#define _KNX_FILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define KNX_ADDR_NON           0x00       /* this address is blocked with sending ack.    */
#define KNX_ADDR_HIGH          0x01       /* this address High = Self-addr Hi             */
#define KNX_ADDR_OWN           0x02       /* this address is ourselves.                   */
#define KNX_ADDR_PASS          0x03       /* this address is passed.                      */

#define KNX_SECOND_ADDR    KNX_SRC_SLAV_DEV       /* second(KNX) side's address. */
#define KNX_MAIN_ADDR      KNX_SRC_MAIN_DEV       /* Main side's address.        */




/**************************************************************************
* 函数名称：BYTE Knx_AddrFilter(BYTE ucSide,BYTE ucFrameType,WORD16 wDestAddr)
* 功能描述：Filterring the address according to the routing rule.
* 输入参数：BYTE ucSide       :KNX_SECOND_ADDR-KNX side's address.
                               KNX_MAIN_ADDR  -Main side's address.
            BYTE ucFrameType : frame type and address type.
                               LL_STANDARD_P2P_FRAME : 0x10:P2P standard frame.  Bit7:0-Phy,Bit5Bit4:01-Standard.
                               LL_STANDARD_GRP_FRAME : 0x90:Group standard frame.Bit7:1-Grp,Bit5Bit4:01-Standard.
                               LL_EXTENDED_P2P_FRAME : 0x20:P2P extended frame.  Bit7:0-Phy,Bit5Bit4:10-Extended.
                               LL_EXTENDED_GRP_FRAME : 0xA0:Group extended frame.Bit7:1-Grp,Bit5Bit4:10-Extended.
                               LL_EXTENDED_LTE_FRAME : 0xA4:LTE extended frame.
            WORD16 wDestAddr : destination address.
* 输出参数：无。
* 返 回 值：KNX_ADDR_PASS : this address is passed.
            KNX_ADDR_NON  : this address is blocked with sending ack.
* 其它说明：
**************************************************************************/
extern BYTE Knx_AddrFilter(BYTE ucSide,BYTE ucFrameType,WORD16 wDestAddr);





#ifdef __cplusplus
}
#endif

#endif /* _KNX_PROP_H_ */



/* End of file. */


