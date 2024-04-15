/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：KnxProp_091a.h
* 文件标识：无
* 内容摘要：本文件为KNX 091a协议栈的属性定义。
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


#ifndef _KNXPROP_0705_H_
#define _KNXPROP_0705_H_

#ifdef __cplusplus
extern "C" {
#endif




#define M0705_OBJ_NUM                     5            /* Object number of 0705.            */
#define M0705_DEVOBJ_PROP_NUM             10           /* Property number of device object. */
#define M0705_ADDROBJ_PROP_NUM            4            /* Property number of address table object.     */
#define M0705_ASSOCOBJ_PROP_NUM           4            /* Property number of association table object. */
#define M0705_APP_PROP_NUM                6            /* Property number of application object. */
#define M0705_PEI_PROP_NUM                5            /* Property number of PEI program object. */


/****************************************************
*   结构名：T_0705_DEV_OBJ
*   描述：  Mask 0705's device object structure.
*   参数：  BYTE ucPropNum  : property number in the object.
            T_KNXPROP_DESC tPropDescpt[]:defined properties in the object.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucPropNum;
    T_KNXPROP_DESC tPropDescpt[M0705_DEVOBJ_PROP_NUM];
}T_0705_DEV_OBJ;

/****************************************************
*   结构名：T_0705_ADDR_OBJ
*   描述：  Mask 0705's address table object structure.
*   参数：  BYTE ucPropNum  : property number in the object.
            T_KNXPROP_DESC tPropDescpt[]:defined properties in the object.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucPropNum;
    T_KNXPROP_DESC tPropDescpt[M0705_ADDROBJ_PROP_NUM];
}T_0705_ADDR_OBJ;

/****************************************************
*   结构名：T_0705_ASSOC_OBJ
*   描述：  Mask 0705's association table object structure.
*   参数：  BYTE ucPropNum  : property number in the object.
            T_KNXPROP_DESC tPropDescpt[]:defined properties in the object.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucPropNum;
    T_KNXPROP_DESC tPropDescpt[M0705_ASSOCOBJ_PROP_NUM];
}T_0705_ASSOC_OBJ;

/****************************************************
*   结构名：T_0705_APP_OBJ
*   描述：  Mask 0705's application object structure.
*   参数：  BYTE ucPropNum  : property number in the object.
            T_KNXPROP_DESC tPropDescpt[]:defined properties in the object.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucPropNum;
    T_KNXPROP_DESC tPropDescpt[M0705_APP_PROP_NUM];
}T_0705_APP_OBJ;

/****************************************************
*   结构名：T_0705_PEI_OBJ
*   描述：  Mask 0705's PEI object structure.
*   参数：  BYTE ucPropNum  : property number in the object.
            T_KNXPROP_DESC tPropDescpt[]:defined properties in the object.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucPropNum;
    T_KNXPROP_DESC tPropDescpt[M0705_PEI_PROP_NUM];
}T_0705_PEI_OBJ;

/****************************************************
*   结构名：T_0705_DEVOBJ_PARAM
*   描述：  Mask 0705's device object's properties parameter.
            we use PID_DEVICE_CONTROL as a function property.
*   参数：  
            BYTE aucObjType[2]       : object ID.
            BYTE aucSvrCtrl[2]       : service control.
            BYTE aucFirmVer          : firmware version.
            BYTE aucSeriNum[6]       : serial number.
            BYTE aucFactoryId[2]     : factory ID.
            BYTE aucOrderInfo[10]    : order information.
            BYTE aucFactoryData[4]   : factory data.
            BYTE aucHardWareType[6]  : hardware type.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE aucObjType[2];              /*  3/X  */
    BYTE aucSvrCtrl[2];              /* (3/3) */
    BYTE aucFirmVer;                 /* (3/X) */
    BYTE aucSeriNum[6];              /*  3/X  */
    BYTE aucFactoryId[2];            /* 3/(1) */
    /*   ucDeviceControl */          /*  3/3  */
    BYTE aucOrderInfo[10];           /* (3/3) */
    /*   ucPeiType       */          /* (3/3) */
    BYTE aucFactoryData[4];          /* (3/3) */
    BYTE aucHardWareType[6];         /*  3/1  */
}T_0705_DEVOBJ_PARAM;
#pragma pack()

