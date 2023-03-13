//
// Created by ngr on 2023/3/10.
//

#ifndef BERTREE_NODE_H
#define BERTREE_NODE_H

#include "../../IndefiniteArray/include/IndefiniteArray.h"

#define SIZENODES 1024
typedef struct node
{
    uint32_t indexParent;
    uint32_t indexBrother;
    uint32_t indexChild;

    IndefArray *type;
    IndefArray *length;
    IndefArray *value;
} NODE;

typedef struct nodeArray
{
    uint32_t nextEntry;
    NODE arr[SIZENODES];
} NODES;

void init_node(NODE *initNode, IndefArray *type, IndefArray *length, IndefArray *value);

uint32_t add_child(NODE *parent, NODE *child, NODES *nodes);

#endif //BERTREE_NODE_H
