//
// Created by 720 on 2023/3/18.
//

#include "../include/interface.h"
#include "../../Base/include/base.h"
#include "stdio.h"

static void handle_primitive_value(IA *pValue, TREE *tree)
{

}

static void handle_constructed_value(IA *pValue, TREE *tree)
{

}

void handle_TLV(int32_t indexParent, IA *pData, TREE *pTree, int32_t *pErrCode)
{
    // Handle Type
    unsigned char firstOctetType = get_octet_ia(pData, pErrCode);
    int32_t flagConstructed = firstOctetType >> 5 & 0x01;

    IA *pType = create_ia(1);
    append_octet_ia(pType, firstOctetType, pErrCode);
    if ((firstOctetType & 0x1f) == 0x1f)    // Value of Type is bigger than 31(Hex:1f)
    {
        unsigned char curOctet = get_octet_ia(pData, pErrCode);
        while (curOctet >> 7 & 0x01) // msb is "1", which means more octets
        {

        }
    }

    // Handle Length
    unsigned char firstOctetLength = get_octet_ia(pData, pErrCode);
    IA *pLength = create_ia(1);
    append_octet_ia(pLength, firstOctetLength, pErrCode);
    if (firstOctetLength > 128 && firstOctetLength < 255)   // Definite, long
    {
        int32_t numOctetsLength = firstOctetLength & 0x7f;
        expand_capacity_ia(pLength, 1 + numOctetsLength, pErrCode);

        unsigned char *octetsLength = get_octets_ia(pData, numOctetsLength, pErrCode);
        append_octets_ia(pLength, octetsLength, numOctetsLength, pErrCode);
    }
    else if (firstOctetLength == 255)   // Reserved
    {
        if (pErrCode != NULL)
        {
            *pErrCode = BER_ERROR_CODE_RESERVED_LENGTH;
        }
        return;
    }

    // Handle Value
    int32_t numOctetsValue = -1;
    if (flagConstructed)    // Constructed Value
    {

    }
    else    // Primitive Value
    {
        if (firstOctetLength < 128) // Definite, short
        {
            numOctetsValue = firstOctetLength;
            IA *pValue = create_ia(numOctetsValue);
            unsigned char *octetsValue = get_octets_ia(pData, numOctetsValue, pErrCode);
            set_all_octets_ia(pValue, octetsValue, numOctetsValue, pErrCode);
        }
        else if (firstOctetLength == 128)    // Indefinite
        {

        }
        else if (firstOctetLength > 128 && firstOctetLength < 255)  // Definite, long
        {

        }
        else    // Reserved
        {
            if (pErrCode != NULL)
            {

            }
        }
    }
}

void convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree, int32_t *errCode)
{
    if (data == NULL || lengthData <= 0)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }

    // Convert unsigned char *pOctets to IA
    IA *tmp = create_indef_array(lengthData);
    set_data_indef_array(tmp, data, lengthData, errCode);
    if (*errCode != 0)
    {
        return;
    }

//    handle_TLV(tmp, tree, errCode);
}

void show_mb_tree(TREE *tree, int32_t *errCode)
{

}

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree, int32_t *errCode)
{

}