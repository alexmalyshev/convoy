#include "../include/binoheap.h"

#include <stdio.h>


typedef struct block {
    BINOHEAP_LINK(block, int, link);

    int key;
    int val;
} block_t;


BINOHEAP_NEW(binoheap, block);


static void elem_init(block_t *blk, int key, int val);
static void insert(binoheap *heap, block_t *blk);
static block_t *removemin(binoheap *heap);


int main(void) {
    binoheap heap = BINOHEAP_STATIC_INIT;

    block_t b0;
    elem_init(&b0, 3, 4);

    block_t b1;
    elem_init(&b1, 2, 3);

    block_t b2;
    elem_init(&b2, 1, 2);

    insert(&heap, &b0);
    insert(&heap, &b1);
    insert(&heap, &b2);

    block_t *res = removemin(&heap);

    printf("(%d,%d)", res->key, res->val);

    return res->key;
}


static int less(int a, int b) {
    return a < b;
}

static void elem_init(block_t *blk, int key, int val) {
    blk->key = key;
    blk->val = val;

    BINOHEAP_ELEM_INIT(blk, blk->key, link);
}

static void insert(binoheap *heap, block_t *blk) {
    BINOHEAP_INSERT(heap, blk, less, link);
}


static block_t *removemin(binoheap *heap) {
    block_t *res = NULL;

    BINOHEAP_REMOVEMIN(res, heap, less, block, link);

    return res;
}
