#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

size_t btol(char* buff, const size_t typesize)
{
    size_t num = 0;

    for(size_t i = 0; i < typesize; i++)
    {   
        unsigned char to_shift = (unsigned char)buff[i];
        num |= ((to_shift << ((i) * 8)));
    }

    return num;
}