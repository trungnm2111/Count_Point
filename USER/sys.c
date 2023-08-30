#include "sys.h"

Information flash_write_str, flash_read_str;
FrameMsg_t frame_detect;

static uint8_t game_ended = 0;
u8 flag_check_save_flash = 0;
uint8_t *string_name2;
uint8_t *string_name1;
static uint16_t fsm_len_string_name1 = 0, fsm_len_string_name2 = 0;

static void Print_Data_Detect(FrameMsg_t frame);

void SYS_Init(void)
{	
	previous_point1 = (uint8_t)0, previous_point2 = (uint8_t)0;
	GPIO_Inits();
	Usart_Config(USART1, 9600);
	DELAY_Init();
	LCD_Init();
	TOUCH_Init();
	SYS_ReadFlash();
	UI_Init();
	current_player = 1;
}

void SYS_Run(void)
{
	SYS_WriteFlash();
	SYS_ButtonFunction();
	TP_Screen();
	TP_Touch();
}



///////////////////////////////////////////FUNCTION////////////////////////////////////////////////////////////////////////

void SYS_ButtonFunction(void)
{
	BUTTON_Reads();	
	BUTTON_Display();
	if(count1 >= 11 && (count1 - count2) >= 2)
	{
		game_ended = 1;
		score_player1 ++;
		UI_Score1(score_player1);
	}
	else if(count2 >= 11 && (count2 - count1) >= 2)
	{
		game_ended = 2;
		score_player2 ++;
		UI_Score2(score_player2);
	}
	if(count1 >= 5 && count2 == 0)
	{
		game_ended = 1;
		score_player1 ++;
		UI_Score1(score_player1);
	}
	else if(count2 >= 5 && count1 == 0)
	{
		game_ended  = 2;
		score_player2 ++;
		UI_Score2(score_player2);
	}
	if(game_ended == 1 || game_ended == 2)
	{
		game_ended = 0;
		count1 = 0 ;
		count2 = 0;
		game_round ++;
		UI_RoundNumber(game_round, select_round);
		if(score_player1 + score_player2 >= select_round)
		{
			score_player1 = 0;
			score_player2 =0;
			game_round = 1;
			UI_RoundNumber(game_round, select_round);
			UI_Score1(score_player1);
			UI_Score2(score_player2);
			game_ended = 0;
			count1 =0;
			count2 =0;
		}
	}
}


