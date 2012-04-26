/** @file deque.h
 *  @brief Header for a deque (double-ended queue) data structure library
 *  @author Alexander Malyshev
 */


#ifndef __DEQUE_H__
#define __DEQUE_H__


#include <assert.h>
#include <stddef.h>


#define DEQUE_NEW(DEQ_TYPE, ELEM_TYPE)  \
    typedef struct DEQ_TYPE {           \
        struct ELEM_TYPE *head;         \
        struct ELEM_TYPE *tail;         \
        size_t len;                     \
    } DEQ_TYPE


#define DEQUE_LINK(ELEM_TYPE, LINK) \
    struct {                        \
        struct ELEM_TYPE *next;     \
        struct ELEM_TYPE *prev;     \
    } LINK


#define DEQUE_INIT(DEQ) do {    \
    assert((DEQ) != NULL);      \
                                \
    (DEQ)->head = NULL;         \
    (DEQ)->tail = NULL;         \
    (DEQ)->len = 0;             \
} while (0)


#define DEQUE_STATIC_INIT { \
    .head = NULL,           \
    .tail = NULL,           \
    .len = 0                \
}


#define DEQUE_ELEM_INIT(ELEM, LINK) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->LINK.next = NULL;               \
    (ELEM)->LINK.prev = NULL;               \
} while (0)


#define DEQUE_PEEK_HEAD(DEST, DEQ) do { \
    CHECK_DEQUE(DEQ);                   \
                                        \
    (DEST) = (DEQ)->head;               \
} while (0)


#define DEQUE_PEEK_TAIL(DEST, DEQ) do { \
    CHECK_DEQUE(DEQ);                   \
                                        \
    (DEST) = (DEQ)->tail;               \
} while (0)


#define DEQUE_PUSH_HEAD(DEQ, ELEM, LINK) do {                               \
    CHECK_DEQUE(DEQ);                                                       \
    CHECK_NEW_ELEM(ELEM, LINK);                                             \
                                                                            \
    /* the element's next points to the old head of the deque */            \
    (ELEM)->LINK.next = (DEQ)->head;                                        \
                                                                            \
    /* the old head's prev points to our new element if it exists,
     * otherwise the deque is empty and needs its tail reference updated */ \
    if ((DEQ)->head != NULL)                                                \
        (DEQ)->head->LINK.prev = (ELEM);                                    \
    else                                                                    \
        (DEQ)->tail = (ELEM);                                               \
                                                                            \
    /* point the deque's head at our new element */                         \
    (DEQ)->head = (ELEM);                                                   \
                                                                            \
    (DEQ)->len += 1;                                                        \
} while (0)


#define DEQUE_PUSH_TAIL(DEQ, ELEM, LINK) do {                               \
    CHECK_DEQUE(DEQ);                                                       \
    CHECK_NEW_ELEM(ELEM, LINK);                                             \
                                                                            \
    /* the element's prev points to the old tail of the deque */            \
    (ELEM)->LINK.prev = (DEQ)->tail;                                        \
                                                                            \
    /* the old tail's next points to our new element if it exists,
     * otherwise the deque is empty and needs its head reference updated */ \
    if ((DEQ)->tail != NULL)                                                \
        (DEQ)->tail->LINK.next = (ELEM);                                    \
    else                                                                    \
        (DEQ)->head = (ELEM);                                               \
                                                                            \
    /* point the deque's tail at our new element */                         \
    (DEQ)->tail = (ELEM);                                                   \
                                                                            \
    (DEQ)->len += 1;                                                        \
} while (0)


#define DEQUE_POP_HEAD(DEST, DEQ, LINK) do {    \
    CHECK_DEQUE(DEQ);                           \
                                                \
    if ((DEQ)->head == NULL) {                  \
        (DEST) = NULL;                          \
        break;                                  \
    }                                           \
                                                \
    (DEST) = (DEQ)->head;                       \
                                                \
    DEQUE_REMOVE(DEQ, DEST, LINK);              \
} while (0)


#define DEQUE_POP_TAIL(DEST, DEQ, LINK) do {    \
    CHECK_DEQUE(DEQ);                           \
                                                \
    if ((DEQ)->tail == NULL) {                  \
        (DEST) = NULL;                          \
        break;                                  \
    }                                           \
                                                \
    (DEST) = (DEQ)->tail;                       \
                                                \
    DEQUE_REMOVE(DEQ, DEST, LINK);              \
} while (0)


