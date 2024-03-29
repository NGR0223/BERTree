//
// Created by 720 on 2023/3/18.
//

#ifndef BERTREE_INTERFACE_H
#define BERTREE_INTERFACE_H

#include "../../MBTree/include/tree.h"

void handle_TLV(int32_t indexParent, IA *pData, TREE *pTree, int32_t *pErrCode);

void convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree, int32_t *errCode);

void show_mb_tree(TREE *tree, int32_t *errCode);

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree, int32_t *errCode);

#endif //BERTREE_INTERFACE_H
