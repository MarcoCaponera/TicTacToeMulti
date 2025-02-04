#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t ltob(const char* buff, const size_t typesize)
{
    size_t num = 0;

    for(size_t i = 0; i < typesize; i++)
    {   
        unsigned char to_shift = (unsigned char)buff[i];
        num |= ((to_shift << ((typesize - i - 1) * 8)));
    }
    
    return num;
}

char* num_to_str(const size_t num, const size_t base)
{
    size_t digits = 0;
    size_t temp_num = num;
    do
    {
        temp_num = temp_num / base;
        digits++;
    }while(temp_num != 0);

    char* str = malloc(digits+1);
    memset(str, 0, digits+1);

    size_t curr_num = num;
    for(size_t i = 0; i < digits; i++)
    {
        size_t base_pow = (pow(base, digits - i - 1));
        size_t digit = curr_num / base_pow;
        curr_num -= digit * base_pow;
        char ch;
        switch(digit)
        {
            case 0:
                ch = '0';
                break;
            case 1:
                ch = '1';
                break;
            case 2:
                ch = '2';
                break;
            case 3:
                ch = '3';
                break;
            case 4:
                ch = '4';
                break;
            case 5:
                ch = '5';
                break;
            case 6:
                ch = '6';
                break;
            case 7:
                ch = '7';
                break;
            case 8:
                ch = '8';
                break;
            case 9:
                ch = '9';
                break;
            default:
                break;
        }
        str[i] = ch;
    }

    str[digits+1] = '\0';

    return str;
}