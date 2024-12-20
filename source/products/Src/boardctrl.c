/********************************************************************
* Right reserved (C 2019) Shufan information technology company.
*
* File Name        : boardctrl.c
*
* File Description : stm32f10xx demo board control.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : Danny Cao
*
* Data             : 2019.4.1
*
* Modification Rec.:
*   Modify Data    : 2019.4.1
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
********************************************************************/

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Buffer.h"
#include "boardcfg.h"
#include "boardctrl.h"
#include "hardware.h"
#include "Stm32g0xx_systick.h"
#include "Stm32G0XX_Flash.h"
#include "Stm32G0xxx_adc.h"
#include "stm32g0xx_iwdg.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "app_common.h"
#include "Common_media.h"
#include "Knx_Prop.h"
#include "Application.h"
#include "Math_service.h"
#include "Comm_service.h"
#include "Knx_InternalApp.h"
#include "Application.h"
#include "Application_Data.h"
#include "Knx_Timer.h"
#include "knx_chip.h"
#include "knx_M0705_Ll.h"
#include "Knx_M0705.h"
#include "Knx_mem.h"

BYTE   sg_ucKeySt=0;
WORD32 sg_adwKeyPressTm[4]={0,0,0,0};
extern BYTE is_prgm_mode;



/********** peripheral devices table *******************/

const T_DEV_DISC sg_tDeviceTable[5]=\
{
    {
        /* ucAppType     */ SW_CONTROL_INTERFACE,\
        /* ucDevId       */ SW_PERIPHERAL_TIMER, \
        /* ucLogDevlNo   */ TIMER_LOGIC_NO,      \
        /* ucDevNo       */ TIMER_PHYSICAL_NO,   \
        /* pfDevRegister */ SysTick_Reg
    },
    {
        /* ucAppType     */ SW_SAVE_INTERFACE,  \
        /* ucDevId       */ SW_PERIPHERAL_FLASH,\
        /* ucLogDevlNo   */ FLASH_LOGIC_NO,     \
        /* ucDevNo       */ FLASH_PHYSICAL_NO,  \
        /* pfDevRegister */ Stm32G0xxx_Flash_Reg
    },
    {
        /* ucAppType     */ SW_MATH_INTERFACE,\
        /* ucDevId       */ SW_PERIPHERAL_AD, \
        /* ucLogDevNo    */ AD_LOGIC_NO,      \
        /* ucDevNo       */ AD_PHYSICAL_NO,   \
        /* pfDevRegister */ ADC_Reg
    },
    {
        /* ucAppType     */ 0,\
        /* ucDevId       */ 0,\
        /* ucLogDevNo    */ 0,
        /* ucDevNo       */ 0,\
        /* pfDevRegister */ NULL
    }
};

/********** Table for mapping AD channel *******************
 Note: Developers should change this table according to the
       real hardware design. 0 to 7 is kept for KNX stack,
       and others is kept for application. If a channel is
       idle, it's physical number should be set as 0xFF.
************************************************************/
BYTE sg_aucAdChnlMap[16]=\
    {
           /* Logic Port Num*/     /* Physical AD Port */
                                    /* For KNX stack */   
              /* 00 */               SW_NONE_MEANING,                         \
              /* 01 bus voltage  */  0,                                       \
              /* 02 */               SW_NONE_MEANING,                         \
              /* 03 */               SW_NONE_MEANING,                         \
              /* 04 */               SW_NONE_MEANING,                         \
              /* 05 */               SW_NONE_MEANING,                         \
              /* 06 */               SW_NONE_MEANING,                         \
              /* 07 */               SW_NONE_MEANING,                         \
                                    /* For application */
              /* 08 */               1,                         \
              /* 09 */               SW_NONE_MEANING,                         \
              /* 10 */               4,                         \
              /* 11 */               7,                         \
              /* 12 */               2,                         \
              /* 13 */               3,                         \
              /* 14 */               SW_NONE_MEANING,                         \
              /* 15 */               SW_NONE_MEANING,                         \
    };


