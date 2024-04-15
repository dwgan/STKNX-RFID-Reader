/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Knx_Prop.h
* 文件标识：无
* 内容摘要：本文件为KNX协议栈描述的公共定义。
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



#ifndef _KNX_PROP_H_
#define _KNX_PROP_H_

#ifdef __cplusplus
extern "C" {
#endif

            
/* Object ID for interface object. */
#define OBJECT_DEVICE_ID                       (0)  /* Device Object                       */
#define OBJECT_ADDR_TABLE_ID                   (1)  /* Addresstable Object                 */
#define OBJECT_ASSOC_TABLE_ID                  (2)  /* Associationtable Object             */
#define OBJECT_APPLICATION_ID                  (3)  /* Applicationprogram Object           */
#define OBJECT_INTERFACE_PRGM_ID               (4)  /* Interfaceprogram Object             */
#define OBJECT_KNXOBJ_ASSOC_TABLE_ID           (5)  /* KNX-Object Associationtable Object  */
#define OBJECT_ROUTER_ID                       (6)  /* Router Object                       */
#define OBJECT_LTE_RTTABLE_ID                  (7)  /* LTE Address Routing Table Object    */
#define OBJECT_CEMISVR_ID                      (8)  /* cEMI Server Object                  */
#define OBJECT_GRP_TABLE_ID                    (9)  /* Group Object Table Object           */
#define OBJECT_POLL_MAST_ID                    (10) /* Polling Master                      */
#define OBJECT_NETIP_PARAM_ID                  (11) /* KNXnet/IP Parameter Object          */
#define OBJECT_RSV_ID                          (12) /* Reserved. Shall not be used.        */
#define OBJECT_FILESVR_ID                      (13) /* File Server Object                  */
#define SYS_OBJECT_NUMBER                      (14) /* system object count.                */

#define USER_OBJECT_START_ID                   (257)/* user defining interface object's start ID. */
#define USER_OBJECT_PROPSTART_ID               (201)/* user defining interface object's property start ID. */
#define USER_OBJ15_ID                          USER_OBJECT_START_ID
#define USER_OBJ15_PROP1                       USER_OBJECT_PROPSTART_ID

/* define the ID for some common properties. */
#define PID_OBJECT_TYPE                        (1)           /* Object ID                          */
#define PID_OBJECT_NAME                        (2)           /* Interface Object Name              */
#define PID_LOAD_STATE_CONTROL                 (5)           /* Load state control                 */
#define PID_RUN_STATE_CONTROL                  (6)           /* Run state control                  */
#define PID_TABLE_REFERENCE                    (7)           /* Pointer to table                   */
#define PID_SERVICE_CONTROL                    (8)           /* Control record                     */
#define PID_FIRMWARE_REVISION                  (9)           /* Firmware Rev. BAU                  */
#define PID_SERVICES_SUPPORTED                 (10)          /* Services Supported                 */
#define PID_SERIAL_NUMBER                      (11)          /* Ser. No. BAU                       */
#define PID_MANUFACTURER_ID                    (12)          /* Manufact. ID                       */
#define PID_PROGRAM_VERSION                    (13)          /* Program Version                    */
#define PID_DEVICE_CONTROL                     (14)          /* Device Control (Flags)             */
#define PID_ORDER_INFO                         (15)          /* Manufacturer specific order info   */
#define PID_PEI_TYPE                           (16)          /* PEI type                           */
#define PID_PORT_CONFIGURATION                 (17)          /* Port A direction register          */
#define PID_POLL_GROUP_SETTINGS                (18)          /* Pollgroup Settings                 */
#define PID_MANUFACTURER_DATA                  (19)          /* Manufacturer specific data         */
#define PID_DESCRIPTION                        (21)          /* additional descriptive information */
#define PID_TABLE                              (23)          /* Table                              */
#define PID_VERSION                            (25)          /* version information related to the Interface Object */
#define PID_MCB_TABLE                          (27)          /* Memory Control Table               */
#define PID_OBJECT_INDEX                       (29)          /* Object Index                       */
#define PID_DOWNLOAD_COUNTER                   (30)          /* Download Counter                   */
/* property ID for device object. */
#define PID_ROUTING_COUNT                      (51)          /* the default value for the hop count   */
#define PID_MAX_RETRY_COUNT                    (52)          /* Max Retry Count                       */
#define PID_ERROR_FLAGS                        (53)          /* Error Flags                           */
#define PID_PROGMODE                           (54)          /* Programming Mode                      */
#define PID_PRODUCT_ID                         (55)          /* the manufacturer specific device type */
#define PID_MAX_APDU_LENGTH                    (56)          /* MAX. APDU-Length                      */
#define PID_SUBNET_ADDR                        (57)          /* the Subnetwork Address part (high octet) of the Individual Address */
#define PID_DEVICE_ADDR                        (58)          /* the Device Address part (low octet) of the Individual Address      */
#define PID_PB_CONFIG                          (59)          /* PID_PB_CONFIG                         */
#define PID_ADDR_REPORT                        (60)          /* include the KNX Serial Number of the device (6 octets) */
#define PID_ADDR_CHECK                         (61)          /* Address Check                         */
#define PID_OBJECT_VALUE                       (62)          /* Object Value,a Function Property      */
#define PID_OBJECTLINK                         (63)          /* Object Link                           */
#define PID_APPLICATION                        (64)          /* Application                           */
#define PID_PARAMETER                          (65)          /* Parameter                             */
#define PID_OBJECTADDRESS                      (66)          /* Object Address                        */
#define PID_PSU_TYPE                           (67)          /* the nominal supply current            */
#define PID_PSU_STATUS                         (68)          /* the bus power supply is switched on or off */
#define PID_PSU_ENABLE                         (69)          /* control operation of the bus power supply  */
#define PID_DOMAIN_ADDRESS                     (70)          /* Domain Address             */
#define PID_IO_LIST                            (71)          /* Interface Object List      */
#define PID_MGT_DESCRIPTOR_01                  (72)          /* Management Descriptor 1    */
#define PID_PL110_PARAM                        (73)          /* PL110 Parameters           */
#define PID_RECEIVE_BLOCK_TABLE                (75)          /* BiBat Receive Block Table  */
#define PID_RANDOM_PAUSE_TABLE                 (76)          /* BiBat Random Pause Table   */
#define PID_RECEIVE_BLOCK_NR                   (77)          /* BiBat Receive Block Number */
#define PID_HARDWARE_TYPE                      (78)          /* Hardware Type              */
#define PID_RETRANSMITTER_NUMBER               (79)          /* BiBat Retransmitter Number */
#define PID_SERIAL_NR_TABLE                    (80)          /* KNX Serial Number Tabl     */
#define PID_BIBAT_MASTER_ADDRESS               (81)          /* BiBat Master Individual Address */
#define PID_RF_DOMAIN_ADDRESS                  (82)          /* RF Domain Address */
#define PID_DEVICE_DESCRIPTOR                  (83)          /* Device Descriptor */
#define PID_GROUP_TELEGR_RATE_LIMIT_TIME_BASE  (85)          /* group telegram rate limitation time base           */
#define PID_GROUP_TELEGR_RATE_LIMIT_NO_OF_TELEGR (86)        /* group telegram rate limitation number of telegrams */

/* Property IDs for router object. */
#define PID_LINE_STATUS                        (51)          /* the status of the Subnetwork connected               */
#define PID_MAIN_LCCONFIG                      (52)          /* Defining the handling of primary side frames(p2p).   */
#define PID_SUB_LCCONFIG                       (53)          /* Defining the handling of secondary side frames(p2p). */
#define PID_MAIN_LCGRPCONFIG                   (54)          /* The handling of primary side frames in multicast.    */
#define PID_SUB_LCGRPCONFIG                    (55)          /* The handling of secondary side frames in multicast.  */
#define PID_ROUTETABLE_CONTROL                 (56)          /* The Management of the Routing Table                  */
#define PID_COUPL_SERV_CONTROL                 (57)          /* Used to control SNA management.                      */
#define PID_ROUTER_MAX_APDU_LENGTH             (58)          /* MAX. APDU-Length                                     */
#define PID_L2_COUPLER_TYPE                    (59)          /* L2 Coupler Type                                      */

/* Property IDs for LTE address routing table object. */
#define PID_LTE_ROUTESELECT                    (51)
#define PID_LTE_ROUTETABLE                     (52)

/* Property IDs for cEMI server object. */
#define PID_MEDIUM_TYPE                        (51)          /* Medium Type                                 */
#define PID_COMM_MODE                          (52)          /* Communication Mode                          */
#define PID_MEDIUM_AVAILABILITY                (53)          /* Medium Availability                         */
#define PID_ADD_INFO_TYPES                     (54)          /* Additional Information Types                */
#define PID_TIME_BASE                          (55)          /* Time Base                                   */
#define PID_TRANSP_ENABLE                      (56)          /* cEMI Server Link Layer Transparency Control */
#define PID_BIBAT_NEXTBLOCK                    (59)          /* BiBat Next Block                            */
#define PID_RF_MODE_SELECT                     (60)          /* RF Communication Mode                       */
#define PID_RF_MODE_SUPPORT                    (61)          /* Supported RF Communication Modes            */
#define PID_RF_FILTERING_MODE_SELECT           (62)          /* RF Filtering Mode Selection                 */
#define PID_RF_FILTERING_MODE_SUPPORT          (63)          /* Supported RF Filtering Modes                */

/* Property IDs for KnxNet/Ip parameter object. */
#define PID_PROJECT_INSTALLATION_ID            (51)          /* Project Installation Identification */
#define PID_KNX_INDIVIDUAL_ADDRESS             (52)          /* KNX Individual Address              */
#define PID_ADDITIONAL_INDIVIDUAL_ADDRESSES    (53)          /* Additional Individual Addresses     */
#define PID_CURRENT_IP_ASSIGNMENT_METHOD       (54)          /* Current IP Assignment Method        */
#define PID_IP_ASSIGNMENT_METHOD               (55)          /* IP Assignment Method                */
#define PID_IP_CAPABILITIES                    (56)          /* IP Capabilities                     */
#define PID_CURRENT_IP_ADDRESS                 (57)          /* Current IP Address                  */
#define PID_CURRENT_SUBNET_MASK                (58)          /* Current Subnet Mask                 */
#define PID_CURRENT_DEFAULT_GATEWAY            (59)          /* Current Default Gateway             */
#define PID_IP_ADDRESS                         (60)          /* IP Address                          */
#define PID_SUBNET_MASK                        (61)          /* Subnet Mask                         */
#define PID_DEFAULT_GATEWAY                    (62)          /* Default Gateway                     */
#define PID_DHCP_BOOTP_SERVER                  (63)          /* DHCP/BootP Server                   */
#define PID_MAC_ADDRESS                        (64)          /* MAC Address                         */
#define PID_SYS_SETUP_MULTICAST_ADDRESS        (65)          /* System Setup Multicast Address      */
#define PID_ROUTING_MULTICAST_ADDRESS          (66)          /* Routing Multicast Address           */
#define PID_TTL                                (67)          /* Time To Live                        */
#define PID_EIBNETIP_DEVICE_CAPABILITIES       (68)          /* KNXnet/IP Device Capabilities       */
#define PID_EIBNETIP_DEVICE_STATE              (69)          /* KNXnet/IP Device State              */
#define PID_EIBNETIP_ROUTING_CAPABILITIES      (70)          /* KNXnet/IP Routing Capabilities      */
#define PID_PRIORITY_FIFO_ENABLED              (71)          /* Priority FIFO Enabled               */
#define PID_QUEUE_OVERFLOW_TO_IP               (72)          /* Queue Overflow to IP                */
#define PID_QUEUE_OVERFLOW_TO_KNX              (73)          /* Queue Overflow to KNX               */
#define PID_MSG_TRANSMIT_TO_IP                 (74)          /* Telegrams Transmitted to IP         */
#define PID_MSG_TRANSMIT_TO_KNX                (75)          /* Telegrams Transmitted to KNX        */
#define PID_FRIENDLY_NAME                      (76)          /* Friendly Name                       */
#define PID_ROUTING_BUSY_WAIT_TIME             (78)          /* Routing Busy Wait Time              */

#define PID_ID_ERROR                           0xFF

/* definition for the data type of KNX properties. */
#define PDT_CONTROL                       0x00            /* Property value type: 1/10 bytes             */
#define PDT_CHAR                          0x01            /* Property value type:  1 byte                */
#define PDT_UNSIGNED_CHAR                 0x02            /* Property value type:  1 byte                */
#define PDT_INT                           0x03            /* Property value type:  2 bytes               */
#define PDT_UNSIGNED_INT                  0x04            /* Property value type:  2 bytes               */
#define PDT_KNX_FLOAT                     0x05            /* Property value type:  2 bytes               */
#define PDT_DATE                          0x06            /* Property value type:  3 bytes               */
#define PDT_TIME                          0x07            /* Property value type:  3 bytes               */
#define PDT_LONG                          0x08            /* Property value type:  4 bytes               */
#define PDT_UNSIGNED_LONG                 0x09            /* Property value type:  4 bytes               */
#define PDT_FLOAT                         0x0A            /* Property value type:  4 bytes               */
#define PDT_DOUBLE                        0x0B            /* Property value type:  4 bytes               */
#define PDT_CHAR_BLOCK                    0x0C            /* Property value type: 10 bytes               */
#define PDT_POLL_GROUP_SETTINGS           0x0D            /* Property value type:  3 bytes               */
#define PDT_SHORT_CHAR_BLOCK              0x0E            /* Property value type:  5 bytes               */
#define PDT_DATE_TIME                     0x0F            /* Property value type:  7 bytes               */
#define PDT_VARIABLE_LENGTH               0x10            /* Property value type: length undefined (0xFF)*/
#define PDT_GENERIC_01                    0x11            /* Property value type:  1 byte                */
#define PDT_GENERIC_02                    0x12            /* Property value type:  2 bytes               */
#define PDT_GENERIC_03                    0x13            /* Property value type:  3 bytes               */
#define PDT_GENERIC_04                    0x14            /* Property value type:  4 bytes               */
#define PDT_GENERIC_05                    0x15            /* Property value type:  5 bytes               */
#define PDT_GENERIC_06                    0x16            /* Property value type:  6 bytes               */
#define PDT_GENERIC_07                    0x17            /* Property value type:  7 bytes               */
#define PDT_GENERIC_08                    0x18            /* Property value type:  8 bytes               */
#define PDT_GENERIC_09                    0x19            /* Property value type:  9 bytes               */
#define PDT_GENERIC_10                    0x1A            /* Property value type: 10 bytes               */
#define PDT_GENERIC_11                    0x1B            /* Property value type: 11 bytes               */
#define PDT_GENERIC_12                    0x1C            /* Property value type: 12 bytes               */
#define PDT_GENERIC_13                    0x1D            /* Property value type: 13 bytes               */
#define PDT_GENERIC_14                    0x1E            /* Property value type: 14 bytes               */
#define PDT_GENERIC_15                    0x1F            /* Property value type: 15 bytes               */
#define PDT_GENERIC_16                    0x20            /* Property value type: 16 bytes               */
#define PDT_GENERIC_17                    0x21            /* Property value type: 17 bytes               */
#define PDT_GENERIC_18                    0x22            /* Property value type: 18 bytes               */
#define PDT_GENERIC_19                    0x23            /* Property value type: 19 bytes               */
#define PDT_GENERIC_20                    0x24            /* Property value type: 20 bytes               */
#define PDT_FUNCTION                      0x3E            /* Property value type: function               */


/* Enable write or Read mask. */
#define PROP_TYPE_MASK                    0x3F            /* Bit0-5:property type. */
#define PROP_WRITE_ENABLE_MASK            0x80            /* Bit7:writable flag. */
#define PROP_WRITE_EN                     0x80            /* Bit7:writable flag. */
#define PROP_FUNC_FLAG_MASK               0x40            /* Bit6:function flag. */
#define PROP_FUNC_SET                     0x40            /* Bit6:function flag. */
#define PROP_WR_FUNC_SET                  (PROP_WRITE_EN | PROP_FUNC_SET)  /* FUNC and write enable. */
#define PROP_W_TYPE_MASK                  (PROP_TYPE_MASK | PROP_WRITE_EN)
/* Read and write level of properties. */
#define READ_L_0                          0x00
#define READ_L_1                          0x10
#define READ_L_2                          (ACC_SYS   << 4)
#define READ_L_3                          (ACC_PARAM << 4)
#define READ_L_FREE                       (ACC_FREE  << 4)
#define WRITE_L_0                         0x00
#define WRITE_L_1                         0x01
#define WRITE_L_2                         ACC_SYS
#define WRITE_L_3                         ACC_PARAM
#define WRITE_L_FREE                      ACC_FREE
#define WR_FREE                           (READ_L_FREE | WRITE_L_FREE)

/* Access levels of system objects (AN072) */
#define ACC_DEV                           (READ_L_FREE | WRITE_L_2)    /* Access level of device object            */
#define ACC_ADDR                          (READ_L_FREE | WRITE_L_2)    /* Access level of address table object     */
#define ACC_ASSOC                         (READ_L_FREE | WRITE_L_2)    /* Access level of assoc. table object      */
#define ACC_APP                           (READ_L_FREE | WRITE_L_2)    /* Access level of application object       */
#define ACC_PEI                           (READ_L_FREE | WRITE_L_2)    /* Access level of PEI program object       */
#define ACC_PAR                           (READ_L_FREE | WRITE_L_3)    /* Access level of application's parameters */

#define GET_WRITE_ACCESS(ucStatus)        ((ucStatus & WRITE_L_FREE) >> 4)
#define GET_READ_ACCESS(ucStatus)         (ucStatus & READ_L_FREE)

#define KNX_DEV_VERIFY_MODE               0x04        /* device veriry mode set. */
#define PROP_READ_MODE                    0x00        /* conditions for property read. */
#define PROP_WRITE_MODE                   0x01        /* conditions for property write. */

/* function ID definition. */
#define PROP_SYS_FUNC                       0x4000                          /* Flag in sytem property function pointer             */
#define PROP_SYSFUNC_OBJECT_ID              (PROP_SYS_FUNC | 0x00)          /* The ID of the object ID function (read only)        */
#define PROP_SYSFUNC_DEV_PEI_TYPE           (PROP_SYS_FUNC | 0x01)          /* The ID of the PEI type device function (read/write) */
#define PROP_SYSFUNC_DEV_CONTROL            (PROP_SYS_FUNC | 0x02)          /* The ID of the device control function (read/write)  */
#define PROP_SYSFUNC_LOAD_CONTROL           (PROP_SYS_FUNC | 0x03)          /* The ID of the load control function (read/write)    */
#define PROP_SYSFUNC_RUN_CONTROL_APP        (PROP_SYS_FUNC | 0x04)          /* The ID of the app run control function (read/write) */
#define PROP_SYSFUNC_RUN_CONTROL_PEI        (PROP_SYS_FUNC | 0x05)          /* The ID of the PEI run control function (read/write) */
#define PROP_SYSFUNC_MCB_TABLE              (PROP_SYS_FUNC | 0x06)          /* The ID of the MCB table function (read only)        */
#define PROP_SYSFUNC_RTTABLE_CTRL           (PROP_SYS_FUNC | 0x07)          /* The ID of the route table control (read/write)      */


/****************************************************
*   结构名：T_KNXPROP_DESC
*   描述：  knx property description structure.
*   参数：  BYTE ucPropId       :  Property ID                        
            BYTE ucTypeFlg      :  Bit0-Bit5:Type code of property;
                                   Bit6:function flag.
                                   Bit7:writebility flag,1-writeable. 
            BYTE ucMaxElemHi    :  High byte of max. count of elements
            BYTE ucMaxElemtLo   :  Low byte of max. count of elements 
            BYTE ucAccess       :  Read and write access rights       
            WORDPTR dwAccessAdd :  Data or function's address.        
*   修改记录：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE    ucPropId;               /* Property ID                         */
    BYTE    ucTypeFlg;              /* Bit0-Bit5:Type code of property;
                                       Bit6:function flag.
                                       Bit7:writable flag,1-writable.      */
    BYTE    ucMaxElemHi;            /* High byte of max. count of elements */
    BYTE    ucMaxElemtLo;           /* Low byte of max. count of elements  */
    BYTE    ucAccess;               /* Read and write access rights        */
    WORDPTR dwDestAddr;             /* Data offset or function's address.  */
}T_KNXPROP_DESC;
#pragma pack()

