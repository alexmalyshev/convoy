#ifndef __BINOHEAP_H__
#define __BINOHEAP_H__


#include <assert.h>
#include <limits.h>
#include <stddef.h>


#define BINOHEAP_NEW(HEAP_TYPE, ELEM_TYPE)  \
    typedef struct HEAP_TYPE {              \
        struct ELEM_TYPE *min;              \
        size_t nelems;                      \
    } HEAP_TYPE


#define BINOHEAP_LINK(ELEM_TYPE, KEY_TYPE, LINK)    \
    struct {                                        \
        struct ELEM_TYPE *parent;                   \
        struct ELEM_TYPE *left;                     \
        struct ELEM_TYPE *right;                    \
        struct ELEM_TYPE *child;                    \
        size_t rank;                                \
        KEY_TYPE key;                               \
    } LINK


#define BINOHEAP_STATIC_INIT {  \
    .min = NULL,                \
    .nelems = 0                 \
}


#define BINOHEAP_INIT(HEAP) do {    \
    assert((HEAP) != NULL);         \
                                    \
    (HEAP)->min = NULL;             \
    (HEAP)->nelems = 0;             \
} while (0)


#define BINOHEAP_ELEM_INIT(ELEM, KEY, LINK) do {            \
    assert((ELEM) != NULL);                                 \
                                                            \
    /* element starts off with no parent and no children */ \
    (ELEM)->LINK.parent = NULL;                             \
    (ELEM)->LINK.child = NULL;                              \
    (ELEM)->LINK.rank = 0;                                  \
                                                            \
    /* no siblings either */                                \
    (ELEM)->LINK.left = (ELEM);                             \
    (ELEM)->LINK.right = (ELEM);                            \
                                                            \
    (ELEM)->LINK.key = (KEY);                               \
} while (0)


#define BINOHEAP_MERGE(DEST, SOURCE, LESS, LINK) do {                       \
    BINOHEAP_CHECK(DEST);                                                   \
    BINOHEAP_CHECK(SOURCE);                                                 \
                                                                            \
    /* shouldn't be attempting to merge a heap with itself */               \
    assert((DEST)->min != (SOURCE)->head || (DEST)->head == NULL);          \
                                                                            \
    /* if the source heap is empty, then we're done */                      \
    if ((SOURCE)->min == NULL)                                              \
        break;                                                              \
                                                                            \
    /* otherwise if the destination heap is empty, we need to move the
     * source heap over into the destination heap */                        \
    if ((DEST)->min == NULL) {                                              \
        (DEST)->min = (SOURCE)->min;                                        \
        (DEST)->nelems = (SOURCE)->nelems;                                  \
        BINOHEAP_INIT(SOURCE);                                              \
        break;                                                              \
    }                                                                       \
                                                                            \
    /* merge the two heaps' lists together */                               \
    MERGE_LISTS((DEST)->min, (SOURCE)->min, LINK);                          \
                                                                            \
    /* might need to update the minimum value in the destination heap */    \
    if (LESS((SOURCE)->min->LINK.key, (DEST)->min->LINK.key))               \
        (DEST)->min = (SOURCE)->min;                                        \
                                                                            \
    (DEST)->nelems += (SOURCE)->nelems;                                     \
                                                                            \
    BINOHEAP_INIT(SOURCE);                                                  \
} while (0)


#define BINOHEAP_INSERT(HEAP, ELEM, LESS, LINK) do {    \
    BINOHEAP_CHECK(HEAP);                               \
    BINOHEAP_CHECK_NEW_ELEM(ELEM, LINK);                \
                                                        \
    if ((HEAP)->min == NULL) {                          \
        (HEAP)->min = (ELEM);                           \
        (HEAP)->nelems = 1;                             \
        break;                                          \
    }                                                   \
                                                        \
    MERGE_LISTS((HEAP)->min, ELEM, LINK);               \
                                                        \
    if (LESS((ELEM)->LINK.key, (HEAP)->min->LINK.key))  \
        (HEAP)->min = (ELEM);                           \
                                                        \
    (HEAP)->nelems += 1;                                \
} while (0)


