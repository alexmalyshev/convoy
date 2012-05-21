#include "../include/binoheap.h"

#include <stdio.h>


typedef struct block {
    BINOHEAP_LINK(block, int, link);

    int key;
    int val;
} block_t;


BINOHEAP_NEW(binoheap, block);

static binoheap heap = BINOHEAP_STATIC_INIT;

#define LESS(a, b) ((a) < (b))

int main(void) {
    block_t b0;
    b0.key = 3;
    b0.val = 4;
    BINOHEAP_ELEM_INIT(&b0, b0.key, link);

    block_t b1;
    b1.key = 2;
    b1.val = 3;
    BINOHEAP_ELEM_INIT(&b1, b1.key, link);

    block_t b2;
    b2.key = 1;
    b2.val = 2;
    BINOHEAP_ELEM_INIT(&b2, b2.key, link);

    BINOHEAP_INSERT(&heap, &b0, LESS, link);
    BINOHEAP_INSERT(&heap, &b1, LESS, link);
    BINOHEAP_INSERT(&heap, &b2, LESS, link);

    block_t *res = NULL;

    BINOHEAP_REMOVEMIN(res, &heap, LESS, block, link);

    printf("(%d,%d)", res->key, res->val);

    return 0;
}
