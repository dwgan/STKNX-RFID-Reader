#ifndef NFC_APP_H
#define NFC_APP_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "demo.h"
  
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


#define MAX_TAGS 20  // maximum number of id
#define MAX_ID_LEN 8  // maximum lenth of each id
#define NFC_DURATION 6000  // nfc disable duration

#define KNX_TAG_ID_ADD 1
#define KNX_TAG_ID_RM  2
#define KNX_TAG_ID_CAT 3
    
typedef enum {
    NONE=0,
    HIGH=1,
    MEDIUM=2,
    LOW=3
} VIP_LEVEL;

typedef enum {
    INSERT=1,
    DELETE=2,
    UPDATE=3,
    SELECT=4
} CRUD;

typedef enum {
    NFC_A=1,
    NFC_B=2,
    NFC_F=3,
    NFC_V=4
} NFCTagType;

typedef enum {
    RECORDERtoBUS=0xaa,
    CHARGERtoBUS=0xbb,
    ETStoBUS=0xcc
} DATA_DIRECTIION;

#pragma pack(push, 1)
typedef struct {
    NFCTagType tag_type;
    VIP_LEVEL vipLevel;
    char id_len;
    char id[MAX_ID_LEN];
} TagInfo;

// ensure the size of this structure are the times of 8 bytes
// because the flash need to be write 8 bytes each times for STM32G0xx
// head len = 8 bytes, each info len = 8 bytes
typedef struct {
    uint16_t size; // the number of id
    // unsigned char pointer; // insert point, used to indicate insert location in flash
    // char flash_index[MAX_TAGS]; // insert point, used to indicate insert location in flash
    TagInfo info[MAX_TAGS];
    uint8_t reserve[6+5*MAX_TAGS]; // to compensate len for ensure the size of times of 8 bytes
} TagArray;

typedef struct {
    DATA_DIRECTIION dir;
    CRUD cmd;
    char mem_index; // used to indicate insert location in memmory
    TagInfo info;
} KNX_NFCInfo;

typedef struct {
    unsigned char is_tag_detected;
    char mem_index;
    TagInfo info;
} SCAN_NFCInfo;
#pragma pack(pop)

extern SCAN_NFCInfo local_info;
extern TagArray tagArray;
void nfcTagID_process(KNX_NFCInfo *knx_msg, SCAN_NFCInfo *local_info) ;
WORD32 erase_a_flash_page(uint32_t addr);
char write_data_to_flash(uint32_t addr, void *data, uint16_t len);
char read_data_from_flash(uint32_t addr, void *data, uint16_t len);
void Error_Handler(void);
void nfc_app_init();
#ifdef __cplusplus
}
#endif

#endif
