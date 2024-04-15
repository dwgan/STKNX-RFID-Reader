/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：common_media.h
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


#ifndef _COMMON_MEDIA_H_
#define _COMMON_MEDIA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SW_MEDIA_DEV_MAX_NUM     2      /* max. number of media devices. */

#ifndef FLASH_WRT_SIZE
    #define FLASH_WRT_SIZE       2      /* 2bytes(word16) */
#endif

/* media operation mode. */
#define SW_MEDIA_ERASE           0      /* erase the media from given address.         */
#define SW_MEDIA_BYTE            1      /* operate the media according to a byte.      */
#define SW_MEDIA_WORD            2      /* operate the media according to a word.      */
#define SW_MEDIA_LWORD           3      /* operate the media according to a long word. */
#define SW_MEDIA_LLWORD          4      /* operate the media according to 2 long word. */
#define SW_MEDIA_READ            5      /* read byte from the given address.           */

#define FLASH_BUF_ADDRESS_ALIGNMENT(x)  ((BYTE*)((((WORDPTR)(x))+MCU_SIZE-1) & (~(MCU_SIZE-1))))  /* align the address of the buffer. */
#define FLASH_BUF_SIZE_ALIGNMENT(x)     (((x)+MCU_SIZE-1) & (~(MCU_SIZE-1)))                      /* align the size of the buffer.    */

/**************************************************************************
* 函数名称：WORD32 API_Media_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* 功能描述： 通用设备控制。
* 输入参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 输出参数：T_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* 返 回 值： SW_OK： 成功
             SW_ERR：失败
* 其它说明： 
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建 
**************************************************************************/
WORD32 API_Media_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* 函数名称：WORD32 API_Media_Read(T_DATA_OPERARTION *ptDataOp)
* 功能说明：interface for reading media.
* 输入参数：T_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :device's logical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE
                                             SW_MEDIA_BYTE
                                             SW_MEDIA_WORD
                                             SW_MEDIA_LWORD
                               ->pucBuffer  :buffer for writing the data.
                               ->dwDestAddr : the destination address.
* 输出参数：T_DATA_OPERARTION *ptDataOp
                               ->wDataLength:length of read data in byte..
* 返 回 值：SW_OK    ：成功
            SW_ERROR ：出错
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_Media_Read(T_DATA_OPERARTION *ptDataOp);

/*********************************************************************************************
* 函数名称： WORD32 API_MediaDev_Init(BYTE ucDevType,BYTE ucLogNo,CALLBACK_HANDLER pfCallBack)
* 功能描述： this function is called to initialize the given media device.
* 输入参数： BYTE ucLogNo : media device's logical No.
* 输出参数： No.
* 返 回 值： SW_OK :successfully.
             SW_ERR:failed.
 其它说明：  
* 修改日期        版本号     修改人          修改内容
* --------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建
**********************************************************************************************/
extern WORD32 API_MediaDev_Init(BYTE ucDevType,BYTE ucLogNo,CALLBACK_HANDLER pfCallBack);

/**************************************************************************
* 函数名称：WORD32 API_Media_Write(T_DATA_OPERARTION *ptDataOp)
* 功能说明：通讯层发送数据接口。
* 输入参数：T_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :device's logical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE
                                             SW_MEDIA_BYTE
                                             SW_MEDIA_WORD
                                             SW_MEDIA_LWORD
                               ->pucBuffer  :buffer for writing the data.
                               ->wDataLength:length of data in byte.
                               ->dwDestAddr : the destination address.
* 输出参数：无
* 返 回 值: SW_OK   ：成功
            SW_ERROR：失败
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
extern WORD32 API_Media_Write(T_DATA_OPERARTION *ptDataOp);

/**************************************************************************
* 函数名称： WORD32 API_MediaDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* 功能描述： 存储介质驱动层的设备注册入口。
* 输入参数： T_REGISTED_DEVICE *ptRegDev:input device parameter.
                                    ->ucAppType:interface type
                                                   SW_SAVE_INTERFACE
                                    ->ucDevId  :device type 
                                                   SW_SVMWDIA_EEPROM
                                                   SW_SVMEDIA_FRAM
                                                   SW_SVMEDIA_FLASH
                                    ->ucLogDevNo:logical device No.
                                    ->ucDevNo   :physical device No.
                                    ->ptDevOp   :device operation handler.
                                    ->pfCallBack:device's call back handler.
* 输出参数： no.
* 返 回 值： SW_ERR:注册失败
             SW_OK :注册成功
  其它说明： 
* 修改日期        版本号     修改人          修改内容
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        创建  
**************************************************************************/
WORD32 API_MediaDev_Reg(T_REGISTED_DEVICE *ptRegDev);

#if(FLASH_PAGE_SIZE != 0)

/*****************************************************************************************************
* Function        : VOID API_Common_Media_Init(VOID)
* Description     : initialize common media.
* Input parameter : No.
* Output parameter: No.
* Return          : No.
* Other description:
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
VOID API_Common_Media_Init(VOID);

/***********************************************************************************************
* function name   : WORD32 API_FlashMedia_DataFlush(BYTE ucDevNo)
* Description     : flush the data in buffer to the flash media.
* Input parameter : ucDevNo   : logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing buffered byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
WORD32 API_FlashMedia_DataFlush(BYTE ucDevNo);

/***********************************************************************************************
* function name   : WORD32 API_FlashMedia_Read_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucBuffer)
* Description     : read a byte data from Flash.
* Input parameter : dwAddr    : real address of the destination.
                    pucBuffer : data buffer pointer for saving.
                    ucDevNo   : logical device no.
* Output parameter: *pucBuffer: output data.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for reading byte data of FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
WORD32 API_FlashMedia_Read_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucBuffer);

/**********************************************************************************************************
* function name   : WORD32 API_FlashMedia_WriteData(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucData,WORD16 wCunt)
* Description     : write wCunt bytes to Flash buffer(not the practical media).
* Input parameter : dwAddr   : real address of the destination.
                    *pucData : written data.
                    ucDevNo  : logical device no.
                    wCunt    : byte's counts.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************************/
WORD32 API_FlashMedia_WriteData(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucData,WORD16 wCunt);

/************************************************************************************
* function name   : WORD32 API_FlashMedia_Write_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE ucData)
* Description     : write a byte data to Flash buffer(not the practical media).
* Input parameter : dwAddr : real address of the destination.
                    ucData : written data.
                    ucDevNo: logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 API_FlashMedia_Write_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE ucData);

/************************************************************************************
* function name   : WORD32 API_FlashMedia_Erase_Sector(BYTE ucDevNo,WORDPTR dwAddr)
* Description     : erase a sector of flash media.
* Input parameter : dwAddr : real address of the sector.
                    ucDevNo: logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for FLASH media.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 API_FlashMedia_Erase_Sector(BYTE ucDevNo,WORDPTR dwAddr);

#endif /* #if(FLASH_PAGE_SIZE != 0) */


#endif /* _COMMON_MEDIA_H_ */

/* End of common_driver.h */

