#ifndef DEQUE_H_
#define DEQUE_H_

/*
    Alexander Malyshev - deque.h

    Implementation of a double-ended queue(deque) that is backed by a
    doubly linked list. NULL cannot be stored.
*/

/* a dnode holds onto the data passed in as well as pointers to its prev and
   next nodes */
typedef struct dnode_t {
    struct dnode_t *prev;
    struct dnode_t *next;
    void *data;
} dnode;

/* a deque is just a doubly linked list of nodes where front is the first
   element and back is the last */
typedef struct {
    dnode *front;
    dnode *back;
    long len;
} deque;

/* set up */
int deque_init(deque **);
int deque_destroy(deque *);

/* standard deque methods */
int deque_insertb(deque *, void *);
int deque_insertf(deque *, void *);
void *deque_peekb(deque *);
void *deque_peekf(deque *);
void *deque_removeb(deque *);
void *deque_removef(deque *);

/* auxiliary */
int deque_clear(deque *);
long deque_len(deque *);

#endif
