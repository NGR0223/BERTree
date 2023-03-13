//
// Created by ngr on 2023/3/10.
//

#include <stdio.h>
#include <string.h>
#include "../include/node.h"
#include "../../IndefiniteArray/include/IndefiniteArray.h"

void init_node(NODE *initNode, IndefArray *type, IndefArray *length, IndefArray *value)
{
    initNode->indexParent = 0;
    initNode->indexBrother = 0;
    initNode->indexChild = 0;

    copy_indef_array(initNode->type, type);
    copy_indef_array(initNode->length, length);
    copy_indef_array(initNode->value, value);
}

static uint32_t get_index_last_child(uint32_t indexChild, NODES *nodes)
{
    while (nodes->arr[indexChild].indexBrother != 0)
    {
        indexChild = nodes->arr[indexChild].indexBrother;
    }
    return indexChild;
}

uint32_t add_child(NODE *parent, NODE *child, NODES *nodes)
{
    if (parent == NULL || child == NULL)
    {
        return 1;
    }

    if (parent->indexChild == 0)
    {
        parent->indexChild = nodes->nextEntry;
    }
    else
    {
        uint32_t indexLastChild = get_index_last_child(parent->indexChild, nodes);
        nodes->arr[indexLastChild].indexBrother = nodes->nextEntry;
    }

    memcpy(&nodes->arr[nodes->nextEntry], child, sizeof(NODE));
    nodes->nextEntry++;
    return 0;
}
