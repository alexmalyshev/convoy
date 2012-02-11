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
static void resize(binaheap *heap, size_t newcap);
static void swap(void **elems, size_t i, size_t j);


void binaheap_init(binaheap *heap, cmpfn cmp, size_t cap) {
    assert(heap != NULL);
    assert(cmp != NULL);
    assert(cap != 0);

    heap->elems = malloc(cap * sizeof(void *));
    assert(heap->elems != NULL);

    heap->cap = cap;
    heap->size = 0;
    heap->cmp = cmp;
}

void binaheap_destroy(binaheap *heap) {
    binaheap_clear(heap);
    free(heap->elems);
}

void binaheap_insert(binaheap *heap, void *elem) {
    assert(heap != NULL);
    assert(elem != NULL);

    if (heap->size == heap->cap)
        resize(heap, 2 * heap->cap);

    (heap->elems)[heap->size] = elem;
    ++(heap->size);

    percolate_up(heap);
}

void *binaheap_removemin(binaheap *heap) {
    void *min;
    void **elems;

    assert(heap != NULL);
    assert(heap->size > 0);

    elems = heap->elems;
    min = elems[0];
    --(heap->size);

    if (heap->size == 0)
        return min;

    elems[0] = elems[heap->size];
    percolate_down(heap);

    return min;
}

void binaheap_clear(binaheap *heap) {
    assert(heap != NULL);

    heap->size = 0;
}

void binaheap_trunc(binaheap *heap) {
    assert(heap != NULL);

    resize(heap, heap->size);
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
    size_t i;
    size_t min;
    size_t left;

    for (i = 0; 2*i + 1 <= size; ) {
        left = 2*i + 1;
        if (left == size) {
            if (cmp(elems[i], elems[size]) > 0)
                swap(elems, i, size);
            return;
        }
        min = left + ((cmp(elems[left], elems[left + 1]) < 0) ? 0 : 1);
        if (cmp(elems[i], elems[min]) <= 0)
            return;
        swap(elems, i, min);
        i = min;
    }
}

static void resize(binaheap *heap, size_t newcap) {
    heap->elems = realloc(heap->elems, newcap * sizeof(void *));
    assert(heap->elems != NULL);

    heap->cap = newcap;
}

static void swap(void **elems, size_t i, size_t j) {
    void *temp;
    temp = elems[i];
    elems[i] = elems[j];
    elems[j] = temp;
}
