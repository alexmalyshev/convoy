#include "../include/stack.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    STACK_LINK(block, next);

    int elem;
} block_t;


STACK_NEW(stack, block);


static void block_init(block_t *blk, int elem) {
    assert(blk != NULL);

    blk->elem = elem;
    STACK_ELEM_INIT(blk, next);
}

static void push(stack *stk, block_t *blk) {
    STACK_PUSH(stk, blk, next);
}

static block_t *peek(stack *stk) {
    block_t *res = NULL;
    STACK_PEEK(res, stk);
    return res;
}

static block_t *pop(stack *stk) {
    block_t *res = NULL;
    STACK_POP(res, stk, next);
    return res;
}

void run(stack *stk) {
    assert(peek(stk) == NULL);
    assert(stk->len == 0);
    assert(pop(stk) == NULL);
    assert(stk->len == 0);

    block_t b0;
    block_init(&b0, 0);

    block_t b1;
    block_init(&b1, 1);

    block_t b2;
    block_init(&b2, 2);

    push(stk, &b0);
    assert(peek(stk) == &b0);
    assert(stk->len == 1);

    push(stk, &b1);
    assert(peek(stk) == &b1);
    assert(stk->len == 2);

    push(stk, &b2);
    assert(peek(stk) == &b2);
    assert(stk->len == 3);

    block_t *res = NULL;
    block_t *peekr = NULL;

    STACK_FOREACH(res, stk, next)
        res->elem += 1;

    printf("[ ");
    peekr = peek(stk);
    res = pop(stk);
    assert(res == &b2);
    assert(res == peekr);
    assert(peek(stk) == &b1);
    assert(stk->len == 2);
    printf("%d ", res->elem);

    peekr = peek(stk);
    res = pop(stk);
    assert(res == &b1);
    assert(res == peekr);
    assert(peek(stk) == &b0);
    assert(stk->len == 1);
    printf("%d ", res->elem);

    peekr = peek(stk);
    res = pop(stk);
    assert(res == &b0);
    assert(res == peekr);
    assert(peek(stk) == NULL);
    assert(stk->len == 0);
    printf("%d ", res->elem);

    puts("]");

    assert(stk->len == 0);
    assert(peek(stk) == NULL);
    assert(pop(stk) == NULL);
    assert(stk->len == 0);
}

int main(void) {
    stack stk;
    STACK_INIT(&stk);
    run(&stk);
    return 0;
}
