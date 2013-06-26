#include "../include/dlist.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    DLIST_DECLARE_LINK(block, link);

    int elem;
} block_t;

#define BLOCK_STATIC_INIT(ELEM) {   \
    .link = DLIST_LINK_STATIC_INIT, \
    .elem = (ELEM)                  \
}

DLIST_DECLARE(deque, block);

static size_t len(deque *deq) { return DLIST_LEN(deq, link); }
static void pushf(deque *deq, block_t *blk) {
    DLIST_PUSH_FRONT(deq, blk, link);
}
static void pushb(deque *deq, block_t *blk) { DLIST_PUSH_BACK(deq, blk, link); }
static block_t *peekf(deque *deq) { return DLIST_PEEK_FRONT(deq, link); }
static block_t *peekb(deque *deq) { return DLIST_PEEK_BACK(deq, link); }

static block_t *popf(deque *deq) { return DLIST_POP_FRONT(deq, link); }
static block_t *popb(deque *deq) { return DLIST_POP_BACK(deq, link); }


int main(void) {
    deque deq = DLIST_STATIC_INIT;
    assert(len(&deq) == 0);

    block_t b0 = BLOCK_STATIC_INIT(0);
    block_t b1 = BLOCK_STATIC_INIT(1);
    block_t b2 = BLOCK_STATIC_INIT(2);

    pushf(&deq, &b0);
    assert(len(&deq) == 1);
    pushf(&deq, &b1);
    assert(len(&deq) == 2);
    pushb(&deq, &b2);
    assert(len(&deq) == 3);

    block_t *res = NULL;

    DLIST_FOREACH(res, &deq, link) {
        block_t *_ = peekf(&deq);
        _ = peekb(&deq);
        (void)_;

        res->elem += 1;
    }

    printf("[ ");
    res = popb(&deq);
    assert(len(&deq) == 2);
    printf("%d ", res->elem);
    res = popb(&deq);
    assert(len(&deq) == 1);
    printf("%d ", res->elem);
    res = popf(&deq);
    assert(len(&deq) == 0);
    printf("%d ", res->elem);
    printf("]\n");

    return 0;
}
