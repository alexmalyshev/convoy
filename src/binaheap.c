/** @file binaheap.c
 *  @brief A binary heap library.
 *
 *  The binary heap is stored as an array, where the element at
 *  <tt>elems[i]</tt> has its left child at <tt>elems[2*i]</tt> and its right
 *  child at <tt>elems[2*i + 1]</tt>. We compare elements in the heap using the
 *  generic compare function that is given as an argument to
 *  <tt>binaheap_init</tt>.
 *
 *  @author Alexander Malyshev
 */


#include "binaheap.h"

#include <assert.h>
#include <stdlib.h>


static void percolate_up(binaheap *heap);
static void percolate_down(binaheap *heap);
static int resize(binaheap *heap, size_t newcap);
static void swap(void **elems, size_t i, size_t j);


int binaheap_init(binaheap *heap, cmpfn cmp, size_t cap) {
    if (heap == NULL || cmp == NULL || cap == 0)
        return -1;

    /* allocate a new dynamic array */
    heap->elems = malloc(cap * sizeof(void *));
    if (heap->elems == NULL)
        return -1;

    /* set the heap's fields */
    heap->cap = cap;
    heap->size = 0;
    heap->cmp = cmp;

    return 0;
}


int binaheap_destroy(binaheap *heap) {
    if (binaheap_clear(heap))
        return -1;

    free(heap->elems);

    return 0;
}


int binaheap_insert(binaheap *heap, void *elem) {
    if (heap == NULL || elem == NULL)
        return -1;

    /* if the size and capacity of the heap are equal, we need to resize before
     * we can add on 'elem' */
    if (heap->size == heap->cap && resize(heap, 2 * heap->cap))
        return -1;

    /* move the 'elem' into the last slot of the binaheap */
    (heap->elems)[heap->size] = elem;
    ++(heap->size);

    /* percolate 'elem' up until 'heap' obeys heap invariants */
    percolate_up(heap);

    return 0;
}


void *binaheap_removemin(binaheap *heap) {
    void *min;

    if (heap == NULL || heap->size == 0)
        return NULL;

    /* grab the minimum element from 'heap' */
    min = heap->elems[0];
    --(heap->size);

    if (heap->size == 0)
        return min;

    /* if there are still elements in 'heap', we need to fix its invariants,
     * so move its last element into its first slot */
    heap->elems[0] = heap->elems[heap->size];

    /* and percolate it up until 'heap' obeys heap invariants */
    percolate_down(heap);

    return min;
}


int binaheap_clear(binaheap *heap) {
    if (heap == NULL)
        return -1;

    heap->size = 0;

    return 0;
}


int binaheap_trunc(binaheap *heap) {
    if (heap == NULL)
        return -1;

    /* resize the dynamic array to 'heap->size' */
    return resize(heap, heap->size);
}


static void percolate_up(binaheap *heap) {
    size_t i;

    assert(heap != NULL);
    assert(heap->size != 0);

    i = heap->size - 1;

    for (; i > 0; i /= 2) {
        if (heap->cmp(heap->elems[i], heap->elems[i/2]) >= 0)
            return;
        swap(heap->elems, i, i/2);
    }
}


static void percolate_down(binaheap *heap) {
    size_t i;
    size_t min;
    size_t left;

    for (i = 0; 2*i + 1 <= heap->size; ) {
        left = 2*i + 1;

        if (left == heap->size) {
            if (heap->cmp(heap->elems[i], heap->elems[heap->size]) > 0)
                swap(heap->elems, i, heap->size);
            return;
        }

        min = left;
        if (heap->cmp(heap->elems[min], heap->elems[min + 1]) >= 0)
            ++min;

        if (heap->cmp(heap->elems[i], heap->elems[min]) <= 0)
            return;

        swap(heap->elems, i, min);
        i = min;
    }
}


static int resize(binaheap *heap, size_t newcap) {
    assert(heap != NULL);

    heap->elems = realloc(heap->elems, newcap * sizeof(void *));
    if (heap->elems == NULL)
        return -1;

    heap->cap = newcap;

    return 0;
}


static void swap(void **elems, size_t i, size_t j) {
    void *temp;

    assert(elems != NULL);

    temp = elems[i];
    elems[i] = elems[j];
    elems[j] = temp;
}
