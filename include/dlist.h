/**
 * @file dlist.h
 * @brief Header for a generic doubly-linked list
 *
 * @author Alexander Malyshev
 */

#ifndef __DLIST_H__
#define __DLIST_H__

#include <assert.h>
#include <stddef.h>


/**
 * @brief The void "value"
 *
 * Used to force macros to have a void return type
 */
#define DLIST_VOID ((void)NULL)

/**
 * @brief Declares a new list type
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * Usage:
 *
 * DLIST_DECLARE(point_deque, point);
 *
 * @param LIST_TYPE The type of the list
 * @param ELEM_TYPE The type of the list's elements
 */
#define DLIST_DECLARE(LIST_TYPE, ELEM_TYPE)                                 \
    typedef struct LIST_TYPE {                                              \
        struct ELEM_TYPE *front; /**< the first element in the list */      \
        struct ELEM_TYPE *back;  /**< the last element in the list */       \
        struct ELEM_TYPE *temp;  /**< hacky "local" variable for macros */  \
        size_t len;              /**< the length of the list */             \
    } LIST_TYPE

/**
 * @brief Declares a link in a struct for use with a list
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * Usage:
 *
 * struct point {
 *     DLIST_DECLARE_LINK(point, linkname);
 *     int x;
 *     int y;
 * };
 *
 * @param ELEM_TYPE The type of the element
 * @param LINK The name of the link field
 */
#define DLIST_DECLARE_LINK(ELEM_TYPE, LINK) \
    struct {                                \
        struct ELEM_TYPE *next;             \
        struct ELEM_TYPE *prev;             \
    } LINK

/**
 * @brief Initializes a list
 *
 * @param LIST The address of the list
 */
#define DLIST_INIT(LIST) (      \
    assert((LIST) != NULL),     \
                                \
    (LIST)->front = NULL,       \
    (LIST)->back = NULL,        \
    (LIST)->temp = NULL,        \
    (LIST)->len = 0,            \
                                \
    DLIST_VOID                  \
)

/// @brief Statically initializes a list
#define DLIST_STATIC_INIT { \
    .front = NULL,          \
    .back = NULL,           \
    .temp = NULL,           \
    .len = 0                \
}

/**
 * @brief Initializes the list link of an element
 *
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define DLIST_ELEM_INIT(ELEM, LINK) (   \
    assert((ELEM) != NULL),             \
                                        \
    (ELEM)->LINK.next = NULL,           \
    (ELEM)->LINK.prev = NULL,           \
                                        \
    DLIST_VOID                          \
)

/// @brief Statically initializes the list link of an element
#define DLIST_LINK_STATIC_INIT { .next = NULL, .prev = NULL }

/**
 * @brief Returns the number of elements in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The number of elements in the list
 */
#define DLIST_LEN(LIST, LINK) (DLIST_CHECK(LIST, LINK), (LIST)->len)

/**
 * @brief Returns the first element in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The first element in the list
 */
#define DLIST_PEEK_FRONT(LIST, LINK) (DLIST_CHECK(LIST, LINK), (LIST)->front)

/**
 * @brief Returns the last element in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The last element in the list
 */
#define DLIST_PEEK_BACK(LIST, LINK) (DLIST_CHECK(LIST, LINK), (LIST)->back)

/**
 * @brief Inserts an element at the front of a list
 *
 * @param LIST The address of the list
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define DLIST_PUSH_FRONT(LIST, ELEM, LINK) (                                \
    DLIST_CHECK(LIST, LINK),                                                \
    DLIST_CHECK_NEW_ELEM(ELEM, LINK),                                       \
                                                                            \
    /* the element's next points to the old front of the list */            \
    (ELEM)->LINK.next = (LIST)->front,                                      \
                                                                            \
    /* the old front's prev points to our new element if it exists,
     * otherwise the list is empty and needs its back reference updated */  \
    ((LIST)->front != NULL)?(                                               \
        (LIST)->front->LINK.prev = (ELEM)                                   \
    ):(                                                                     \
        (LIST)->back = (ELEM)                                               \
    ),                                                                      \
                                                                            \
    /* point the list's front at our new element */                         \
    (LIST)->front = (ELEM),                                                 \
                                                                            \
    (LIST)->len += 1,                                                       \
                                                                            \
    DLIST_VOID                                                              \
)

/**
 * @brief Inserts an element at the back of a list
 *
 * @param LIST The address of the list
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define DLIST_PUSH_BACK(LIST, ELEM, LINK) (                                 \
    DLIST_CHECK(LIST, LINK),                                                \
    DLIST_CHECK_NEW_ELEM(ELEM, LINK),                                       \
                                                                            \
    /* the element's prev points to the old back of the list */             \
    (ELEM)->LINK.prev = (LIST)->back,                                       \
                                                                            \
    /* the old back's next points to our new element if it exists,
     * otherwise the list is empty and needs its front reference updated */ \
    ((LIST)->back != NULL)?(                                                \
        (LIST)->back->LINK.next = (ELEM)                                    \
    ):(                                                                     \
        (LIST)->front = (ELEM)                                              \
    ),                                                                      \
                                                                            \
    /* point the list's back at our new element */                          \
    (LIST)->back = (ELEM),                                                  \
                                                                            \
    (LIST)->len += 1,                                                       \
                                                                            \
    DLIST_VOID                                                              \
)

