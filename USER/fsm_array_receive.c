#include "fsm_array_receive.h"

fsm_state_e fsm_state = FSM_STATE_START_FRAME;

static uint8_t fsm_count_array = 0;
uint16_t length_arr_recerive = 0; 

uint8_t fsm_data_length;


uint8_t Fsm_Test_Array_Receive(uint8_t array_in, uint8_t *array_out)
{
    uint8_t temp_data = array_in;

    switch (fsm_state)
    {
        case FSM_STATE_START_FRAME:
            array_out[fsm_count_array] = temp_data;
            
            fsm_count_array++;

            if(fsm_count_array == FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE)
            {
                fsm_state = FSM_STATE_TYPE_MESSAGE;
            }
        break;
        
        case FSM_STATE_TYPE_MESSAGE:
            array_out[fsm_count_array] = temp_data;
            
            fsm_count_array++;

            if(fsm_count_array == FSM_STATE_CHANGE_VALUE_LENGHT_DATA)
            {
                fsm_state = FSM_STATE_LENGHT_DATA;
            }
        break;

        case FSM_STATE_LENGHT_DATA:
            array_out[fsm_count_array] = temp_data;
            
            fsm_count_array++;

            if(fsm_count_array == FSM_STATE_CHANGE_VALUE_END)
            {
                fsm_data_length = Sec_Convert_From_Bytes_To_Uint16(array_out[2], array_out[3]) + 4;
                // printf("\nfsm_data_length: %d\n", fsm_data_length);
                if(fsm_data_length < 22)
                {
                    fsm_state = FSM_STATE_END;
                }
                else if(fsm_data_length > 22)
                {
                    fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_END:
            array_out[fsm_count_array] = temp_data;
            
            fsm_count_array++;

            if(fsm_count_array == fsm_data_length)
            {
                length_arr_recerive = fsm_count_array;
                fsm_count_array = 0;
                fsm_state = FSM_STATE_START_FRAME;
                return 1;
            }
        break;
    }
    return 0; 
}
