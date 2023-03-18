//
// Created by 720 on 2023/3/18.
//

#include "../include/interface.h"

void convert_hex_string_to_mb_tree(unsigned char *data, int32_t lengthData, TREE *tree, int32_t *errCode)
{
    if (data == NULL || lengthData <= 0)
    {
        *errCode = BER_ERROR_CODE_INVALID_ARG;
        return;
    }

    // Convert unsigned char *data to IndefArray
    IndefArray *tmp = create_indef_array(lengthData);
    set_data_indef_array(tmp, data, lengthData, errCode);
    if (*errCode != 0)
    {
        return;
    }

    handle_TLV(tmp, tree, errCode);
}

void show_mb_tree(TREE *tree, int32_t *errCode)
{

}

unsigned char *convert_mb_tree_to_hex_string(int32_t *lengthData, TREE *tree, int32_t *errCode)
{

}