/*************************************************************************
* 函数名称：VOID Prdt_PortsInit(VOID) 
* 功能说明：产品相关端口初始化。
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
void Prdt_PortsInit(void)
{
    /* Lvkong demo-kit 103
      Chip 2 Mcu                 PA9    I
      Mcu  2 Chip Ctrl           PA7    O  1 enable
      Run-Led                    PA5    O  0-on

      KNX-ok                     PC13   I

      Prg-key                    PB10   I  0-pressed
      Prg-Led                    PB0    O  0-on
    */
    RCC_IOPENR  |= (RCC_IOPENR_GPIOAEN     | RCC_IOPENR_GPIOBEN   | RCC_IOPENR_GPIOCEN);
    RCC_IOPRSTR |= (RCC_IOPRSTR_GPIOARST   | RCC_IOPRSTR_GPIOBRST | RCC_IOPRSTR_GPIOCRST);
    RCC_IOPRSTR &= (~(RCC_IOPRSTR_GPIOARST | RCC_IOPRSTR_GPIOBRST | RCC_IOPRSTR_GPIOCRST));

    /************************ Port A set. *****************************************/
    GPIOA->MODER   &= GPIO_MODE_MASK_PA;
    GPIOA->MODER   |= GPIO_MODER_MODER5_0     | GPIO_MODER_MODER7_1 | GPIO_MODER_MODER9_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR5_1 | GPIO_OSPEEDR_OSPEEDR7;
    GPIOA->PUPDR   |= GPIO_PUPDR_PUPDR9_0;
    GPIOA->AFR[0]  |= 0x10000000;                     /* PA7:AF1 PA9:AF2 */
    GPIOA->AFR[1]  |= 0x00000020;                     /* PA7:AF1 PA9:AF2 */

    /*********************** Port B set. ******************************************/
    SYSCFG->CFGR1  |= SYSCFG_CFGR1_UCPD1_STROBE;
    GPIOB->MODER   &= GPIO_MODE_MASK_PA_EX;
    GPIOB->MODER   |= GPIO_MODER_MODER0_0;
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0_1;
    GPIOB->PUPDR   |= GPIO_PUPDR_PUPDR10_0;
    
    GPIOB->MODER   &= GPIO_MODE_MASK_PA_EX;
    GPIOB->MODER   |= GPIO_MODER_MODER7_0   |GPIO_MODER_MODER8_0 |GPIO_MODER_MODER9_0 | GPIO_MODER_MODER12_0;
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_0 | GPIO_OSPEEDR_OSPEEDR8_0|GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR12_0;
    
    /********************** Port C set. ****************************************/
    GPIOC->MODER   &= GPIO_MODE_MASK_PA_EX;              /* KNX OK */
    GPIOC->PUPDR   |= GPIO_PUPDR_PUPDR13_0;
    SET_RUN_LED_OFF;
    SET_KNX_LED_OFF;                                     /* Program LED OFF            */                      
    
    return;
}

/*************************************************************************
* 函数名称：BOOL BoardCtrl_AdRead(BYTE ucLogDevNo,BYTE ucLogChnlNo,BYTE ucCunt,WORD16 *pwData)
* 功能说明：get AD data.
* 输入参数：BYTE ucLogDevNo : logical device No.
            BYTE ucLogChnlNo: logical channel No.
            BYTE ucCunt     : sample count.
            WORD16 *pwData  : pointer of retuen data.
* 输出参数：WORD16 *pwData  : return AD data.
* 返 回 值：TRUE : get successfully.
            FALSE: get failed.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL BoardCtrl_AdRead(BYTE ucLogDevNo,BYTE ucLogChnlNo,BYTE ucCunt,WORD16 *pwData)
{
    T_SW_DEVICEDRIVER_PARA tDevPara;
    
    /* start conversion. */
    tDevPara.ucPara[0]  = SW_PERIPHERAL_AD;
    tDevPara.ucPara[1]  = ucLogDevNo;
    tDevPara.ucPara[2]  = ucLogChnlNo;
    tDevPara.ucPara[3]  = SW_ADC_SOFT_START;
    API_MathDrv_Ctrl(&tDevPara);
    /* get AD data. */
    API_MathDrv_Read(ucLogDevNo,1,pwData);
    
    if(PIN_SAVE_SIGNAL)
    {
        /* power down. */
        *pwData = 0;
    }
    else
    {
        *pwData = 0x0644;  /* 30 v */
    }

    return TRUE;
}

/*************************************************************************
* 函数名称：VOID BoardCtrl_Init(VOID) 
* 功能说明：设备描述初始化。
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
VOID BoardCtrl_Init(VOID) 
{
    T_DEV_DISC             *ptDev = (T_DEV_DISC*)sg_tDeviceTable;
    T_SW_DEVICEDRIVER_PARA tDevPara;
    
    /* Ports init. */
    Prdt_PortsInit();
    
    /* initialize the rxtx pool. */
    Buffer_Pool_Init();
