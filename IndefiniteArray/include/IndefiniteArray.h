//
// Created by ngr on 2023/3/13.
//

#ifndef BERTREE_INDEFINITEARRAY_H
#define BERTREE_INDEFINITEARRAY_H

#include <stdint.h>

typedef struct indef_array
{
    uint32_t capacity;
    uint32_t length;
    unsigned char *data;
} IndefArray;

IndefArray *create_indef_array(uint32_t capacity);

void delete_indef_array(IndefArray *pIndefArray);

uint32_t set_indef_array_data(IndefArray *pIndefArray, unsigned char *newData, uint32_t lengthNewData);

unsigned char *get_indef_array_data(IndefArray *pIndefArray, uint32_t lengthData);

void copy_indef_array(IndefArray *dest, IndefArray *src);

#endif //BERTREE_INDEFINITEARRAY_H
