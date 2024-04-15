/******************************************************************************
* 版权所有 (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* 文件名称：Main.c
* 文件标识：无
* 内容摘要：KNX应用源主函数文件，应用入口。
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
#include "Hardware.h"
#include "boardctrl.h"
#include "Knx_Run.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "stm32g0xx_iwdg.h"

#include "stm32g0xx_ll_usart.h" 
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx.h"
#include "main.h"
#include "co2_sensor.h"
#include "demo.h"
#include "spi.h"
#include "gpio.h"
#include "usart.h"

__IO uint8_t ubSend = 0;
uint8_t aStringToSend[] = "STM32G0xx USART LL API Example : TX in IT mode\r\nConfiguration UART 115200 bps, 8 data bit/1 stop bit/No parity/No HW flow control\r\n";
uint8_t ubSizeToSend = sizeof(aStringToSend);
uint8_t globalCommProtectCnt = 0; /*!< Global Protection counter */

extern uint32_t LL_Tick;
uint32_t LL_GetTick(void) {
    return LL_Tick;
}

///* Private function prototypes -----------------------------------------------*/
//static void MX_USART2_UART_Init(void);
void USART_SendStringData(unsigned char * datasource, unsigned char sendsize);

/**************************************************************************************************************
* 函数名称：void main(void)
* 功能描述：device software start entry.
* 输入参数：no.
* 输出参数：no.
* 返 回 值：no.
* 其它说明：
* 修改日期     版本号     修改人      修改内容
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   创建
***************************************************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
void main(void)
{
    system_base_clk();
    /* initializing productor board control . */
    BoardCtrl_Init();
    /* set the device working handler and parameters. */
    BoardCtrl_Set();
    
    MX_USART2_UART_Init();
    MX_GPIO_Init();
    MX_SPI1_Init();
    demoIni();
    
    while(1)
    {
        /* renew the cycle time. */
        API_KnxTm_UpdateCycle();
        /* get the programming key state and store it. */
        API_Knx_GetProgKey();
        /* set the programming LED. */
        API_Knx_SetPrgLed();
        /* process messages. */
        if(API_Knx_GetRunStateEx() < RUNSTATE_FLAG_SAVE_SUPPLY)
        {
            /* knx messages handling. */
            API_Knx_MsgProcess();
        }
        /* Run status management. */
        API_Knx_RunProcess();
        /* wdg. */
        Stm32G0xx_Iwdg_Reset();
    }
}          


/**
* @brief  Function called for achieving next TX Byte sending
* @param  None
* @retval None
*/
void USART_TXEmpty_Callback(void)
{
    if (ubSend == (ubSizeToSend - 1))
    {
        /* Disable TXE interrupt */
        LL_USART_DisableIT_TXE(USART2);
        
        /* Enable TC interrupt */
        LL_USART_EnableIT_TC(USART2);
    }
    
    /* Fill TDR with a new char */
    LL_USART_TransmitData8(USART2, aStringToSend[ubSend++]);
}

void USART_SendStringData(unsigned char * datasource, unsigned char sendsize)
{
    unsigned char i;
    for(i =0 ;i < sendsize; i++)
    {
        aStringToSend[i] = (datasource[i]);
    }
    ubSizeToSend = sendsize;
    ubSend = 0;
    
    /* Start USART transmission : Will initiate TXE interrupt after TDR register is empty */
    LL_USART_TransmitData8(USART2, aStringToSend[ubSend++]);
    
    /* Enable TXE interrupt */
    LL_USART_EnableIT_TXE(USART2);
    
}



/**
* @brief  Function called at completion of last byte transmission
* @param  None
* @retval None
*/
void USART_CharTransmitComplete_Callback(void)
{
    if (ubSend == sizeof(aStringToSend))
    {
        ubSend = 0;
        
        /* Disable TC interrupt */
        LL_USART_DisableIT_TC(USART2);
        
        /* Turn LED4 On at end of transfer : Tx sequence completed successfully */
        //  LED_On();
    }
}

/**
* @brief  Function called from USART IRQ Handler when RXNE flag is set
*         Function is in charge of reading character received on USART RX line.
* @param  None
* @retval None
*/
void USART_CharReception_Callback(void)
{
    uint8_t received_char;
    
    /* Read Received character. RXNE flag is cleared by reading of RDR register */
    received_char = LL_USART_ReceiveData8(USART2);
    
    seneair_decoder(received_char);
    //  UART_ReceiveData_ApplicationProcess(received_char);
    
    /* Echo received character on TX */
    LL_USART_TransmitData8(USART2, received_char);
    
}
int32_t BSP_SPI1_SendRecv_LL(const uint8_t *const pTxData, uint8_t *const pRxData, uint16_t Length)
{
    uint16_t i = 0;
    if ((pTxData == NULL && pRxData == NULL) || (Length == 0)) {
        return -1;  // 参数检查
    }
    
    for (i = 0; i < Length; i++) {
        while (!LL_SPI_IsActiveFlag_TXE(SPI1));  // 等待，直到发送缓冲区为空
        LL_SPI_TransmitData8(SPI1, pTxData[i]);  // 发送数据
        
        while (!LL_SPI_IsActiveFlag_RXNE(SPI1));  // 等待，直到接收缓冲区非空
        pRxData[i] = LL_SPI_ReceiveData8(SPI1);   // 接收数据
        
        while (LL_SPI_IsActiveFlag_BSY(SPI1));  // 确保SPI不忙，完成当前传输
    }
    
    return 0;  // 成功执行
}
/**
* @brief  Function called in case of error detected in USART IT Handler
* @param  None
* @retval None
*/
void Error_Callback(void)
{
    __IO uint32_t isr_reg;
    
    /* Disable USARTx_IRQn */
    NVIC_DisableIRQ(USART2_IRQn);
    
    /* Error handling example :
    - Read USART ISR register to identify flag that leads to IT raising
    - Perform corresponding error handling treatment according to flag
    */
    isr_reg = LL_USART_ReadReg(USART2, ISR);
    if (isr_reg & LL_USART_ISR_NE)
    {
        /* case Noise Error flag is raised : ... */
        ;// LED_Blinking(LED_BLINK_FAST);
    }
    else
    {
        /* Unexpected IT source : Set LED to Blinking mode to indicate error occurs */
        ;//  LED_Blinking(LED_BLINK_ERROR);
    }
}

/**
* @brief  This function is executed in case of error occurrence.
* @retval None
*/
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

// End of Main.c