#define DEQUE_REMOVE(DEQ, ELEM, LINK) do {                  \
    CHECK_DEQUE(DEQ);                                       \
    CHECK_INSERTED_ELEM(ELEM, DEQ, LINK);                   \
                                                            \
    assert((DEQ)->len != 0);                                \
                                                            \
    if ((DEQ)->head == (ELEM))                              \
        (DEQ)->head = (ELEM)->LINK.next;                    \
    else                                                    \
        (ELEM)->LINK.prev->LINK.next = (ELEM)->LINK.next;   \
                                                            \
    if ((DEQ)->tail == (ELEM))                              \
        (DEQ)->tail = (ELEM)->LINK.prev;                    \
    else                                                    \
        (ELEM)->LINK.next->LINK.prev = (ELEM)->LINK.prev;   \
                                                            \
    (ELEM)->LINK.next = NULL;                               \
    (ELEM)->LINK.prev = NULL;                               \
                                                            \
    (DEQ)->len -= 1;                                        \
} while (0)


#define DEQUE_FOREACH(CURR, DEQ, LINK)                  \
    for (assert((DEQ) != NULL), (CURR) = (DEQ)->head;   \
         (CURR) != NULL;                                \
         (CURR) = (CURR)->LINK.next)


/** @def CHECK_DEQUE(DEQ)
 *
 *  @brief Checks the validity of a deque
 *
 *  @param DEQ the address of the deque
 */
#define CHECK_DEQUE(DEQ) do {                                               \
    /* check that we haven't gotten a NULL deque */                         \
    assert((DEQ) != NULL);                                                  \
                                                                            \
    /* and that our length makes sense with regards to our head and tail */ \
    if ((DEQ)->head == NULL || (DEQ)->tail == NULL || (DEQ)->len == 0) {    \
        assert((DEQ)->head == NULL);                                        \
        assert((DEQ)->tail == NULL);                                        \
        assert((DEQ)->len == 0);                                            \
    }                                                                       \
    if (((DEQ)->head != NULL && (DEQ)->head == (DEQ)->tail) ||              \
        (DEQ)->len == 1) {                                                  \
        assert((DEQ)->head != NULL && (DEQ)->head == (DEQ)->tail);          \
        assert((DEQ)->len == 1);                                            \
    }                                                                       \
} while (0)


/** @def CHECK_NEW_ELEM(ELEM, LINK)
 *
 *  @brief Checks the validity of a new, uninserted deque element
 *
 *  @param ELEM the address of the deque element
 *  @param LINK the name of the link field
 */
#define CHECK_NEW_ELEM(ELEM, LINK) do {                             \
    /* check that we haven't gotten a NULL element */               \
    assert((ELEM) != NULL);                                         \
                                                                    \
    /* and that our element is not already inserted into a deque */ \
    assert((ELEM)->LINK.next == NULL);                              \
    assert((ELEM)->LINK.prev == NULL);                              \
} while (0)


/** @def CHECK_INSERTED_ELEM(ELEM, DEQ, LINK)
 *
 *  @brief Checks the validity of an already-inserted deque element
 *
 *  Assumes that DEQ has already been checked for validity
 *
 *  @param ELEM the address of the deque element
 *  @param DEQ the address of the deque
 *  @param LINK the name of the link field
 */
#define CHECK_INSERTED_ELEM(ELEM, DEQ, LINK) do {                       \
    /* can't have inserted a NULL element */                            \
    assert((ELEM) != NULL);                                             \
                                                                        \
    /* element should have a valid prev reference if it is not the head,
     * otherwise its prev reference should be NULL */                   \
    if ((DEQ)->head != (ELEM))                                          \
        assert((ELEM)->LINK.prev != NULL);                              \
    else                                                                \
        assert((ELEM)->LINK.prev == NULL);                              \
                                                                        \
    /* ditto with the element's next reference and the tail */          \
    if ((DEQ)->tail != (ELEM))                                          \
        assert((ELEM)->LINK.next != NULL);                              \
    else                                                                \
        assert((ELEM)->LINK.next == NULL);                              \
} while (0)


#endif /* __DEQUE_H__ */
