//
// Created by ngr on 2023/3/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "../IndefiniteArray/include/indefiniteArray.h"
#include "../MBTree/include/tree.h"

unsigned char test[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};

void testIndefArray()
{
    IA *a = create_ia(10);
    set_all_octets_ia(a, test, 5, NULL);
    IA *b = create_ia(10);
    copy_ia(b, a, NULL);
    double_capacity_ia(a, NULL);
    append_octets_ia(a, test, 10, NULL);
    int lengthGotten = 0;
    unsigned char *allOctets = get_all_octets_ia(a, &lengthGotten, NULL);
    free(allOctets);
    allOctets = NULL;
    expand_capacity_ia(b, 11, NULL);
    reduce_capacity_ia(b, 6, NULL);
    append_octet_ia(b, test[0], NULL);
    unsigned char octet = get_octet_ia(b, NULL);
    printf("%d\n", octet);
    allOctets = get_octets_ia(b, 5, NULL);
    free(allOctets);
    allOctets = NULL;
    delete_ia(&b);
    delete_ia(&a);
}

void testTree()
{

}

int main()
{
    testIndefArray();
    testTree();
    return 0;
}