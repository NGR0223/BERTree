//
// Created by ngr on 2023/3/10.
//

#include "../include/tree.h"
#include "../../Base/include/base.h"
#include <string.h>
#include <stdlib.h>

void init_node(NODE *initNode, TLV *pTlv)
{
    initNode->indexParent = -1;
    initNode->indexBrother = -1;
    initNode->indexChild = -1;

    copy_ia(initNode->pTlv->type, pTlv->type, NULL);
    copy_ia(initNode->pTlv->length, pTlv->length, NULL);
    copy_ia(initNode->pTlv->value, pTlv->value, NULL);
}

static int32_t get_index_last_child(int32_t indexChild, TREE *tree)
{
    while (tree->nodes[indexChild].indexBrother != 0)
    {
        indexChild = tree->nodes[indexChild].indexBrother;
    }
    return indexChild;
}

void add_child(NODE *parent, NODE *child, TREE *tree, int32_t *errCode)
{
    if (parent == NULL || child == NULL || errCode == NULL)
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    if (parent->indexChild == 0)
    {
        parent->indexChild = tree->nextEntry;
    }
    else
    {
        int32_t indexLastChild = get_index_last_child(parent->indexChild, tree);
        tree->nodes[indexLastChild].indexBrother = tree->nextEntry;
    }

    memcpy(&tree->nodes[tree->nextEntry], child, sizeof(NODE));
    tree->nextEntry++;
    if (errCode != NULL)
    {
        *errCode = BER_ERROR_CODE_OK;
    }
}

static void handle_primitive_value(IA *pValue, TREE *tree)
{

}

static void handle_constructed_value(IA *pValue, TREE *tree)
{

}

static void handle_TLV(IA *pData, TREE *pTree, int32_t *errCode)
{
    // Handle Type
    unsigned char firstOctetType = get_octet_ia(pData, errCode);
    int32_t flagConstructed = firstOctetType >> 5 & 0x01;

    IA *pType = create_ia(1);
    append_octet_ia(pType, firstOctetType, errCode);
    if ((firstOctetType & 0x1f) == 0x1f)    // Value of Type is bigger than 31(Hex:1f)
    {
        unsigned char curOctet = get_octet_ia(pData, errCode);
        while (curOctet >> 7 & 0x01) // msb is "1", which means more octets
        {

        }
    }

    // Handle Length
    unsigned char firstOctetLength = get_octet_ia(pData, errCode);
    IA *pLength = create_ia(1);
    append_octet_ia(pLength, firstOctetLength, errCode);
    if (firstOctetLength > 128 && firstOctetLength < 255)   // Definite, long
    {
        int32_t numOctetsLength = firstOctetLength & 0x7f;
        expand_capacity_ia(pLength, 1 + numOctetsLength, errCode);

        unsigned char *octetsLength = get_octets_ia(pData, numOctetsLength, errCode);
        append_octets_ia(pLength, octetsLength, numOctetsLength, errCode);
    }
    else if (firstOctetLength == 255)   // Reserved
    {
        if (errCode != NULL)
        {
            *errCode = BER_ERROR_CODE_RESERVED_LENGTH;
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
            unsigned char *octetsValue = get_octets_ia(pData, errCode, numOctetsValue);
            set_all_octets_ia(pValue, octetsValue, numOctetsValue, errCode);
        }
        else if (firstOctetLength == 128)    // Indefinite
        {

        }
        else if (firstOctetLength > 128 && firstOctetLength < 255)  // Definite, long
        {

        }
        else    // Reserved
        {
            if (errCode != NULL)
            {

            }
        }
        NODE *pNode = (NODE *) calloc(1, sizeof(NODE));
        init_node(pNode, NULL);
    }
}