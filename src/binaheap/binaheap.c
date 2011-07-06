/** @file binaheap.c
 *  @brief A binary heap library.
 *
 *  The binary heap is stored as an array, where the element at elems[i]
 *  has its left child at elems[2*i] and its right child at elems[2*i + 1].
 *  We compare elements in the heap using the generic compare function that is
 *  given as an argument to binaheap_init.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "binaheap.h"
#include "binaheap-int.h"

binaheap *binaheap_init(cmpfn cmp) {
    binaheap *heap;

    if (cmp == NULL)
        return NULL;

    if ((heap = malloc(sizeof(binaheap))) == NULL)
        return NULL;
    if ((heap->elems = malloc(INITIAL_CAPACITY * sizeof(void *))) == NULL)
        return NULL;
    heap->cap = INITIAL_CAPACITY;
    heap->size = 0;
    heap->cmp = cmp;
    return heap;
}

int binaheap_destroy(binaheap *heap) {
    if (binaheap_clear(heap))
        return 1;

    free(heap->elems);
    free(heap);
    return 0;
}

int binaheap_insert(binaheap *heap, void *elem) {
    if (heap == NULL || elem == NULL)
        return 1;

    if (heap->size == heap->cap)
        resize(heap);
    (heap->elems)[heap->size] = elem;
    ++(heap->size);
    percolate_up(heap);
    return 0;
}

void *binaheap_removemin(binaheap *heap) {
    void *min, **elems;

    if (heap == NULL || heap->size <= 0)
        return NULL;

    elems = heap->elems;
    min = elems[0];
    --(heap->size);
    if (heap->size == 0)
        return min;
    elems[0] = elems[heap->size];
    percolate_down(heap);
    return min;
}

int binaheap_clear(binaheap *heap) {
    if (heap == NULL)
        return 1;

    heap->size = 0;
    return 0;
}

static int resize(binaheap *heap) {
    void *new;

    if ((new = realloc(heap->elems, 2 * heap->cap * sizeof(void *))) == NULL)
        return 1;
    heap->cap *= 2;
    return 0;
}

static void percolate_up(binaheap *heap) {
    size_t i = heap->size - 1;
    void **elems = heap->elems;
    cmpfn cmp = heap->cmp;

    for (; i > 0; i /= 2) {
        if (cmp(elems[i], elems[i/2]) >= 0)   
            return;
        swap(elems, i, i/2);
    }
}

static void percolate_down(binaheap *heap) {
    void **elems = heap->elems;
    cmpfn cmp = heap->cmp;
    size_t size = heap->size;
    size_t i, min, left;

    for (i = 0; 2*i + 1 <= size; ) {
        left = 2*i + 1;
        /* check if there is only a left child */
        if (left == size) {
            if (cmp(elems[i], elems[size]) > 0)
                swap(elems, i, size);
            return;
        }
        /* find the index of the smaller of items[i]'s children */
        min = left + ((cmp(elems[left], elems[left + 1]) < 0) ? 0 : 1);
        if (cmp(elems[i], elems[min]) <= 0)
            return;
        swap(elems, i, min);
        i = min;
    }
}

static void swap(void **elems, long i, long j) {
    void *temp;
    temp = elems[i];
    elems[i] = elems[j];
    elems[j] = temp;
}
