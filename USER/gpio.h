#ifndef _GPIO_H_
#define _GPIO_H_

#include "sys.h"

#define PIN_LED_RED GPIO_Pin_5
#define PORT_LED_RED GPIOB
#define PIN_LED_GREEN GPIO_Pin_6
#define PORT_LED_GREEN GPIOB

#define PIN_BUTTON_1 GPIO_Pin_0
#define PORT_BUTTON_1 GPIOA
#define PIN_BUTTON_2 GPIO_Pin_1
#define PORT_BUTTON_2 GPIOA
#define PIN_BUTTON_RESET GPIO_Pin_2
#define PORT_BUTTON_RESET GPIOA


void GPIO_Inits(void);
void GPIO_LedChange(void);

#endif
