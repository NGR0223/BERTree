//
// Created by ngr on 2023/3/10.
//

#include "../include/tree.h"
#include "../../Base/include/base.h"
#include <string.h>
#include <stdlib.h>

void init_node(NODE *initNode, IndefArray *type, IndefArray *length, IndefArray *value)
{
    initNode->indexParent = 0;
    initNode->indexBrother = 0;
    initNode->indexChild = 0;

    copy_indef_array(initNode->type, type, NULL);
    copy_indef_array(initNode->length, length, NULL);
    copy_indef_array(initNode->value, value, NULL);
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
        *errCode = BER_ERROR_CODE_INVALID_ARG;
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
    *errCode = BER_ERROR_CODE_OK;
}

static void handle_primitive_value(IndefArray *pValue, TREE *tree)
{

}

static void handle_constructed_value(IndefArray *pValue, TREE *tree)
{

}

static void handle_TLV(IndefArray *pData, TREE *pTree, int32_t *errCode)
{
    // Handle Type
    unsigned char firstOctetType = get_octet_indef_array(pData, errCode);
    int32_t flagConstructed = firstOctetType >> 5 & 0x01;

    IndefArray *pType = create_indef_array(1);
    append_octet_indef_array(pType, firstOctetType, errCode);
    if ((firstOctetType & 0x1f) == 0x1f)    // Value of Type is bigger than 31(Hex:1f)
    {
        unsigned char curOctet = get_octet_indef_array(pData, errCode);
        while (curOctet >> 7 & 0x01) // msb is "1", which means more octets
        {

        }
    }

    // Handle Length
    unsigned char firstOctetLength = get_octet_indef_array(pData, errCode);
    IndefArray *pLength = create_indef_array(1);
    append_octet_indef_array(pLength, firstOctetLength, errCode);
    if (firstOctetLength > 128 && firstOctetLength < 255)   // Definite, long
    {
        int32_t numOctetsLength = firstOctetLength & 0x7f;
        expand_capacity_indef_array(pLength, 1 + numOctetsLength, errCode);

        unsigned char *octetsLength = get_octets_indef_array(pData, errCode, numOctetsLength);
        append_octets_indef_array(pLength, octetsLength, numOctetsLength, errCode);
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
            IndefArray *pValue = create_indef_array(numOctetsValue);
            unsigned char *octetsValue = get_octets_indef_array(pData, errCode, numOctetsValue);
            set_data_indef_array(pValue, octetsValue, numOctetsValue, errCode);
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
        init_node(pNode, pType, pLength, pData);
    }
}

void convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree, int32_t *errCode)
{
    if (data == NULL || lengthData <= 0)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }

    // Convert unsigned char *data to IndefArray
    IndefArray *tmp = create_indef_array(lengthData);
    set_data_indef_array(tmp, data, lengthData, errCode);
    if (*errCode != 0)
    {
        return;
    }

    handle_TLV(tmp, tree, errCode);
}

void show_mb_tree(TREE *tree, int32_t *errCode)
{

}

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree, int32_t *errCode)
{

}
