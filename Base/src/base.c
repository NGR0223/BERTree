//
// Created by ngr on 2023/3/15.
//

#include <stdio.h>
#include "../include/base.h"


void print_error_info(int32_t errCode)
{
    switch (errCode)
    {
        case BER_ERROR_CODE_RESERVED_LENGTH:
            printf("First octet of Length is 255, which means reserved\n");
            break;
        case BER_ERROR_CODE_ARRAY_NO_DATA:
            printf("There is no data in a indefinite array\n");
            break;
        case BER_ERROR_CODE_NO_ENOUGH_OCTETS:
            printf("Expected number of octets is bigger than remain number of octets in indefinite array\n");
            break;
        case BER_ERROR_CODE_INVALID_ARG:
            printf("At least one argument of function is invalid\n");
            break;
        case BER_ERROR_CODE_OK:
            printf("No error\n");
            break;
        default:
            printf("Unknown error code\n");
            break;
    }
}