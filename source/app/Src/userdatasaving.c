

#include "userdatasaving.h"
#include "Stm32G0XX_Flash.h"


BYTE applicationsavedata[16] ={0,1,2,3,4,5,6,7},applicationreaddata[16];
DataBlock datablock[MAXIMUM_DATABLOCK_NUMBER];
BYTE datapageindex;
PageHeadStatus pagesatus;
WORD32 current_address;
BYTE flashinitialflag;
BYTE page2eraseflag;


void Demp_App_FlashData_Initialize(void)
{
	WORD32 address;
	T_DATA_OPERARTION tFlashData;

	current_address = DATAPAGE1_STARTADDRESS;

	for(address = DATAPAGE1_STARTADDRESS; address < DATAPAGE2_ENDADDRESS; address += sizeof(datablock))
	{
        DataBlock* flashData = (DataBlock*)address;
		if((address == DATAPAGE1_STARTADDRESS)||(address == DATAPAGE2_STARTADDRESS))		
		{
		    if((flashData->data[0] != FLASHPAGE_USEING)||(flashData->data[1] != FLASHPAGE_USEING))
		    {
		        if(address == DATAPAGE1_STARTADDRESS)
		        {
				    address = DATAPAGE2_STARTADDRESS - sizeof(datablock);
		        }
				else
				{
				    break;
				}
		    }
#ifdef 0			
			else if((flashData->data[0] != FLASHPAGE_USEING)||(flashData->data[1] != FLASHPAGE_USEING)) // other status initial the flash 
			{			
				tFlashData.dwDestAddr = address;
				tFlashData.wDataLength = FLASH_WRT_SIZE *2;
				Stm32G0xxx_Flash_application_erase(&tFlashData);
		        if(address == DATAPAGE1_STARTADDRESS)
		        {
				    address = DATAPAGE2_STARTADDRESS - sizeof(datablock);
		        }
				else
				{
				    break;
				}

			}
#endif 
		}
		else if((flashData->data[0] == FLASHPAGE_INITIALIZED)&&(flashData->data[1] == FLASHPAGE_INITIALIZED)&&(flashData->data[2] == FLASHPAGE_INITIALIZED)&&(flashData->data[3] == FLASHPAGE_INITIALIZED))
		{
			if(address <= DATAPAGE1_ENDADDRESS)
			{
				address = DATAPAGE2_STARTADDRESS - sizeof(datablock);
			
			}
			else
			{			
				break;
			}
		}
		else if(flashData->checksum == CalculateChecksum(flashData))			
		{
		   if(flashData->dataindex <= MAXIMUM_DATABLOCK_NUMBER)
		   	{
		   	    for(char i = 0; i<= 5;i++)
		   	    {
			        datablock[flashData->dataindex].data[i] = flashData->data[i];
		   	    }
				datablock[flashData->dataindex].dataindex = flashData->dataindex;
				datablock[flashData->dataindex].checksum = flashData->checksum;
		   	}
            current_address = address + sizeof(DataBlock);
        }       
    }
}


BYTE CalculateChecksum(DataBlock* data) 
{
    return data->data[0] ^ data->data[1] ^ data->data[2]^data->data[3] ^ data->data[4] ^ data->data[5]^data->data[6] ^ data->data[7] ^ data->data[8]^ data->data[9]^data->data[10] ^ data->data[11] ^ data->data[12]^ data->data[13];  // 简单的异或校验
}

