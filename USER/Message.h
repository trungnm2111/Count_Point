    #ifndef MESSAGE_H
#define MESSAGE_H

#include "stdint.h"
#include "string.h"
#include "uart.h"

#define START_BYTE          0xAA
#define LENGTH_DEFAULT      2 /* StartFrame 1 + TypeMessage 1 */
#define LENGTH_ROUND        2 /* CheckFrame 2 */
#define LENGTH_BASE         2 /* CheckFrame 2 */

// #define END_STRING          0x21 /* D?u ch?m than !*/
/* TypeMessage */
typedef enum
{
    ROUND3x3        = 1,
    ROUND5x5        = 2,
    ROUND7X7        = 3,
    NAME_PLAYER_1   = 4,
    NAME_PLAYER_2   = 5,
    POINT1          = 6,
    POINT2          = 7,
    SCORE1          = 8,
    SCORE2          = 9,
    ROUND           = 10,  
} type_message_e;

/* B?n tin c?p nh?t */
typedef struct
{
    uint8_t StartFrame;
    uint8_t TypeMessage;
    uint16_t LengthData; 
    uint8_t  Data[16];
    uint16_t CheckFrame;
} FrameMsg_t;

/*
    @brief: H�m t?o Frame data chu?n.
    @node: Ch?c nang c?a h�m l� chuy?n data t? d?ng struct v? d?ng arr.
    @param datain: L� m?t struct chua c�c th�ng tin du?c ngu?i d�ng ch? d?nh d? t?o b?n tin.
    @param dataout: L� con tr? d�ng d? l?y m?ng sao khi t?o th�nh c�ng.
    @retval: Tr? v? 0 l� l?i, L?n hon 0 l� th�nh c�ng.
*/
uint8_t SEC_Message_Create_Frame(FrameMsg_t DataIn, uint8_t *DataOut);

/*
    @brief: H�m t�ch Frame data.
    @node: Ch?c nang c?a h�m l� chuy?n data t? d?ng arr v? d?ng struct.
    @param datain: L� m?t m?ng ch?a data.
    @param dataout: L� m?t struct ch?a data d?u ra.
    @retval: tr? v? 1 th�nh c�ng, tr? v? 0 l� l?i.
*/
uint8_t SEC_Message_Detect_Frame(uint8_t *DataIn, FrameMsg_t *DataOut, uint16_t length_arr);
uint16_t CheckSum(uint8_t *buf, uint8_t len);
void Message_SendPoint1(uint8_t point1);
void Message_SendPoint2(uint8_t point2);
void Message_SendScore1(uint8_t score1);
void Message_SendScore2(uint8_t score2);
void Message_SendRound(uint8_t round);

#endif // MESSAGE_H
