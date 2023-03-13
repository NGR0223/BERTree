//
// Created by ngr on 2023/3/13.
//

#include <stdlib.h>
#include <string.h>
#include "../include/IndefiniteArray.h"

IndefArray *create_indef_array(uint32_t capacity)
{
    IndefArray *pIndefArray = (IndefArray *) calloc(1, sizeof(IndefArray));
    pIndefArray->capacity = capacity;
    pIndefArray->length = 0;
    pIndefArray->data = (unsigned char *) calloc(capacity, sizeof(unsigned char));
    return pIndefArray;
}

void delete_indef_array(IndefArray *pIndefArray)
{
    if (pIndefArray != NULL)
    {
        if (pIndefArray->data != NULL)
        {
            free(pIndefArray->data);
            pIndefArray->data = NULL;
        }
        free(pIndefArray);
        pIndefArray = NULL;
    }
}

uint32_t set_indef_array_data(IndefArray *pIndefArray, unsigned char *newData, uint32_t lengthNewData)
{
    if (pIndefArray == NULL)
    {
        return 0;
    }

    if (lengthNewData > pIndefArray->capacity)
    {
        pIndefArray->capacity = lengthNewData;
        if (pIndefArray->data)
        {
            free(pIndefArray->data);
        }
        pIndefArray->data = (unsigned char *) calloc(lengthNewData, sizeof(unsigned char));
    }
    else
    {
        memset(pIndefArray->data, 0, pIndefArray->capacity);
    }
    pIndefArray->length = lengthNewData;
    memcpy(pIndefArray->data, newData, lengthNewData);

    return lengthNewData;
}

unsigned char *get_indef_array_data(IndefArray *pIndefArray, uint32_t lengthData)
{
    if (lengthData > pIndefArray->length || pIndefArray->data == NULL)
    {
        return NULL;
    }

    unsigned char *data = (unsigned char *) calloc(lengthData, sizeof(unsigned char));
    memcpy(data, pIndefArray, lengthData);

    return data;
}

void copy_indef_array(IndefArray *dest, IndefArray *src)
{
    if (dest == NULL || src == NULL)
    {
        return;
    }
    dest->capacity = src->capacity;
    dest->length = src->length;
    if (dest->data != NULL)
    {
        free(dest->data);
    }
    dest->data = (unsigned char *) calloc(src->capacity, sizeof(unsigned char));
    memcpy(dest->data, src->data, src->length);
}