/****************************************************
*   结构名：T_0705_ADDROBJ_PARAM
*   描述：  Mask 0705's address table object's properties 
            parameter.
            Load state control & Mcb table property are 
            functions.
*   参数：  
            BYTE aucObjType[2]       : object ID.
            BYTE aucAddrTblRefer[2]  : Address table reference.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE aucObjType[2];              /*  3/X  */
    /* ucLoadStatusCtrl                  3/3  */
    BYTE aucAddrTblRefer[2];         /*  3/3  */
    /* ucMcbTable                       (3/3) */
}T_0705_ADDROBJ_PARAM;
#pragma pack()

/****************************************************
*   结构名：T_0705_ASSOCOBJ_PARAM
*   描述：  Mask 0705's association table object's properties 
            parameter.
            Load state control & Mcb table property are 
            functions.
*   参数：  
            BYTE aucObjType[2]       : object ID.
            BYTE aucAssocTblRefer[2] : association table reference.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE aucObjType[2];              /*  3/X  */
    /* ucLoadStatusCtrl                  3/3  */
    BYTE aucAssocTblRefer[2];        /*  3/3  */
    /* ucMcbTable                       (3/3) */
}T_0705_ASSOCOBJ_PARAM;
#pragma pack()

/****************************************************
*   结构名：T_0705_APPOBJ_PARAM
*   描述：  Mask 0705's application object's properties 
            parameter.
            Load state control & Mcb table property are 
            functions.
*   参数：  
            BYTE aucObjType[2]       : object ID.
            BYTE aucAppVersion[5]    : the application version.
            BYTE ucPeiType           : currently connected PEI-Type.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE aucObjType[2];              /*  3/X   */
    /* ucLoadStatusCtrl                  3/3   */
    /* ucRunStatusCtrl                   3/3   */
    BYTE aucAppVersion[5];           /*  3/(3) */
    BYTE ucPeiType;                  /*  3/(3) */
    /* ucMcbTable                       (3/3)  */
}T_0705_APPOBJ_PARAM;
#pragma pack()

/****************************************************
*   结构名：T_0705_PEIOBJ_PARAM
*   描述：  Mask 0705's PEI object's properties 
            parameter.
            Load state control & Mcb table property are 
            functions.
*   参数：  
            BYTE aucObjType[2]       : object ID.
            BYTE aucAppVersion[5]    : the application version.
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE aucObjType[2];              /*  3/X   */
    /* ucLoadStatusCtrl                  3/3   */
    /* ucRunStatusCtrl                   3/3   */
    BYTE aucAppVersion[5];           /*  3/(3) */
    /* ucMcbTable                       (3/3)  */
}T_0705_PEIOBJ_PARAM;
#pragma pack()


/************ definition for data operation *************************/
#define VALUE_SERVICE_CONTROL             0xFFFC          /* service control data.            */

/* define operation. */
#define GET_SRV_CTRL                      ((((WORD16)gt_DevObj_Prop.aucSvrCtrl[0])<<8) + gt_DevObj_Prop.aucSvrCtrl[1])

/* property parameter. */
extern const T_0705_DEVOBJ_PARAM   gt_DevObj_Prop;
extern const T_0705_ADDROBJ_PARAM  tAddrObj_Prop_Dflt;
extern const T_0705_DEVOBJ_PARAM   tDevObj_Prop_Dflt;
extern const T_0705_ASSOCOBJ_PARAM tAssocObj_Prop_Dflt;
extern const T_0705_APPOBJ_PARAM   tAppObj_Prop_Dflt;
extern const T_0705_PEIOBJ_PARAM   tPeiObj_Prop_Dflt;
/* object define structure. */
extern const T_0705_PEI_OBJ   g_tM0705_PeiObj;
extern const T_0705_APP_OBJ   g_tM0705_AppObj;
extern const T_0705_ASSOC_OBJ g_tM0705_AssocObj;
extern const T_0705_ADDR_OBJ  g_tM0705_AddrObj;
extern const T_0705_DEV_OBJ   g_tM0705_DevObj;


/**************************************************************************************************************
* 函数名称：WORDPTR KnxProp_GetSysObjectRef(BYTE ucObIndex)
* 功能描述：Get the system object pointer.
* 输入参数：BYTE ucObIndex:the object index.
* 输出参数：no.
* 返 回 值：the pointer of the object.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORDPTR KnxProp_GetSysObjectRef(BYTE ucObIndex);










#ifdef __cplusplus
}
#endif

#endif /* _KNXPROP_0705_H_ */



/* end of file */
