#ifndef _SERIAL_PROC_H_
#define _SERIAL_PROC_H_

#include "stdint.h"
#include "demo_app.h"

#define RTXBUFFDEEP     20
#define RTXBUFFLEN      50

uint8_t serialProc_TxData(uint8_t *pBuffer,uint8_t pSize);
void serialProc_Routine(UARTINPUT_STATUS *keystatus);
void serialProc_ByteRecv(uint8_t nByte);
void UART_ReceiveData_ApplicationProcess(uint8_t newdata);
void UART_ReceiveData_ApplicationProcess_MB(uint8_t newdata);
//uint8_t serialData2Buff_Write( uint8_t *pData, uint16_t Size );
//uint8_t serialBuffData_Send();

WORD16 calculate_crc(BYTE *data, int length);

#endif