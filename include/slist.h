/**
 * @file slist.h
 * @brief Header for a generic singly-linked list
 *
 * @author Alexander Malyshev
 */

#ifndef __SLIST_H__
#define __SLIST_H__

#include <assert.h>
#include <stddef.h>


/**
 * @brief The void "value"
 *
 * Used to force macros to have a void return type
 */
#define SLIST_VOID ((void)NULL)

/**
 * @brief Declares a new list type
 *
 * ELEM_TYPE must be the name of a struct type with a declared link
 *
 * Usage:
 *
 * SLIST_DECLARE(point_queue, point);
 *
 * @param LIST_TYPE The type of the list
 * @param ELEM_TYPE The type of the list's elements
 */
#define SLIST_DECLARE(LIST_TYPE, ELEM_TYPE)                                 \
    typedef struct LIST_TYPE {                                              \
        struct ELEM_TYPE *head; /**< the first element in the list */       \
        struct ELEM_TYPE *tail; /**< the last element in the list */        \
        struct ELEM_TYPE *temp; /**< hacky "local" variable for macros */   \
        size_t len;             /**< the length of the list */              \
    } LIST_TYPE

/**
 * @brief Declares a link in a struct for use with a list
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * Usage:
 *
 * struct point {
 *     SLIST_DECLARE_LINK(point, linkname);
 *     int x;
 *     int y;
 * };
 *
 * @param ELEM_TYPE The type of the element
 * @param LINK The name of the link field
 */
#define SLIST_DECLARE_LINK(ELEM_TYPE, LINK) \
    struct ELEM_TYPE *LINK

/**
 * @brief Initializes a list
 *
 * @param LIST the address of the list
 */
#define SLIST_INIT(LIST) (  \
    assert((LIST) != NULL), \
                            \
    (LIST)->head = NULL,    \
    (LIST)->tail = NULL,    \
    (LIST)->temp = NULL,    \
    (LIST)->len = 0,        \
                            \
    SLIST_VOID              \
)

/// @brief Statically initializes a list
#define SLIST_STATIC_INIT { \
    .head = NULL,           \
    .tail = NULL,           \
    .temp = NULL,           \
    .len = 0                \
}

/**
 * @brief Initializes the list link of an element
 *
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define SLIST_ELEM_INIT(ELEM, LINK) (       \
    assert((ELEM) != NULL),                 \
                                            \
    (ELEM)->LINK = NULL,                    \
                                            \
    SLIST_VOID                              \
)

/// @brief Statically initializes the list link of an element
#define SLIST_LINK_STATIC_INIT NULL

/**
 * @brief Returns the number of elements in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The number of elements in the list
 */
#define SLIST_LEN(LIST, LINK) ( SLIST_CHECK(LIST, LINK), (LIST)->len)

/**
 * @brief Returns true iff an element is inserted into a list
 *
 * Does not search any lists
 *
 * @param ELEM The address of the element
 * @return True iff the element is inserted into a list
 */
#define SLIST_IS_ELEM_INSERTED(ELEM) (  \
    assert((ELEM) != NULL),             \
                                        \
    (ELEM)->LINK != NULL                \
)

/**
 * @brief Returns the first element in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the first element, NULL if the list is empty
 */
#define SLIST_PEEK_HEAD(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->head)

/**
 * @brief Returns the last element in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the last element, NULL if the list is empty
 */
#define SLIST_PEEK_TAIL(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->tail)

/**
 * @brief Pops the first element off of a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the first element, NULL if the list is empty
 */
