/** @file stack.c
 *  @brief A stack library.
 *
 *  Implemented as a singly linked list, we malloc a node every time we push
 *  an new element onto the stack and free the node that wraps around the
 *  top element when we call <tt>stack_pop</tt>.
 *
 *  @author Alexander Malyshev
 */

#include "stack.h"

#include <assert.h>
#include <stdlib.h>


void stack_init(stack *stk) {
    assert(stk != NULL);

    /* set the stack's fields to be empty */
    stk->top = NULL;
    stk->len = 0;
}

void stack_clear(stack *stk) {
    snode *node;
    snode *dead;

    assert(stk != NULL);

    /* loop through all the nodes in the stack and free them */
    node = stk->top;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }

    /* set the stack's fields to be empty */
    stk->top = NULL;
    stk->len = 0;
}

void *stack_peek(stack *stk) {
    assert(stk != NULL);

    /* "good" empty stack means we return NULL */
    if (stk->top == NULL || stk->len == 0) {
        assert(stk->top == NULL && stk->len == 0);
        return NULL;
    }

    /* otherwise return the top element */
    return stk->top->elem;
}

void *stack_pop(stack *stk) {
    snode *dead;
    void *elem;

    assert(stk != NULL);

    /* "good" empty stack means we return NULL */
    if (stk->top == NULL || stk->len == 0) {
        assert(stk->top == NULL && stk->len == 0);
        return NULL;
    }

    /* pull out the top node */
    dead = stk->top;
    stk->top = stk->top->next;

    /* get the top element */
    elem = dead->elem;

    /* free the top node */
    free(dead);

    /* update length */
    --(stk->len);

    return elem;
}

void stack_push(stack *stk, void *elem) {
    snode *new;

    assert(stk != NULL);
    assert(elem != NULL);

    /* make our new node */
    new = malloc(sizeof(snode));
    assert(new != NULL);

    /* initalize its element to 'elem' and its next pointer
     * to the stack's top node */
    new->elem = elem;
    new->next = stk->top;

    /* set the new node as the stack's new top node */
    stk->top = new;

    /* update length */
    ++(stk->len);
}
