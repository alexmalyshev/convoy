#include "../include/dlist.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    DLIST_DECLARE_LINK(block, link);

    int elem;
} block_t;

DLIST_DECLARE(deque, block);

static deque deq = DLIST_STATIC_INIT;


static void block_init(block_t *blk, int elem) {
    assert(blk != NULL);

    blk->elem = elem;
    DLIST_ELEM_INIT(blk, link);
}


int main(void) {
    block_t b0;
    block_init(&b0, 0);

    block_t b1;
    block_init(&b1, 1);

    block_t b2;
    block_init(&b2, 2);

    DLIST_PUSH_HEAD(&deq, &b0, link);
    DLIST_PUSH_HEAD(&deq, &b1, link);
    DLIST_PUSH_HEAD(&deq, &b2, link);

    block_t *res = NULL;

    DLIST_FOREACH(res, &deq, link) {
        block_t *head = DLIST_PEEK_HEAD(&deq, link);
        block_t *tail = DLIST_PEEK_TAIL(&deq, link);
        (void)head;
        (void)tail;

        res->elem += 1;
    }

    printf("[ ");
    res = DLIST_POP_TAIL(&deq, link);
    printf("%d ", res->elem);
    res = DLIST_POP_TAIL(&deq, link);
    printf("%d ", res->elem);
    res = DLIST_POP_TAIL(&deq, link);
    printf("%d ", res->elem);
    printf("]\n");

    return 0;
}
