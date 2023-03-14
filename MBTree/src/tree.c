//
// Created by ngr on 2023/3/10.
//

#include "../include/tree.h"
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

int32_t add_child(NODE *parent, NODE *child, TREE *tree)
{
    if (parent == NULL || child == NULL)
    {
        return TREE_RETURN_VALUE_NO_ARG_PTR;
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
    return TREE_RETURN_VALUE_OK;
}

static void handle_TLV(unsigned char *data, int32_t lengthData, TREE *tree)
{
    unsigned char *tmp = (unsigned char *) calloc(lengthData, sizeof(unsigned char));
    memcpy(tmp, data, lengthData);
    int32_t indexTmp = 0;

    // Handle Type
    unsigned char firstByte = *tmp;
    indexTmp++;

    int32_t flagConstructed = firstByte >> 5 & 0x01;
    int32_t type = 0;
    if ((firstByte & 0x31) == 0x31)
    {
        unsigned char curByte = *tmp;
        indexTmp++;
        while (curByte >> 7 & 0x01)
        {

        }
    }
}

int32_t convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree)
{
    if (data == NULL || lengthData <= 0)
    {
        return TREE_RETURN_VALUE_NO_ARG_PTR;
    }

    unsigned char *tmp = (unsigned char *) calloc(lengthData, sizeof(unsigned char));
    memcpy(tmp, data, lengthData);

    int32_t indexData = 0;
    while (indexData < lengthData - 1)
    {

    }
}

void show_mb_tree(TREE *tree)
{

}

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree)
{

}
