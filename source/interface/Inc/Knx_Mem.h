/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Mem.h
* 文件标识：无
* 内容摘要：协议memory处理头文件。
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


#ifndef _KNX_MEM_H_
#define _KNX_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Flash state define.we use these defines to check if the system start the first time. */
#define VIR_MEM_STATE_CLEAR          0xFF    /* State after erasing                 */
#define VIR_MEM_STATE_NEW            0xFE    /* State after loading EEPROM via JTAG */
#define VIR_MEM_STATE_OK             0xFC    /* State after KnxMem_InitEeprom()     */
#define VIR_MEM_STATE_WRITING        0xF0    /* Data writing is in progress         */
#define VIR_MEM_STATE_ERROR          0x00    /* Used for return value               */

#define NOT_PROGRAMMING              0x00    /* No programming in progress          */
#define ADDR_IN_PROG_AREA            0x01    /* Programming in progress but address in prog. area */
#define ADDR_OUT_OF_PROG_AREA        0x02    /* Programming in progress and address out of prog. area.*/
#define ADDR_OUT_OF_EEPROM           0x03    /* Error: Address is not valid eeprom space              */

#define GET_FLASH_PAGE(dwAddr)       (GET_REAL_OF_VIR(dwAddr)&(~(FLASH_PAGE_SIZE-1)))


/* Defines for communication object descriptor tabe.*/
#define COTAB_POS_COUNT              0    /* The count of communication objects */
#define COTAB_POS_RAMFLAGS_REF       1    /* The pointer to RAM flags (2 bytes) */
#define COTAB_POS_FIRSTVAL_REF       3    /* Start of the first object desc.    */

/* Defines for a single communication object descriptor */
#define CO_POS_VALUE_REF             0    /* The value pointer of the co (2 bytes)    */
#define CO_POS_CONFIG                2    /* The config byte of the co                */
#define CO_POS_TYPE                  3    /* The type byte of the co                  */
#define CO_DESC_SIZE                 4    /* The count of bytes for one co descriptor */

/* define for set parameter by user. */
#define PARID_RESTART_COUNT            0         /* Parameter ID for restart count (BIM112) */
#define PARID_ROUTING_COUNT            1         /* Parameter ID for routing count (BIM112) */
#define PARID_DEL_USER_MSG             11        /* Parameter ID for delete user messages   */
#define PARID_TELRATE_LIMIT            12        /* Parameter ID for tel. limitation rate   */

/****************************************************
*   结构名：T_RAM_DESC
*   描述：  KNX virtual RAM discription structure.
*   参数：  
            WORD16  wStart         Start of the block in virtual address space
            WORD16  wLength        Length of the block in bytes
            BYTE    *pucData       Pointer to block in physical address space
*   作者：  Jackson
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    WORDPTR wStart;         /* Start of the block in virtual address space */
    WORD16  wLength;        /* Length of the block in bytes */
    BYTE    *pucData;       /* Pointer to block in physical address space */
}T_RAM_DESC;