/**
 * @brief Inserts an element after an existing list element
 *
 * @param LIST The address of the list
 * @param INS The address of the element already in the list
 * @param NEW The address of the new element to insert
 * @param LINK The name of the link field
 */
#define DLIST_INSERT_NEXT(LIST, INS, NEW, LINK) (                           \
    DLIST_CHECK(LIST, LINK),                                                \
    DLIST_CHECK_INSERTED_ELEM(INS, LIST, LINK),                             \
    DLIST_CHECK_NEW_ELEM(NEW, LINK),                                        \
                                                                            \
    /* list is supposed to be non-empty */                                  \
    assert((LIST)->len != 0),                                               \
                                                                            \
    /* have the new element point to its new neighbors */                   \
    (NEW)->LINK.prev = (INS),                                               \
    (NEW)->LINK.next = (INS)->LINK.next,                                    \
                                                                            \
    /* if the inserted element is not the back, then we want to have the
     * inserted element's next's prev reference point to the new element */ \
    ((INS) != (LIST)->back)?(                                               \
        (INS)->LINK.next->LINK.prev = (NEW)                                 \
    /* otherwise we need to update the list's back reference */             \
    ):(                                                                     \
        (LIST)->back = (NEW)                                                \
    ),                                                                      \
                                                                            \
    /* splice in the new element into the list */                           \
    (INS)->LINK.prev = (NEW),                                               \
                                                                            \
    (LIST)->len += 1,                                                       \
                                                                            \
    DLIST_VOID                                                              \
)

/**
 * @brief Inserts an element before an existing list element
 *
 * @param LIST The address of the list
 * @param INS The address of the element already in the list
 * @param NEW The address of the new element to insert
 * @param LINK The name of the link field
 */
#define DLIST_INSERT_PREV(LIST, INS, NEW, LINK) (                           \
    DLIST_CHECK(LIST, LINK),                                                \
    DLIST_CHECK_INSERTED_ELEM(INS, LIST, LINK),                             \
    DLIST_CHECK_NEW_ELEM((NEW), LINK),                                      \
                                                                            \
    /* list is supposed to be non-empty */                                  \
    assert((LIST)->len != 0),                                               \
                                                                            \
    /* have the new element point to its new neighbors */                   \
    (NEW)->LINK.prev = (INS)->LINK.prev,                                    \
    (NEW)->LINK.next = (INS),                                               \
                                                                            \
    /* if the inserted element is not the front, then we want to have the
     * inserted element's prev's next reference point to the new element */ \
    ((INS) != (LIST)->front)?(                                              \
        (INS)->LINK.prev->LINK.next = (NEW)                                 \
    /* otherwise we need to update the list's front reference */            \
    ):(                                                                     \
        (LIST)->front = (NEW)                                               \
    ),                                                                      \
                                                                            \
    /* splice in the new element into the list */                           \
    (INS)->LINK.prev = (NEW),                                               \
                                                                            \
    (LIST)->len += 1,                                                       \
                                                                            \
    DLIST_VOID                                                              \
)

/**
 * @brief Pops the first element off of a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the first element, NULL if the list is empty
 */
#define DLIST_POP_FRONT(LIST, LINK) (                               \
    DLIST_CHECK(LIST, LINK),                                        \
                                                                    \
    ((LIST)->len == 0)?(                                            \
        LIST->temp = NULL                                           \
    ):((LIST)->len == 1)?(                                          \
        (LIST)->temp = (LIST)->front,                               \
                                                                    \
        (LIST)->front = NULL,                                       \
        (LIST)->back = NULL                                         \
    ):(                                                             \
        (LIST)->temp = (LIST)->front,                               \
                                                                    \
        /* update the new front of the list */                      \
        (LIST)->front = (LIST)->front->LINK.next,                   \
        (LIST)->front->LINK.prev = NULL                             \
    ),                                                              \
                                                                    \
    ((LIST)->temp == NULL)?(                                        \
        NULL                                                        \
    ):(                                                             \
        /* mark the old front as not being inserted in a list */    \
        DLIST_ELEM_INIT((LIST)->temp, LINK),                        \
                                                                    \
        /* update the list's length, and return the old front */    \
        (LIST)->len -= 1,                                           \
        (LIST)->temp                                                \
    )                                                               \
)

/**
 * @brief Pops the last element off of a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the last element, NULL if the list is empty
 */
