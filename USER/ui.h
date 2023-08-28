#ifndef _UI_H_
#define _UI_H_

#include "sys.h"

//#define ROUND_ONE 	1
//#define	ROUND_TWO 	2
//#define ROUND_THREE 3
//#define ROUND_FOUR  4
//#define ROUND_FIVE  5
//#define ROUND_SIX   6
//#define	FINAL		7

extern uint8_t previous_point1, previous_point2;
extern uint8_t score_past1, score_past2;

void UI_Frame(void);
void UI_RoundNumber(uint8_t number,uint8_t round);
void UI_Points1(uint8_t point);
void UI_Points2(uint8_t point);
void UI_NamePlayer(u8 mode, u8 *player);
void UI_Score1(uint8_t score);
void UI_Score2(uint8_t score);
void UI_MenuOption(void);
void UI_Init(void);

#endif