/**************************************************************************
* 函数名称：BYTE API_KnxMem_GetByte(WORDPTR dwAddr)
* 功能描述：get a byte data from the given virtual address.
* 输入参数：WORDPTR dwAddr:source address.
* 输出参数：no.
* 返 回 值：memory data.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BYTE KnxMem_GetByte(WORDPTR dwAddr);

/**************************************************************************
* 函数名称：WORD16 API_KnxMem_GetWord(WORDPTR dwAddrHi)
* 功能描述：This function reads one word from virtual memory area.
* 输入参数：WORDPTR dwAddr:source address.
* 输出参数：no.
* 返 回 值：memory data.
* 其它说明：The requested word in virtual memory is assumed to have the 
            hibyte at address dwAddrHi and the lobyte at dwAddrHi+1
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
WORD16 KnxMem_GetWord(WORDPTR dwAddrHi);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
* 功能描述：get a byte data from the given virtual address.
* 输入参数：WORDPTR dwAddr:source address.
            BYTE *pucData : destination address.
* 输出参数：BYTE *pucData : destination data.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
* 功能描述：This function writes one byte to virtual memory area.
* 输入参数：WORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
* 功能描述：This function writes one word to virtual memory area.
* 输入参数：WORDPTR dwAddrHi:destination high address.
            WORD16 wData    :source data.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
* 功能描述：This function writes ucCount bytes to virtual memory area.
* 输入参数：WORDPTR dwAddr:destination high address.
            BYTE *pucData :source data.
            BYTE ucCount  :byte count.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_WriteFinished(VOID)
* 功能描述：This function is called to force writing data to the flash.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_WriteFinished(VOID);

/**********************************************************************************
* 函数名称：BYTE API_KnxMem_GetCoCount(VOID)
* 功能描述：This function returns the number of communication objects.
* 输入参数：WORD16 wPhysAddr : physical address.
* 输出参数：no.
* 返 回 值：BYTE :communication object number.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetCoCount(VOID);

/**************************************************************************
* 函数名称：BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* 功能描述：This function writes the checksum for the given memory block.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_SetChecksum(BYTE ucObjIndex);

/**********************************************************************************
* 函数名称：BOOL API_KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
* 功能描述：This function may be called by application to set some system parameters.
* 输入参数：BYTE ucItem : communication object N.
            BYTE ucValue: 
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue);

/**************************************************************************
* 函数名称：VOID KnxMem_MediaRecoveDefault(VOID)
* 功能描述：This function clears the parameter area in flash.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：this function will be called at the start.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
VOID KnxMem_MediaRecoveDefault(VOID);

/**********************************************************************************
* 函数名称：WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
* 功能描述：This function retrieves the virtual address of the buffer of the given 
            communication object.
* 输入参数：BYTE ucCoNo : number of communication object.
* 输出参数：no.
* 返 回 值：WORDPTR :communication object's value reference(Virtual).
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo);

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetCoValueType(BYTE nCoNo)
* 功能描述：This function returns the value type of the given communication object.
* 输入参数：BYTE ucCoNo : number of communication object.
* 输出参数：no.
* 返 回 值：BYTE :communication object's value type.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetCoValueType(BYTE ucCoNo);

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo)
* 功能描述：returns the configuration flags of the given communication object.
* 输入参数：BYTE ucCoNo : number of communication object.
* 输出参数：no.
* 返 回 值：BYTE :communication object's configuration.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo);

/**************************************************************************
* 函数名称：BOOL KnxMem_InitMedia(BYTE ucDevNo)
* 功能描述：This function is called by main at the begin.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_InitMedia(BYTE ucDevNo);

/**************************************************************************************************************
* 函数名称：BOOL KnxMem_VirRamInit(VOID)
* 功能描述：This function initialize the virtual RAM.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxMem_VirRamInit(VOID);

/**************************************************************************************************************
* 函数名称：VOID KnxMem_Init(VOID)
* 功能描述：This function does the initialisation of the internal variables.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxMem_Init(VOID);

/**************************************************************************
* 函数名称：BYTE KnxMem_GetByte(WORDPTR dwAddr)
* 功能描述：This function reads one byte from virtual memory as well as from
            physical memory.
* 输入参数：WORDPTR dwAddr:source address.
* 输出参数：no.
* 返 回 值：memory data.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BYTE KnxMem_GetByteEx(WORDPTR dwAddr);

/**********************************************************************************
* 函数名称：BYTE* KnxMem_GetCoRamFlags(VOID)
* 功能描述：This function returns the pointer to the communication objects RAM flags.
* 输入参数：WORD16 wPhysAddr : physical address.
* 输出参数：no.
* 返 回 值：BYTE *:physical address of RAM.
* 其它说明：The pointer returned by this function is valid in the physical address 
            space of the controller
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE* KnxMem_GetCoRamFlags(VOID);

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetSendConnNo(BYTE ucCoNo)
* 功能描述：This function is used by sending communication object to retrieve the 
            sending connection number.
* 输入参数：BYTE ucCoNo : communication object N.
* 输出参数：no.
* 返 回 值：BYTE : connection number(Grp. index).
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetSendConnNo(BYTE ucCoNo);

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetAssocCount(VOID)
* 功能描述：This function returns the count of associations defined in virtual ROM 
            area.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：BYTE : associations count.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetAssocCount(VOID);

/**********************************************************************************
* 函数名称：BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo)
* 功能描述：This function retrieves an association given by index.
* 输入参数：BYTE ucIndex    : association index.
* 输出参数：BYTE *pucConnNo : connection number.
            BYTE *pucCoNo   : communication object No.
* 返 回 值：BYTE : associations count.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo);

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetAlTelRateLimit(void)
* 功能描述：This function retrieves the current telegram rate limitation rate.
* 输入参数：no. 
* 输出参数：no.
* 返 回 值：hop count.
* 其它说明：Value definition: Telegram rate whithin 17s, 0x00,if limitation is off
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetAlTelRateLimit(void);

/**************************************************************************
* 函数名称：BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
* 功能描述：This function sets the physical address of the device.
* 输入参数：WORD16 wPhysAddr : physical address.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr);

/**************************************************************************
* 函数名称：BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData)
* 功能描述：This function writes one byte to virtual media area.
* 输入参数：WORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData);

/**********************************************************************************
* 函数名称：BOOL KnxMem_GetDelUserMsg(void)
* 功能描述：This function retrieves whether automated deleting of user messages is enabled.
* 输入参数：no. 
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BOOL KnxMem_GetDelUserMsg(void);

/**********************************************************************************
* 函数名称：BYTE KnxMem_GetNlRoutingCount(VOID)
* 功能描述：This function retrieves the current routing count.
* 输入参数：no. 
* 输出参数：no.
* 返 回 值：hop count.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetNlRoutingCount(VOID);

/**************************************************************************
* 函数名称：BOOL KnxMem_CheckChecksum(VOID)
* 功能描述：This function checks the checksum(s) of the data in EEPROM area.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
BOOL KnxMem_CheckChecksum(VOID);

/**********************************************************************************
* 函数名称：BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
* 功能描述：This function returns the connection number of the given group address.
* 输入参数：WORD16 wPhysAddr : physical address.
* 输出参数：no.
* 返 回 值：TRUE / FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***********************************************************************************/
BYTE KnxMem_GetConnNo(WORD16 wGrpAddr);









#ifdef __cplusplus
}
#endif

#endif /* _KNX_MEM_H_ */


/* end of file. */

