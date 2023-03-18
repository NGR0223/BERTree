//
// Created by ngr on 2023/3/13.
//

#ifndef BERTREE_INDEFINITEARRAY_H
#define BERTREE_INDEFINITEARRAY_H

#include <stdint.h>

typedef struct ia
{
    int32_t capacity;
    int32_t length;
    int32_t index;
    unsigned char *pOctets;
} IA;

/*!
 * Create an indefinite array
 * @param capacity
 * @return a pointer of an indefinite array
 */
IA *create_ia(int32_t capacity);

/*!
 * Delete an indefinite array
 * @param ppIA
 */
void delete_ia(IA **ppIA);

void copy_ia(IA *dest, IA *src, int32_t *errCode);

void double_capacity_ia(IA *pIA, int32_t *errCode);

void expand_capacity_ia(IA *pIA, int32_t newCapacity, int32_t *errCode);

void reduce_capacity_ia(IA *pIA, int32_t newCapacity, int32_t *errCode);

static void resize_capacity_ia(IA *pIA, int32_t newCapacity, int32_t *errCode);

unsigned char get_octet_ia(IA *pIA, int32_t *errCode);

unsigned char *get_all_octets_ia(IA *pIA, int32_t *lengthGotten, int32_t *errCode);

unsigned char *get_octets_ia(IA *pIA, int32_t expectedLength, int32_t *errCode);

void set_all_octets_ia(IA *pIA, unsigned char *pOctets, int32_t lengthData, int32_t *errCode);

void append_octet_ia(IA *pIA, unsigned char octet, int32_t *errCode);

void append_octets_ia(IA *pIA, unsigned char *octets, int32_t appendedLength, int32_t *errCode);

#endif //BERTREE_INDEFINITEARRAY_H
