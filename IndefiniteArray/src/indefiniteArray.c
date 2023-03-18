//
// Created by ngr on 2023/3/13.
//

#include <stdlib.h>
#include <string.h>
#include "../include/indefiniteArray.h"
#include "../../Base/include/base.h"


IA *create_ia(int32_t capacity)
{
    IA *pIA = (IA *) calloc(1, sizeof(IA));
    pIA->capacity = capacity;
    pIA->length = 0;
    pIA->index = 0;
    pIA->pOctets = (unsigned char *) calloc(capacity, sizeof(unsigned char));
    return pIA;
}

void delete_ia(IA **ppIA)
{
    if (*ppIA != NULL)
    {
        if ((*ppIA)->pOctets != NULL)
        {
            free((*ppIA)->pOctets);
            (*ppIA)->pOctets = NULL;
        }
        free(*ppIA);
        *ppIA = NULL;
    }
}


void copy_ia(IA *dest, IA *src, int32_t *errCode)
{
    if (dest == NULL || src == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    dest->capacity = src->capacity;
    dest->length = src->length;
    if (dest->pOctets != NULL)
    {
        free(dest->pOctets);
        dest->pOctets = NULL;
    }
    dest->pOctets = (unsigned char *) calloc(src->capacity, sizeof(unsigned char));
    memcpy(dest->pOctets, src->pOctets, src->length);

    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void double_capacity_ia(IA *pIA, int32_t *errCode)
{
    if (pIA == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_ia(pIA, pIA->capacity * 2, errCode);
    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void expand_capacity_ia(IA *pIA, int32_t newCapacity, int32_t *errCode)
{
    if (pIA == NULL || newCapacity <= pIA->capacity)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_ia(pIA, newCapacity, errCode);
    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void reduce_capacity_ia(IA *pIA, int32_t newCapacity, int32_t *errCode)
{
    if (pIA == NULL || newCapacity >= pIA->capacity)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    resize_capacity_ia(pIA, newCapacity, errCode);
    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

static void resize_capacity_ia(IA *pIA, int32_t newCapacity, int32_t *errCode)
{
    if (pIA == NULL || newCapacity <= 0)
    {
        if (errCode != NULL)
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
     * If new capacity is smaller than length of pOctets in IA, it will not copy old pOctets to new pOctets space
     */
    unsigned char *tmpData = (unsigned char *) calloc(newCapacity, sizeof(unsigned char));
    if (newCapacity >= pIA->length)
    {
        memcpy(tmpData, pIA->pOctets, pIA->length);
        free(pIA->pOctets);
        pIA->pOctets = tmpData;
    }
    else
    {
        pIA->length = 0;
    }
}

unsigned char get_octet_ia(IA *pIA, int32_t *errCode)
{
    if (pIA == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return 0;
    }
    if (pIA->index + 1 > pIA->length)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_NO_ENOUGH_OCTETS;
        }
        return 0;
    }
    if (pIA->length == 0 || pIA->pOctets == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        }
        return 0;
    }
    unsigned char octet = *(pIA->pOctets + pIA->index);
    pIA->index++;

    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
    return octet;
}

unsigned char *get_all_octets_ia(IA *pIA, int32_t *lengthGotten, int32_t *errCode)
{
    if (pIA == NULL || lengthGotten == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return NULL;
    }
    if (pIA->pOctets == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        }
        return NULL;
    }
    unsigned char *data = (unsigned char *) calloc(pIA->length, sizeof(unsigned char));
    memcpy(data, pIA->pOctets, pIA->length);
    *lengthGotten = pIA->length;
    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
    return data;
}

unsigned char *get_octets_ia(IA *pIA, int32_t expectedLength, int32_t *errCode)
{
    if (pIA == NULL || expectedLength == 0)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return NULL;
    }
    if (pIA->index + expectedLength > pIA->length)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_NO_ENOUGH_OCTETS;
        }
        return NULL;
    }
    if (pIA->length == 0 || pIA->pOctets == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_ARRAY_NO_DATA;
        }
        return NULL;
    }
    unsigned char *data = (unsigned char *) calloc(expectedLength, sizeof(unsigned char));
    memcpy(data, pIA->pOctets + pIA->index, expectedLength);
    pIA->index += expectedLength;

    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
    return data;
}


void set_all_octets_ia(IA *pIA, unsigned char *pOctets, int32_t lengthData, int32_t *errCode)
{
    if (pIA == NULL || pOctets == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    if (lengthData > pIA->capacity)
    {
        pIA->capacity = lengthData;
        if (pIA->pOctets)
        {
            free(pIA->pOctets);
            pIA->pOctets = NULL;
        }
        pIA->pOctets = (unsigned char *) calloc(lengthData, sizeof(unsigned char));
    }
    else
    {
        memset(pIA->pOctets, 0, pIA->capacity);
    }
    pIA->length = lengthData;
    memcpy(pIA->pOctets, pOctets, lengthData);

    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void append_octet_ia(IA *pIA, unsigned char octet, int32_t *errCode)
{
    if (pIA == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    if (pIA->length == pIA->capacity)
    {
//        IA *pNewIA = create_ia(pIA->capacity * 2);
//        memcpy(pNewIA->pOctets, pIA->pOctets, pIA->length);
//        pNewIA->pOctets[pNewIA->length] = octet;
//        pNewIA->index = pIA->index;
//        pNewIA->length = pIA->length + 1;
    }
    else
    {
        pIA->pOctets[pIA->length] = octet;
        pIA->length++;
    }

    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

void append_octets_ia(IA *pIA, unsigned char *octets, int32_t appendedLength, int32_t *errCode)
{
    if (pIA == NULL || octets == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }
    if (pIA->length + appendedLength > pIA->capacity)
    {
//        IA *pNewIA = create_ia(pIA->capacity * 2);
//        memcpy(pNewIA->pOctets, pIA->pOctets, pIA->length);
//        memcpy(pNewIA->pOctets + pIA->length, octets, appendedLength);
//        pNewIA->index = pIA->index;
//        pNewIA->length = pIA->length + appendedLength;

    }
    else
    {
        memcpy(pIA->pOctets + pIA->length, octets, appendedLength);
        pIA->length += appendedLength;
    }
    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}