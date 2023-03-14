#include <stdio.h>
#include "IndefiniteArray/include/IndefiniteArray.h"

unsigned char test[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10};

int main()
{
    IndefArray *a = create_indef_array(10);
    int32_t ret = set_data_indef_array(a, test, 10);
    IndefArray *b = create_indef_array(10);
    ret = copy_indef_array(b, a);
    ret = expand_indef_array(a);
    ret = append_octets_indef_array(a, test, 10);

    return 0;
}
