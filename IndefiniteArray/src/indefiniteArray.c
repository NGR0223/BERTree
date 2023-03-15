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

int32_t set_data_indef_array(IndefArray *pIndefArray, unsigned char *data, int32_t lengthData)
{
    if (pIndefArray == NULL || data == NULL)
    {
        return BER_ERROR_CODE_INVALID_ARG;
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

    return lengthData;
}

int32_t get_all_data_indef_array(IndefArray *pIndefArray, unsigned char **data, int32_t *lengthData)
{
    if (pIndefArray->data == NULL)
    {
        return IA_RETURN_VALUE_NO_ARG_PTR;
    }

    if (*data != NULL)
    {
        free(*data);
        *data = NULL;
    }
    *data = (unsigned char *) calloc(pIndefArray->length, sizeof(unsigned char));
    memcpy(*data, pIndefArray->data, pIndefArray->length);
    *lengthData = pIndefArray->length;

    return IA_RETURN_VALUE_OK;
}

int32_t copy_indef_array(IndefArray *dest, IndefArray *src)
{
    if (dest == NULL || src == NULL)
    {
        return IA_RETURN_VALUE_NO_ARRAY_PTR;
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

    return IA_RETURN_VALUE_OK;
}

int32_t expand_indef_array(IndefArray *pIndefArray)
{
    unsigned char *tmp = (unsigned char *) calloc(pIndefArray->capacity * 2, sizeof(unsigned char));
    memcpy(tmp, pIndefArray->data, pIndefArray->length);

    free(pIndefArray->data);
    pIndefArray->data = NULL;

    pIndefArray->data = tmp;
    pIndefArray->capacity *= 2;
    return IA_RETURN_VALUE_OK;
}

int32_t get_octet_indef_array(IndefArray *pIndefArray, unsigned char *octet)
{
    if (pIndefArray == NULL)
    {
        return IA_RETURN_VALUE_NO_ARRAY_PTR;
    }
    if (pIndefArray->index + 1 > pIndefArray->length)
    {
        return IA_RETURN_VALUE_OVER_REMAIN_LENGTH;
    }
    if (pIndefArray->length == -1 || pIndefArray->data == NULL)
    {
        return IA_RETURN_VALUE_NO_DATA_PTR;
    }
    if (octet == NULL)
    {
        return IA_RETURN_VALUE_NO_ARG_PTR;
    }
    *octet = *(pIndefArray->data + pIndefArray->index);
    pIndefArray->index++;

    return IA_RETURN_VALUE_OK;
}

int32_t get_octets_indef_array(IndefArray *pIndefArray, unsigned char **pOctets, int32_t expectedLength)
{
    if (pIndefArray == NULL)
    {
        return IA_RETURN_VALUE_NO_ARRAY_PTR;
    }
    if (pIndefArray->index + expectedLength > pIndefArray->length)
    {
        return IA_RETURN_VALUE_OVER_REMAIN_LENGTH;
    }
    if (pIndefArray->length == 0 || pIndefArray->data == NULL)
    {
        return IA_RETURN_VALUE_NO_DATA_PTR;
    }
    *pOctets = (unsigned char *) calloc(expectedLength, sizeof(unsigned char));
    memcpy(*pOctets, pIndefArray->data + pIndefArray->index, expectedLength);
    pIndefArray->index += expectedLength;

    return IA_RETURN_VALUE_OK;
}


int32_t append_octet_indef_array(IndefArray *pIndefArray, unsigned char octet)
{
    if (pIndefArray == NULL)
    {
        return IA_RETURN_VALUE_NO_ARRAY_PTR;
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

    return IA_RETURN_VALUE_OK;
}

int32_t append_octets_indef_array(IndefArray *pIndefArray, unsigned char *octets, int32_t appendedLength)
{
    if (pIndefArray == NULL)
    {
        return IA_RETURN_VALUE_NO_ARRAY_PTR;
    }
    if (pIndefArray->length + appendedLength > pIndefArray->capacity)
    {
//        IndefArray *pNewIndefArray = create_indef_array(pIndefArray->capacity * 2);
//        memcpy(pNewIndefArray->data, pIndefArray->data, pIndefArray->length);
//        memcpy(pNewIndefArray->data + pIndefArray->length, octets, appendedLength);
//        pNewIndefArray->index = pIndefArray->index;
//        pNewIndefArray->length = pIndefArray->length + appendedLength;

        return IA_RETURN_VALUE_OK;
    }
    else
    {
        memcpy(pIndefArray->data + pIndefArray->length, octets, appendedLength);
        pIndefArray->length += appendedLength;

        return IA_RETURN_VALUE_OK;
    }
}