#define DLIST_POP_BACK(LIST, LINK) (                                \
    DLIST_CHECK(LIST, LINK),                                        \
                                                                    \
    ((LIST)->len == 0)?(                                            \
        (LIST)->temp = NULL                                         \
    ):((LIST)->len == 1)?(                                          \
        (LIST)->temp = (LIST)->front,                               \
                                                                    \
        (LIST)->front = NULL,                                       \
        (LIST)->back = NULL                                         \
    ):(                                                             \
        (LIST)->temp = (LIST)->back,                                \
                                                                    \
        /* update the new back of the list */                       \
        (LIST)->back = (LIST)->back->LINK.prev,                     \
        (LIST)->back->LINK.next = NULL                              \
    ),                                                              \
                                                                    \
    ((LIST)->temp == NULL)?(                                        \
        NULL                                                        \
    ):(                                                             \
        /* mark the old back as not being inserted in a list */     \
        DLIST_ELEM_INIT((LIST)->temp, LINK),                        \
                                                                    \
        /* update the list's length, and return the old front */    \
        (LIST)->len -= 1,                                           \
        (LIST)->temp                                                \
    )                                                               \
)

/**
 * @brief Removes an element from a list
 *
 * @param LIST The address of the list
 * @param ELEM The address of the inserted element
 * @param LINK The name of the link field
 */
#define DLIST_REMOVE(LIST, ELEM, LINK) (                                    \
    DLIST_CHECK(LIST, LINK),                                                \
    DLIST_CHECK_INSERTED_ELEM(ELEM, LIST, LINK),                            \
                                                                            \
    /* cannot remove an element from an empty list */                       \
    assert((LIST)->len != 0),                                               \
                                                                            \
    /* if we're removing the front element, then we need to update the
     * list's front reference to the next element. otherwise we want to
     * update the next reference of the removed element's prev */           \
    ((LIST)->front == (ELEM))?(                                             \
        (LIST)->front = (ELEM)->LINK.next                                   \
    ):(                                                                     \
        (ELEM)->LINK.prev->LINK.next = (ELEM)->LINK.next                    \
    ),                                                                      \
                                                                            \
    /* ditto for the back element, and the prev reference of the removed
     * element's next */                                                    \
    ((LIST)->back == (ELEM))?(                                              \
        (LIST)->back = (ELEM)->LINK.prev                                    \
    ):(                                                                     \
        (ELEM)->LINK.next->LINK.prev = (ELEM)->LINK.prev                    \
    ),                                                                      \
                                                                            \
    /* the element is no longer inserted in the list */                     \
    (ELEM)->LINK.next = NULL,                                               \
    (ELEM)->LINK.prev = NULL,                                               \
                                                                            \
    (LIST)->len -= 1,                                                       \
                                                                            \
    DLIST_VOID                                                              \
)

/**
 * @brief Iterates through all elements of a list
 *
 * @param CURR The address of the current element in the iteration
 * @param LIST The address of the list
 * @param LINK The name of the link field
 */
#define DLIST_FOREACH(CURR, LIST, LINK)                     \
    for (DLIST_CHECK(LIST, LINK), (CURR) = (LIST)->front;   \
         (CURR) != NULL;                                    \
         (CURR) = (CURR)->LINK.next)

/**
 * @brief Checks the validity of a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 */
#define DLIST_CHECK(LIST, LINK) (                                           \
    assert((LIST) != NULL),                                                 \
                                                                            \
    /* check that the length makes sense considering the front and back */  \
    ((LIST)->front == NULL || (LIST)->back == NULL || (LIST)->len == 0)?(   \
        assert((LIST)->front == NULL),                                      \
        assert((LIST)->back == NULL),                                       \
        assert((LIST)->len == 0)                                            \
    ):((LIST)->front == (LIST)->back || (LIST)->len == 1)?(                 \
        assert((LIST)->front != NULL && (LIST)->front == (LIST)->back),     \
        assert((LIST)->len == 1)                                            \
    ):(                                                                     \
        DLIST_VOID                                                          \
    )                                                                       \
)

/**
 * @brief Checks the validity of a new, uninserted list element
 *
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define DLIST_CHECK_NEW_ELEM(ELEM, LINK) (  \
    assert((ELEM) != NULL),                 \
                                            \
    assert((ELEM)->LINK.next == NULL),      \
    assert((ELEM)->LINK.prev == NULL)       \
)

/**
 * @brief Checks the validity of an already-inserted list element
 *
 * Assumes that LIST has already been checked for validity
 *
 * @param ELEM The address of the element
 * @param LIST The address of the list
 * @param LINK The name of the link field
 */
#define DLIST_CHECK_INSERTED_ELEM(ELEM, LIST, LINK) (                   \
    assert((ELEM) != NULL),                                             \
                                                                        \
    /* element should have a valid prev reference if it is not the front,
     * otherwise its prev reference should be NULL */                   \
    ((LIST)->front != (ELEM))?(                                         \
        assert((ELEM)->LINK.prev != NULL)                               \
    ):(                                                                 \
        assert((ELEM)->LINK.prev == NULL)                               \
    ),                                                                  \
                                                                        \
    /* ditto with the element's next reference and the back */          \
    ((LIST)->back != (ELEM))?(                                          \
        assert((ELEM)->LINK.next != NULL)                               \
    ):(                                                                 \
        assert((ELEM)->LINK.next == NULL)                               \
    )                                                                   \
)


#endif
