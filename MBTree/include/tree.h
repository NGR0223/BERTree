//
// Created by ngr on 2023/3/10.
//

#ifndef BERTREE_TREE_H
#define BERTREE_TREE_H

#include "../../IndefiniteArray/include/indefiniteArray.h"

#define MAXTREENODES 1024


typedef struct tlv
{
    IndefArray *type;
    IndefArray *length;
    IndefArray *value;
} TLV;

typedef struct node
{
    int32_t indexParent;
    int32_t indexBrother;
    int32_t indexChild;

    TLV *pTlv;
} NODE;

typedef struct tree
{
    int32_t nextEntry;
    NODE nodes[MAXTREENODES];
} TREE;


static void init_node(NODE *initNode, IndefArray *type, IndefArray *length, IndefArray *value);

void add_child(NODE *parent, NODE *child, TREE *tree, int *errCode);

#endif //BERTREE_TREE_H