#if(DEBUG_ONOFF)
    Application_Para_Debug();
#endif
    while(SW_NA_INTERFACE != ptDev->ucAppType)
    {
        if((SW_PERIPHERAL_FLASH == ptDev->ucDevId)&&(SW_SAVE_INTERFACE == ptDev->ucAppType))
        {
            /* flash device. */
            T_FLASH_TMOPER tFlashTmOp;

            tFlashTmOp.pfAppCheck = KnxLl_HaveToWaitCheck;
            ptDev->pfDevRegister(ptDev->ucLogDevNo,ptDev->ucDevNo,(VOID *)(&tFlashTmOp));
        }
        else
        {
            ptDev->pfDevRegister(ptDev->ucLogDevNo,ptDev->ucDevNo,NULL);   /* register device. */
        }
        ptDev++;
    }
    /* flash initialize. */
    API_Common_Media_Init();
    API_MediaDev_Init(SW_SAVE_INTERFACE,FLASH_LOGIC_NO,NULL);
    /* AD initialization. */
    tDevPara.ucPara[0]  = SW_PERIPHERAL_AD;
    tDevPara.ucPara[1]  = 0;
    tDevPara.ucPara[2]  = 0;
    tDevPara.ucPara[3]  = SW_ADC_CONFIGURE;
    tDevPara.ucPara[4]  = (SW_ADC_LOWEST_SPEED | SW_ADC_TRIGGER_SOFT | SW_ADC_SINGLE_CHL);
    tDevPara.ucPara[5]  = 0;
    tDevPara.ucPara[6]  = ADC_OVERSMPLE_64;
    tDevPara.pdwPara[0] = 0x0000001;                             /* physical channel 0. */
    tDevPara.pucBuf     = sg_aucAdChnlMap;
    tDevPara.pIntCallBackHandler = NULL;
    API_MathDrv_Init(&tDevPara);
        
    /* KNX chip register. */
    KnxPh_Register();

    return;
}

/*************************************************************************
* 函数名称：BOOL Board_PrgmLed_Off(VOID)
* 功能说明：编程指示灯灭
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_PrgmLed_Off(VOID)
{
    SET_KNX_LED_OFF;
    return TRUE;
}

/*************************************************************************
* 函数名称：BOOL Board_PrgmKey_Handle(VOID)
* 功能说明：编程按钮状态判断
* 输入参数：无
* 输出参数：无
* 返 回 值：TRUE:编程按钮按下
            FALSE:编程按钮未按下
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_PrgmKey_Handle(VOID)
{
    return KNX_KEY_PORT;
}

/*************************************************************************
* 函数名称：BOOL Board_PrgmLed_On(VOID)
* 功能说明：编程指示灯亮
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_PrgmLed_On(VOID)
{
    is_prgm_mode=1;

    SET_KNX_LED_ON;
    return  TRUE;
}

/*************************************************************************
* 函数名称：BOOL Board_SavePin_Check(VOID)
* 功能说明：判断总线掉电管脚是否有掉电。
* 输入参数：无
* 输出参数：无
* 返 回 值：TRUE:出现总线掉电
            FALSE:没有总线掉电
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_SavePin_Check(VOID)
{
    return PIN_SAVE_SIGNAL;
}

/***************************************************************************************
* 函数名称：BOOL Board_CheckMasterReset(VOID)
* 功能说明：检查是否需要进行上电恢复默认设置。
* 输入参数：无
* 输出参数：无
* 返 回 值：TRUE:要恢复
            FALSE:不要恢复
* 其它说明：if Programming key is pressed over MASTER_RESET_TIME seconds at the start,
            we will reset the device to the default status.
* 修改日期     版本号     修改人      修改内容
* --------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
****************************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_CheckMasterReset(VOID)
{
    WORD32 dwPressTime,dwTimeDiff;

	/* Check programming key status. */
    if(KNX_KEY_PORT)
    {
        dwPressTime = API_KnxTm_GetTimeMs();
        while(1)
        {
            dwTimeDiff = API_KnxTm_GetDelayMs(dwPressTime);
            if(dwTimeDiff < 100)
            {
                /* de-bounce 50ms. */
                continue;
            }
            if((dwTimeDiff >= MASTER_RESET_TIME)&&(KNX_KEY_PORT))
            {
                return TRUE;
            }
            else if(!KNX_KEY_PORT)
            {
                break;
            }
        }
    }

    return FALSE;
}