#define SLIST_POP_HEAD(LIST, LINK) (                                \
    SLIST_CHECK(LIST, LINK),                                        \
                                                                    \
    ((LIST)->len == 0)?(                                            \
        (LIST)->temp = NULL                                         \
    ):((LIST)->len == 1)?(                                          \
        (LIST)->temp = (LIST)->head,                                \
                                                                    \
        (LIST)->head = NULL,                                        \
        (LIST)->tail = NULL                                         \
    ):(                                                             \
        (LIST)->temp = (LIST)->head,                                \
                                                                    \
        /* update the new head of the list */                       \
        (LIST)->head = (LIST)->head->LINK,                          \
                                                                    \
        /* make the tail point to the new head */                   \
        (LIST)->tail->LINK = (LIST)->head                           \
    ),                                                              \
                                                                    \
    ((LIST)->temp == NULL)?(                                        \
        NULL                                                        \
    ):(                                                             \
        /* mark the old head as not being inserted in a list */     \
        (LIST)->temp->LINK = NULL,                                  \
                                                                    \
        /* update the list's length, and return the old head */     \
        (LIST)->len -= 1,                                           \
        (LIST)->temp                                                \
    )                                                               \
)

/**
 * @brief Pushes an element onto the front of a list
 *
 * @param LIST The address of the list
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define SLIST_PUSH_HEAD(LIST, ELEM, LINK) (         \
    SLIST_CHECK(LIST, LINK),                        \
    assert((ELEM) != NULL),                         \
    assert((ELEM)->LINK == NULL),                   \
                                                    \
    /* add the element to the front of the list */  \
    ((LIST)->len != 0)?(                            \
        (ELEM)->LINK = (LIST)->head                 \
    ):(                                             \
        (LIST)->tail = (ELEM)                       \
    ),                                              \
                                                    \
    /* update the list's head and length */         \
    (LIST)->head = (ELEM),                          \
    (LIST)->len += 1,                               \
                                                    \
    /* update the tail to point to the new head */  \
    (LIST)->tail->LINK = (LIST)->head,              \
                                                    \
    SLIST_VOID                                      \
)

/**
 * @brief Pushes an element onto the back of a list
 *
 * @param LIST The address of the list
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 */
#define SLIST_PUSH_TAIL(LIST, ELEM, LINK) (         \
    SLIST_CHECK(LIST, LINK),                        \
    assert((ELEM) != NULL),                         \
    assert((ELEM)->LINK == NULL),                   \
                                                    \
    /* add the element to the end of the list */    \
    ((LIST)->len != 0)?(                            \
        (LIST)->tail->LINK = (ELEM)                 \
    ):(                                             \
        (LIST)->head = (ELEM)                       \
    ),                                              \
                                                    \
    /* update the list's tail and length */         \
    (LIST)->tail = (ELEM),                          \
    (LIST)->len += 1,                               \
                                                    \
    /* update the new tail to point to the head */  \
    (LIST)->tail->LINK = (LIST)->head,              \
                                                    \
    SLIST_VOID                                      \
)

/**
 * @brief Iterates through all elements of a list
 *
 * @param CURR The address of the current element in the iteration
 * @param LIST The address of the list
 * @param LINK The name of the link field
 */
#define SLIST_FOREACH(CURR, LIST, LINK)                                     \
    for ((CURR) = (LIST)->head, (LIST)->temp = (LIST)->head;                \
         (CURR) != NULL && ((CURR) != (LIST)->head || (LIST)->temp != NULL);\
         (LIST)->temp = NULL, (CURR) = (CURR)->LINK)

/**
 * @brief Checks the validity of a list
 *
 * @param LIST The address of the list
 */
#define SLIST_CHECK(LIST, LINK) (                                           \
    assert((LIST) != NULL),                                                 \
                                                                            \
    ((LIST)->head == NULL || (LIST)->tail == NULL || (LIST)->len == 0)?(    \
        assert((LIST)->head == NULL),                                       \
        assert((LIST)->tail == NULL),                                       \
        assert((LIST)->len == 0)                                            \
    ):((LIST)->head == (LIST)->tail ||                                      \
       (LIST)->head->LINK == (LIST)->head ||                                \
       (LIST)->tail->LINK == (LIST)->tail ||                                \
       (LIST)->len == 1)?(                                                  \
        assert((LIST)->head == (LIST)->tail),                               \
        assert((LIST)->head->LINK == (LIST)->head),                         \
        assert((LIST)->len == 1)                                            \
    ):(                                                                     \
        SLIST_VOID                                                          \
    )                                                                       \
)


#endif
