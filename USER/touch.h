#ifndef _TOUCH_H_
#define _TOUCH_H_

#ifdef __cplusplus
 extern "C" {
#endif

	 
#include "sys.h"
#include "display.h"


#define T_IRQ_PIN GPIO_Pin_5
#define T_IRQ_POST GPIOA
#define T_DO_PIN GPIO_Pin_6 // MISO
#define T_DO_POST GPIOA
#define T_DIN_PIN GPIO_Pin_7 // MOSI
#define T_DIN_POST GPIOA
#define T_CS_PIN GPIO_Pin_4
#define T_CS_POST GPIOA
#define T_CLK_PIN GPIO_Pin_3
#define T_CLK_POST GPIOA

#define NO_OF_POSITION_SAMPLES	 	1000

/*man hinh doc: TFT_Gui_Direction(0)*/
//#define CMD_RDY             			0X90
//#define CMD_RDX             			0XD0

//#define X_OFFSET									13
//#define Y_OFFSET									15
//#define X_MAGNITUDE								1.16
//#define Y_MAGNITUDE								1.16


/*CONVERTING 16bit Value to Screen coordinates
 65535/273 = 240!
 65535/204 = 320!
*/
/*man hinh doc: TFT_Gui_Direction(0)*/
//#define X_TRANSLATION							273
//#define Y_TRANSLATION							204

/*man hinh ngang: TFT_Gui_Direction(3)*/
#define CMD_RDY             			0XD0
#define CMD_RDX             			0X90

#define X_TRANSLATION					204
#define Y_TRANSLATION					273

#define X_OFFSET						15
#define Y_OFFSET						13
#define X_MAGNITUDE						1.16
#define Y_MAGNITUDE						1.16

//RETURN VALUES FOR TP_Touchpad_Pressed 
#define TOUCHPAD_NOT_PRESSED			0
#define TOUCHPAD_PRESSED					1

//RETURN VALUES FOR TP_Read_Coordinates
#define TOUCHPAD_DATA_OK					1
#define TOUCHPAD_DATA_NOISY				0

typedef struct{
	unsigned char	vruc_DataOld;
	unsigned int 	vruc_CountAccess;
	unsigned char	vruc_FlagChange;
	unsigned char	vruc_hold;
}TS_TypeInput;
extern TS_TypeInput BT_IRQ_Pin;

extern uint16_t coordinates_x, coordinates_y;
extern uint16_t touch_pad[];
extern uint16_t select_round;
extern uint8_t flag_touch_menu;

void TOUCH_Init(void);
//Internal Touchpad command, do not call directly
uint16_t TP_Read(void);

//Internal Touchpad command, do not call directly
void TP_Write(uint8_t value);

//Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2]);

//Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void);

void Fn_INPUT_ReadInput (unsigned char _vruc_Input, TS_TypeInput *_vrts_DataInput);
void TP_IRQ_Pin_Run(void);
void TP_Screen(void);
void TP_TouchMenu(void);
void TP_Touch(void);
void TP_TouchReset(void);

#ifdef __cplusplus
}
#endif

#endif
