#ifndef _BUTTON_H_
#define _BUTTON_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART	 
#include "stdio.h"
#include "stm32f10x_tim.h"
#include "gpio.h"
#include "uart.h"
#include "sys.h"
	 
extern uint8_t current_player;
extern uint8_t game_round;
extern	uint8_t score_player1, score_player2;
extern uint16_t count1 , count2;

void BUTTON_CountProcess(void);
void BUTTON_Reads(void);
void BUTTON_Display(void);
void BUTTON_Read3(void);

#ifdef __cplusplus
}
#endif

#endif
