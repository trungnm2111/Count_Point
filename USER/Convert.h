#ifndef CONVERT_H
#define CONVERT_H

#include "stdio.h"
#include "stdint.h"
#include <stdlib.h>
#include "string.h"

// typedef union 
// {
//     *uint8_t data_string[];
//     *uint8_t byte[];
// }data_format_string_byte;
typedef union 
{
    uint32_t data_int;
    uint8_t bytes[4];
} data_format_int_bytes;


typedef union 
{
    uint16_t data_uint16;
    uint8_t bytes[2];
} data_format_uint8_16_t;

uint8_t *Sec_Convert_From_Int_To_Bytes(int data);
uint16_t Sec_Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2);
char* Convert_HexToString(uint8_t* arr_in, size_t length);
uint16_t Sec_Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2);

#endif // CONVERT_H
