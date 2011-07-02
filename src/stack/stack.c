/** @file stack.c
 *  @brief A stack library.
 *
 *  Implemented as a singly linked list, we malloc a node every time we push
 *  an new element onto the stack and free the node that wraps around the
 *  top element when we call stack_pop.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "stack.h"

stack *stack_init(void) {   
    return calloc(1, sizeof(stack));
}

int stack_destroy(stack *s) {
    if (stack_clear(s))
        return 1;

    free(s);
    return 0;
}

void *stack_peek(stack *s) {
    if (s == NULL || s->top == NULL)
        return NULL;

    return s->top->data;
}

void *stack_pop(stack *s) {
    snode *dead;
    void *data;

    if (s == NULL || s->top == NULL)
        return NULL;
        
    dead = s->top;
    s->top = s->top->next;
    data = dead->data;
    free(dead);
    --(s->len);
    return data;
}

int stack_push(stack *s, void *elem) {
    snode *new;
    
    if (s == NULL || elem == NULL)
        return 1;
    if ((new = malloc(sizeof(snode))) == NULL)
        return 1;

    new->data = elem;
    new->next = s->top;
    s->top = new;
    ++(s->len);
    return 0;
}

int stack_clear(stack *s) {
    snode *node, *dead;

    if (s == NULL)
        return 1;

    node = s->top;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    s->len = 0;
    return 0;
}

size_t stack_len(stack *s) {
    if (s == NULL)
        return 0;

    return s->len;
}
