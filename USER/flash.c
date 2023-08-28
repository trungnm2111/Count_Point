#include "flash.h"

uint8_t arr_data8bit[1000];
uint16_t arr_data16bit[1000];
uint32_t arr_data32bit[1000];
uint64_t arr_data64bit[1000];
uint8_t flash_read_string_flag = 0 ;

void Flash_Lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}

void Flash_Unlock(void)
{
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;	
}

void Flash_Erase(uint32_t start_address)
{
	//wait busy reset
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = start_address;
	FLASH->CR |= FLASH_CR_STRT;
	WAIT_BUSY
	FLASH->CR &= ~FLASH_SR_BSY;
	FLASH->CR &= ~FLASH_CR_PER;
}

// VIT DU LIEU MANG

void Flash_WriteArray8bit(uint32_t *start_address,uint8_t *arr_data, uint16_t lenght_data)
{   
	uint16_t i;
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	for(i=0; i < lenght_data; i++)
	{  
		WAIT_BUSY
		*(uint16_t*)*start_address = arr_data[i];
		*start_address += 2U;
	}
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void  Flash_WriteArray16bit(uint32_t *start_address,uint16_t *arr_data, uint16_t lenght_data)
{
	uint16_t i;
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	for(i=0; i < lenght_data; i++)
	{  
		WAIT_BUSY
		*(uint16_t*)*start_address = arr_data[i];
		*start_address += 2U;
	}

	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void  Flash_WriteArray32bit(uint32_t *start_address,uint32_t *arr_data, uint16_t lenght_data)
{
	uint16_t i;
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	for(i=0; i < lenght_data; i++)
	{  
		WAIT_BUSY
		*(uint16_t*)*start_address = (uint16_t)(arr_data[i] & 0xffff);
		*start_address += 2U;
		WAIT_BUSY
		*(uint16_t*)*start_address = (uint16_t)(arr_data[i]>>16 & 0xffff);
		*start_address += 2U;
	}
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void  Flash_WriteArray64bit(uint32_t *start_address,uint64_t *arr_data, uint16_t lenght_data)
{
	uint16_t i;
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	for(i=0; i < lenght_data; i++)
	{  
		WAIT_BUSY
		*(uint16_t*)*start_address = (uint16_t)(arr_data[i] & 0xffff);
		WAIT_BUSY
		*start_address += 2U;
		*(uint16_t*)*start_address = (uint16_t)(arr_data[i]>>16 & 0xffff);
		WAIT_BUSY
		*start_address += 2U;
		*(uint16_t*)*start_address = (uint16_t)(arr_data[i]>>32 & 0xffff);
		WAIT_BUSY
		*start_address += 2U;
		*(uint16_t*)*start_address = (uint16_t)(arr_data[i]>>48 & 0xffff);
		*start_address += 2U;
	}
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}
void Flash_WriteString(uint32_t *start_address,uint8_t *buff, uint16_t lenght_data)
{
	uint16_t i;
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;

	if(lenght_data % 2 == 0)
	{
		buff[lenght_data] = 0xff;
	}
	for(i=0; i <  (lenght_data/2) + (lenght_data % 2); i++)
	{  
		WAIT_BUSY
		uint16_t data = buff[i * 2] | (uint16_t)buff[i * 2 + 1] << 8;
		*(uint16_t*)*start_address = data;
		*start_address += 2U;
	}
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void Flash_WriteStruct(uint32_t *start_address, Information DATA, uint16_t len_string1, uint16_t len_string2)
{
	Flash_Write8bit(start_address, DATA.Selection_round);
	Flash_Write8bit(start_address, DATA.Round);
	Flash_Write8bit(start_address, DATA.Score1);
	Flash_Write8bit(start_address, DATA.Score2);
	Flash_Write8bit(start_address, DATA.Point1);
	Flash_Write8bit(start_address, DATA.Point2);
	Flash_WriteString(start_address, DATA.Name_Player1, len_string1);
	Flash_WriteString(start_address, DATA.Name_Player2, len_string2);
}


//DOC DU LIEU MANG

void Flash_ReadArray8bit(uint32_t *start_address,uint16_t lenght_data)
{
	uint16_t i;
	for(i = 0; i < lenght_data; i++)
	{
		arr_data8bit[i] = *(uint8_t *)*start_address;
		*start_address += 2U;
	}
}
// DOC DU LIEU MANG

void Flash_ReadArray16bit(uint32_t *start_address, uint16_t lenght_data)
{
	uint16_t i;
	for(i = 0; i < lenght_data; i++)
	{
		arr_data16bit[i] = *(uint16_t *)*start_address;
		*start_address += 2U;
	}
}


void Flash_ReadArray32bit(uint32_t *start_address,uint16_t lenght_data)
{
	uint16_t i;
	for(i = 0; i < lenght_data; i++)
	{
		arr_data32bit[i]  = *(uint32_t*)*start_address;
		*start_address += 4U;
	}
}

void Flash_ReadArray64bit( uint32_t *start_address,uint16_t lenght_data)
{
	uint16_t i;
	for(i = 0; i < lenght_data; i++)
	{
		arr_data64bit[i] =*(uint64_t*)*start_address;
		*start_address += 8U;
	}
}

void Flash_ReadString( uint32_t *start_address, char *buff)
{
	uint16_t i = 0;
	while(1)
	{
		*(uint8_t *)(buff + i) = *(uint8_t*)(*start_address + i);
		if((*(buff + i) == (char)0x00) || (*(buff + i) == (char)0xFF))
		{
			break;
		}	
		i++;
	}
	if(i % 2 == 0)
	{
		*start_address += (i+2)*1U;
	}
	if(i % 2 != 0)
	{
		*start_address += (i+1)*1U;
	}
}

Information Flash_ReadStruct(uint32_t *start_address, Information save_str )
{
	save_str.Selection_round = Flash_Read8bit(start_address);
	if(save_str.Selection_round == 0xff)
	{
		save_str.Selection_round  = 3;
	}
	save_str.Round = Flash_Read8bit(start_address);
	if(save_str.Round == 0xff)
	{
		save_str.Round  = 1;
	}
	save_str.Score1 = Flash_Read8bit(start_address);
	if(save_str.Score1 == 0xff)
	{
		save_str.Score1 = 0;
	}
	save_str.Score2 = Flash_Read8bit(start_address);
	if(save_str.Score2 == 0xff)
	{
		save_str.Score2 = 0;
	}
	save_str.Point1 = Flash_Read8bit(start_address);
	if(save_str.Point1 == 0xff)
	{
		save_str.Point1 = 0;
	}
	save_str.Point2 = Flash_Read8bit(start_address);
	if(save_str.Point2 == 0xff)
	{
		save_str.Point2 = 0;
	}
	Flash_ReadString(start_address, (char *)save_str.Name_Player1);
//	start_address++;
//	Usart_Send_String((char *)save_str.Name_Player1);
	
	Flash_ReadString(start_address, (char *)save_str.Name_Player2);
//	Usart_Send_String((char *)save_str.Name_Player2);
	return save_str;
}

void  Flash_Write8bit(uint32_t *start_address,uint8_t data)
{
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	WAIT_BUSY
	*(uint16_t*)*start_address = data;
	*start_address += 2U;
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void  Flash_Write16bit(uint32_t *start_address,uint16_t data)
{
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	WAIT_BUSY
	*(uint16_t*)*start_address = data;
	*start_address += 2U;
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void  Flash_Write32bit(uint32_t *start_address,uint32_t data)
{
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	WAIT_BUSY
	*(uint16_t*)*start_address = (uint16_t)(data & 0xffff);
	*start_address += 2U;
	WAIT_BUSY
	*(uint16_t*)*start_address = (uint16_t)(data>>16 & 0xffff);
	*start_address += 2U;
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

void  Flash_Write64bit(uint32_t *start_address, uint64_t data)
{
	WAIT_BUSY
	FLASH->CR |= FLASH_CR_PG;
	WAIT_BUSY
	*(uint16_t*)*start_address = (uint16_t)(data & 0xffff);
	WAIT_BUSY
	*start_address += 2U;
	*(uint16_t*)*start_address = (uint16_t)(data>>16 & 0xffff);
	WAIT_BUSY
	*start_address += 2U;
	*(uint16_t*)*start_address = (uint16_t)(data>>32 & 0xffff);
	WAIT_BUSY
	*start_address += 2U;
	*(uint16_t*)*start_address = (uint16_t)(data>>48 & 0xffff);
	*start_address += 2U;
	WAIT_BUSY
	FLASH->CR &= ~FLASH_CR_PG;	
}

// DOC DU LIEU DON


uint8_t Flash_Read8bit(uint32_t *start_address)
{
	uint8_t tmp = *(uint32_t *)*start_address;
	*start_address += 2U;
	return tmp;
}

uint16_t Flash_Read16bit(uint32_t *start_address)
{
	uint16_t tmp = *(uint32_t *)*start_address;
	*start_address += 2U;
	return tmp;
}

uint32_t Flash_Read32bit(uint32_t *start_address)
{
	uint32_t tmp = *(uint32_t *)*start_address;
	*start_address += 4U;
	return tmp;
}

uint64_t Flash_Read64bit( uint32_t *start_address)
{
	uint64_t tmp = *(uint64_t *)*start_address;
	*start_address += 8U;
	return tmp;
}
