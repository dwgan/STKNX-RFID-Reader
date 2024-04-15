/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_LoadCtrl.h
* 文件标识：无
* 内容摘要：KNX加载控制头文件。
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


#ifndef _KNX_LOADCTRL_H_
#define _KNX_LOADCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif




/* Definition of load state machine */

/* The load states */
#define LOAD_STATE_UNLOADED            0x00    /* unloaded  */
#define LOAD_STATE_LOADED              0x01    /* loaded    */
#define LOAD_STATE_LOADING             0x02    /* loading   */
#define LOAD_STATE_ERROR               0x03    /* Load error*/
#define LOAD_STATE_UNLOADING           0x04    /* unloading */

/* The load events */
#define LOAD_EVENT_NONE                0x00    /* Nothing to do       */
#define LOAD_EVENT_START               0x01    /* Start to load       */
#define LOAD_EVENT_COMPLETE            0x02    /* Loading is complete */
#define LOAD_EVENT_SEGMENT             0x03    /* load segment        */
#define LOAD_EVENT_UNLOAD              0x04    /* Unload              */

/* The segment events */
#define SEG_EVENT_ALLOC                0x00    /* Allocation of abs. memory area       */
#define SEG_EVENT_STACK                0x01    /* Allocation of stack area (dummy)     */
#define SEG_EVENT_CONTROL              0x02    /* Set segment pointer (e.g. user main) */
#define SEG_EVENT_TASK_PTR             0x03    /* Set pointer to user init, save       */
#define SEG_EVENT_TASK_CONTROL1        0x04    /* Set user objects count and pointer   */
#define SEG_EVENT_TASK_CONTROL2        0x05    /* Set AL callback and CO pointer       */

/* Owner types of memory blocks used for memory control blocks MCB. */
#define OWNER_SYS                      0x00    /* Owner is system                      */
#define OWNER_ADDR                     0x01    /* Owner is address table               */
#define OWNER_ASSOC                    0x02    /* Owner is assiciation table           */
#define OWNER_APP                      0x03    /* Owner is application program         */
#define OWNER_PEI                      0x04    /* Owner is PEI program (only in 070x)  */
#define OWNER_ERROR_NONE               0x05    /* Error: Memory does not exist         */
#define OWNER_ERROR_MIXED              0x06    /* Error: Memory has not a unique owner */
#define OWNER_FREE                     0x07    /* Memory is not used                   */
#define OWNER_MAX_VALID                0x04    /* Max ID of a valid owner              */

#define FIRST_MCB_INDEX                0x00    /* First index for memory control records */
#define LAST_MCB_INDEX                 0x0B    /* Max number of memory control records   */
#define END_OF_MCB_INDEX               0xFF    /* Used as return value at end of MCB iteration */