/**************************************************************************************************************
* 函数名称：VOID KnxProp_PreparePropResp(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：prepare the property operation response data.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_PreparePropResp(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_ReadInvalidProperty(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：the property is invalid,we set the invalid response.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_ReadInvalidProperty(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：WORDPTR KnxProp_GetObjectRef(BYTE ucObIndex)
* 功能描述：Get the object pointer.
* 输入参数：BYTE ucObIndex:the object index.
* 输出参数：no.
* 返 回 值：the pointer of the object.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORDPTR KnxProp_GetObjectRef(BYTE ucObIndex);

/**************************************************************************************************************
* 函数名称：WORDPTR KnxProp_GetPropertyRef(BYTE *pucUpFrame)
* 功能描述：Get the property pointer.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
* 输出参数：no.
* 返 回 值：the pointer of the property.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORDPTR KnxProp_GetPropertyRef(BYTE ucObIndex,BYTE ucPropId);

/**************************************************************************************************************
* 函数名称：WORD16 KnxProp_GetPropMaxLength(WORDPTR dwPropRef)
* 功能描述：get the property's max element length.
* 输入参数：WORDPTR dwPropRef : reference pointer of the property.
* 输出参数：no.
* 返 回 值：max length of the property.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORD16 KnxProp_GetPropMaxLength(WORDPTR dwPropRef);

/**************************************************************************************************************
* 函数名称：BYTE KnxProp_GetPropValueLength(WORDPTR dwPropRef)
* 功能描述：get the property's element length.
* 输入参数：WORDPTR dwPropRef : reference pointer of the property.
* 输出参数：no.
* 返 回 值：length of the property(in byte).
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxProp_GetPropValueLength(WORDPTR dwPropRef);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_PropIsFunction(WORDPTR dwPropRef)
* 功能描述：Check if a property is a function property.
* 输入参数：WORDPTR dwPropRef : reference pointer of the property.
* 输出参数：no.
* 返 回 值：TRUE or FALSE.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_PropIsFunction(WORDPTR dwPropRef);

/**************************************************************************************************************
* 函数名称：WORDPTR KnxProp_GetPropPointer(WORDPTR dwPropRef)
* 功能描述：get the pointer defined in the property description(the address for saving data).
* 输入参数：WORDPTR dwPropRef : reference pointer of the property.
* 输出参数：no.
* 返 回 值：WORDPTR,the defined address.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORDPTR KnxProp_GetPropPointer(WORDPTR dwPropRef);

/**************************************************************************************************************
* 函数名称：WORD16 KnxProp_GetPropActualLength(WORDPTR dwPropRef)
* 功能描述：get the property's actual data length.
* 输入参数：WORDPTR dwPropRef : reference pointer of the property.
* 输出参数：no.
* 返 回 值：actual count of values.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORD16 KnxProp_GetPropActualLength(WORDPTR dwPropRef);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_CheckPropAccessAbility(BYTE *pucUpFrame,BYTE ucOpMode)
* 功能描述：get the property's read or write ability.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE ucOpMode   :read or write mode flag.
                             PROP_READ_MODE : check the read ability.
                             PROP_WRITE_MODE: check the write ability.
* 输出参数：no.
* 返 回 值：TRUE or FLASE.
* 其它说明：if the property can be read or written,we will return TRUE.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_CheckPropAccessAbility(BYTE *pucUpFrame,BYTE ucOpMode);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_PropertyValueLenRead(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：get the actual length of a property.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_PropertyValueLenRead(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：WORDPTR KnxProp_GetPropertyValueRef(WORDPTR dwPropRef,WORD16 wValIndex)
* 功能描述：retrieves the pointer to the indexed value of the given property
            in virtual memory address space.
* 输入参数：WORDPTR dwPropRef:property reference;
            WORD16 wValIndex:value index;
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
WORDPTR KnxProp_GetPropertyValueRef(WORDPTR dwPropRef,WORD16 wValIndex);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_GetPropertyValue(WORDPTR dwPropRef,WORD16 wValIndex,BYTE *pucDwBuffer)
* 功能描述：retrieves the indexed value of the given property.
* 输入参数：WORDPTR dwPropRef:property reference;
            WORD16 wValIndex:value index;
            BYTE *pucDwBuffer:destination buffer;
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_GetPropertyValue(WORDPTR dwPropRef,WORD16 wValIndex,BYTE *pucDwBuffer);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_PropertyValueMemRead(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：get property value via standard access to virtual memory.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_PropertyValueMemRead(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_ValueRead(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：get the pointed property value.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_ValueRead(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_SetPropertyActualLength(WORDPTR dwPropRef,WORD16 wLength)
* 功能描述：sets the actual count of values of a given property.
* 输入参数：WORDPTR dwPropRef:property pointer.
            WORD16 wlength:actual length.
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：only the array properties can be set the actual length.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_SetPropertyActualLength(WORDPTR dwPropRef,WORD16 wLength);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_PropertyValueLenWrite(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：write the actual length of a property.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：the only allowwed length is 0 to reset the array.
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_PropertyValueLenWrite(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_SetPropertyValue(WORDPTR dwPropRef,WORD16 wValuIndex,BYTE *pucData)
* 功能描述：writes the indexed value of the given property.
            The value will be copied byte per byte from pBuffer.
* 输入参数：WORDPTR dwPropRef:property reference;
            WORD16 wValIndex:value index;
            BYTE *pucData:source buffer;
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_SetPropertyValue(WORDPTR dwPropRef,WORD16 wValuIndex,BYTE *pucData);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_PropertyValueMemWrite(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：write property value via standard access to virtual memory.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_PropertyValueMemWrite(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncObjectId(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the object ID property of system objects
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncObjectId(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncDevPeiType(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：This function handles the access to the PEI type
            property of the device object; If a PEI is implemented
            this function should retrieve the current connected
            PEI type via a ADC read; Here we have no PEI and the
            function retrieves 0x00 as PEI type.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncDevPeiType(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncDevCtrl(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the device control property of the device object
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncDevCtrl(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncLoadStateCtrl(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the load control property of the address table, assoc table ,application
            and router table object.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncLoadStateCtrl(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncRunStateApp(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the run state control property of the application object
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncRunStateApp(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncRunStatePei(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the run state control property of the PEI program object
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncRunStatePei(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncMcbTable(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the MCB tables
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncMcbTable(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxProp_FuncRouteTableControl(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：handles the access to the router table.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：TRUE or FALSE
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_FuncRouteTableControl(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_ValueWrite(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：property value write.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxProp_PropertyFunction(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_ValueWrite(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：property value write.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_ValueWrite(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BYTE KnxProp_GetPropertyId(BYTE ucObIndex,BYTE ucPropIndex)
* 功能描述：retrieves the property ID of a property that is given by object index and an property index
* 输入参数：BYTE ucObIndex  : object index.
            BYTE ucPropIndex: property index.
* 输出参数：no.
* 返 回 值：BYTE property ID.PID_ID_ERROR:wrong ID.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BYTE KnxProp_GetPropertyId(BYTE ucObIndex,BYTE ucPropIndex);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_DescriptionRead(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：property description read.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_DescriptionRead(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：BOOL KnxLocal_FnctFilterTableCtrl(BYTE *pucSrcBuf,BYTE *pucDestBuf,BYTE *ucLen)
* 功能描述：CEMI router table control property service.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：BYTE *ucLen : data length.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
BOOL KnxLocal_FnctFilterTableCtrl(BYTE *pucSrcBuf,BYTE *pucDestBuf,BYTE *ucLen);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_InvalidFuncOperate(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：the property is invalid,we set the invalid response.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_InvalidFuncOperate(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_FunctionPropHandle(BYTE *pucUpFrame,BYTE *pucDwFrame)
* 功能描述：function property operation.
* 输入参数：BYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:response frame buffer's pointer
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_FunctionPropHandle(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* 函数名称：VOID KnxProp_GetSerialNo(BYTE *pucSerNo)
* 功能描述：read serial number and set to the user's buffer.
* 输入参数：BYTE *pucSerNo:user's data buffer pointer.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
VOID KnxProp_GetSerialNo(BYTE *pucSerNo);


#ifdef __cplusplus
}
#endif

#endif /* _KNX_PROP_H_ */



/* End of file. */

