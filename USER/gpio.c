#include "gpio.h"

static void GPIO_InitButton(void);
static void GPIO_InitLed(void);
static void GPIO_InitSpi(void);
	
void GPIO_InitLed(void)
{
	GPIO_InitTypeDef Led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	Led.GPIO_Mode = GPIO_Mode_Out_PP;
	Led.GPIO_Pin = PIN_LED_RED | PIN_LED_GREEN;
	Led.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Led);
	
	GPIO_SetBits(PORT_LED_RED, PIN_LED_RED);
	GPIO_SetBits(PORT_LED_GREEN, PIN_LED_GREEN);
}

void GPIO_InitButton(void)
{
	GPIO_InitTypeDef Button;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	Button.GPIO_Mode = GPIO_Mode_IPU;
	Button.GPIO_Pin = PIN_BUTTON_1 | PIN_BUTTON_2 | PIN_BUTTON_RESET;
	Button.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Button);
}

void GPIO_InitSpi(void)
{
	GPIO_InitTypeDef GPIOInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* PB8 - DC/RS */
	GPIOInit.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_8;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	
	/* PB9 - CS */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_9;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	
	/* PB12 - Reset */
	GPIOInit.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 	= GPIO_Pin_12;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);
}

void GPIO_LedChange(void)
{
	if(game_round % 2 != 0)
	{
		if(current_player == 1)
		{
			GPIO_SetBits(PORT_LED_RED, PIN_LED_RED);
			GPIO_ResetBits(PORT_LED_GREEN, PIN_LED_GREEN);
		}
		else 
		{
			GPIO_SetBits(PORT_LED_GREEN, PIN_LED_GREEN);
			GPIO_ResetBits(PORT_LED_RED, PIN_LED_RED);
		}
	}
	if(game_round % 2 == 0)
	{
		if(current_player == 1)
		{
			GPIO_SetBits(PORT_LED_GREEN, PIN_LED_GREEN);
			GPIO_ResetBits(PORT_LED_RED, PIN_LED_RED);
		}
		else  
		{
			GPIO_SetBits(PORT_LED_RED, PIN_LED_RED);
			GPIO_ResetBits(PORT_LED_GREEN, PIN_LED_GREEN);
		}
	}
}

void GPIO_Inits(void)
{
	GPIO_InitLed();
	GPIO_InitSpi();
	GPIO_InitButton();
}