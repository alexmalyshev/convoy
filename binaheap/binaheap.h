#ifndef BINAHEAP_H_
#define BINAHEAP_H_

#include <limits.h> /* LONG_MAX */

/*
    Alexander Malyshev - binaheap.h

    Implementation of a minimum binary heap that is backed by a dynamic array.
    Priority is handled with a user-defined cmp function that is passed in as
    an argument to the binaheap_init function. NULL cannot be stored.
*/

#define INITIAL_CAPACITY 10
#define BINAHEAP_MAX_BYTES LONG_MAX
#define BINAHEAP_MAX_ITEMS ((long)(BINAHEAP_MAX_BYTES/sizeof(void *)))

typedef int (*cmpfun)(void *, void *);

/* a binaheap holds onto a dynamic array of element pointers, the compare
   function passed in through binaheap_init so as to compare elements,
   the number of elements and the total current capacity of the array */
typedef struct {
    void **items;
    cmpfun cmp;
    long size;
    long cap;
} binaheap;

/* set up */
int binaheap_init(binaheap **, cmpfun);
int binaheap_destroy(binaheap *);

/* standard heap operations */
void *binaheap_deletemin(binaheap *);
int binaheap_insert(binaheap *, void *);

/* auxiliary */
int binaheap_clear(binaheap *);

#endif
