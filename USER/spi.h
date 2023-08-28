#ifndef _SPI_H_
#define _SPI_H_

#include "sys.h"


void SPI1_Init(void);
void SPI2_Init(void);
uint8_t SPI_WriteByte(SPI_TypeDef* SPIx, uint8_t byte);

/*
	VCC 
	GND 
	CS - B9
	RESET - B12 
	DC/RS - B8 
	SDI (MOSI) - B15
	SCK - B13
	LED - 3,3 V 
	SDO (MISO) - B14
	
	T_CLK - A3
	T_CS - A4
	T_DIN - A7
	T_DO - A6
	T_IRQ - A5
*/

#endif
