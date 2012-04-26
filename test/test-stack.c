#include "../include/stack.h"

#include <stdio.h>


typedef struct block {
    STACK_LINK(block, next);

    int elem;
} block_t;


STACK_NEW(stack, block);

static stack stk = STACK_STATIC_INIT;


int main(void ) {
    block_t b0;
    b0.elem = 0;
    STACK_ELEM_INIT(&b0, next);

    block_t b1;
    b1.elem = 1;
    STACK_ELEM_INIT(&b1, next);

    block_t b2;
    b2.elem = 2;
    STACK_ELEM_INIT(&b2, next);

    STACK_PUSH(&stk, &b0, next);
    STACK_PUSH(&stk, &b1, next);
    STACK_PUSH(&stk, &b2, next);

    block_t *res;

    STACK_FOREACH(res, &stk, next) {
        res->elem += 1;
    }

    printf("[ ");
    STACK_POP(res, &stk, next);
    printf("%d ", res->elem);
    STACK_POP(res, &stk, next);
    printf("%d ", res->elem);
    STACK_POP(res, &stk, next);
    printf("%d ", res->elem);
    printf("]\n");

    return 0;
}