/**************************************************************************
* function name   : BOOL BoardCtrl_Reset(VOID)
* Description     : reset the device.
* Input parameter : no.
* Output parameter: no.
* Return          : TRUE :successfully.
                    FALSE:failed.
* Other description:
* Modify date     Ver.     Modifier      Action
* ------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
**************************************************************************/
BOOL BoardCtrl_Reset(VOID)
{
    WORD32 dwAircr,dwResCnt = 0xffffffffu;
    
    dwAircr  = SCB->AIRCR;
    dwAircr &= 0x0000ffffu;
    dwAircr |= 0x05FA0004u;
    /* reset the cpu. */
    SCB->AIRCR = dwAircr;
    while(dwResCnt)
    {
        dwResCnt--;
    }
    
    return TRUE;
}

/* 
   Attention: if you want to set your device's serial number automaticall, you can define this macro. 
              Theoretically each device should have a unique serial number. It can be set in factory.
              Here we set it by software.Hardware should have a capacitance with big capacity in order
              to save the data on power fail.
*/
#if DEFINE_AUTO_SER_SERIAL_NUMBER
/***************************************************************************************
* Func. Name: VOID BrdCtrl_CheckFacId(VOID)
* Func. Description: check if we have right factory data.
* Input para. : no.
* Output para.: no.
* Return      : no.
* Other description: 
*            Attention : if you change factory ID via a bus tool, the checking result
*                        maybe is different with the factory ID in code. So be careful
*                        please.
* Date       Version     Modifier   Content
* --------------------------------------------------------------------------------------
* 2021-07-08   V1.00                 create
****************************************************************************************/
VOID BrdCtrl_CheckFacId(VOID)
{
    BYTE ucCheck;
    
    /* first we check factory ID. */
    ucCheck = API_KnxMem_GetByte(VIR_MANUFACT_ID);
    if(ucCheck != GET_HIBYTE(VALUE_FACTORY_ID))
    {
        KnxMem_MediaRecoveDefault();
        return;
    }
    ucCheck = API_KnxMem_GetByte(VIR_MANUFACT_ID + 1);
    if(ucCheck != GET_LOWBYTE(VALUE_FACTORY_ID))
    {
        KnxMem_MediaRecoveDefault();
    }
    
    return;
}

/***************************************************************************************
* 函数名称：VOID BrdCtrl_CheckSetSerNo(VOID)
* 功能说明：check if we have already set the serial number.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* --------------------------------------------------------------------------------------
* 2021-07-08   V1.00                   创建
****************************************************************************************/
VOID BrdCtrl_CheckSetSerNo(VOID)
{
    BYTE   aucCpuId[6],aucSerNo[6],ucIndex;
    WORD32 dwBaseAddr = STM32G070_MCUID_START;
    
    for(ucIndex=0;ucIndex<6;ucIndex++)
    {
        aucSerNo[ucIndex] = API_KnxMem_GetByte(VIR_SERIAL_NO+ucIndex);
    }
    for(ucIndex=0;ucIndex<12;)
    {
        aucCpuId[ucIndex/2]  = *(BYTE*)(dwBaseAddr + ucIndex);
        aucCpuId[ucIndex/2] ^= *(BYTE*)(dwBaseAddr + ucIndex + 1);
        ucIndex += 2;
    }
    for(ucIndex=0;ucIndex<6;ucIndex++)
    {
        if(aucSerNo[ucIndex] != aucCpuId[ucIndex])
        {
            /* we need to write new serial No. into the device. */
            API_KnxMem_WriteData(VIR_SERIAL_NO,aucCpuId,6);
            API_KnxMem_WriteFinished();
            break;
        }
    }
    
    return;
}
#endif

