/** @file queue.h
 *  @brief Header for a queue data structure library.
 *  @author Alexander Malyshev
 */


#ifndef __QUEUE_H__
#define __QUEUE_H__


#include <assert.h>
#include <stddef.h>


#define QUEUE_NEW(QU_TYPE, ELEM_TYPE)   \
    typedef struct QU_TYPE {            \
        struct ELEM_TYPE *head;         \
        struct ELEM_TYPE *tail;         \
        size_t len;                     \
    } QU_TYPE


#define QUEUE_LINK(ELEM_TYPE, NEXT) \
    struct ELEM_TYPE *NEXT


#define QUEUE_INIT(QU) do { \
    assert((QU) != NULL);   \
                            \
    (QU)->head = NULL;      \
    (QU)->tail = NULL;      \
    (QU)->len = 0;          \
} while (0)


#define QUEUE_STATIC_INIT { \
    .head = NULL,           \
    .tail = NULL,           \
    .len = 0                \
}


#define QUEUE_ELEM_INIT(ELEM, NEXT) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->NEXT = NULL;                    \
} while (0)


#define QUEUE_DEQUEUE(DEST, QU, NEXT) do {                          \
    CHECK_QUEUE(QU);                                                \
                                                                    \
    /* return NULL if the queue is empty */                         \
    if ((QU)->len == 0) {                                           \
        (DEST) = NULL;                                              \
        break;                                                      \
    }                                                               \
                                                                    \
    /* otherwise move the front element into the destination */     \
    (DEST) = (QU)->head;                                            \
                                                                    \
    /* move the front element down */                               \
    (QU)->head = (QU)->head->NEXT;                                  \
                                                                    \
    /* if the queue is now empty, also empty the tail reference */  \
    if ((QU)->head == NULL)                                         \
        (QU)->tail = NULL;                                          \
                                                                    \
    /* clear out the old front element's next reference */          \
    (DEST)->NEXT = NULL;                                            \
                                                                    \
    (QU)->len -= 1;                                                 \
} while (0)


#define QUEUE_ENQUEUE(QU, ELEM, NEXT) do {                              \
    CHECK_QUEUE(QU);                                                    \
    assert((ELEM) != NULL);                                             \
    assert((ELEM)->NEXT == NULL);                                       \
                                                                        \
    /* add the element to the end of the queue */                       \
    if ((QU)->len != 0)                                                 \
        (QU)->tail->NEXT = (ELEM);                                      \
    else                                                                \
        (QU)->head = (ELEM);                                            \
                                                                        \
    /* update the tail reference in the queue */                        \
    (QU)->tail = (ELEM);                                                \
                                                                        \
    (QU)->len += 1;                                                     \
} while (0)


#define QUEUE_PEEK(DEST, QU) do {   \
    CHECK_QUEUE(QU);                \
                                    \
    (DEST) = (QU)->head;            \
} while (0)


#define CHECK_QUEUE(QU) do {                                                \
    /* check that we haven't gotten a NULL queue */                         \
    assert((QU) != NULL);                                                   \
                                                                            \
    /* and that our length makes sense with regards to our head and tail */ \
    if ((QU)->head == NULL || (QU)->tail == NULL || (QU)->len == 0) {       \
        assert((QU)->head == NULL);                                         \
        assert((QU)->tail == NULL);                                         \
        assert((QU)->len == 0);                                             \
    }                                                                       \
} while (0)


#endif /* __QUEUE_H__ */