#define BINOHEAP_REMOVEMIN(DEST, HEAP, LESS, ELEM_TYPE, LINK) do {          \
    /* allocate a NULLed buffer of size 'bitlen(size_t) + 1' */             \
    struct ELEM_TYPE *buf[sizeof(size_t) * CHAR_BIT + 1] = { NULL };        \
                                                                            \
    struct ELEM_TYPE *rem = NULL;                                           \
    struct ELEM_TYPE *min = NULL;                                           \
                                                                            \
    size_t i;                                                               \
                                                                            \
    BINOHEAP_CHECK(HEAP);                                                   \
                                                                            \
    /* return NULL if the heap is empty */                                  \
    if ((HEAP)->min == NULL) {                                              \
        (DEST) = NULL;                                                      \
        break;                                                              \
    }                                                                       \
                                                                            \
    /* otherwise write the minimum element to the destination */            \
    (DEST) = (HEAP)->min;                                                   \
                                                                            \
    /* keep looping until all siblings of the minimum element have been
     * compressed into the buffer */                                        \
    while ((HEAP)->min->LINK.left != (HEAP)->min) {                         \
        rem = (HEAP)->min->LINK.right;                                      \
                                                                            \
        REMOVE_ELEM(rem, LINK);                                             \
                                                                            \
        /* if there already exists an element of the same rank in the
         * buffer, then we need to link the two binomial trees and retry
         * the insert at the next rank */                                   \
        while (buf[rem->LINK.rank] != NULL) {                               \
            struct ELEM_TYPE *temp = buf[rem->LINK.rank];                   \
            LINK_TREES(rem, temp, LESS, LINK);                              \
        }                                                                   \
                                                                            \
        /* once we're out here, then we can insert the current binomial
         * tree into the buffer at the same index as its rank */            \
        buf[rem->LINK.rank] = rem;                                          \
    }                                                                       \
                                                                            \
    /* loop through the buffer and merge all the trees into one list */     \
    min = NULL;                                                             \
    for (i = 0; i < sizeof(size_t) * CHAR_BIT + 1; ++i) {                   \
        if (buf[i] == NULL)                                                 \
            continue;                                                       \
                                                                            \
        if (min == NULL) {                                                  \
            min = buf[i];                                                   \
            continue;                                                       \
        }                                                                   \
                                                                            \
        /* merge the tree from the buffer into our accumulator */           \
        MERGE_LISTS(min, buf[i], LINK);                                     \
                                                                            \
        /* track the new minimum as well */                                 \
        if (LESS(buf[i]->LINK.key, min->LINK.key))                          \
            min = buf[i];                                                   \
    }                                                                       \
                                                                            \
    /* check if the minimum element has any children */                     \
    if ((HEAP)->min->LINK.child != NULL) {                                  \
        /* need to store the heap as it is here, as we might overwrite our
         * 'min' variable with a child */                                   \
        struct ELEM_TYPE *heap = min;                                       \
                                                                            \
        struct ELEM_TYPE *child = (HEAP)->min->LINK.child;                  \
                                                                            \
        /* first scan through them to check for a smaller new minimum */    \
        do {                                                                \
            if (LESS(child->LINK.key, min->LINK.key))                       \
                min = child;                                                \
                                                                            \
            child = child->LINK.right;                                      \
        } while (child != (HEAP)->min->LINK.child);                         \
                                                                            \
        /* then merge them into our heap */                                 \
        MERGE_LISTS(heap, child, LINK);                                     \
    }                                                                       \
                                                                            \
    /* clear out the children list from the old minimum */                  \
    (HEAP)->min->LINK.child = NULL;                                         \
                                                                            \
    /* assign the heap's new minimum */                                     \
    (HEAP)->min = min;                                                      \
} while (0)


#define BINOHEAP_CHECK(HEAP) do {                       \
    assert((HEAP) != NULL);                             \
                                                        \
    if ((HEAP)->min == NULL || (HEAP)->nelems == 0) {   \
        assert((HEAP)->min == NULL);                    \
        assert((HEAP)->nelems == 0);                    \
    }                                                   \
} while (0)


#define BINOHEAP_CHECK_ELEM(ELEM, LINK) do {                            \
    assert((ELEM) != NULL);                                             \
                                                                        \
    if ((ELEM)->LINK.left == (ELEM) || (ELEM)->LINK.right == (ELEM)) {  \
        assert((ELEM)->LINK.left == (ELEM));                            \
        assert((ELEM)->LINK.right == (ELEM));                           \
    }                                                                   \
                                                                        \
    if ((ELEM)->LINK.rank == 0 || (ELEM)->LINK.child == NULL) {         \
        assert((ELEM)->LINK.rank == 0);                                 \
        assert((ELEM)->LINK.child == NULL);                             \
    }                                                                   \
} while (0)


