/**
  ******************************************************************************
  * @file    main.h
  * @author  
  * @brief  
  *
  ******************************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

void USART_TXEmpty_Callback(void);
void USART_CharTransmitComplete_Callback(void);
void Error_Callback(void);
void USART_CharReception_Callback(void);
void USART_SendStringData(unsigned char * datasource, unsigned char sendsize);

#endif





