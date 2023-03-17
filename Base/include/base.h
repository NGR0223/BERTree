//
// Created by ngr on 2023/3/15.
//

#ifndef BERTREE_BASE_H
#define BERTREE_BASE_H

#include <stdint.h>

typedef enum
{
    BER_ERROR_CODE_RESERVED_LENGTH = -4,
    BER_ERROR_CODE_ARRAY_NO_DATA = -3,
    BER_ERROR_CODE_NO_ENOUGH_OCTETS = -2,
    BER_ERROR_CODE_INVALID_ARG = -1,
    BER_ERROR_CODE_OK = 0,
} BER_ERROR_CODE;


void print_error_info(int32_t errCode);

#endif //BERTREE_BASE_H