#define BINOHEAP_CHECK_NEW_ELEM(ELEM, LINK) do {            \
    BINOHEAP_CHECK_ELEM(ELEM, LINK);                        \
                                                            \
    /* new element should not have a parent or children */  \
    assert((ELEM)->LINK.parent == NULL);                    \
    assert((ELEM)->LINK.child == NULL);                     \
    assert((ELEM)->LINK.rank == 0);                         \
                                                            \
    /* shouldn't have siblings either */                    \
    assert((ELEM)->LINK.left == (ELEM));                    \
    assert((ELEM)->LINK.right == (ELEM));                   \
} while (0)


#define BINOHEAP_CHECK_ROOT(ELEM, LINK) do {        \
    BINOHEAP_CHECK_ELEM(ELEM, LINK);                \
                                                    \
    /* roots don't have parents */                  \
    assert((ELEM)->LINK.parent == NULL);            \
                                                    \
    /* the roots of trees must not have siblings */ \
    assert((ELEM)->LINK.left == (ELEM));            \
    assert((ELEM)->LINK.right == (ELEM));           \
} while (0)


#define LINK_TREES(DEST, SOURCE, LESS, LINK) do {                           \
    BINOHEAP_CHECK_ROOT(DEST, LINK);                                        \
    BINOHEAP_CHECK_ROOT(SOURCE, LINK);                                      \
                                                                            \
    /* can only link two binomial trees of the same rank */                 \
    assert((DEST)->LINK.rank == (SOURCE)->LINK.rank);                       \
                                                                            \
    if (LESS((DEST)->LINK.key, (SOURCE)->LINK.key)) {                       \
        (SOURCE)->LINK.parent = (DEST);                                     \
        MERGE_LISTS((DEST)->LINK.child, SOURCE, LINK);                      \
        (DEST)->LINK.rank += 1;                                             \
    }                                                                       \
    else {                                                                  \
        (DEST)->LINK.parent = (SOURCE);                                     \
        MERGE_LISTS((SOURCE)->LINK.child, DEST, LINK);                      \
        (SOURCE)->LINK.rank += 1;                                           \
                                                                            \
        SWAP(DEST, SOURCE);                                                 \
    }                                                                       \
} while (0)


#define REMOVE_ELEM(ELEM, LINK) do {                                    \
    BINOHEAP_CHECK_ELEM(ELEM, LINK);                                    \
                                                                        \
    /* should only be removing a root element from its sibling list */  \
    assert((ELEM)->LINK.parent == NULL);                                \
                                                                        \
    /* should not be removing an element from a single-element list */  \
    assert((ELEM)->LINK.left != (ELEM));                                \
                                                                        \
    /* element's siblings point to each other */                        \
    (ELEM)->LINK.left->LINK.right = (ELEM)->LINK.right;                 \
    (ELEM)->LINK.right->LINK.left = (ELEM)->LINK.left;                  \
                                                                        \
    /* element now has no siblings */                                   \
    (ELEM)->LINK.left = (ELEM);                                         \
    (ELEM)->LINK.right = (ELEM);                                        \
} while (0)


#define MERGE_LISTS(ELEM1, ELEM2, LINK) do {        \
    /* abusing the C type system to its fullest */  \
    void *left1;                                    \
                                                    \
    BINOHEAP_CHECK_ELEM(ELEM1, LINK);               \
    BINOHEAP_CHECK_ELEM(ELEM2, LINK);               \
                                                    \
    (ELEM1)->LINK.left->LINK.right = (ELEM2);       \
    (ELEM2)->LINK.left->LINK.right = (ELEM1);       \
                                                    \
    left1 = (ELEM1)->LINK.left;                     \
                                                    \
    (ELEM1)->LINK.left = (ELEM2)->LINK.left;        \
    (ELEM2)->LINK.left = left1;                     \
} while (0)


#define SWAP(REF1, REF2) do {   \
    void *temp;                 \
                                \
    temp = (REF1);              \
    (REF1) = (REF2);            \
    (REF2) = temp;              \
} while (0)


#endif // __BINOHEAP_H__