void SYS_ReceiveFuntion(void)
{
	if(Usart_CheckFlag_Fsm() == 1)
	{
		static unsigned int count =0;
		for(count = 0 ; count < length_arr_recerive ; count ++)
		{
			Usart_Send_Char(arr_data_fsm[count]);
		}
		SEC_Message_Detect_Frame(arr_data_fsm,&frame_detect,length_arr_recerive);
		Print_Data_Detect(frame_detect);
		switch(frame_detect.TypeMessage)
		{
			case 1:
				Usart_SendNumber(frame_detect.TypeMessage);
				Usart_Send_Char('\n');
				Usart_Send_String("ROUND3x3");
				flash_write_str.Selection_round = (uint8_t)3;
				select_round = 3;
				game_round = 1;
				score_player1 = 0;
				score_player2 =0;
				count1 =0;
				count2 =0;
				UI_Points1(count1);
				UI_Points2(count2);
				UI_Score1(score_player1);
				UI_Score2(score_player2);
				UI_RoundNumber(game_round, select_round);
				flag_check_save_flash = 1;	
			break;
			
			case 2:
				Usart_SendNumber(frame_detect.TypeMessage);
				Usart_Send_Char('\n');
				Usart_Send_String("ROUND5x5");
				flash_write_str.Selection_round = (uint8_t)5;
				select_round = 5;
				game_round = 1;
				score_player1 = 0;
				score_player2 =0;
				count1 =0;
				count2 =0;
				UI_Points1(count1);
				UI_Points2(count2);
				UI_Score1(score_player1);
				UI_Score2(score_player2);
				UI_RoundNumber(game_round, select_round);
				flag_check_save_flash = 1;
			break;
			
			case 3:
				Usart_SendNumber(frame_detect.TypeMessage);
				Usart_Send_Char('\n');
				Usart_Send_String("ROUND7x7");
				flash_write_str.Selection_round = (uint8_t)7;
				select_round = 7;
				game_round = 1;
				score_player1 = 0;
				score_player2 =0;
				count1 =0;
				count2 =0;
				UI_Points1(count1);
				UI_Points2(count2);
				UI_Score1(score_player1);
				UI_Score2(score_player2);
				UI_RoundNumber(game_round, select_round);
				flag_check_save_flash = 1;
			break;
			
			case 4:
				Usart_SendNumber(frame_detect.TypeMessage);
				Usart_Send_Char('\n');
				Usart_Send_String("NAME_PLAYER_1");
				free(string_name1);
				string_name1 = malloc(frame_detect.LengthData-2);
				fsm_len_string_name1 = frame_detect.LengthData-2;
				flash_read_len_string1 = fsm_len_string_name1;
				memcpy(string_name1, frame_detect.Data, frame_detect.LengthData-2);
				Usart_Send_Char('\n');
				Usart_Send_String((char *)string_name1);
				u8 len;
				score_player1 = 0;
				score_player2 =0;
				count1 =0;
				count2 =0;
				UI_Points1(count1);
				UI_Points2(count2);
				UI_Score1(score_player1);
				UI_Score2(score_player2);
				for(len = 0 ; len < frame_detect.LengthData-2; len ++)
				{
					flash_write_str.Name_Player1[len] = string_name1[len];
				}	
				UI_NamePlayer(0,string_name1 );
				flag_check_save_flash = 1;
			break;
			
			case 5: 
				Usart_SendNumber(frame_detect.TypeMessage);
				Usart_Send_Char('\n');
				Usart_Send_String("NAME_PLAYER_2");
				string_name2 = malloc(frame_detect.LengthData-2);
				fsm_len_string_name2 = frame_detect.LengthData-2;
				flash_read_len_string2 = fsm_len_string_name2;
				memcpy(string_name2, frame_detect.Data, frame_detect.LengthData-2);
				Usart_Send_Char('\n');
				Usart_Send_String((char *)string_name2);
				for(len = 0 ; len <frame_detect.LengthData-2; len ++)
				{
					flash_write_str.Name_Player2[len] = string_name2[len];
				}
				score_player1 = 0;
				score_player2 =0;
				count1 =0;
				count2 =0;
				UI_Points1(count1);
				UI_Points2(count2);
				UI_Score1(score_player1);
				UI_Score2(score_player2);
				UI_NamePlayer(1, string_name2);
				flag_check_save_flash = 1;		
			break;
		}
		length_arr_recerive = 0;
	}
}

void Print_Data_Detect(FrameMsg_t frame)
{
	Usart_Send_Char((char)frame.StartFrame);
	Usart_SendNumber(frame.TypeMessage);
	Usart_SendNumber(frame.LengthData);
	if(frame_detect.LengthData > 2 )
	{
		Usart_Send_String((char *)frame.Data);
	}
	Usart_SendNumber(frame.CheckFrame);
}

void SYS_WriteFlash(void)
{
	uint32_t address = 0x0800FC00;
	if(flag_check_save_flash == 1)
	{
		Flash_Unlock();
		Flash_Erase(address);
		Flash_WriteStruct(&address, flash_write_str, flash_read_len_string1, flash_read_len_string1 );
		Flash_Lock();		
		flag_check_save_flash = 0;
	}
}

void SYS_ReadFlash(void)
{
	uint32_t add = 0x0800FC00;
	flash_read_str = Flash_ReadStruct(&add, flash_read_str);
	select_round = flash_read_str.Selection_round;
	game_round = flash_read_str.Round;
	previous_point1 = flash_read_str.Point1;
	count1 = flash_read_str.Point1;
	previous_point2 = flash_read_str.Point2;
	count2 = flash_read_str.Point2;
	score_past1 = flash_read_str.Score1;
	score_past2 = flash_read_str.Score2;	
//	free(string_name1);
//	string_name1 = malloc(flash_read_len_string1);
	
}