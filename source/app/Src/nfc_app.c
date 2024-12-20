#include "nfc_app.h"
#include "Application_Data.h"
#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "app_common.h"
#include "Hardware.h"
#include "Knx_Prop.h"
#include "Rec_Table.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "demo_app.h"
#include "App_Api.h"
#include "demo.h"
#include "Stm32G0XX_Flash.h"
#include "common_media.h"


SCAN_NFCInfo local_info;
TagArray tagArray;
extern T_CHARGER_STATUSUPDATGE chargerupdateflag;

char mem_index_to_flash_index(char mem_index, char *flash_index)
{
    for (char i=0,j=0;i<MAX_TAGS;i++)
    {
        if (*(flash_index+i) == 1)
        {
            if (j++ == mem_index)
            {
                return i;
            }
        }
    }
    return 0xff;
}

char find_1st_index(char *flash_index)
{
    for (char i=0;i<MAX_TAGS;i++)
    {
        if (*(flash_index+i) == 0xff)
        {
            return i;
        }
    }
    return 0xff;
}

void load_flash_info(uint32_t Addr, TagArray *tagArray)
{
//    for (uint32_t i=0; i<sizeof(TagArray); i++)
//    {
//        *((BYTE*)tagArray+i)=API_KnxMem_GetByte(Addr+i);
//    }
    read_data_from_flash(DATAPAGE2_STARTADDRESS, tagArray, sizeof(TagArray));
}

char findTag(TagArray *array, const char *id, char id_len, NFCTagType tag_type) {
    // char ind=0;
    for (size_t ind = 0; ind < array->size; ind++) {
        // ind = mem_index_to_flash_index(i, array->flash_index);
        if (memcmp(array->info[ind].id, id, id_len) == 0 && array->info[ind].id_len == id_len && array->info[ind].tag_type == tag_type) {
            return ind;
        }
    }
    return 0xff;
}

char addTag(TagArray *array, const char *id, NFCTagType tag_type, char id_len, VIP_LEVEL vipLevel, unsigned char id_index) {
    char ind;
    ind = findTag(array, id, id_len, tag_type);
    // if this ID do not exist
    if (ind != 0xff) {
        return ind;
    }
    // save this ID to memory
    TagInfo *info = &array->info[array->size];
    memcpy(info->id, id, id_len);
    memset(info->id + id_len, 0, sizeof(info->id) - id_len); // keep the rest id num to 0
    info->tag_type = tag_type;
    info->id_len = id_len;
    info->vipLevel = vipLevel;
    // array->flash_index[array->pointer]=1;
    array->size++;
    // array->pointer++;
    // if (array->pointer >= MAX_TAGS) {
    //     array->pointer = find_1st_index(array->flash_index);
    // }
    
    // save info to flash
//    API_KnxMem_WriteData(NFC_UID_DATA_REF, (unsigned char*)&tagArray, 2);
//    API_KnxMem_WriteByte(NFC_UID_DATA_REF+2+array->pointer-1, array->flash_index[array->pointer-1]);
//    API_KnxMem_WriteData(NFC_UID_DATA_REF+2+MAX_TAGS+(array->pointer-1)*sizeof(TagInfo), (unsigned char*)&array->info[array->pointer-1], sizeof(TagInfo));
//    API_KnxMem_WriteFinished();
//    WORD32 TimesMsRef;
//    TimesMsRef = API_KnxTm_GetTimeMs();
//    while (API_KnxTm_GetDelayMs( TimesMsRef ) < 200 );
    erase_a_flash_page(DATAPAGE2_STARTADDRESS);
    write_data_to_flash(DATAPAGE2_STARTADDRESS, array, sizeof(TagArray));
    
    // load info from flash
    // load_flash_info(DATAPAGE2_STARTADDRESS, array);
    ind = findTag(array, id, id_len, tag_type);
    if (ind != 0xff) {
        return ind;
    }
    return 0xff;
}

