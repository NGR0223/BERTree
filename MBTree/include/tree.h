//
// Created by ngr on 2023/3/10.
//

#ifndef BERTREE_TREE_H
#define BERTREE_TREE_H

#include "../include/node.h"

typedef struct tree
{
    int32_t nextEntry;
    NODE nodes[SIZENODES];
} TREE;

void add_child(NODE *parent, NODE *child, TREE *tree, int *errCode);

void convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree, int32_t *errCode);

void show_mb_tree(TREE *tree, int32_t *errCode);

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree, int32_t *errCode);

#endif //BERTREE_TREE_H
