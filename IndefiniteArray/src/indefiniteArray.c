//
// Created by ngr on 2023/3/13.
//

#include <stdlib.h>
#include <string.h>
#include "../include/indefiniteArray.h"
#include "../../Base/include/base.h"


IA *create_indef_array(int32_t capacity)
{
    IA *pIA = (IA *) calloc(1, sizeof(IA));
    pIA->capacity = capacity;
    pIA->length = 0;
    pIA->index = 0;
    pIA->data = (unsigned char *) calloc(capacity, sizeof(unsigned char));
    return pIA;
}

void delete_indef_array(IA **ppIA)
{
    if (*ppIA != NULL)
    {
        if ((*ppIA)->data != NULL)
        {
            free((*ppIA)->data);
            (*ppIA)->data = NULL;
        }
        free(*ppIA);
        *ppIA = NULL;
    }
}

void set_data_indef_array(IA *pIA, unsigned char *data, int32_t lengthData, int32_t *errCode)
{
    if (pIA == NULL || data == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }

    if (lengthData > pIA->capacity)
    {
        pIA->capacity = lengthData;
        if (pIA->data)
        {
            free(pIA->data);
            pIA->data = NULL;
        }
        pIA->data = (unsigned char *) calloc(lengthData, sizeof(unsigned char));
    }
    else
    {
        memset(pIA->data, 0, pIA->capacity);
    }
    pIA->length = lengthData;
    memcpy(pIA->data, data, lengthData);

    *errCode = BER_ERROR_CODE_OK;
}

unsigned char *get_all_data_indef_array(IA *pIA, int32_t *lengthGotten, int32_t *errCode)
{
    if (pIA == NULL || lengthGotten == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return NULL;
    }
    if (pIA->data == NULL)
    {
        *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        return NULL;
    }
    unsigned char *data = (unsigned char *) calloc(pIA->length, sizeof(unsigned char));
    memcpy(data, pIA->data, pIA->length);
    *lengthGotten = pIA->length;

    *errCode = BER_ERROR_CODE_OK;
    return data;
}

void copy_indef_array(IA *dest, IA *src, int32_t *errCode)
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

void double_capacity_indef_array(IA *pIA, int32_t *errCode)
{
    if (pIA == NULL)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_indef_array(pIA, pIA->capacity * 2, errCode);
    if (errCode)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void expand_capacity_indef_array(IA *pIA, int32_t newCapacity, int32_t *errCode)
{
    if (pIA == NULL || newCapacity <= pIA->capacity)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_indef_array(pIA, newCapacity, errCode);
    if (errCode)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void reduce_capacity_indef_array(IA *pIA, int32_t newCapacity, int32_t *errCode)
{
    if (pIA == NULL || newCapacity >= pIA->capacity)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_indef_array(pIA, newCapacity, errCode);
    if (errCode)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

static void resize_capacity_indef_array(IA *pIA, int32_t newCapacity, int32_t *errCode)
{
    if (pIA == NULL || newCapacity <= 0)
    {
        if (errCode)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    pIA->capacity = newCapacity;
    /*
     * If index is bigger than new capacity, the index will be set to zero
     */
    if (pIA->index > newCapacity - 1)
    {
        pIA->index = 0;
    }
    /*
     * If new capacity is smaller than length of data in IA, it will not copy old data to new data space
     */
    unsigned char *tmpData = (unsigned char *) calloc(newCapacity, sizeof(unsigned char));
    if (newCapacity >= pIA->length)
    {
        memcpy(tmpData, pIA->data, pIA->length);
        free(pIA->data);
        pIA->data = tmpData;
    }
    else
    {
        pIA->length = 0;
    }
}

unsigned char get_octet_indef_array(IA *pIA, int32_t *errCode)
{
    if (pIA == NULL || errCode == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return 0;
    }
    if (pIA->index + 1 > pIA->length)
    {
        *errCode = BER_ERROR_CODE_NO_ENOUGH_OCTETS;
        return 0;
    }
    if (pIA->length == 0 || pIA->data == NULL)
    {
        *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        return 0;
    }
    unsigned char octet = *(pIA->data + pIA->index);
    pIA->index++;

    *errCode = BER_ERROR_CODE_OK;
    return octet;
}

unsigned char *get_octets_indef_array(IA *pIA, int32_t *errCode, int32_t expectedLength)
{
    if (pIA == NULL || expectedLength == 0)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return NULL;
    }
    if (pIA->index + expectedLength > pIA->length)
    {
        *errCode = BER_ERROR_CODE_NO_ENOUGH_OCTETS;
        return NULL;
    }
    if (pIA->length == 0 || pIA->data == NULL)
    {
        *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        return NULL;
    }
    unsigned char *data = (unsigned char *) calloc(expectedLength, sizeof(unsigned char));
    memcpy(data, pIA->data + pIA->index, expectedLength);
    pIA->index += expectedLength;

    *errCode = BER_ERROR_CODE_OK;
    return data;
}


void append_octet_indef_array(IA *pIA, unsigned char octet, int32_t *errCode)
{
    if (pIA == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }
    if (pIA->length == pIA->capacity)
    {
//        IA *pNewIA = create_indef_array(pIA->capacity * 2);
//        memcpy(pNewIA->data, pIA->data, pIA->length);
//        pNewIA->data[pNewIA->length] = octet;
//        pNewIA->index = pIA->index;
//        pNewIA->length = pIA->length + 1;
    }
    else
    {
        pIA->data[pIA->length] = octet;
        pIA->length++;
    }

    *errCode = BER_ERROR_CODE_OK;
}

void append_octets_indef_array(IA *pIA, unsigned char *octets, int32_t appendedLength, int32_t *errCode)
{
    if (pIA == NULL || octets == NULL)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }
    if (pIA->length + appendedLength > pIA->capacity)
    {
//        IA *pNewIA = create_indef_array(pIA->capacity * 2);
//        memcpy(pNewIA->data, pIA->data, pIA->length);
//        memcpy(pNewIA->data + pIA->length, octets, appendedLength);
//        pNewIA->index = pIA->index;
//        pNewIA->length = pIA->length + appendedLength;

    }
    else
    {
        memcpy(pIA->data + pIA->length, octets, appendedLength);
        pIA->length += appendedLength;
    }
    *errCode = BER_ERROR_CODE_OK;
}