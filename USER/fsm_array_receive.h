#ifndef FSM_ARRAY_RECEIVE_H
#define FSM_ARRAY_RECEIVE_H

#include "stdint.h"
#include "Convert.h"
#include "Message.h"


#define FSM_STATE 4 
typedef enum
{
    FSM_STATE_START_FRAME  = 0,
    FSM_STATE_TYPE_MESSAGE = 1,
    FSM_STATE_LENGHT_DATA  = 2,
    FSM_STATE_END          = 3,
} fsm_state_e;
 

typedef enum
{
    FSM_STATE_CHANGE_VALUE_START_FRAME  = 0, //1
    FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE = 1, //1
    FSM_STATE_CHANGE_VALUE_LENGHT_DATA  = 2, //2
    FSM_STATE_CHANGE_VALUE_END          = 4, //2
} fsm_state_change_value_e;
extern uint16_t length_arr_recerive;

uint8_t Fsm_Test_Array_Receive(uint8_t array_in, uint8_t *array_out);

#endif // FSM_ARRAY_RECEIVE_H
