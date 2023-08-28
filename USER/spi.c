#include "spi.h"


uint8_t SPI_WriteByte(SPI_TypeDef* SPIx, uint8_t byte)
{
	while((SPIx->SR&SPI_I2S_FLAG_TXE) == RESET);		
	SPIx->DR = byte;	 	
	while((SPIx->SR&SPI_I2S_FLAG_RXNE) == RESET);
	return SPIx->DR;          	     	
} 

void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIOInit;
	SPI_InitTypeDef Spi1_Initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	/* PA1 - DC/RS */
	GPIOInit.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_1;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	
	/* PA2 - Reset */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_2;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	
	/* PA4 - CS */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_4;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	
	/* PA5 - SCK */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_5;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	
	/* PA6 - MISO */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_6;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	
	/* PA7 - MOSI */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_7;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	
	/* SPI1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	Spi1_Initstructure.SPI_Direction 		= SPI_Direction_2Lines_FullDuplex;
	Spi1_Initstructure.SPI_Mode 				= SPI_Mode_Master;
	Spi1_Initstructure.SPI_DataSize 			= SPI_DataSize_8b;
	Spi1_Initstructure.SPI_CPOL 				= SPI_CPOL_Low;
	Spi1_Initstructure.SPI_CPHA 				= SPI_CPHA_1Edge;
	Spi1_Initstructure.SPI_NSS 				= SPI_NSS_Soft;
	Spi1_Initstructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	Spi1_Initstructure.SPI_FirstBit 			= SPI_FirstBit_MSB;
	Spi1_Initstructure.SPI_CRCPolynomial 	= 7;
	SPI_Init(SPI1, &Spi1_Initstructure);
	
	/* Enable SPI1 CRC calculation */
	SPI_CalculateCRC(SPI1, ENABLE);
	SPI_Cmd(SPI1, ENABLE);
}

void SPI2_Init(void)
{
	GPIO_InitTypeDef GPIOInit;
	SPI_InitTypeDef Spi2_Initstructure;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* PB13 - SCK */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_13;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	
	/* PB14 - MISO */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_14;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	
	/* PB15 - MOSI */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_15;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	
	/* SPI2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	Spi2_Initstructure.SPI_Direction 		= SPI_Direction_2Lines_FullDuplex;
	Spi2_Initstructure.SPI_Mode 				= SPI_Mode_Master;
	Spi2_Initstructure.SPI_DataSize 			= SPI_DataSize_8b;
	Spi2_Initstructure.SPI_CPOL 				= SPI_CPOL_Low;
	Spi2_Initstructure.SPI_CPHA 				= SPI_CPHA_1Edge;
	Spi2_Initstructure.SPI_NSS 				= SPI_NSS_Soft;
	Spi2_Initstructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	Spi2_Initstructure.SPI_FirstBit 			= SPI_FirstBit_MSB;
	Spi2_Initstructure.SPI_CRCPolynomial 	= 7;
	SPI_Init(SPI2, &Spi2_Initstructure);
	
	/* Enable SPI2 CRC calculation */
	SPI_CalculateCRC(SPI2, ENABLE);
	SPI_Cmd(SPI2, ENABLE);
}
