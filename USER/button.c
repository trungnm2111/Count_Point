#include "button.h"
#include "delay.h"
#include "gpio.h"


static uint16_t stt_new1 = 1, stt_old1 = 1;
static uint16_t stt_new2 = 1, stt_old2 = 1;
static uint16_t stt_new3 = 1, stt_old3 = 1;

uint16_t count1 = 0;
uint16_t count2 = 0;
uint8_t button_pressed = 0;
uint8_t current_player;

uint8_t game_round = 1;
uint8_t score_player1 = 0, score_player2 = 0;

 void BUTTON_Reads(void)
{
	stt_old1 = stt_new1;
	stt_new1 = GPIO_ReadInputDataBit(PORT_BUTTON_1, PIN_BUTTON_1);
	if(stt_old1 == 1 && stt_new1 == 0 && button_pressed == 0)
	{
		count1++;
		button_pressed = 1;
	}
	else if(stt_old1 == 0 && stt_new1 == 1)
	{
		button_pressed = 0;
	}
	stt_old2 = stt_new2;
	stt_new2 = GPIO_ReadInputDataBit(PORT_BUTTON_2, PIN_BUTTON_2);
	if(stt_old2 == 1 && stt_new2 == 0 && button_pressed == 0)
	{
		count2++;
		button_pressed = 1;
	}
	else if(stt_old2 == 0 && stt_new2 == 1)
	{
		button_pressed = 0;
	}
	DELAY_ms(10);
}

void BUTTON_Read3(void)
{
	stt_old3 = stt_new3;
	stt_new3 = GPIO_ReadInputDataBit(PORT_BUTTON_RESET, PIN_BUTTON_RESET);
	if(stt_old3 == 1 && stt_new3 == 0 && button_pressed == 0)
	{
		count1 = previous_point1;
		count2 = previous_point2;
		UI_Points1(count1);
		UI_Points2(count2);
		flag_check_save_flash = 1;
		button_pressed = 1;
	}
	else if(stt_old3 == 0 && stt_new3 == 1)
	{
		button_pressed = 0;
	}
	DELAY_ms(10);
}

void BUTTON_Display(void)
{
	if(button_pressed == 1)
	{
		if((count1 + count2) % 2 == 0)
		{
			switch(current_player)
			{
				case 1:
					current_player = 2;
				break;

				case 2:
					current_player = 1;
				break;
			}
		}
		UI_Points1(count1);
		UI_Points2(count2);
		flag_check_save_flash = 1;
	}
}

