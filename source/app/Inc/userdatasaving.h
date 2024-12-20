
#ifndef _USERDATA_SAVING_H_
#define _USERDATA_SAVING_H_

#include "type_def.h"



#ifndef FLASH_PAGE_SIZE
    #define FLASH_PAGE_SIZE                   2048
#endif

#ifdef FLASH_WRT_SIZE
    #undef  FLASH_WRT_SIZE
    #define FLASH_WRT_SIZE                    8
#else
    #define FLASH_WRT_SIZE                    8
#endif

#define DATAPAGE1_STARTADDRESS   0X0801F000
#define DATAPAGE1_ENDADDRESS     0X0801F7FF
#define DATAPAGE2_STARTADDRESS   0X0801F800
#define DATAPAGE2_ENDADDRESS     0X0801FFFF

#define FLASHPAGE_INITIALIZED    0XFF
#define FLASHPAGE_TRANSFERRING   0XEE
#define FLASHPAGE_USEING         0XCC
#define FLASHPAGE_CLOSED         0X00

#define KNOBEKEY_NUMBER_ADDR     0X0801F000
#define DATA_BLOCK_SIZE          16
#define MAXIMUM_DATABLOCK_NUMBER 2

typedef struct {
    BYTE   data[DATA_BLOCK_SIZE - sizeof(WORD16)];
	BYTE  dataindex;
    BYTE  checksum;
} DataBlock;

typedef struct {
	WORD32  pagestatus;
    WORD32  reserveddata;
} PageHeadStatus;


void Demp_App_FlashData_Initialize(void);
void Demo_App_Data_Saving(BYTE *savingdata,BYTE datalength);
BYTE CalculateChecksum(DataBlock* data) ;
WORD32 Demp_APP_FlashAddress_Checking(WORD32 targetaddress);



#endif

