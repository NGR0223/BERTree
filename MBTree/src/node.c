//
// Created by ngr on 2023/3/10.
//

#include <string.h>
#include "../include/node.h"

void init_node(NODE *initNode, IndefArray *type, IndefArray *length, IndefArray *value)
{
    initNode->indexParent = 0;
    initNode->indexBrother = 0;
    initNode->indexChild = 0;

    copy_indef_array(initNode->type, type, NULL);
    copy_indef_array(initNode->length, length, NULL);
    copy_indef_array(initNode->value, value, NULL);
}