/**************************************************************************************************************
* 函数名称：BOOL Knx_LoadControl(BYTE* pucUpFrame,BYTE *pucDwFrame)
* 功能描述：Handling the load control requests sent by property write to PID_LOAD_STATE_CONTROL Load state 
            machine according to AN080.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:down frame buffer's pointer.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_LoadControl(BYTE* pucUpFrame);

/**************************************************************************************************************
* 函数名称：BOOL Knx_LoadStart(BYTE ucObjIndex)
* 功能描述：This function handles the load start request.
* 输入参数：BYTE ucObjIndex:object index.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_LoadStart(BYTE ucObjIndex);

/**************************************************************************************************************
* 函数名称：BOOL Knx_LoadComplete(BYTE ucObjIndex)
* 功能描述：This function handles the load complete request.
* 输入参数：BYTE ucObjIndex:object index.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_LoadComplete(BYTE ucObjIndex);

/**************************************************************************************************************
* 函数名称：BOOL Knx_GetNextMcb(BYTE *pucIndex, T_KNXMEM_MCB *ptMcb)
* 功能描述：This function retrieves the next memory control block beginning from the given index.
            This function may be used for an iteration through all MCBs.
* 输入参数：BYTE *pucIndex     :MCB index.
            T_KNXMEM_MCB *ptMcb:MCB block.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：The function does not check whether the returned block is valid.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_GetNextMcb(BYTE *pucIndex, T_KNXMEM_MCB *ptMcb);

/**************************************************************************************************************
* 函数名称：BOOL Knx_WriteMcb(BYTE ucIndex, T_KNXMEM_MCB* pMcb)
* 功能描述：This function writes the MCB to the location given by nIndex.
* 输入参数：BYTE *pucIndex     :MCB index.
            T_KNXMEM_MCB *ptMcb:MCB block.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：The function does not check whether the returned block is valid.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_WriteMcb(BYTE ucIndex, T_KNXMEM_MCB* ptMcb);

/**************************************************************************************************************
* 函数名称：BOOL Knx_WriteChecksum(BYTE ucIndex, WORD16 wChecksum)
* 功能描述：This function writes the checksum into the MCB given by ucIndex
* 输入参数：BYTE ucIndex     :MCB index.
            WORD16 wChecksum : check sum.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：In the device model 070x, the memory checksums are stored in the corresponding MCB.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_WriteChecksum(BYTE ucIndex, WORD16 wChecksum);

/**************************************************************************************************************
* 函数名称：BOOL Knx_LoadUnload(BYTE ucObjIndex)
* 功能描述：This function handles the unload request
* 输入参数：BYTE ucObjIndex : object index.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_LoadUnload(BYTE ucObjIndex);

/**************************************************************************************************************
* 函数名称：BOOL Knx_LoadSegment(BYTE* pucUpFrame)
* 功能描述：This function handles the load segment requests.
* 输入参数：BYTE* pucUpFrame : frame buffer pointer.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_LoadSegment(BYTE* pucUpFrame);

/**************************************************************************************************************
* 函数名称：BOOL Knx_SegAllocation(BYTE *pucUpFrame)
* 功能描述：This function handles the load segment request "Absolute Code/Data Allocation Record"
* 输入参数：BYTE* pucUpFrame : frame buffer pointer.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_SegAllocation(BYTE *pucUpFrame);

/**************************************************************************************************************
* 函数名称：BOOL Knx_SegControl(BYTE* pucUpFrame)
* 功能描述：This function handles the load segment request "Segment Control Record".
* 输入参数：BYTE* pucUpFrame : frame buffer pointer.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_SegControl(BYTE* pucUpFrame);

/**************************************************************************************************************
* 函数名称：BOOL Knx_SegControl(BYTE* pucUpFrame)
* 功能描述：This function handles the load segment request "Task Control Record-1".
* 输入参数：BYTE* pucUpFrame : frame buffer pointer.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_SegTaskControl1(BYTE* pucUpFrame);

/**************************************************************************************************************
* 函数名称：BYTE Knx_GetMcbOwner(WORD16 wAddr, WORD16 wLength)
* 功能描述：return the owner of a given memory location in eeprom memory space.
* 输入参数：BYTE* pucUpFrame : frame buffer pointer.
* 输出参数：no.
* 返 回 值：ID.
* 其它说明：Only unused blocks can be allocated.The maximum of MCBs are defined in LAST_MCB_INDEX
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE Knx_GetMcbOwner(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* 函数名称：BYTE Knx_GetMcb(WORD16 wAddr, WORD16 wLength, T_KNXMEM_MCB *ptMcb)
* 功能描述：This function returns the owner of a given memory block in virtual memory space and retrieves the
            MCB data copied to pMcb.This pointer must point to a valid buffer with size of MCB.
* 输入参数：WORD16 wAddr  : memory address.
            WORD16 wLength:memory length.
            T_KNXMEM_MCB *ptMcb:ginven MCB.
* 输出参数：no.
* 返 回 值：ID.
* 其它说明：The maximum of MCBs are defined in LAST_MCB_INDEX
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE Knx_GetMcb(WORD16 wAddr, WORD16 wLength, T_KNXMEM_MCB *ptMcb);

/**************************************************************************************************************
* 函数名称：BOOL Knx_CheckLoadStates(VOID)
* 功能描述：This function checks whether the load states are ok.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：ID.
* 其它说明：It is called at startup an on disconnect.Never call this function during a download,because the 
            load states may be set to error.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_CheckLoadStates(VOID);

/**************************************************************************************************************
* 函数名称：BYTE Knx_GetLoadState(BYTE ucObjIndex)
* 功能描述：This function returns the load state of the given object.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：load state.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE Knx_GetLoadState(BYTE ucObjIndex);

/**************************************************************************************************************
* 函数名称：BOOL Knx_SetLoadState(BYTE ucObjIndex, BYTE ucLoadState)
* 功能描述：This function sets the load state of the given object.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FLASE.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_SetLoadState(BYTE ucObjIndex, BYTE ucLoadState);

/**************************************************************************************************************
* 函数名称：BOOL KnxLc_IsReadingAllowed(WORD16 wAddr, WORD16 wLength)
* 功能描述：This function checks whether a read operation is allowed.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FLASE.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_IsReadingAllowed(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* 函数名称：BOOL Knx_IsWritingAllowed(WORD16 wAddr, WORD16 wLength)
* 功能描述：This function checks whether a write operation is allowed.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：TRUE / FLASE.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_IsWritingAllowed(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* 函数名称：BOOL Knx_GetRamAlloc(BYTE ucRamType, WORD16 *pwAddr, WORD16 *pwLength)
* 功能描述：This function retrieves the start address and the size of the virtual RAM memory allocated via 
            load controls.
* 输入参数：BYTE ucRamType : ram type.
            WORD16 *pwAddr : ram address.
            WORD16 *pwLength:ram length.
* 输出参数：no.
* 返 回 值：TRUE / FLASE.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL Knx_GetRamAlloc(BYTE ucRamType, WORDPTR *pwAddr, WORD16 *pwLength);








#ifdef __cplusplus
}
#endif

#endif /* _KNX_LOADCTRL_H_ */



/* end of file */
