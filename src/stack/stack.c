/** @file stack.c
 *  @brief A stack library.
 *
 *  Implemented as a singly linked list, we malloc a node every time we push
 *  an new element onto the stack and free the node that wraps around the
 *  top element when we call <tt>stack_pop</tt>.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "stack.h"

int stack_init(stack *stk) {
    if (stk == NULL)
        return 1;

    stk->top = NULL;
    stk->len = 0;
    return 0;
}

int stack_clear(stack *stk) {
    snode *node, *dead;

    if (stk == NULL)
        return 1;

    node = stk->top;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    stk->len = 0;
    return 0;
}

void *stack_peek(stack *stk) {
    if (stk == NULL || stk->top == NULL)
        return NULL;

    return stk->top->elem;
}

void *stack_pop(stack *stk) {
    snode *dead;
    void *elem;

    if (stk == NULL || stk->top == NULL)
        return NULL;
        
    dead = stk->top;
    stk->top = stk->top->next;
    elem = dead->elem;
    free(dead);
    --(stk->len);
    return elem;
}

int stack_push(stack *stk, void *elem) {
    snode *new;
    
    if (stk == NULL || elem == NULL)
        return 1;
    if ((new = malloc(sizeof(snode))) == NULL)
        return 1;

    new->elem = elem;
    new->next = stk->top;
    stk->top = new;
    ++(stk->len);
    return 0;
}
