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
    .min = NULL;                \
    .nelems = 0;                \
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
    assert((DEST) != NULL);                                                 \
    assert((SOURCE) != NULL);                                               \
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


#define BINOHEAP_INSERT(HEAP, ELEM, LINK) do {          \
    assert((HEAP) != NULL);                             \
    assert((ELEM) != NULL);                             \
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
        (HEAP)->head = (ELEM);                          \
                                                        \
    (HEAP)->nelems += 1;                                \
} while (0)


#define BINOHEAP_REMOVEMIN(DEST, HEAP, LESS, LINK) do {     \
    /* allocate a buffer of size 'bitlen(size_t) + 1' */    \
    void *buf[sizeof(size_t) * CHAR_BIT + 1];               \
                                                            \
    

#define LINK_TREES(DEST, SOURCE, LESS, LINK) do {                           \
    assert((DEST) != NULL);                                                 \
    assert((SOURCE) != NULL);                                               \
                                                                            \
    /* can only link two binomial trees of the same rank */                 \
    assert((DEST)->LINK.rank == (SOURCE)->LINK.rank);                       \
                                                                            \
    /* the roots of trees must not have siblings */                         \
    assert((DEST)->LINK.prev == (DEST));                                    \
    assert((DEST)->LINK.next == (DEST));                                    \
    assert((SOURCE)->LINK.prev == (SOURCE));                                \
    assert((SOURCE)->LINK.next == (SOURCE));                                \
                                                                            \
    /* can't link trees with parents, one of them would be overwritten */   \
    assert((DEST)->LINK.parent == NULL);                                    \
    assert((SOURCE)->LINK.parent == NULL);                                  \
                                                                            \
    if (LESS((DEST)->LINK.key, (SOURCE)->LINK.key)) {                       \
        (SOURCE)->LINK.parent = (DEST);                                     \
        MERGE_LISTS((DEST)->child, SOURCE, LINK);                           \
        (DEST)->LINK.rank += 1;                                             \
    }                                                                       \
    else {                                                                  \
        (DEST)->LINK.parent = (SOURCE);                                     \
        MERGE_LISTS((SOURCE)->child, DEST, LINK);                           \
        (SOURCE)->LINK.rank += 1;                                           \
                                                                            \
        SWAP(DEST, SOURCE);                                                 \
    }                                                                       \
} while (0)


#define MERGE_LISTS(ELEM1, ELEM2, LINK) do {        \
    /* abusing the C type system to its fullest */  \
    void *left1;                                    \
                                                    \
    assert((ELEM1) != NULL);                        \
    assert((ELEM2) != NULL);                        \
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