/***************************************************************************************
* 函数名称：BOOL VOID BoardCtrl_Set(VOID)
* 功能说明：set device working parameters.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：no.
* 修改日期     版本号     修改人      修改内容
* --------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
****************************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
VOID BoardCtrl_Set(VOID)
{
    BOOL ucCheck;
  
    /* set the Application handler.every productor has to set the handlers. */
    API_Knx_UserAppHandler_Set((VOID*)Application_Process,APP_HANDLER_MAIN);
    /* set the handler for application initiation. */
    API_Knx_UserAppHandler_Set((VOID*)Application_Init,APP_HANDLER_INIT);
    /* set application save handler in running halt/stop. before running stop/halt stack will call 
    this handler to save the user's data. */
    API_Knx_UserAppHandler_Set((VOID*)Application_Save,APP_HANDLER_SAVE);
    /* set application bus voltage down saving handler. when bus voltage down stack will call
    this handler to save the user's data. */
    API_Knx_UserAppHandler_Set((VOID*)Application_BusSave,APP_HANDLER_BUS_SAVE);
    /* set application power down saving handler. when power down stack will call
    this handler to save the user's data. */
    API_Knx_UserAppHandler_Set((VOID*)Application_PowerSave,APP_HANDLER_POWER_SAVE);
    /* set watchdog reset handler. */
    API_Knx_UserAppHandler_Set((VOID*)NULL,APP_HANDLER_WDG_RESET);
    /* set CPU reset handler */
    API_Knx_UserAppHandler_Set((VOID*)BoardCtrl_Reset,APP_HANDLER_RESET_CPU);
    /* set program led off handler */
    API_Knx_UserAppHandler_Set((VOID*)Board_PrgmLed_Off,APP_HANDLER_PRGM_LED_OFF);
    /* set program led oN handler */
    API_Knx_UserAppHandler_Set((VOID*)Board_PrgmLed_On,APP_HANDLER_PRGM_LED_ON);
    /* set program key press handler */
    API_Knx_UserAppHandler_Set((VOID*)Board_PrgmKey_Handle,APP_HANDLER_PRGM_KEY);
    /* set bus power down check handler */
    API_Knx_UserAppHandler_Set((VOID*)Board_SavePin_Check,APP_HANDLER_BUS_POWER_CHECK);
    /* set AD operation handler. */
    API_Knx_UserAppHandler_Set((VOID*)BoardCtrl_AdRead,APP_HANDLER_ADC_OP);
    /**********************************************************************/    
    /* start the knx timer. */
    Hw_SetIntPriority(SysTick_IRQn,2); 
    /* Timer initialization will be done. */
    API_KnxTm_TimerInit(TIMER_LOGIC_NO);
    API_RecTable_OpInit(FLASH_LOGIC_NO,FLASH_WRT_SIZE);
    /* check master reset. 
          Attention: You should modify Board_CheckMasterRest function in BoardCtrl.c according to your application. */
    ucCheck = Board_CheckMasterReset();
    if(TRUE == ucCheck)
    {
        /* proframming key has been pressed over MASTER_RESET_TIME. */
        API_KnxMem_MediaRecoveDefault();
    }
    /* Init the media.check it's status. */
    API_KnxMem_InitMedia(FLASH_LOGIC_NO);
    /* record table clean up. */
    API_RecTable_CleanUpTable();
    /* KNX application layer management initialization. */
    API_Knx_AlMgmInit();
    /* KNX  virtual RAM memory management initialization. */
    API_KnxMem_VirRamInit();
    /* KNX virtual memory management initialization. */
    API_KnxMem_Init();

    /* KNX message process initialization. */
    API_Knx_MsgInit();

    /* register the uart device to knx link layer. */
    API_KnxLl_DevReg(KNX_CHIP_LOGIC_NO,KNX_CHIP_PH_NO,RX_BUFFER_NUMBER,TX_BUFFER_NUMBER);

    /* Knx link layer initalization. */
    API_KnxLl_Init(TX_BUFFER_NUMBER,TX_PHY_BUFFER_SIZE);

    /* priority set. */
    Hw_SetIntPriority(TIM3_IRQn,0);
    Hw_SetIntPriority(TIM1_CC_IRQn,1);
    /* Open interrupt. */
    Hw_InterruptEn(TIM1_CC_IRQn);
    Hw_InterruptEn(TIM3_IRQn);
    
#if DEFINE_AUTO_SER_SERIAL_NUMBER
    /* BrdCtrl_CheckFacId();  */                              /* if you want this, you can open it. */
    BrdCtrl_CheckSetSerNo();
#endif
    /* initializing the wathchdog,2000ms period. */
    API_Knx_UserAppHandler_Set((VOID*)Stm32G0xx_Iwdg_Reset,APP_HANDLER_WDG_RESET);
    Stm32G0xx_Iwdg_Init(2000);

    return;
}

/* check key state. */
BYTE Get_Input(BYTE ucChNum)
{
    return 0;
}

/* control led. */
void Set_Output(BYTE ucChnlNo, BYTE ucOnOff)
{
    return;
}


/* End of file */

