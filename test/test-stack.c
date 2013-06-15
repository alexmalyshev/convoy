#include "../include/slist.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    SLIST_DECLARE_LINK(block, next);

    int elem;
} block_t;


SLIST_DECLARE(stack, block);


static void push(stack *stk, block_t *blk) { SLIST_PUSH_HEAD(stk, blk, next); }
static block_t *peek(stack *stk) { return SLIST_PEEK_HEAD(stk, next); }
static block_t *pop(stack *stk) { return SLIST_POP_HEAD(stk, next); }

int main(void) {
    stack s = SLIST_STATIC_INIT;
    stack *stk = &s;

    assert(peek(stk) == NULL);
    assert(stk->len == 0);
    assert(pop(stk) == NULL);
    assert(stk->len == 0);

    block_t b0 = { .next = SLIST_LINK_STATIC_INIT, .elem = 0 };
    block_t b1 = { .next = SLIST_LINK_STATIC_INIT, .elem = 1 };
    block_t b2 = { .next = SLIST_LINK_STATIC_INIT, .elem = 2 };

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

    SLIST_FOREACH(res, stk, next)
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
