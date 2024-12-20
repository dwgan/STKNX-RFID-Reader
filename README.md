# STKNX RFID for CYG Charging Station



![image-20240711175747573](https://raw.githubusercontent.com/dwgan/PicGo/main/img/image-20240711175747573.png)



## How to get ID from devices

#### Data structure

```c
//DATA_DIRECTIION,CRUD,mem_index,NFCTagType,VIP_LEVEL,id_len,id[0],id[1],id[2],id[3],id[4],id[5],id[6],id[7]
```

#### Read ID list from devices

```c
//DATA_DIRECTIION=ETStoBUS,CRUD=SELECT,others=any
CC 04 00 00 00 00 00 00 00 00 00 00 00 00
```

#### Write ID to devices

```c
//DATA_DIRECTIION=ETStoBUS,CRUD=INSERT,mem_index=any,NFCTagType=NFC_A,VIP_LEVEL=MEDIUM,id_len=4,id[0],id[1],id[2],id[3],id[4],id[5],id[6],id[7]
AA 01 00 01 02 04 11 22 33 44 00 00 00 00
```

#### Delete ID from divices

```c
//DATA_DIRECTIION=ETStoBUS,CRUD=DELETE,mem_index=01,others=any
CC 02 01 00 00 00 00 00 00 00 00 00 00 00
```



#### Structure define

```c
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

typedef struct {
    unsigned char size; // the number of id
    unsigned char pointer; // insert point, used to indicate insert location in flash
    char flash_index[MAX_TAGS]; // insert point, used to indicate insert location in flash
    TagInfo info[MAX_TAGS];
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
```



#### NFC data process

```c
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
            memcpy((void*)&knx_msg->info, (void*)&tagArray.info[mem_index_to_flash_index(out_pos++, tagArray.flash_index)], sizeof(TagInfo));
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
```



#### ID list

Note that ID list is a *.zip file, unzip password is `the complex password`

