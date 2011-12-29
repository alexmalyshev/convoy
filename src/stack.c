/** @file stack.c
 *  @brief A stack library.
 *
 *  Implemented as a singly linked list, we malloc a node every time we push
 *  an new element onto the stack and free the node that wraps around the
 *  top element when we call <tt>stack_pop</tt>.
 *
 *  @author Alexander Malyshev
 */

#include <assert.h>
#include <stdlib.h>
#include "stack.h"

void stack_init(stack *stk) {
    assert(stk != NULL);

    stk->top = NULL;
    stk->len = 0;
}

void stack_clear(stack *stk) {
    snode *node, *dead;

    assert(stk != NULL);

    node = stk->top;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    stk->len = 0;
}

void *stack_peek(stack *stk) {
    assert(stk != NULL);

    if (stk->top == NULL)
        return NULL;

    return stk->top->elem;
}

void *stack_pop(stack *stk) {
    snode *dead;
    void *elem;

    assert(stk != NULL);

    if (stk->top == NULL)
        return NULL;

    dead = stk->top;
    stk->top = stk->top->next;
    elem = dead->elem;
    free(dead);
    --(stk->len);
    return elem;
}

void stack_push(stack *stk, void *elem) {
    snode *new;
    
    assert(stk != NULL);
    assert(elem != NULL);

    new = malloc(sizeof(snode));
    assert(new != NULL);

    new->elem = elem;
    new->next = stk->top;
    stk->top = new;
    ++(stk->len);
}
