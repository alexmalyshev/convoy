#include "../include/deque.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    DEQUE_LINK(block, link);

    int elem;
} block_t;

DEQUE_NEW(deque, block);

static deque deq = DEQUE_STATIC_INIT;


static void block_init(block_t *blk, int elem) {
    assert(blk != NULL);

    blk->elem = elem;
    DEQUE_ELEM_INIT(blk, link);
}


int main(void) {
    block_t b0;
    block_init(&b0, 0);

    block_t b1;
    block_init(&b1, 1);

    block_t b2;
    block_init(&b2, 2);

    DEQUE_PUSH_HEAD(&deq, &b0, link);
    DEQUE_PUSH_HEAD(&deq, &b1, link);
    DEQUE_PUSH_HEAD(&deq, &b2, link);

    block_t *res = NULL;

    DEQUE_FOREACH(res, &deq, link)
        res->elem += 1;

    printf("[ ");
    DEQUE_POP_TAIL(res, &deq, link);
    printf("%d ", res->elem);
    DEQUE_POP_TAIL(res, &deq, link);
    printf("%d ", res->elem);
    DEQUE_POP_TAIL(res, &deq, link);
    printf("%d ", res->elem);
    printf("]\n");

    return 0;
}
