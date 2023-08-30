#ifndef _SYS_H_
#define _SYS_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "ui.h"
#include "lcd.h"
#include "spi.h"
#include "uart.h"
#include "gpio.h"
#include "delay.h"
#include "touch.h"
#include "display.h"
#include "uart.h"
#include "button.h"
#include "Message.h"
#include "Convert.h"
#include "fsm_array_receive.h"
#include "flash.h"

extern Information flash_write_str, flash_read_str;
extern uint8_t player1[], player2[];
extern u8 flag_check_save_flash;
extern FrameMsg_t frame_detect;
extern uint8_t *string_name2;
extern uint8_t *string_name1;



void SYS_Init(void);
void SYS_Run(void);
void SYS_ButtonFunction(void);
void SYS_ReceiveFuntion(void);
void SYS_WriteFlash(void);
void SYS_ReadFlash(void);

#endif
