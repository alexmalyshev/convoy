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


int stack_init(stack *stk) {
    if (stk == NULL)
        return -1;

    /* set the stack's fields to be empty */
    stk->top = NULL;
    stk->len = 0;

    return 0;
}


int stack_clear(stack *stk) {
    snode *node;
    snode *dead;

    if (stk == NULL)
        return -1;

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

    return 0;
}


void *stack_peek(stack *stk) {
    if (stk == NULL)
        return NULL;

    if (stk->top == NULL || stk->len == 0)
        return NULL;

    return stk->top->elem;
}


void *stack_pop(stack *stk) {
    snode *dead;
    void *elem;

    if (stk == NULL)
        return NULL;

    if (stk->top == NULL || stk->len == 0)
        return NULL;

    /* pull out the top node */
    dead = stk->top;
    stk->top = stk->top->next;

    /* get the top element */
    elem = dead->elem;

    /* free the old top node */
    free(dead);

    /* update length */
    --(stk->len);

    return elem;
}


int stack_push(stack *stk, void *elem) {
    snode *new;

    if (stk == NULL || elem == NULL)
        return -1;

    /* make our new node */
    new = malloc(sizeof(snode));
    if (new == NULL)
        return -1;

    /* initalize its element to 'elem' and its next pointer
     * to the stack's top node */
    new->elem = elem;
    new->next = stk->top;

    /* set the new node as the stack's new top node */
    stk->top = new;

    /* update length */
    ++(stk->len);

    return 0;
}
