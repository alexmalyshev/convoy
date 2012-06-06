#include "../include/stack.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    STACK_LINK(block, next);

    int elem;
} block_t;


STACK_NEW(stack, block);

static stack stk = STACK_STATIC_INIT;


static void block_init(block_t *blk, int elem) {
    assert(blk != NULL);

    blk->elem = elem;
    STACK_ELEM_INIT(blk, next);
}


int main(void ) {
    block_t b0;
    block_init(&b0, 0);

    block_t b1;
    block_init(&b1, 1);

    block_t b2;
    block_init(&b2, 2);

    STACK_PUSH(&stk, &b0, next);
    STACK_PUSH(&stk, &b1, next);
    STACK_PUSH(&stk, &b2, next);

    block_t *res = NULL;
    STACK_FOREACH(res, &stk, next)
        res->elem += 1;

    printf("[ ");
    STACK_POP(res, &stk, next);
    printf("%d ", res->elem);
    STACK_POP(res, &stk, next);
    printf("%d ", res->elem);
    STACK_POP(res, &stk, next);
    printf("%d ", res->elem);
    printf("]\n");

    STACK_POP(res, &stk, next);
    assert(res == NULL);

    return 0;
}
