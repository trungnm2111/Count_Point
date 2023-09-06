#include "ui.h"
#include "sys.h"

uint8_t previous_point1 = 0;
uint8_t previous_point2 = 0;
uint8_t score_past1, score_past2;

void UI_Init(void)
{
	current_player = 1;
	UI_Frame();
	UI_Points1(count1);
	UI_Points2(count2);
	UI_RoundNumber(game_round, select_round);
	UI_Score1(score_player1);
	UI_Score2(score_player2);
	UI_NamePlayer(0,flash_read_str.Name_Player1);
	UI_NamePlayer(1,flash_read_str.Name_Player2);
}
void UI_Frame(void)
{
	LCD_DrawLine(0, 60, 320, 60);
	LCD_DrawLine(160, 60, 160, 240);
	LCD_Fill(0, 0, 320, 59, WHITE);
	LCD_Fill(0, 61, 159, 240, GREEN);
	LCD_Fill(161, 61, 320, 240, YELLOW);
	gui_circle(30, 30, RED, 25, 1);
	LCD_ShowString(10, 22, BLACK, RED, 16, (uint8_t *)"Reset", 1);
	gui_circle(290, 30, RED, 25, 1);
	LCD_ShowString(274, 22, BLACK, RED, 16,(uint8_t *) "Reset", 1);
}

void UI_MenuOption(void)
{
//	LCD_Fill(210, 6, 320, 139,LIGHTBLUE );
//	LCD_DrawLine(210, 8, 320, 8);
//	LCD_DrawLine(210, 39, 320, 39);
//	LCD_DrawLine(210, 88, 320, 88);
//	LCD_DrawLine(210, 137, 320, 137);
//	LCD_ShowString(220, 15, BLACK, LIGHTBLUE, 24,(uint8_t *) "3 ROUND", 0);
//	LCD_ShowString(220, 63, BLACK, LIGHTBLUE, 24,(uint8_t *)"5 ROUND", 0);
//	LCD_ShowString(220, 111, BLACK, LIGHTBLUE, 24,(uint8_t *) "7 ROUND", 0);
//	flag_touch_menu = 1;
}

void UI_RoundNumber(uint8_t number,uint8_t round)
{
	if(round == 3)
	{
		switch(number)
		{
			case 1:
				LCD_ShowString(100, 17, WHITE, WHITE, 24, (uint8_t *)"CHUNG KET", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 1", 0);
			break;
			
			case 2:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 1", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 2", 0);
			
			break;
			
			case 3:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 2", 0);
				LCD_ShowString(100, 17, RED, WHITE, 24, (uint8_t *)"CHUNG KET", 0);
			break;
		}
	}else if(round == 5)
	{
		switch(number)
		{
			case 1:
				LCD_ShowString(100, 17, WHITE, WHITE, 24, (uint8_t *)"          ", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 1", 0);
			break;
			
			case 2:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 1", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 2", 0);
			break;
			
			case 3:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 2", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 3", 0);
			break;
			
			case 4:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 3", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 4", 0);
			break;
			
			case 5:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 4", 0);
				LCD_ShowString(100, 17, RED, WHITE, 24, (uint8_t *)"CHUNG KET", 0);
			break;
		}
	}else if(round == 7)
	{
		switch(number)
		{
			case 1:
				LCD_ShowString(100, 17, WHITE, WHITE, 24, (uint8_t *)"          ", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 1", 0);
			break;
			
			case 2:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 1", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 2", 0);
			break;
			
			case 3:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 2", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 3", 0);
			break;
			
			case 4:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 3", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 4", 0);
			break;
			
			case 5:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 4", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 5", 0);
			
			break;
			
			case 6:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 5", 0);
				LCD_ShowString(120, 17, RED, WHITE, 24, (uint8_t *)"ROUND 6", 0);
			break;
			
			case 7:
				LCD_ShowString(120, 17, WHITE, WHITE, 24, (uint8_t *)"ROUND 6", 0);
				LCD_ShowString(100, 17, RED, WHITE, 24, (uint8_t *)"CHUNG KET", 0);
			break;
		}
	}
	flash_write_str.Round = number;
	flash_write_str.Selection_round = round;
}

void UI_NamePlayer(u8 mode, u8 *player)
{
	u8 len;
	switch(mode%2)
	{
		case 0:
			LCD_ShowString(28, 70, GREEN, GREEN, 24, (uint8_t*)"          ", 0);
			LCD_ShowString(28, 70, BLACK, GREEN, 24, player, 0);
			for(len = 0 ; len < flash_read_len_string1; len ++)
			{
				flash_write_str.Name_Player1[len] = player[len];
			}	
		break;
		
		case 1:
			Usart_Send_Char('\n');
			LCD_ShowString(188, 70, YELLOW, YELLOW, 24, (uint8_t*)"          ", 0);
			LCD_ShowString(188, 70, BLACK, YELLOW, 24, player, 0);
			for(len = 0 ; len < flash_read_len_string2; len ++)
			{
				flash_write_str.Name_Player2[len] = player[len];
			}		
		break;
	}
}

void UI_Points1(uint8_t point)
{
	if( previous_point1 != point)
	{
		LCD_Show_24x48_char(70+12, 120, GREEN, GREEN, '0' + previous_point1 %10, 1);
		if( previous_point1 /10 != 0)
		{
			LCD_Show_24x48_char(70-12, 120, GREEN, GREEN, '0' + previous_point1 /10, 1);
		}
	}
	
	LCD_Show_24x48_char(70+12, 120, RED, GREEN, '0' + point %10, 1);
	if( point /10 != 0)
	{
		LCD_Show_24x48_char(70-12, 120, RED, GREEN, '0' + point /10, 1);
	}
	previous_point1 = point;
//	Message_SendPoint1(point);
	flash_write_str.Point1 = point;
}


void UI_Points2(uint8_t point)
{
	if(previous_point2 != point)
	{
		LCD_Show_24x48_char(225+12, 120, YELLOW, YELLOW, '0' + ((previous_point2) %10), 1);
		if(previous_point2 / 10 != 0)
		{
			LCD_Show_24x48_char(225-12, 120, YELLOW, YELLOW, '0' + (previous_point2 / 10), 1);
		}
	}
	
	LCD_Show_24x48_char(225+12, 120, RED, YELLOW, '0' + ((point) % 10), 1);
	if(point / 10 != 0)
	{
		LCD_Show_24x48_char(225-12, 120, RED, YELLOW, '0' + ((point) /10), 1);
	}
	previous_point2 = point;
//	Message_SendPoint2(point);
	flash_write_str.Point2 = point;
}

void UI_Score1(uint8_t score)
{
	LCD_Show_24x48_char(70, 17, WHITE, WHITE, '0' + (score_past1), 1);
	LCD_Show_24x48_char(70, 17, BLUE, WHITE, '0' + score, 1);
	score_past1 = score;
//	Message_SendScore1(score);
	flash_write_str.Score1 = score;
}
void UI_Score2(uint8_t score)
{
	LCD_Show_24x48_char(230, 17, WHITE, WHITE, '0' + (score_past2), 1);
	LCD_Show_24x48_char(230, 17, BLUE, WHITE, '0' + score, 1);
	score_past2 = score;
//	Message_SendScore2(score);
	flash_write_str.Score2 = score;
}