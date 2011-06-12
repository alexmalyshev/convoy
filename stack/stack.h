#ifndef STACK_H_
#define STACK_H_

/*
    Alexander Malyshev - stack.h

    Implementation of a stack that is backed by a singly linked list.
    NULL cannot be stored.
*/

/* an snode holds the data passed in through stack_push as well as
   a pointer to the next node in the stack */
typedef struct snode_t {
    void *data;
    struct snode_t *next;
} snode;

/* a stack just holds a pointer to a linked list of nodes as well as
   the number of nodes in the linked list */
typedef struct {
    snode *top;
    long len;
} stack;

/* set up */
int stack_init(stack **);
int stack_destroy(stack *);

/* standard stack methods */
void *stack_peek(stack *);
void *stack_pop(stack *);
int stack_push(stack *, void *);

/* auxiliary */
int stack_clear(stack *);
long stack_len(stack *);

#endif
