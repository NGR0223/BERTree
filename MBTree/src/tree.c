//
// Created by ngr on 2023/3/10.
//

#include "../include/tree.h"
#include "../../Base/include/base.h"
#include <string.h>


void init_node(NODE *pInitNode, IA *pType, IA *pLength, IA *pValue, int32_t *pErrCode)
{
    if (pInitNode == NULL || pType == NULL || pLength == NULL || pValue == NULL)
    {
        if (pErrCode != NULL)
        {
            *pErrCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    if (pInitNode->type == NULL)
    {
        pInitNode->type = create_ia(pType->capacity);
    }
    if (pInitNode->length == NULL)
    {
        pInitNode->length = create_ia(pLength->capacity);
    }
    if (pInitNode->value == NULL)
    {
        pInitNode->value = create_ia(pValue->capacity);
    }

    pInitNode->indexParent = -1;
    pInitNode->indexBrother = -1;
    pInitNode->indexChild = -1;
    copy_ia(pInitNode->type, pType, NULL);
    copy_ia(pInitNode->length, pLength, NULL);
    copy_ia(pInitNode->value, pValue, NULL);

    if (pErrCode != NULL)
    {
        *pErrCode = BER_ERROR_CODE_OK;
    }
}

static int32_t get_index_last_child(int32_t indexChild, TREE *tree)
{
    while (tree->nodes[indexChild].indexBrother != -1)
    {
        indexChild = tree->nodes[indexChild].indexBrother;
    }
    return indexChild;
}

void add_child(NODE *pParent, NODE *pChild, TREE *pTree, int32_t *pErrCode)
{
    if (pParent == NULL || pChild == NULL)
    {
        if (pErrCode != NULL)
        {
            *pErrCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    if (pParent->indexChild == -1)
    {
        pParent->indexChild = pTree->nextEntry;
    }
    else
    {
        int32_t indexLastChild = get_index_last_child(pParent->indexChild, pTree);
        pTree->nodes[indexLastChild].indexBrother = pTree->nextEntry;
    }

    memcpy(&pTree->nodes[pTree->nextEntry], pChild, sizeof(NODE));
    pTree->nextEntry++;

    if (pErrCode != NULL)
    {
        *pErrCode = BER_ERROR_CODE_OK;
    }
}

void add_node(TREE *pTree, int32_t indexParent, NODE *pNewNode, int32_t *pErrCode)
{
    if (pTree == NULL || pNewNode == NULL)
    {
        if (pErrCode != NULL)
        {
            *pErrCode = BER_ERROR_CODE_INVALID_ARG;
        }
        return;
    }

    if (indexParent == -1)  // Root node
    {
        memcpy(&pTree->nodes[0], pNewNode, sizeof(NODE));
        pTree->nextEntry++;
    }
    else
    {
        pNewNode->indexParent = indexParent;
        add_child(&pTree->nodes[indexParent], pNewNode, pTree, NULL);
    }
}

