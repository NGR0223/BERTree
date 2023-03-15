//
// Created by ngr on 2023/3/13.
//

#ifndef BERTREE_INDEFINITEARRAY_H
#define BERTREE_INDEFINITEARRAY_H

#include <stdint.h>

typedef struct indef_array
{
    int32_t capacity;
    int32_t length;
    int32_t index;
    unsigned char *data;
} IndefArray;

IndefArray *create_indef_array(int32_t capacity);

void delete_indef_array(IndefArray **ppIndefArray);

int32_t set_data_indef_array(IndefArray *pIndefArray, unsigned char *data, int32_t lengthData);

int32_t get_all_data_indef_array(IndefArray *pIndefArray, unsigned char **data, int32_t *lengthData);

int32_t copy_indef_array(IndefArray *dest, IndefArray *src);

int32_t expand_indef_array(IndefArray *pIndefArray);

int32_t get_octet_indef_array(IndefArray *pIndefArray, unsigned char *octet);

int32_t get_octets_indef_array(IndefArray *pIndefArray, unsigned char **pOctets, int32_t expectedLength);

int32_t append_octet_indef_array(IndefArray *pIndefArray, unsigned char octet);

int32_t append_octets_indef_array(IndefArray *pIndefArray, unsigned char *octets, int32_t appendedLength);

#endif //BERTREE_INDEFINITEARRAY_H
