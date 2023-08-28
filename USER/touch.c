#include "touch.h"
#include "math.h"

uint16_t select_round;
uint8_t flag_touch_menu = 0;
TS_TypeInput BT_IRQ_Pin;
static void reset(void);

void TOUCH_Init(void)
{
	GPIO_InitTypeDef GPIO_TOUCH;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/*Configure GPIO pin : PtPin */
	GPIO_TOUCH.GPIO_Pin = T_IRQ_PIN;
	GPIO_TOUCH.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(T_IRQ_POST, &GPIO_TOUCH);

	GPIO_TOUCH.GPIO_Pin = T_DO_PIN;
	GPIO_TOUCH.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(T_DO_POST, &GPIO_TOUCH);
	
	/*Configure GPIO pins : PEPin PEPin PEPin */
	GPIO_TOUCH.GPIO_Pin = T_CLK_PIN;
	GPIO_TOUCH.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_TOUCH.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(T_CLK_POST, &GPIO_TOUCH);

	GPIO_TOUCH.GPIO_Pin = T_DIN_PIN;
	GPIO_TOUCH.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_TOUCH.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(T_DIN_POST, &GPIO_TOUCH);

	GPIO_TOUCH.GPIO_Pin = T_CS_PIN;
	GPIO_TOUCH.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_TOUCH.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(T_CS_POST, &GPIO_TOUCH);
	
	BT_IRQ_Pin.vruc_FlagChange = 1;
}

void Fn_INPUT_ReadInput(unsigned char _vruc_Input, TS_TypeInput *_vrts_DataInput)
{
  _vrts_DataInput->vruc_DataOld = _vruc_Input;
  if(!_vruc_Input)
	{
    if(_vrts_DataInput->vruc_DataOld == _vruc_Input)
		{
      if(_vrts_DataInput->vruc_CountAccess <= 20)
			{ // thoi gian nhan nut < 500ms -> nhan nha; nguoc lai la nhan giu
        _vrts_DataInput->vruc_CountAccess++;
        if(_vrts_DataInput->vruc_CountAccess == 20)
				{ // nhan nha
          _vrts_DataInput->vruc_FlagChange = 1;
          _vrts_DataInput->vruc_hold = 0;
        }
      }
      else// nhan giu
      {
				_vrts_DataInput->vruc_FlagChange = 0;
        _vrts_DataInput->vruc_hold = 1;
      }
    }
    else
		{
      _vrts_DataInput->vruc_CountAccess = 0;
    }
  }
  else
	{
    _vrts_DataInput->vruc_CountAccess = 0;
  }
}

void TP_IRQ_Pin_Run(void)
{
  Fn_INPUT_ReadInput (GPIO_ReadInputDataBit(T_IRQ_POST,T_IRQ_PIN), (TS_TypeInput*) (&BT_IRQ_Pin));
}

//Internal Touchpad command, do not call directly
uint16_t TP_Read(void){
	uint8_t i = 16;
	uint16_t value = 0;

	while(i > 0x00){
		value <<= 1;

		GPIO_WriteBit(T_CLK_POST, T_CLK_PIN, Bit_SET);
		GPIO_WriteBit(T_CLK_POST, T_CLK_PIN, Bit_RESET);
	
		if(GPIO_ReadInputDataBit(T_DO_POST, T_DO_PIN) != 0){
			value++;
		}
		i--;
	}

	return value;
}

//Internal Touchpad command, do not call directly
void TP_Write(uint8_t value)
{
	uint8_t i = 0x08;
	GPIO_WriteBit(T_CLK_POST, T_CLK_PIN, Bit_RESET);	
	while(i > 0){
		if((value & 0x80) != 0x00){
			GPIO_WriteBit(T_DIN_POST, T_DIN_PIN, Bit_SET);
		}
		else{
			GPIO_WriteBit(T_DIN_POST, T_DIN_PIN, Bit_RESET);
		}
		value <<= 1;
		GPIO_WriteBit(T_CLK_POST, T_CLK_PIN, Bit_SET);
		GPIO_WriteBit(T_CLK_POST, T_CLK_PIN, Bit_RESET);        
		i--;
	}
}

//Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2]){
	uint32_t avg_x, avg_y = 0;		
	uint16_t rawx, rawy = 0;	
	uint32_t calculating_x, calculating_y = 0;

	uint32_t samples = NO_OF_POSITION_SAMPLES;
	uint32_t counted_samples = 0;	
	
	GPIO_WriteBit(T_CLK_POST, T_CLK_PIN, Bit_SET);		
	GPIO_WriteBit(T_DIN_POST, T_DIN_PIN, Bit_SET);		
	GPIO_WriteBit(T_CS_POST, T_CS_PIN, Bit_SET);		
	GPIO_WriteBit(T_CS_POST, T_CS_PIN, Bit_RESET);
	TP_IRQ_Pin_Run();
	while((samples > 0)&&(BT_IRQ_Pin.vruc_FlagChange == 0)){			
		TP_Write(CMD_RDY);

		rawy = TP_Read();	
		avg_y += rawy;
		calculating_y += rawy;

		
		TP_Write(CMD_RDX);
		rawx = TP_Read();
		avg_x += rawx;
		calculating_x += rawx;
		samples--;
		counted_samples++;
	}	
	GPIO_WriteBit(T_CS_POST, T_CS_PIN, Bit_SET);
	if((counted_samples == NO_OF_POSITION_SAMPLES)&&(BT_IRQ_Pin.vruc_FlagChange == 0)){
	
		calculating_x /= counted_samples;
		calculating_y /= counted_samples;
		
		rawx = calculating_x;
		rawy = calculating_y;		
		
		rawx *= -1;
		rawy *= -1;
		
		//CONVERTING 16bit Value to Screen coordinates
		// 65535/273 = 240!
		// 65535/204 = 320!
		/*TFT_Gui_Direction(0)*/
//		Coordinates[0] = ((240 - (rawx/X_TRANSLATION)) - X_OFFSET)*X_MAGNITUDE;
//		Coordinates[1] = ((rawy/Y_TRANSLATION)- Y_OFFSET)*Y_MAGNITUDE;
		
		
		/*TFT_Gui_Direction(3)*/
		Coordinates[0] =  fabs((((rawx/X_TRANSLATION)) - X_OFFSET)*X_MAGNITUDE - 320);
		Coordinates[1] = ((240 - (rawy/Y_TRANSLATION))- Y_OFFSET)*Y_MAGNITUDE;
		

		return TOUCHPAD_DATA_OK;			
	}
	else{
		Coordinates[0] = 0;
		Coordinates[1] = 0;
		return TOUCHPAD_DATA_NOISY;
	}
	GPIO_WriteBit(T_CS_POST, T_CS_PIN, Bit_SET);
}

//Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void)
{
	TP_IRQ_Pin_Run();
	if(BT_IRQ_Pin.vruc_FlagChange == 0)
	{
		return TOUCHPAD_PRESSED;
	}
	else{
		return TOUCHPAD_NOT_PRESSED;
	}
}
uint16_t coordinates_x = 0;
uint16_t coordinates_y = 0;
uint16_t touch_pad[3];

void TP_Screen(void)
{
	LCD_direction(3);
	if(TP_Touchpad_Pressed())
	{
		coordinates_x = 0;
		coordinates_y = 0;
		if(TP_Read_Coordinates(touch_pad) == TOUCHPAD_DATA_OK)
		{
			coordinates_x = touch_pad[0];
			coordinates_y = touch_pad[1];
//			gui_circle(coordinates_x, coordinates_y, BLACK, 20 ,1);
		}
		if(coordinates_x > 35 && coordinates_x < 210 && coordinates_y > 5 && coordinates_y < 220)
		{
			reset();
		}
		coordinates_x = 0;
		coordinates_y = 0;
	}
//				Usart_SendNumber(coordinates_x);
//			Usart_Send_Char('\n');
//			Usart_SendNumber(coordinates_y);
//		coordinates_x = 0;
//		coordinates_y = 0;
}
 
void TP_TouchMenu(void)
{
		//select 3 round
	if(coordinates_x > 210 && coordinates_x < 320 && coordinates_y > 8 && coordinates_y < 39 && flag_touch_menu == 1)
	{
		select_round = 3;
		reset();
		coordinates_x = 0;
		coordinates_y = 0;
		flag_touch_menu = 0;
	}
	//select 5 round
	if(coordinates_x > 210 && coordinates_x < 320 && coordinates_y >= 39 && coordinates_y < 88 && flag_touch_menu == 1)
	{
		select_round = 5;
		reset();
		coordinates_x = 0;
		coordinates_y = 0;
		flag_touch_menu = 0;
	}
	//select 7 round
	if(coordinates_x > 210 && coordinates_x < 320 && coordinates_y >= 88 && coordinates_y < 137 && flag_touch_menu == 1)
	{
		select_round = 7;
		reset();
		coordinates_x = 0;
		coordinates_y = 0;
		flag_touch_menu = 0;
	}
		
	if(coordinates_x > 264 && coordinates_x < 316 && coordinates_y > 6 && coordinates_y < 38 && flag_touch_menu == 0)
	{
		UI_MenuOption();
		coordinates_x = 0;
		coordinates_y = 0;
	}	
	
	//press reset
}

void TP_TouchReset(void)
{
	if(coordinates_x > 35 && coordinates_x < 210 && coordinates_y > 5 && coordinates_y < 220)
	{
		reset();
	}
}

void TP_Touch(void)
{
	TP_TouchReset();
}

void reset(void)
{
	UI_Frame();
	game_round = 1;
	score_player1 = 0;
	score_player2 = 0;
	count1 = 0 , count2 = 0;
	UI_Points1(count1);
	UI_Points2(count2);
	UI_Score1(score_player1);
	UI_Score2(score_player2);
	UI_RoundNumber(game_round, select_round);
	UI_NamePlayer(0,flash_read_str.Name_Player1);
	UI_NamePlayer(1,flash_read_str.Name_Player2);
	flag_check_save_flash = 1;
}