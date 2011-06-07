#include <stdlib.h>
#include "pqueue.h"
#include "pqueue-int.h"

/* pqueue_init - allocs and initializes a new pqueue at *pq with the
                 given compare function
 * Fails: pq is NULL or cmp is NULL, or if mmalloc fails */
int pqueue_init(pqueue **pq, cmpfun cmp) {
    if (pq == NULL || cmp == NULL)
        return 1;

    if ((*pq = malloc(sizeof(pqueue))) == NULL)
        return 1;
    if (((*pq)->items = malloc(INITIAL_CAPACITY * sizeof(void *))) == NULL)
        return 1;
    (*pq)->cap = INITIAL_CAPACITY;
    (*pq)->size = 0;
    (*pq)->cmp = cmp;
    return 0;
}

/* pqueue_destroy - removes all elements from pq, frees the dynamic array
                    in pq and pq itself
 * Warning: Will cause memory leaks if the elements in the tree were malloc'd
            and never get free'd after this function call
 * Fails: pq is NULL */
int pqueue_destroy(pqueue *pq) {
    if (pqueue_clear(pq))
        return 1;
    free(pq->items);
    free(pq);
    return 0;
}

/* pqueue_delete_min - removes the minimum element from pq (as per the compare
                       function) and returns it if it exists, returns NULL
                       otherwise
 * Fails: pq is NULL */
void *pqueue_delete_min(pqueue *pq) {
    void *min, **items;

    if (pq == NULL || pq->size <= 0)
        return NULL;

    items = pq->items;
    min = items[0];
    --(pq->size);
    if (pq->size == 0)
        return min;
    items[0] = items[pq->size];
    percolate_down(pq);
    return min;
}

/* pqueue_insert - adds on the item to pq
 * Fails: pq is NULL or item is NULL */
int pqueue_insert(pqueue *pq, void *item) {
    if (pq == NULL || item == NULL)
        return 1;

    if (pq->size == pq->cap)
        resize(pq);
    (pq->items)[pq->size] = item;
    ++(pq->size);
    percolate_up(pq);
    return 0;
}

/* pqueue_clear - removes all elements from pq
 * Warning: Will cause memory leaks if the elements in the tree were malloc'd
            and never get free'd after this function call
 * Fails: pq is NULL */
int pqueue_clear(pqueue *pq) {
    if (pq == NULL)
        return 1;
    pq->size = 0;
    return 0;
}

/* resize - doubles the size of the array inside pq
 * Invariant: pq is not NULL
 * Fails: realloc fails, current array size is already PQUEUE_MAX_ITEMS */
static int resize(pqueue *pq) {
    long cap = pq->cap;
    long newcap;
    void *new;

    if (2 * cap < PQUEUE_MAX_ITEMS)
        newcap = 2 * cap;
    else
        newcap = PQUEUE_MAX_ITEMS;
    if ((new = realloc((void *)(pq->items), newcap * sizeof(void *))) == NULL)
        return 1;
    pq->cap = newcap;
    return 0;
}

/* percolate_up - "heapifies" the dynamic array in pq by percolating the last
                  element up until the array fulfills heap invariants
 * Invariant: pq is not NULL */
static void percolate_up(pqueue *pq) {
    long i = pq->size - 1;
    void **items = pq->items;
    cmpfun cmp = pq->cmp;

    for (; i > 0; i /= 2) {
        if (cmp(items[i], items[i/2]) >= 0)   
            return;
        swap(items, i, i/2);
    }
}

/* percolate_down - "heapifies" the dynamic array in pq by percolating the
                    first element down the array until the array fulfills
                    heap invaraints
 * Invariant: pq is not NULL */
static void percolate_down(pqueue *pq) {
    void **items = pq->items;
    cmpfun cmp = pq->cmp;
    long size = pq->size;
    long i, min, left;

    for (i = 0; 2*i + 1 <= size; ) {
        left = 2*i + 1;
        /* check if there is only a left child */
        if (left == size) {
            if (cmp(items[i], items[size]) > 0)
                swap(items, i, size);
            return;
        }
        /* find the index of the smaller of items[i]'s children */
        min = left + ((cmp(items[left], items[left + 1]) < 0) ? 0 : 1);
        if (cmp(items[i], items[min]) <= 0)
            return;
        swap(items, i, min);
        i = min;
    }
}

/* swap - swaps items[i] and items[j]
 * Invariant: items is not NULL, i and j are not longer than the length of
              items */
static void swap(void **items, long i, long j) {
    void *temp;
    temp = items[i];
    items[i] = items[j];
    items[j] = temp;
}
