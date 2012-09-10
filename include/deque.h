/**
 * @file deque.h
 * @brief Header for a deque (double-ended queue) data structure library
 *
 * @author Alexander Malyshev
 */

#ifndef __DEQUE_H__
#define __DEQUE_H__


#include <assert.h>
#include <stddef.h>


/**
 * @brief Declares a new deque type
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * @param DEQ_TYPE the type of the deque
 * @param ELEM_TYPE the type of the deque's elements
 */
#define DEQUE_NEW(DEQ_TYPE, ELEM_TYPE)  \
    typedef struct DEQ_TYPE {           \
        struct ELEM_TYPE *head;         \
        struct ELEM_TYPE *tail;         \
        size_t len;                     \
    } DEQ_TYPE

/**
 * @brief Declares a link in a struct for use with a deque
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * @param ELEM_TYPE the type of the element
 * @param LINK the name of the link field
 */
#define DEQUE_LINK(ELEM_TYPE, LINK) \
    struct {                        \
        struct ELEM_TYPE *next;     \
        struct ELEM_TYPE *prev;     \
    } LINK

/**
 * @brief Initializes a deque
 *
 * @param DEQ the address of the deque
 */
#define DEQUE_INIT(DEQ) do {    \
    assert((DEQ) != NULL);      \
                                \
    (DEQ)->head = NULL;         \
    (DEQ)->tail = NULL;         \
    (DEQ)->len = 0;             \
} while (0)

/// @brief Statically initializes a deque
#define DEQUE_STATIC_INIT { \
    .head = NULL,           \
    .tail = NULL,           \
    .len = 0                \
}

/**
 * @brief Initializes the deque link of an element
 *
 * @param ELEM the address of the deque element
 * @param LINK the name of the link field
 */
#define DEQUE_ELEM_INIT(ELEM, LINK) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->LINK.next = NULL;               \
    (ELEM)->LINK.prev = NULL;               \
} while (0)

/**
 * @brief Returns the first element in a deque
 *
 * Sets DEST to NULL if the deque is empty
 *
 * @param DEST the variable where to store the reference to the first element
 * @param DEQ the address of the deque
 */
#define DEQUE_PEEK_HEAD(DEST, DEQ) do { \
    DEQUE_CHECK(DEQ);                   \
                                        \
    (DEST) = (DEQ)->head;               \
} while (0)

/**
 * @brief Returns the last element in a deque
 *
 * Sets DEST to NULL if the deque is empty
 *
 * @param DEST the variable where to store the reference to the last element
 * @param DEQ the address of the deque
 */
#define DEQUE_PEEK_TAIL(DEST, DEQ) do { \
    DEQUE_CHECK(DEQ);                   \
                                        \
    (DEST) = (DEQ)->tail;               \
} while (0)

/**
 * @brief Inserts an element at the front of a deque
 *
 * @param DEQ the address of the deque
 * @param ELEM the address of the deque element
 * @param LINK the name of the link field
 */
#define DEQUE_PUSH_HEAD(DEQ, ELEM, LINK) do {                               \
    DEQUE_CHECK(DEQ);                                                       \
    DEQUE_CHECK_NEW_ELEM(ELEM, LINK);                                       \
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

/**
 * @brief Inserts an element at the back of a deque
 *
 * @param DEQ the address of the deque
 * @param ELEM the address of the deque element
 * @param LINK the name of the link field
 */
#define DEQUE_PUSH_TAIL(DEQ, ELEM, LINK) do {                               \
    DEQUE_CHECK(DEQ);                                                       \
    DEQUE_CHECK_NEW_ELEM(ELEM, LINK);                                       \
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

/**
 * @brief Removes the first element in a deque
 *
 * Sets DEST to NULL if the deque is empty
 *
 * @param DEST the variable where to store the reference to the first element
 * @param DEQ the address of the deque
 * @param LINK the name of the link field
 */
#define DEQUE_POP_HEAD(DEST, DEQ, LINK) do {            \
    DEQUE_CHECK(DEQ);                                   \
                                                        \
    /* return NULL if the deque is empty */             \
    if ((DEQ)->head == NULL) {                          \
        (DEST) = NULL;                                  \
        break;                                          \
    }                                                   \
                                                        \
    /* otherwise set DEST to the head of the deque */   \
    (DEST) = (DEQ)->head;                               \
                                                        \
    /* and remove it */                                 \
    DEQUE_REMOVE(DEQ, DEST, LINK);                      \
} while (0)

/**
 * @brief Removes the last element in a deque
 *
 * Sets DEST to NULL if the deque is empty
 *
 * @param DEST the variable where to store the reference to the last element
 * @param DEQ the address of the deque
 * @param LINK the name of the link field
 */
