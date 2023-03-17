//
// Created by ngr on 2023/3/13.
//

#include <stdlib.h>
#include <string.h>
#include "../include/indefiniteArray.h"
#include "../../Base/include/base.h"

IndefArray *create_indef_array(int32_t capacity)
{
    IndefArray *pIndefArray = (IndefArray *) calloc(1, sizeof(IndefArray));
    pIndefArray->capacity = capacity;
    pIndefArray->length = 0;
    pIndefArray->index = 0;
    pIndefArray->data = (unsigned char *) calloc(capacity, sizeof(unsigned char));
    return pIndefArray;
}

void delete_indef_array(IndefArray **ppIndefArray)
{
    if (*ppIndefArray != NULL)
    {
        if ((*ppIndefArray)->data != NULL)
        {
            free((*ppIndefArray)->data);
            (*ppIndefArray)->data = NULL;
        }
        free(*ppIndefArray);
        *ppIndefArray = NULL;
    }
}

void set_data_indef_array(IndefArray *pIndefArray, unsigned char *data, int32_t lengthData, int32_t *errCode)
{
    if (pIndefArray == NULL || data == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }

    if (lengthData > pIndefArray->capacity)
    {
        pIndefArray->capacity = lengthData;
        if (pIndefArray->data)
        {
            free(pIndefArray->data);
            pIndefArray->data = NULL;
        }
        pIndefArray->data = (unsigned char *) calloc(lengthData, sizeof(unsigned char));
    }
    else
    {
        memset(pIndefArray->data, 0, pIndefArray->capacity);
    }
    pIndefArray->length = lengthData;
    memcpy(pIndefArray->data, data, lengthData);

    *errCode = BER_ERROR_CODE_OK;
}

unsigned char *get_all_data_indef_array(IndefArray *pIndefArray, int32_t *lengthGotten, int32_t *errCode)
{
    if (pIndefArray == NULL || lengthGotten == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return NULL;
    }
    if (pIndefArray->data == NULL)
    {
        *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        return NULL;
    }
    unsigned char *data = (unsigned char *) calloc(pIndefArray->length, sizeof(unsigned char));
    memcpy(data, pIndefArray->data, pIndefArray->length);
    *lengthGotten = pIndefArray->length;

    *errCode = BER_ERROR_CODE_OK;
    return data;
}

void copy_indef_array(IndefArray *dest, IndefArray *src, int32_t *errCode)
{
    if (dest == NULL || src == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }
    dest->capacity = src->capacity;
    dest->length = src->length;
    if (dest->data != NULL)
    {
        free(dest->data);
        dest->data = NULL;
    }
    dest->data = (unsigned char *) calloc(src->capacity, sizeof(unsigned char));
    memcpy(dest->data, src->data, src->length);

    *errCode = BER_ERROR_CODE_OK;
}

void double_capacity_indef_array(IndefArray *pIndefArray, int32_t *errCode)
{
    if (pIndefArray == NULL)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_indef_array(pIndefArray, pIndefArray->capacity * 2, errCode);
    if (errCode)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void expand_capacity_indef_array(IndefArray *pIndefArray, int32_t newCapacity, int32_t *errCode)
{
    if (pIndefArray == NULL || newCapacity <= pIndefArray->capacity)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_indef_array(pIndefArray, newCapacity, errCode);
    if (errCode)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void reduce_capacity_indef_array(IndefArray *pIndefArray, int32_t newCapacity, int32_t *errCode)
{
    if (pIndefArray == NULL || newCapacity >= pIndefArray->capacity)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_indef_array(pIndefArray, newCapacity, errCode);
    if (errCode)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

static void resize_capacity_indef_array(IndefArray *pIndefArray, int32_t newCapacity, int32_t *errCode)
{
    if (pIndefArray == NULL || newCapacity <= 0)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    pIndefArray->capacity = newCapacity;
    /*
     * If index is bigger than new capacity, the index will be set to zero
     */
    if (pIndefArray->index > newCapacity - 1)
    {
        pIndefArray->index = 0;
    }
    /*
     * If new capacity is smaller than length of data in IndefArray, it will not copy old data to new data space
     */
    unsigned char *tmpData = (unsigned char *) calloc(newCapacity, sizeof(unsigned char));
    if (newCapacity >= pIndefArray->length)
    {
        memcpy(tmpData, pIndefArray->data, pIndefArray->length);
        free(pIndefArray->data);
        pIndefArray->data = tmpData;
    }
    else
    {
        pIndefArray->length = 0;
    }
}

unsigned char get_octet_indef_array(IndefArray *pIndefArray, int32_t *errCode)
{
    if (pIndefArray == NULL || errCode == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return 0;
    }
    if (pIndefArray->index + 1 > pIndefArray->length)
    {
        *errCode = BER_ERROR_CODE_NO_ENOUGH_OCTETS;
        return 0;
    }
    if (pIndefArray->length == 0 || pIndefArray->data == NULL)
    {
        *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        return 0;
    }
    unsigned char octet = *(pIndefArray->data + pIndefArray->index);
    pIndefArray->index++;

    *errCode = BER_ERROR_CODE_OK;
    return octet;
}

unsigned char *get_octets_indef_array(IndefArray *pIndefArray, int32_t *errCode, int32_t expectedLength)
{
    if (pIndefArray == NULL || expectedLength == 0)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return NULL;
    }
    if (pIndefArray->index + expectedLength > pIndefArray->length)
    {
        *errCode = BER_ERROR_CODE_NO_ENOUGH_OCTETS;
        return NULL;
    }
    if (pIndefArray->length == 0 || pIndefArray->data == NULL)
    {
        *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        return NULL;
    }
    unsigned char *data = (unsigned char *) calloc(expectedLength, sizeof(unsigned char));
    memcpy(data, pIndefArray->data + pIndefArray->index, expectedLength);
    pIndefArray->index += expectedLength;

    *errCode = BER_ERROR_CODE_OK;
    return data;
}


void append_octet_indef_array(IndefArray *pIndefArray, unsigned char octet, int32_t *errCode)
{
    if (pIndefArray == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }
    if (pIndefArray->length == pIndefArray->capacity)
    {
//        IndefArray *pNewIndefArray = create_indef_array(pIndefArray->capacity * 2);
//        memcpy(pNewIndefArray->data, pIndefArray->data, pIndefArray->length);
//        pNewIndefArray->data[pNewIndefArray->length] = octet;
//        pNewIndefArray->index = pIndefArray->index;
//        pNewIndefArray->length = pIndefArray->length + 1;
    }
    else
    {
        pIndefArray->data[pIndefArray->length] = octet;
        pIndefArray->length++;
    }

    *errCode = BER_ERROR_CODE_OK;
}

void append_octets_indef_array(IndefArray *pIndefArray, unsigned char *octets, int32_t appendedLength, int32_t *errCode)
{
    if (pIndefArray == NULL || octets == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }
    if (pIndefArray->length + appendedLength > pIndefArray->capacity)
    {
//        IndefArray *pNewIndefArray = create_indef_array(pIndefArray->capacity * 2);
//        memcpy(pNewIndefArray->data, pIndefArray->data, pIndefArray->length);
//        memcpy(pNewIndefArray->data + pIndefArray->length, octets, appendedLength);
//        pNewIndefArray->index = pIndefArray->index;
//        pNewIndefArray->length = pIndefArray->length + appendedLength;

    }
    else
    {
        memcpy(pIndefArray->data + pIndefArray->length, octets, appendedLength);
        pIndefArray->length += appendedLength;
    }
    *errCode = BER_ERROR_CODE_OK;
}