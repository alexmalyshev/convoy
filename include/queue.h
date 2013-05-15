/**
 * @file queue.h
 * @brief Header for a queue data structure
 *
 * @author Alexander Malyshev
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <assert.h>
#include <stddef.h>


/**
 * @brief Declares a new queue type
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * @param QU_TYPE the type of the queue
 * @param ELEM_TYPE the type of the queue's elements
 */
#define QUEUE_NEW(QU_TYPE, ELEM_TYPE)   \
    typedef struct QU_TYPE {            \
        struct ELEM_TYPE *head;         \
        struct ELEM_TYPE *tail;         \
        size_t len;                     \
    } QU_TYPE

/**
 * @brief Declares a link in a struct for use with a queue
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * @param ELEM_TYPE the type of the element
 * @param NEXT the name of the link field
 */
#define QUEUE_LINK(ELEM_TYPE, NEXT) \
    struct ELEM_TYPE *NEXT

/**
 * @brief Initializes a queue
 *
 * @param QU the address of the queue
 */
#define QUEUE_INIT(QU) do { \
    assert((QU) != NULL);   \
                            \
    (QU)->head = NULL;      \
    (QU)->tail = NULL;      \
    (QU)->len = 0;          \
} while (0)

/// @brief Statically initializes a queue
#define QUEUE_STATIC_INIT { \
    .head = NULL,           \
    .tail = NULL,           \
    .len = 0                \
}

/**
 * @brief Initializes the queue link of an element
 *
 * @param ELEM the address of the queue element
 * @param NEXT the name of the link field
 */
#define QUEUE_ELEM_INIT(ELEM, NEXT) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->NEXT = NULL;                    \
} while (0)

/**
 * @brief Dequeues the first element of a queue
 *
 * Sets DEST to NULL if the queue is empty
 *
 * @param DEST the variable where to store the reference to the first element
 * @param QU the address of the queue
 * @param NEXT the name of the link field
 */
#define QUEUE_DEQUEUE(DEST, QU, NEXT) do {                          \
    QUEUE_CHECK(QU);                                                \
                                                                    \
    /* return NULL if the queue is empty */                         \
    if ((QU)->len == 0) {                                           \
        (DEST) = NULL;                                              \
        break;                                                      \
    }                                                               \
                                                                    \
    /* otherwise move the first element into the destination */     \
    (DEST) = (QU)->head;                                            \
                                                                    \
    /* move the head reference down */                              \
    (QU)->head = (QU)->head->NEXT;                                  \
                                                                    \
    /* if the queue is now empty, also empty the tail reference */  \
    if ((QU)->head == NULL)                                         \
        (QU)->tail = NULL;                                          \
                                                                    \
    /* clear out the old head's next reference */                   \
    (DEST)->NEXT = NULL;                                            \
                                                                    \
    (QU)->len -= 1;                                                 \
} while (0)

/**
 * @brief Enqueues an element onto a queue
 *
 * @param QU the address of the queue
 * @param ELEM the address of the queue element
 * @param NEXT the name of the link field
 */
#define QUEUE_ENQUEUE(QU, ELEM, NEXT) do {          \
    QUEUE_CHECK(QU);                                \
    QUEUE_CHECK_NEW_ELEM(ELEM, NEXT);               \
                                                    \
    /* add the element to the end of the queue */   \
    if ((QU)->len != 0)                             \
        (QU)->tail->NEXT = (ELEM);                  \
    else                                            \
        (QU)->head = (ELEM);                        \
                                                    \
    /* update the tail reference in the queue */    \
    (QU)->tail = (ELEM);                            \
                                                    \
    (QU)->len += 1;                                 \
} while (0)

/**
 * @brief Returns the first element in a queue
 *
 * @param QU the address of the queue
 */
#define QUEUE_PEEK(QU) (    \
    assert((QU) != NULL),   \
                            \
    (QU)->head              \
)

/**
 * @brief Iterates through all elements of a queue
 *
 * @param CURR the reference to the current element in one iteration
 * @param QU the address of the queue
 * @param NEXT the name of the link field
 */
#define QUEUE_FOREACH(CURR, QU, NEXT)               \
    for (assert((QU) != NULL), (CURR) = (QU)->head; \
         (CURR) != NULL;                            \
         (CURR) = (CURR)->NEXT)

/**
 * @brief Checks the validity of a queue
 *
 * @param QU the address of the queue
 */
#define QUEUE_CHECK(QU) do {                                                \
    /* check that we haven't gotten a NULL queue */                         \
    assert((QU) != NULL);                                                   \
                                                                            \
    /* and that our length makes sense with regards to our head and tail */ \
    if ((QU)->head == NULL || (QU)->tail == NULL || (QU)->len == 0) {       \
        assert((QU)->head == NULL);                                         \
        assert((QU)->tail == NULL);                                         \
        assert((QU)->len == 0);                                             \
    }                                                                       \
    else if ((QU)->head == (QU)->tail || (QU)->len == 1) {                  \
        assert((QU)->head == (QU)->tail);                                   \
        assert((QU)->len == 1);                                             \
    }                                                                       \
} while (0)

/**
 * @brief Checks the validity of a new, uninserted element
 *
 * @param ELEM the address of the queue element
 * @param NEXT the name of the link field
 */
#define QUEUE_CHECK_NEW_ELEM(ELEM, NEXT) do {               \
    /* check that we haven't gotten a NULL element */       \
    assert((ELEM) != NULL);                                 \
                                                            \
    /* and that it isn't inserted into a queue already */   \
    assert((ELEM)->NEXT == NULL);                           \
} while (0)


#endif
