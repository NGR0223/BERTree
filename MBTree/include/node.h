//
// Created by ngr on 2023/3/10.
//

#ifndef BERTREE_NODE_H
#define BERTREE_NODE_H

#include "../../IndefiniteArray/include/IndefiniteArray.h"

#define SIZENODES 1024


typedef struct node
{
    int32_t indexParent;
    int32_t indexBrother;
    int32_t indexChild;

    IndefArray *type;
    IndefArray *length;
    IndefArray *value;
} NODE;


void init_node(NODE *initNode, IndefArray *type, IndefArray *length, IndefArray *value);


#endif //BERTREE_NODE_H
