//
// Created by ngr on 2023/3/10.
//

#ifndef BERTREE_TREE_H
#define BERTREE_TREE_H

#include "../include/node.h"

typedef enum
{
    TREE_RETURN_VALUE_NO_ARG_PTR = -1,
    TREE_RETURN_VALUE_OK = 0,
} TREE_RETURN_VALUE;

typedef struct tree
{
    int32_t nextEntry;
    NODE nodes[SIZENODES];
} TREE;

int32_t add_child(NODE *parent, NODE *child, TREE *tree);

int32_t convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree);

void show_mb_tree(TREE *tree);

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree);

#endif //BERTREE_TREE_H