char removeTag(TagArray *array, char mem_index) {
    if (array->size>0)
    {
        // char ind = mem_index_to_flash_index(mem_index, array->flash_index);
        // remove this index
        // memcpy(&array->flash_index[mem_index], &array->flash_index[mem_index]+1, MAX_TAGS - mem_index - 1);
        memcpy(&array->info[mem_index], &array->info[mem_index]+1, (MAX_TAGS - mem_index - 1) * sizeof(TagInfo));
        memset(&array->info[MAX_TAGS - 1], 0xff, sizeof(TagInfo));
        array->size -= 1;
//        API_KnxMem_WriteByte(NFC_UID_DATA_REF, array->size-1);
//        API_KnxMem_WriteByte(NFC_UID_DATA_REF+2+ind, 0xff);
//        API_KnxMem_WriteFinished();
//        WORD32 TimesMsRef;
//        TimesMsRef = API_KnxTm_GetTimeMs();
//        while (API_KnxTm_GetDelayMs( TimesMsRef ) < 200 );
        erase_a_flash_page(DATAPAGE2_STARTADDRESS);
        write_data_to_flash(DATAPAGE2_STARTADDRESS, array, sizeof(TagArray));
        
        // memset((char*)&array->flash_index[mem_index_to_flash_index(mem_index, array->flash_index)], 0xff, 1);
        // array->size--;
        
        // // load info from flash
        // load_flash_info(DATAPAGE2_STARTADDRESS, array);
        // if (array->flash_index[ind] == 0xff) {
        return mem_index;
        // }
        // else
        // {
        //     return 0xff;
        // }
    }
    else
    {
        return 0xff;
    }
}

void initTagArray(TagArray *array) {
    TagArray tmp;
    load_flash_info(DATAPAGE2_STARTADDRESS, &tmp);
    if ( *(uint64_t *)&tmp != 0xffffffffffffffff) // if the flash is not init state
    {
        memcpy(array, &tmp, sizeof(TagArray));
    }
    else
    {
        memset(array, 0xff, sizeof(TagArray));
        array->size=0;
        // array->pointer=0;
    }
    local_info.mem_index=0xff;
}

void nfc_app_init()
{
    initTagArray(&tagArray);
    demoIni();
}

extern T_DATATOCHARGERBOARD_UPDATE chargerboardupdateflag;
extern T_CHARGER_INFORMATION chargerinformation;
WORD32 NFC_Disable_MsRef;
void nfcTagID_process(KNX_NFCInfo *knx_msg, SCAN_NFCInfo *local_info) 
{
    static bool outputDone=true;
    static uint8_t out_pos=0;
    char ind;
    
    // Check the input message
    if (chargerboardupdateflag.chargeridupdate)
    {
        // check if the message is from recorder or ETS
        if (knx_msg->dir == 0xAA || knx_msg->dir == 0xCC)
        {
            // add a tag to flash
            if (knx_msg->cmd == INSERT && knx_msg->info.id_len != 0 && knx_msg->info.tag_type != 0 && knx_msg->info.vipLevel != 0)
            {
                ind = addTag(&tagArray, knx_msg->info.id, knx_msg->info.tag_type, knx_msg->info.id_len, knx_msg->info.vipLevel, knx_msg->mem_index);
                if (ind != 0xff)
                {
                    knx_msg->dir = CHARGERtoBUS;
                    knx_msg->cmd = INSERT;
                    knx_msg->mem_index = tagArray.size;
                    memcpy((void*)&knx_msg->info, (void*)&tagArray.info[ind], sizeof(TagInfo));
                    chargerupdateflag.chargeridupdate = 1;
                }
            }
            // remove a tag from flash
            else if (knx_msg->cmd == DELETE && knx_msg->mem_index >= 0 && knx_msg->mem_index < tagArray.size)
            {
                ind = removeTag(&tagArray, knx_msg->mem_index);
                if (ind != 0xff)
                {
                    knx_msg->dir = CHARGERtoBUS;
                    knx_msg->cmd = DELETE;
                    knx_msg->mem_index = tagArray.size;
                    memcpy((void*)&knx_msg->info, (void*)&tagArray.info[ind], sizeof(TagInfo));
                    chargerupdateflag.chargeridupdate = 1;
                }
            }
            else if (knx_msg->cmd == SELECT)
            {
                // output id list to bus
                outputDone=false;
                out_pos=0;
            }
        }
        chargerboardupdateflag.chargeridupdate=0;
    }
    
    // output id list to bus
    if (!outputDone && chargerupdateflag.chargeridupdate==0)
    {
        if (out_pos<tagArray.size)
        {
            knx_msg->dir = CHARGERtoBUS;
            knx_msg->cmd = SELECT;
            knx_msg->mem_index = out_pos;
            memcpy((void*)&knx_msg->info, (void*)&tagArray.info[out_pos++], sizeof(TagInfo));
            chargerupdateflag.chargeridupdate = 1;
        }
        else
        {
            out_pos=0;
            outputDone=true;
        }
    }
    
    // the nfc card is detected
    if (local_info->is_tag_detected == 1)
    {
        chargerupdateflag.chargeridupdate = 1;
        char ind = findTag(&tagArray, local_info->info.id, local_info->info.id_len, local_info->info.tag_type);
        knx_msg->dir = CHARGERtoBUS;
        knx_msg->cmd = SELECT;
        knx_msg->mem_index = ind;
        
        if (ind != 0xff)
        {
            // if the id is recorder, disable detection function in 4s to avoid frequently turn on / off the charger
            NFC_Disable_MsRef = API_KnxTm_GetTimeMs();
            chargerboardupdateflag.chargerstatussetting = 1; // Enable this flag to set command to charge board
            if (chargerinformation.chargerworkingstatus == 1)
            {
                chargerinformation.chargersetting = 0;
            }
            else
            {
                chargerinformation.chargersetting = 1;
            }
            memcpy((char*)&knx_msg->info, (char*)&tagArray.info[ind], sizeof(TagInfo));
        }
        else
        {
            memcpy((char*)&knx_msg->info, (char*)&local_info->info, sizeof(TagInfo));
        }
        memset((char*)local_info, 0, sizeof(SCAN_NFCInfo));
        local_info->is_tag_detected = 0;
    }
}

