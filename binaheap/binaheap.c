#include <stdlib.h>
#include "binaheap.h"
#include "binaheap-int.h"

/* binaheap_init - allocs and initializes a new binaheap at *heap with the
                   given compare function
 * Fails: heap is NULL or cmp is NULL, or if malloc fails */
int binaheap_init(binaheap **heap, cmpfun cmp) {
    if (heap == NULL || cmp == NULL)
        return 1;

    if ((*heap = malloc(sizeof(binaheap))) == NULL)
        return 1;
    if (((*heap)->items = malloc(INITIAL_CAPACITY * sizeof(void *))) == NULL)
        return 1;
    (*heap)->cap = INITIAL_CAPACITY;
    (*heap)->size = 0;
    (*heap)->cmp = cmp;
    return 0;
}

/* binaheap_destroy - removes all elements from heap, frees the dynamic array
                      in heap and the binaheap struct itself
 * Warning: Will cause memory leaks if the elements in the heap were malloc'd
            and never get free'd after this function call
 * Fails: heap is NULL */
int binaheap_destroy(binaheap *heap) {
    if (binaheap_clear(heap))
        return 1;
    free(heap->items);
    free(heap);
    return 0;
}

/* binaheap_delete_min - removes the minimum element from heap (as per the
                         compare function) and returns it if it exists,
                         returns NULL otherwise
 * Fails: heap is NULL */
void *binaheap_delete_min(binaheap *heap) {
    void *min, **items;

    if (heap == NULL || heap->size <= 0)
        return NULL;

    items = heap->items;
    min = items[0];
    --(heap->size);
    if (heap->size == 0)
        return min;
    items[0] = items[heap->size];
    percolate_down(heap);
    return min;
}

/* binaheap_insert - adds on the item to heap
 * Fails: heap is NULL or item is NULL */
int binaheap_insert(binaheap *heap, void *item) {
    if (heap == NULL || item == NULL)
        return 1;

    if (heap->size == heap->cap)
        resize(heap);
    (heap->items)[heap->size] = item;
    ++(heap->size);
    percolate_up(heap);
    return 0;
}

/* binaheap_clear - removes all elements from heap
 * Warning: Will cause memory leaks if the elements in the heap were malloc'd
            and never get free'd after this function call
 * Fails: heap is NULL */
int binaheap_clear(binaheap *heap) {
    if (heap == NULL)
        return 1;
    heap->size = 0;
    return 0;
}

/* resize - doubles the size of the array inside heap
 * Invariant: heap is not NULL
 * Fails: realloc fails, current array size is already BINAHEAP_MAX_ITEMS */
static int resize(binaheap *heap) {
    long cap = heap->cap;
    long newcap;
    void *new;

    if (2 * cap < BINAHEAP_MAX_ITEMS)
        newcap = 2 * cap;
    else
        newcap = BINAHEAP_MAX_ITEMS;
    if ((new = realloc(heap->items, newcap * sizeof(void *))) == NULL)
        return 1;
    heap->cap = newcap;
    return 0;
}

/* percolate_up - "heapifies" the dynamic array in heap by percolating the
                  last item up until the array fulfills heap invariants
 * Invariant: heap is not NULL */
static void percolate_up(binaheap *heap) {
    long i = heap->size - 1;
    void **items = heap->items;
    cmpfun cmp = heap->cmp;

    for (; i > 0; i /= 2) {
        if (cmp(items[i], items[i/2]) >= 0)   
            return;
        swap(items, i, i/2);
    }
}

/* percolate_down - "heapifies" the dynamic array in heap by percolating the
                    first item down the array until the array fulfills heap
                    invariants
 * Invariant: heap is not NULL */
static void percolate_down(binaheap *heap) {
    void **items = heap->items;
    cmpfun cmp = heap->cmp;
    long size = heap->size;
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
