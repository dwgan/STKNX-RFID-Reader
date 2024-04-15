/******************************************************************************
* ��Ȩ���� (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* �ļ����ƣ�Main.c
* �ļ���ʶ����
* ����ժҪ��KNXӦ��Դ�������ļ���Ӧ����ڡ�
* ����˵����
* ��ǰ�汾��V1.00
* ��    �ߣ�      
* ������ڣ�2013��7��24��
*    
* �޸ļ�¼1��
*        �޸����ڣ�2013��7��24��
*        �� �� �ţ�V1.00
*        �� �� �ˣ�      
*        �޸����ݣ�������������.
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
* �������ƣ�void main(void)
* ����������device software start entry.
* ���������no.
* ���������no.
* �� �� ֵ��no.
* ����˵����
* �޸�����     �汾��     �޸���      �޸�����
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   ����
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
        return -1;  // �������
    }
    
    for (i = 0; i < Length; i++) {
        while (!LL_SPI_IsActiveFlag_TXE(SPI1));  // �ȴ���ֱ�����ͻ�����Ϊ��
        LL_SPI_TransmitData8(SPI1, pTxData[i]);  // ��������
        
        while (!LL_SPI_IsActiveFlag_RXNE(SPI1));  // �ȴ���ֱ�����ջ������ǿ�
        pRxData[i] = LL_SPI_ReceiveData8(SPI1);   // ��������
        
        while (LL_SPI_IsActiveFlag_BSY(SPI1));  // ȷ��SPI��æ����ɵ�ǰ����
    }
    
    return 0;  // �ɹ�ִ��
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