#define DEQUE_POP_TAIL(DEST, DEQ, LINK) do {            \
    DEQUE_CHECK(DEQ);                                   \
                                                        \
    /* return NULL if the deque is empty */             \
    if ((DEQ)->tail == NULL) {                          \
        (DEST) = NULL;                                  \
        break;                                          \
    }                                                   \
                                                        \
    /* otherwise set DEST to the tail of the deque */   \
    (DEST) = (DEQ)->tail;                               \
                                                        \
    /* and remove it */                                 \
    DEQUE_REMOVE(DEQ, DEST, LINK);                      \
} while (0)


/**
 * @brief Removes an element from a deque
 *
 * @param DEQ the address of the deque
 * @param ELEM the address of the inserted element
 * @param LINK the name of the link field
 */
#define DEQUE_REMOVE(DEQ, ELEM, LINK) do {                                  \
    DEQUE_CHECK(DEQ);                                                       \
    DEQUE_CHECK_INSERTED_ELEM(ELEM, DEQ, LINK);                             \
                                                                            \
    /* cannot remove an element from an empty deque */                      \
    assert((DEQ)->len != 0);                                                \
                                                                            \
    /* if we're removing the head element, then we need to update the
     * deque's head reference to the next element. otherwise we want to
     * update the next reference of the removed element's prev */           \
    if ((DEQ)->head == (ELEM))                                              \
        (DEQ)->head = (ELEM)->LINK.next;                                    \
    else                                                                    \
        (ELEM)->LINK.prev->LINK.next = (ELEM)->LINK.next;                   \
                                                                            \
    /* ditto for the tail element, and the prev reference of the removed
     * element's next */                                                    \
    if ((DEQ)->tail == (ELEM))                                              \
        (DEQ)->tail = (ELEM)->LINK.prev;                                    \
    else                                                                    \
        (ELEM)->LINK.next->LINK.prev = (ELEM)->LINK.prev;                   \
                                                                            \
    /* the element is no longer inserted in the deque */                    \
    (ELEM)->LINK.next = NULL;                                               \
    (ELEM)->LINK.prev = NULL;                                               \
                                                                            \
    (DEQ)->len -= 1;                                                        \
} while (0)

/**
 * @brief Iterates through all elements of a deque
 *
 * @param CURR the reference to the current element in one iteration
 * @param DEQ the address of the deque
 * @param LINK the name of the link field
 */
#define DEQUE_FOREACH(CURR, DEQ, LINK)                  \
    for (assert((DEQ) != NULL), (CURR) = (DEQ)->head;   \
         (CURR) != NULL;                                \
         (CURR) = (CURR)->LINK.next)

/**
 * @brief Checks the validity of a deque
 *
 * @param DEQ the address of the deque
 */
#define DEQUE_CHECK(DEQ) do {                                               \
    /* check that we haven't gotten a NULL deque */                         \
    assert((DEQ) != NULL);                                                  \
                                                                            \
    /* and that our length makes sense with regards to our head and tail */ \
    if ((DEQ)->head == NULL || (DEQ)->tail == NULL || (DEQ)->len == 0) {    \
        assert((DEQ)->head == NULL);                                        \
        assert((DEQ)->tail == NULL);                                        \
        assert((DEQ)->len == 0);                                            \
    }                                                                       \
    else if ((DEQ)->head == (DEQ)->tail || (DEQ)->len == 1) {               \
        assert((DEQ)->head != NULL && (DEQ)->head == (DEQ)->tail);          \
        assert((DEQ)->len == 1);                                            \
    }                                                                       \
} while (0)

/**
 * @brief Checks the validity of a new, uninserted deque element
 *
 * @param ELEM the address of the deque element
 * @param LINK the name of the link field
 */
#define DEQUE_CHECK_NEW_ELEM(ELEM, LINK) do {                       \
    /* check that we haven't gotten a NULL element */               \
    assert((ELEM) != NULL);                                         \
                                                                    \
    /* and that our element is not already inserted into a deque */ \
    assert((ELEM)->LINK.next == NULL);                              \
    assert((ELEM)->LINK.prev == NULL);                              \
} while (0)

/**
 * @brief Checks the validity of an already-inserted deque element
 *
 * Assumes that DEQ has already been checked for validity
 *
 * @param ELEM the address of the deque element
 * @param DEQ the address of the deque
 * @param LINK the name of the link field
 */
#define DEQUE_CHECK_INSERTED_ELEM(ELEM, DEQ, LINK) do {                 \
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


#endif // __DEQUE_H__
