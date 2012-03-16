/** @file vector.c
 *  @brief A dynamic array library.
 *
 *  Indices that are out-of-bounds are considered as containing <tt>NULL</tt>.
 *  Inserting into an index that is out-of-bounds will resize the dynamic
 *  array, either by the vector grow macro or up to the index itself if it is
 *  very far away. We don't resize when reading values that are out-of-bounds
 *  or when we swap two values that are out-of-bounds (they're both
 *  <tt>NULL</tt> anyway).
 *
 *  @author Alexander Malyshev
 */


#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


static size_t find_last(vector *vec, size_t start);
static int resize(vector *vec, size_t cap);
static void swap(vector *vec, size_t i, size_t j);


int vector_init(vector *vec, size_t cap) {
    if (vec == NULL)
        return -1;

    if (cap != 0) {
        vec->elems = calloc(cap, sizeof(void *));
        if (vec->elems == NULL)
            return -1;
    }
    else
        vec->elems = NULL;

    vec->last = 0;
    vec->cap = cap;

    return 0;
}


int vector_destroy(vector *vec) {
    if (vec == NULL)
        return -1;

    free(vec->elems);

    return 0;
}


void *vector_at(vector *vec, size_t i) {
    if (vec == NULL)
        return NULL;

    /* either out of bounds or just not there */
    if (vec->last < i)
        return NULL;

    return vec->elems[i];
}


int vector_clear(vector *vec) {
    if (vec == NULL)
        return -1;

    /* everything after vec->last is already NULL anyway */
    memset(vec->elems, 0, vec->last);

    return 0;
}

int vector_compact(vector *vec) {
    size_t empty;
    size_t i;

    if (vec == NULL)
        return -1;

    empty = vec->cap;
    for (i = 0; i <= vec->last; ++i) {
        /* if slot is empty we might need to initialize empty */
        if (vec->elems[i] == NULL) {
            if (empty == vec->cap)
                empty = i;
        } else if (empty != vec->cap) {
            /* move element into our last empty slot */
            swap(vec, empty, i);
            /* find new empty */
            while (vec->elems[empty] != NULL) {
                ++empty;
                /* if no more compacting is needed */
                if (empty == vec->last) {
                    vec->last = empty - 1;
                    return 0;
                }
            }
        }
    }

    vec->last = (empty != 0 ? empty - 1 : 0);

    return 0;
}

void *vector_insert(vector *vec, size_t i, void *elem) {
    void *old;

    if (vec == NULL || elem == NULL)
        return NULL;

    /* if we need to resize */
    if (i >= vec->cap) {
        /* if i is really big, just resize to i + 1 immediately, and
         * if i is 0, then resize to the default capacity */
        if (i == 0)
            resize(vec, VECTOR_DEFAULT_CAP);
        else if (i < VECTOR_GROW_CAP(vec->cap))
            resize(vec, VECTOR_GROW_CAP(vec->cap));
        else
            resize(vec, i + 1);
    }

    old = vec->elems[i];
    vec->elems[i] = elem;

    if (i > vec->last)
        vec->last = i;

    return old;
}


void *vector_pop(vector *vec) {
    return vector_remove(vec, vec->last);
}


int vector_push(vector *vec, void *elem) {
    return vector_insert(vec, vec->last + 1, elem) == NULL;
}


void *vector_remove(vector *vec, size_t i) {
    void *old;

    if (vec == NULL)
        return NULL;

    if (i >= vec->cap)
        return NULL;

    old = vec->elems[i];
    vec->elems[i] = NULL;

    /* if we removed the last element then we need to scan back
     * looking for the new last index */
    if (i == vec->last)
        vec->last = find_last(vec, i);

    return old;
}


int vector_resize(vector *vec, size_t cap) {
    if (vec == NULL)
        return -1;

    return resize(vec, cap);
}


int vector_swap(vector *vec, size_t i, size_t j) {
    size_t max;

    if (vec == NULL)
        return -1;

    /* handles vec->cap = 0, i = 0, j = 0 */
    if (i == j)
        return 0;

    /* if both are out-of-bounds, then they might as well be swapped already */
    if (i >= vec->cap && j >= vec->cap)
        return 0;

    max = (i < j ? j : i);

    /* if we need to resize */
    if (max >= vec->cap) {
        /* if max is really big, just resize to max + 1 directly */
        if (max < VECTOR_GROW_CAP(vec->cap))
            resize(vec, VECTOR_GROW_CAP(vec->cap));
        else
            resize(vec, max + 1);
    }

    swap(vec, i, j);

    return 0;
}


int vector_trim(vector *vec) {
    if (vec == NULL)
        return -1;

    return resize(vec, vec->last + 1);
}


static size_t find_last(vector *vec, size_t start) {
    size_t k;

    assert(vec != NULL);

    if (start == 0)
        return 0;

    for (k = start - 1; k != 0; --k) {
        if (vec->elems[k] != NULL)
            return k;
    }

    return 0;
}


static int resize(vector *vec, size_t cap) {
    assert(vec != NULL);

    vec->elems = realloc(vec->elems, cap * sizeof(void *));
    if (vec->elems == NULL)
        return -1;

    /* everything after the old capacity needs to be zeroed out */
    if (cap > vec->cap)
        memset(vec->elems + vec->cap, 0, cap - vec->cap);

    /* so that we don't accidentally realloc-free it later */
    if (cap == 0)
        vec->elems = NULL;

    vec->cap = cap;

    return 0;
}


static void swap(vector *vec, size_t i, size_t j) {
    void *temp;

    assert(vec != NULL);

    temp = vec->elems[i];
    vec->elems[i] = vec->elems[j];
    vec->elems[j] = temp;
}
