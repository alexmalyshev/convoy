#include <stdlib.h>
#include "stack.h"

/* stack_init - allocs and initializes a new empty stack at *s
 * Fails: s is NULL, or if calloc fails */
int stack_init(stack **s) {
    if (s == NULL)
        return 1;
    if ((*s = calloc(1, sizeof(stack))) == NULL)
        return 1;
    return 0;
}

/* stack_destroy - empties out the given stack, freeing all nodes and frees the
                   stack struct itself
 * Fails: s is NULL */
int stack_destroy(stack *s) {
    if (stack_clear(s))
        return 1;
    free(s);
    return 0;
}

/* stack_peek - returns the top item in the given stack if it exists,
                returns NULL if the stack is empty
 * Fails: s is NULL */
void *stack_peek(stack *s) {
    if (s == NULL || s->top == NULL)
        return NULL;

    return s->top->data;
}

/* stack_pop - pops off the top item of the given stack and returns it if it
               exists, returns NULL if the stack is empty
 * Fails: s is NULL */
void *stack_pop(stack *s) {
    snode *node;
    void *item;

    if (s == NULL || s->top == NULL)
        return NULL;
        
    node = s->top;
    s->top = s->top->next;
    item = node->data;
    free(node);
    --(s->len);
    return item;
}

/* stack_push - pushes the given item onto the top of the given stack
 * Fails: s is NULL or item is NULL, or if malloc fails */
int stack_push(stack *s, void *item) {
    snode *node;
    
    if (s == NULL || item == NULL)
        return 1;
    if ((node = malloc(sizeof(snode))) == NULL)
        return 1;

    node->data = item;
    node->next = s->top;
    s->top = node;
    ++(s->len);
    return 0;
}

/* stack_clear - removes all items from the stack and frees their
                 corresponding nodes
 * Fails: s is NULL */
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

/* stack_len - returns the number of items in the given stack
 * Fails: s is NULL */
long stack_len(stack *s) {
    if (s == NULL)
        return -1;
    return s->len;
}
