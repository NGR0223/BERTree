//
// Created by ngr on 2023/3/10.
//

#include "../include/tree.h"
#include "../../Base/include/base.h"
#include <string.h>
#include <stdlib.h>


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

static void handle_TLV(IndefArray *data, TREE *tree, int32_t *errCode)
{
    // Handle Type
    unsigned char firstOctet = get_octet_indef_array(data, errCode);

    int32_t flagConstructed = firstOctet >> 5 & 0x01;
    if ((firstOctet & 0x1f) == 0x1f) // 0x1F = 31
    {
        unsigned char curOctet = get_octet_indef_array(data, errCode);
        while (curOctet >> 7 & 0x01) // msb is "1", which means more octets
        {

        }
    }
    else
    {
        IndefArray *type = create_indef_array(1);
        append_octet_indef_array(type, firstOctet, errCode);
    }

    // Handle Length
    firstOctet = get_octet_indef_array(data, errCode);
    IndefArray *length = create_indef_array(1);
    append_octet_indef_array(length, firstOctet, errCode);
    if (firstOctet >> 7 & 0x01)
    {
        if ((firstOctet & 0x7f) == 0)    // Indefinite
        {

        }
        else if ((firstOctet & 0x7f) == 127) // Reserved
        {
            *errCode = BER_ERROR_CODE_RESERVED_LENGTH;
            return;
        }
        else    // Definite, long
        {
            int32_t numOctets = firstOctet & 0x7f;
            expand_capacity_indef_array(length, 1 + numOctets, errCode);

            unsigned char *octetsLength = get_octets_indef_array(data, errCode, numOctets);
            append_octets_indef_array(length, octetsLength, numOctets, errCode);
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
