#include "../include/deque.h"

#include <stdio.h>


typedef struct block {
    DEQUE_LINK(block, link);

    int elem;
} block_t;

DEQUE_NEW(deque, block);

static deque deq = DEQUE_STATIC_INIT;


int main(void) {
    block_t b0;
    b0.elem = 0;
    DEQUE_ELEM_INIT(&b0, link);

    block_t b1;
    b1.elem = 1;
    DEQUE_ELEM_INIT(&b1, link);

    block_t b2;
    b2.elem = 2;
    DEQUE_ELEM_INIT(&b2, link);

    DEQUE_PUSH_HEAD(&deq, &b0, link);
    DEQUE_PUSH_HEAD(&deq, &b1, link);
    DEQUE_PUSH_HEAD(&deq, &b2, link);

    block_t *res = NULL;

    DEQUE_FOREACH(res, &deq, link) {
        res->elem += 1;
    }

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
