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
    (LIST)->front = NULL,   \
    (LIST)->back = NULL,    \
    (LIST)->temp = NULL,    \
    (LIST)->len = 0,        \
                            \
    SLIST_VOID              \
)

/// @brief Statically initializes a list
#define SLIST_STATIC_INIT { \
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
#define SLIST_LEN(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->len)

/**
 * @brief Returns true iff an element is inserted into a list
 *
 * Does not search any lists
 *
 * @param ELEM The address of the element
 * @param LINK The name of the link field
 * @return True iff the element is inserted into a list
 */
#define SLIST_IS_ELEM_INSERTED(ELEM, LINK) (    \
    assert((ELEM) != NULL),                     \
                                                \
    (ELEM)->LINK != NULL                        \
)

/**
 * @brief Returns the first element in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the first element, NULL if the list is empty
 */
#define SLIST_PEEK_FRONT(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->front)

/**
 * @brief Returns the last element in a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the last element, NULL if the list is empty
 */
#define SLIST_PEEK_BACK(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->back)

/**
 * @brief Pops the first element off of a list
 *
 * @param LIST The address of the list
 * @param LINK The name of the link field
 * @return The address of the first element, NULL if the list is empty
 */
#define SLIST_POP_FRONT(LIST, LINK) (                               \
    SLIST_CHECK(LIST, LINK),                                        \
                                                                    \
    ((LIST)->len == 0)?(                                            \
        (LIST)->temp = NULL                                         \
    ):((LIST)->len == 1)?(                                          \
        (LIST)->temp = (LIST)->front,                               \
                                                                    \
        (LIST)->front = NULL,                                       \
        (LIST)->back = NULL                                         \
    ):(                                                             \
        (LIST)->temp = (LIST)->front,                               \
                                                                    \
        /* update the new front of the list */                      \
        (LIST)->front = (LIST)->front->LINK,                        \
                                                                    \
        /* make the back point to the new front */                  \
        (LIST)->back->LINK = (LIST)->front                          \
    ),                                                              \
                                                                    \
    ((LIST)->temp == NULL)?(                                        \
        NULL                                                        \
    ):(                                                             \
        /* mark the old front as not being inserted in a list */    \
        (LIST)->temp->LINK = NULL,                                  \
                                                                    \
        /* update the list's length, and return the old front */    \
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
#define SLIST_PUSH_FRONT(LIST, ELEM, LINK) (        \
    SLIST_CHECK(LIST, LINK),                        \
    assert(!SLIST_IS_ELEM_INSERTED(ELEM, LINK)),    \
                                                    \
    /* add the element to the front of the list */  \
    ((LIST)->len != 0)?(                            \
        (ELEM)->LINK = (LIST)->front                \
    ):(                                             \
        (LIST)->back = (ELEM)                       \
    ),                                              \
                                                    \
    /* update the list's front and length */        \
    (LIST)->front = (ELEM),                         \
    (LIST)->len += 1,                               \
                                                    \
    /* update the back to point to the new front */ \
    (LIST)->back->LINK = (LIST)->front,             \
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
#define SLIST_PUSH_BACK(LIST, ELEM, LINK) (         \
    SLIST_CHECK(LIST, LINK),                        \
    assert(!SLIST_IS_ELEM_INSERTED(ELEM, LINK)),    \
                                                    \
    /* add the element to the end of the list */    \
    ((LIST)->len != 0)?(                            \
        (LIST)->back->LINK = (ELEM)                 \
    ):(                                             \
        (LIST)->front = (ELEM)                      \
    ),                                              \
                                                    \
    /* update the list's back and length */         \
    (LIST)->back = (ELEM),                          \
    (LIST)->len += 1,                               \
                                                    \
    /* update the new back to point to the front */ \
    (LIST)->back->LINK = (LIST)->front,             \
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
#define SLIST_FOREACH(CURR, LIST, LINK)                                       \
    for ((CURR) = (LIST)->front, (LIST)->temp = (LIST)->front;                \
         (CURR) != NULL && ((CURR) != (LIST)->front || (LIST)->temp != NULL); \
         (LIST)->temp = NULL, (CURR) = (CURR)->LINK)

/**
 * @brief Checks the validity of a list
 *
 * @param LIST The address of the list
 */
#define SLIST_CHECK(LIST, LINK) (                                           \
    assert((LIST) != NULL),                                                 \
                                                                            \
    ((LIST)->front == NULL || (LIST)->back == NULL || (LIST)->len == 0)?(   \
        assert((LIST)->front == NULL),                                      \
        assert((LIST)->back == NULL),                                       \
        assert((LIST)->len == 0)                                            \
    ):((LIST)->front == (LIST)->back ||                                     \
       (LIST)->front->LINK == (LIST)->front ||                              \
       (LIST)->back->LINK == (LIST)->back ||                                \
       (LIST)->len == 1)?(                                                  \
        assert((LIST)->front == (LIST)->back),                              \
        assert((LIST)->front->LINK == (LIST)->front),                       \
        assert((LIST)->len == 1)                                            \
    ):(                                                                     \
        SLIST_VOID                                                          \
    )                                                                       \
)


#endif
