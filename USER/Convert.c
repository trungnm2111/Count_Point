#include "Convert.h"

/*
    @brief: Chuy?n m?ng các bi?n ki?u bytes sang chuoi ky tu 
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n m?ng các bi?n ki?u bytes sang chuoi ky tu
    @param data0: mang byte truyen vao .
    @param data1: Chuoi ky tu dau ra .
    @retval: chuoi ky tu.
*/

char* Convert_HexToString(uint8_t* arr_in, size_t arr_size)
{
    char* result = (char*)malloc(arr_size + 1);
    for (size_t i = 0; i < arr_size; i++) 
    {
        result[i] = (char)arr_in[i];
    }
    result[arr_size] = '\0';
    return result;
}

/*
    @brief: Chuy?n bi?n ki?u int sang d?ng m?ng byte
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n bi?n ki?u int sang d?ng m?ng byte 4 ph?n t?
    @param data: Là m?t bi?n ki?u int c?n du?c chuy?n sang m?ng byte.
    @retval: M?ng bytes.
*/
uint8_t *Sec_Convert_From_Int_To_Bytes(int data)
{
    static data_format_int_bytes input_convert;
    input_convert.data_int = data;
    return input_convert.bytes;
}
/*
    @brief: Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u uint16_t
    @node: Ch?c nang hàm du?c s? d?ng d? Chuy?n m?ng các bi?n ki?u bytes sang bi?n ki?u uint16_t
    @param data0: Bi?n d?u tiên c?a m?ng .
    @param data1: Bi?n th? hai c?a m?ng .
    @retval: Bi?n Uint16_t.
*/
uint16_t Sec_Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2)
{
    data_format_uint8_16_t input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;

    return input_convert.data_uint16;
}


//void Convert_From_String_To_Byte() 