// write a structure into flash, the len of the structure need to be times of 8 bytes!!!
// make sure to erase flash page before writing data to it
// addr: start address of flash that saving data
// *data: data pointer that point to the sturcture
WORD32 Stm32G0xxx_Flash_Write(T_DATA_OPERARTION *ptPara);
char write_data_to_flash(uint32_t addr, void *data, uint16_t len)
{
    // if the len is not the times of 8, can not be writen into flash, then return
    if ((len & (FLASH_WRT_SIZE-1)) > 0)
    {
        return -1;
    }
    
    // then write data into flsh
    T_DATA_OPERARTION tWriteData;
    for (uint16_t ind = 0; ind < len; ind +=FLASH_WRT_SIZE )
    {
        tWriteData.dwDestAddr  = addr+ind;
        tWriteData.ucOperMode  = SW_MEDIA_LLWORD;
        tWriteData.wDataLength = FLASH_WRT_SIZE;
        tWriteData.pucBuffer = (BYTE*)data + ind;
        Stm32G0xxx_Flash_Write(&tWriteData);
    }
    return 0;
}

// read a structure from flash, the len of the structure need to be times of 1 byte
// addr: start address of flash that saving data
// *data: data pointer that point to the sturcture
WORD32 Stm32G0xxx_Flash_Read(T_DATA_OPERARTION *ptPara);
char read_data_from_flash(uint32_t addr, void *data, uint16_t len)
{
    T_DATA_OPERARTION tWriteData;
    
    tWriteData.dwDestAddr  = addr;
    tWriteData.ucOperMode  = SW_MEDIA_READ;
    tWriteData.wDataLength = len;
    Stm32G0xxx_Flash_Read(&tWriteData);
    return 0;
}


// erase a flash page
// addr: flash page addr
// a flash page = 2048 bytes in default
WORD32 erase_a_flash_page(uint32_t addr)
{
    T_DATA_OPERARTION tWriteData;
    tWriteData.dwDestAddr  = addr;
    tWriteData.ucOperMode  = SW_MEDIA_ERASE;
    WORD32 status = Stm32G0xxx_Flash_Write(&tWriteData);
    return status;
}


