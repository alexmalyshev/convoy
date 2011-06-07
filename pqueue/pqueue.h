#ifndef PQUEUE_H_
#define PQUEUE_H_

#include <limits.h> /* LONG_MAX */

/*
    Alexander Malyshev - pqueue.h

    Implementation of a min priority queue that is backed by a binary heap
    and implemented using a dynamic array. Priority is handled with a
    user-defined cmp function that is passed in as an argument to the
    pqueue_init function. NULL cannot be stored.
*/

#define INITIAL_CAPACITY 10
#define PQUEUE_MAX_BYTES LONG_MAX
#define PQUEUE_MAX_ITEMS ((long)(PQUEUE_MAX_BYTES/sizeof(void *)))

typedef int (*cmpfun)(void *, void *);

/* a pqueue holds onto a dynamic array of element pointers, the compare
   function passed in through pqueue_init so as to compare elements,
   the number of elements and the total current capacity of the array */
typedef struct {
    void **items;
    cmpfun cmp;
    long size;
    long cap;
} pqueue;

/* set up */
int pqueue_init(pqueue **, cmpfun);
int pqueue_destroy(pqueue *);

/* standard pqueue operations */
void *pqueue_delete_min(pqueue *);
int pqueue_insert(pqueue *, void *);

/* auxiliary */
int pqueue_clear(pqueue *);

#endif