/**************************************************************************
*  void Demo_App_Data_Saving(void)
*  saving data to flash
**************************************************************************/
void Demo_App_Data_Saving(BYTE *savingdata,BYTE datalength)
{
	T_DATA_OPERARTION tWriteData,tReadData,tFlashData;   
    static unsigned char knobenalbekeynumber;
    static WORD32  savingflagcleartime;
	BYTE i;
	
 //   if(keyknobstatus.KnobEnableKeynumbersaveflag == 1)
    {
		current_address = Demp_APP_FlashAddress_Checking(current_address);

	    tReadData.dwDestAddr = current_address;
		tReadData.pucBuffer  = &savingdata[0];
		tReadData.wDataLength = FLASH_WRT_SIZE ;
	    Stm32G0xxx_Flash_application_read(&tReadData);
	
	
		tReadData.wDataLength = FLASH_WRT_SIZE;    
		for(i=0; i < 14; i++)
		{
		    datablock[0].data[i] = savingdata[i];
		}
        datablock[0].dataindex = savingdata[14];
		datablock[0].checksum =   CalculateChecksum(&datablock[0]);

		tWriteData.dwDestAddr = current_address;
		tWriteData.pucBuffer  = &(datablock[0].data[0]);
	    Stm32G0xxx_Flash_application_save(&tWriteData);

		tWriteData.dwDestAddr = (current_address + FLASH_WRT_SIZE);
		tWriteData.pucBuffer  = &(datablock[0].data[8]);
	    Stm32G0xxx_Flash_application_save(&tWriteData);

        tReadData.dwDestAddr = current_address;
		tReadData.pucBuffer  = &applicationreaddata[0];
		tReadData.wDataLength = FLASH_WRT_SIZE ;
	    Stm32G0xxx_Flash_application_read(&tReadData);

		current_address = current_address + sizeof(DataBlock);	
	//	keyknobstatus.KnobEnableKeynumbersaveflag = 0;
		savingflagcleartime = API_KnxTm_GetTimeMs();

		if(page2eraseflag == 1)
		{
		    tFlashData.dwDestAddr = DATAPAGE2_STARTADDRESS;
		    tFlashData.wDataLength = FLASH_WRT_SIZE;
		     Stm32G0xxx_Flash_application_erase(&tFlashData);
		     page2eraseflag = 0;
		}

	/*
        UART_IT_DISABLE();
	    API_KnxMem_WriteByte(APP_KNOBKEY_ENABLE_BUTTON_REF,keyknobstatus.KnobEnableKeynumber);
	    API_KnxMem_WriteFinished();
	    keyknobstatus.KnobEnableKeynumbersaveflag = 0;		
	   API_KnxMem_ReadByte(APP_KNOBKEY_ENABLE_BUTTON_REF,&knobenalbekeynumber);
	    uartquickinitialflag = 0;
      */
    }

}

WORD32 Demp_APP_FlashAddress_Checking(WORD32 targetaddress)
{
	T_DATA_OPERARTION tFlashData,tWriteData; 

	if((targetaddress >= DATAPAGE2_ENDADDRESS)||(targetaddress == DATAPAGE1_STARTADDRESS)||(targetaddress == DATAPAGE2_STARTADDRESS))
	{
		if(targetaddress >= DATAPAGE2_ENDADDRESS)
		{
			targetaddress = DATAPAGE1_STARTADDRESS;
			page2eraseflag =1 ;
		}
		DataBlock* flashData = (DataBlock*)targetaddress;
		
		tFlashData.dwDestAddr = targetaddress;
		tFlashData.wDataLength = FLASH_WRT_SIZE;
		Stm32G0xxx_Flash_application_erase(&tFlashData);		
			
		tWriteData.dwDestAddr = targetaddress;
		tWriteData.wDataLength = FLASH_WRT_SIZE;    
		datablock[0].data[0] = FLASHPAGE_USEING;
		datablock[0].data[1] = FLASHPAGE_USEING;
		datablock[0].data[2] = FLASHPAGE_USEING;
		datablock[0].data[3] = FLASHPAGE_USEING;
		datablock[0].data[4] = FLASHPAGE_USEING;
		datablock[0].data[5] = FLASHPAGE_USEING;
		tWriteData.pucBuffer  = &(datablock[0].data[0]);
	    Stm32G0xxx_Flash_application_save(&tWriteData);	

		targetaddress = targetaddress + sizeof(DataBlock);
		
	}

return targetaddress;

}


