#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static size_t find_last(vector *vec, size_t start);
static void resize(vector *vec, size_t cap);

void vector_init(vector *vec, size_t cap) {
    assert(vec != NULL);

    if (cap != 0) {
        vec->elems = calloc(cap, sizeof(void *));
        assert(vec->elems != NULL);
    } else {
        vec->elems = NULL;
    }

    vec->last = 0;
    vec->cap = cap;
}

void vector_destroy(vector *vec) {
    assert(vec != NULL);

    free(vec->elems);
}

void *vector_at(vector *vec, size_t i) {
    assert(vec != NULL);    

    /* either out of bounds or just not there */
    if (vec->last < i)
        return NULL;

    return vec->elems[i];
}

void vector_clear(vector *vec) {
    assert(vec != NULL);

    /* everything after vec->last is already NULL anyway */
    memset(vec->elems, 0, vec->last);
}

void *vector_insert(vector *vec, size_t i, void *elem) {
    void *old;

    assert(vec != NULL);
    assert(elem != NULL);

    /* if i is "unreasonably" big, just resize to i immediately, and
     * if i is 0, then resize to the default capacity */
    if (i >= vec->cap) {
        if (i == 0)
            resize(vec, VECTOR_DEFAULT_CAP);
        else if (i < VECTOR_GROW_CAP(vec->cap))
            resize(vec, VECTOR_GROW_CAP(vec->cap));
        else
            resize(vec, i);
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

void vector_push(vector *vec, void *elem) {
    vector_insert(vec, vec->last + 1, elem);
}

void *vector_remove(vector *vec, size_t i) {
    void *old;

    assert(vec != NULL);
    assert(i < vec->cap);

    old = vec->elems[i];
    vec->elems[i] = NULL;

    /* if we removed the last element then we need to scan back
     * looking for the new last index */
    if (i == vec->last)
        vec->last = find_last(vec, i);

    return old;
}

void vector_resize(vector *vec, size_t cap) {
    assert(vec != NULL);
    resize(vec, cap);
}

void vector_trim(vector *vec) {
    assert(vec != NULL);
    resize(vec, vec->last);
}

static size_t find_last(vector *vec, size_t start) {
    size_t k;

    if (start == 0)
        return 0;

    for (k = start - 1; k != 0; --k) {
        if (vec->elems[k] != NULL)
            return k;
    }
    return 0;
}

static void resize(vector *vec, size_t cap) {
    vec->elems = realloc(vec->elems, cap);

    /* everything after the old capacity needs to be zeroed out */
    if (cap > vec->cap)
        memset(vec->elems + vec->cap, 0, cap - vec->cap);

    /* so that we don't accidentally realloc-free it later */
    if (cap == 0)
        vec->elems = NULL;

    vec->cap = cap;
}
