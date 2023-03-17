#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IndefiniteArray/include/indefiniteArray.h"

unsigned char test[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};


int main()
{
    IndefArray *a = create_indef_array(10);
    int32_t ret = set_data_indef_array(a, test, 10, 0);
    unsigned char *b = NULL;
    ret = get_octets_indef_array(a, &b, 5);

    return 0;
}
