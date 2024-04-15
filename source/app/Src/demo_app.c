/******************************************************************************
* 版权所有 (C)2013，**************公司
*
* 文件名称：demo_app.c
* 文件标识：无
* 内容摘要：demo application for education.
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

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "app_common.h"
#include "Hardware.h"
#include "Knx_Prop.h"
#include "Rec_Table.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "Application.h"
#include "Knx_AlApp.h"
#include "demo_app.h"
#include "App_Api.h"
#include "boardctrl.h"
#include "co2_sensor.h"
#include "demo.h"


BYTE CO2value[2],ucPara,CO2updateflag;



/**************************************************************************
* 函数名称： App_Data_Init(void)
* 功能描述： Initialize the demo application data.
* 输入参数： no.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Init(void)
{
    
    ; 
    
}

/**************************************************************************
* 函数名称： VOID Demo_App_Forced_Run(BYTE ucInputNo)
* 功能描述： handle the force function happening on the input channel.
* 输入参数： BYTE ucInputNo : the NO. of the input channel.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Forced_Run(BYTE ucInputNo)
{
    ;
}

/**************************************************************************
* 函数名称： VOID Demo_App_Scene_Run(BYTE ucInputNo)
* 功能描述： handle the scene function happening on the input channel.
* 输入参数： BYTE ucInputNo : the NO. of the input channel.z
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Scene_Run(BYTE ucInputNo)
{
    ;
}

/**************************************************************************
* 函数名称： VOID Demo_App_Switch_Run(BYTE ucInputNo)
* 功能描述： handle key input function.
* 输入参数： BYTE ucInputNo : the NO. of the input channel.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Switch_Run(BYTE ucInputNo)
{
    ;
}

/**************************************************************************
* 函数名称： void Demo_App_Out_Run(BYTE ucOutputNo)
* 功能描述： handle output function.
* 输入参数： BYTE ucOutputNo : the NO. of the output channel.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Out_Run(BYTE ucOutputNo)
{
    ;
}

/**************************************************************************
* 函数名称： App_Data_Init(void)
* 功能描述： Initialize the demo application data.
* 输入参数： no.
* 输出参数： no.      
* 返 回 值： no.
* 其它说明： no.
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
uint16_t int32_to_custom_float16(int32_t int32) ;
void Demo_App_Run(void)
{
    static WORD32 TimesMsRef;
    BYTE sensorvalue[4];
    static bool enable = true;
    
    if(co2_sensor_knx_bus.co2_valueflag== 1)
    {
        *(WORD32*)sensorvalue=(WORD32)co2_sensor_knx_bus.co2_value*100;
        DataConvert_Int32ToFloat(sensorvalue);
        API_KnxAl_SetCoValue(CO2_VALUE_CO,&sensorvalue[0]);
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite(CO2_VALUE_CO); 
        
        co2_sensor_knx_bus.co2_valueflag= 0;
    }
    //  co2_sensor_Loop();
    
    
    if ( API_KnxTm_GetDelayMs( TimesMsRef ) >= 200 )
    {
        co2_sensor_knx_bus.co2_valueflag= 1;
        enable = true;
        demoCycle(enable);
        enable = false;
        TimesMsRef = API_KnxTm_GetTimeMs();
    }
    else
    {
        demoCycle(enable);
        enable = false;
    }
}


/******************************************************************
The following function was used to convert 2 bytes float data to short
currently only processed postive date

*******************************************************************/
void DataConvert_FloatToInt(BYTE *pData)
{
    WORD16 converrvalue;
    BYTE indexnumer;
    
    indexnumer = ((pData[0] & 0x78)>>3);
    converrvalue = ((pData[0] & 0x07)<<8) + pData[1] ;
    
    for(;indexnumer>=1;indexnumer--)
    {
        converrvalue = converrvalue * 2;
    }
    pData[1] = (BYTE)(converrvalue & 0xff);
    pData[0] = (BYTE)((converrvalue >>8) & 0xff);
}


/******************************************************************
The following function was used to convert short to 2 bytes float data 
currently only processed postive date

*******************************************************************/
void DataConvert_IntToFloat(BYTE *pData)
{
    WORD16 converrvalue;
    BYTE indexnumer;
    
    converrvalue = (pData[0] <<8) + pData[1] ;
    indexnumer = 0;
    
    
    for(;converrvalue> 0x7ff;)
    {
        converrvalue = converrvalue /2;
        indexnumer++;
    }
    pData[1] = (BYTE)(converrvalue & 0xff);
    pData[0] = (BYTE)(((converrvalue >>8) & 0xff)|(indexnumer << 3));
}

void DataConvert_Int32ToFloat( BYTE *pData )
{
    WORD32 converrvalue;
    BYTE indexnumer;
    
    converrvalue = ( pData[3] << 24 ) + ( pData[2] << 16 ) + ( pData[1] << 8 ) + pData[0];
    indexnumer = 0;
    
    
    for( ; converrvalue > 0x7ff; )
    {
        converrvalue = converrvalue / 2;
        indexnumer++;
    }
    pData[1] = ( BYTE )( converrvalue & 0xff );
    pData[0] = ( BYTE )( ( ( converrvalue >> 8 ) & 0xff ) | ( indexnumer << 3 ) );
}

/**
* @description: swap big-endian or little-endian to another type
* @param {none} 
* @return: none
* @date 2023/9/2
* example: swapEndian(&value16, sizeof(value16));
*/
void swapEndian(void* data, size_t size)
{
    uint8_t* byteData = (uint8_t*)data;
    uint8_t temp;
    
    for (size_t i = 0; i < size / 2; ++i)
    {
        temp = byteData[i];
        byteData[i] = byteData[size - 1 - i];
        byteData[size - 1 - i] = temp;
    }
}

uint16_t int32_to_custom_float16(int32_t int32) {
    uint16_t f16 = 0;
    uint32_t absVal, tempVal;
    int32_t exp = 0;
    uint32_t sign = 0;
    
    // 检查符号位，并取绝对值
    if (int32 < 0) {
        sign = 1;
        absVal = -int32; // 如果是负数，取反加1得到绝对值
    } else {
        absVal = int32;
    }
    
    // 特殊情况：如果整数是0，直接返回0
    if (absVal == 0) return 0;
    
    // 计算指数和尾数
    tempVal = absVal;
    while (tempVal > 0) {
        tempVal >>= 1;
        exp++;
    }
    
    // 调整尾数以适应11位空间
    // exp-1因为指数是从最高位1开始计算的，例如如果absVal是1（即2^0），exp应该是0
    int shiftAmount = exp - 12;
    uint32_t mantissa = (shiftAmount > 0) ? (absVal >> shiftAmount) : (absVal << -shiftAmount);
    
    // 组合成16位浮点数
    // 限制指数范围，以适应4位指数位
    if (exp > 15) {
        exp = 15;
    } else if (exp < 1) {
        exp = 1; // 非零值的最小指数
    }
    
    f16 = (sign << 15) | ((exp & 0xF) << 11) | (mantissa & 0x7FF);
    
    return f16;
}


u32_t GetSystemTime_ms(void)
{
    
    return(API_KnxTm_GetTimeMs());
}

void SystemDelay_ms(u32_t ms)
{
    u32_t start = API_KnxTm_GetTimeMs();
    while(API_KnxTm_GetTimeMs() - start < ms);
}

/* end of file. */

