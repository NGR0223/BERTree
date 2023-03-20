//
// Created by ngr on 2023/3/10.
//

#ifndef BERTREE_TREE_H
#define BERTREE_TREE_H

#include "../../IndefiniteArray/include/indefiniteArray.h"

#define MAXTREENODES 1024

typedef struct node
{
    int32_t indexParent;
    int32_t indexBrother;
    int32_t indexChild;

    IA *type;
    IA *length;
    IA *value;
} NODE;

typedef struct tree
{
    int32_t nextEntry;
    NODE nodes[MAXTREENODES];
} TREE;

void init_node(NODE *pInitNode, IA *pType, IA *pLength, IA *pValue, int32_t *pErrCode);

void add_child(NODE *pParent, NODE *pChild, TREE *pTree, int *pErrCode);

void add_node(TREE *pTree, int32_t indexParent, NODE *pNewNode, int32_t *pErrCode);


#endif //BERTREE_TREE_H
