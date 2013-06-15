/**
 * @file circbuf.h
 * @brief Header for a circular buffer data structure
 *
 * @author Alexander Malyshev
 */

#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


/**
 * @brief Declares a new circular buffer type
 *
 * @param CBUF_TYPE the type of the circbuf
 * @param ELEM_TYPE the type of the circbuf's elements
 * @param LIMIT the length of the circbuf (exclusive)
 */
#define CIRCBUF_DECLARE(CBUF_TYPE, ELEM_TYPE, LIMIT)    \
    typedef struct CBUF_TYPE {                          \
        ELEM_TYPE elems[LIMIT];                         \
        size_t head;                                    \
        size_t tail;                                    \
        size_t limit;                                   \
    } CBUF_TYPE

/**
 * @brief Initializes a circular buffer
 *
 * @param CBUF the address of the circbuf
 * @param LIMIT the length of the circbuf (exclusive)
 */
#define CIRCBUF_INIT(CBUF, LIMIT) do {  \
    assert((CBUF) != NULL);             \
                                        \
    (CBUF)->head = 0;                   \
    (CBUF)->tail = 0;                   \
                                        \
    (CBUF)->limit = (LIMIT);            \
} while (0)

/**
 * @brief Statically initializes a circular buffer
 *
 * @param LIMIT the length of the circbuf (exclusive)
 */
#define CIRCBUF_STATIC_INIT(LIMIT) {    \
    .head = 0,                          \
    .tail = 0,                          \
    .limit = (LIMIT)                    \
}

/**
 * @brief Returns the first element in a circular buffer
 *
 * If the buffer is non-empty, then this will set *DEST equal to the first
 * element of the buffer and return true, otherwise just return false.
 *
 * @param DEST the address where to store the first element, if it exists
 * @param CBUF the address of the circbuf
 * @return Whether the first element was stored in DEST
 */
#define CIRCBUF_PEEK_HEAD(DEST, CBUF) (         \
    (CIRCBUF_ISEMPTY(CBUF))?(                   \
        false                                   \
    ):(                                         \
        *(DEST) = (CBUF)->elems[(CBUF)->head],  \
        true                                    \
    )                                           \
)

/**
 * @brief Returns the last element in a circular buffer
 *
 * If the buffer is non-empty, then this will set *DEST equal to the last
 * element of the buffer and return true, otherwise just return false.
 *
 * @param DEST the address where to store the last element, if it exists
 * @param CBUF the address of the circbuf
 */
#define CIRCBUF_PEEK_TAIL(DEST, CBUF) (                                     \
    (CIRCBUF_ISEMPTY(CBUF))?(                                               \
        false                                                               \
    ):(                                                                     \
        (DEST) = (CBUF)->elems[ROTATE_LEFT((CBUF)->tail, (CBUF)->limit)],   \
        true                                                                \
    )                                                                       \
)

/**
 * @brief Removes the first element of a circular buffer
 *
 * Same behavior as CIRCBUF_PEEK_HEAD, except CIRCBUF_POP_HEAD also removes
 * the first element from the buffer if it exists
 *
 * @param DEST the address where to store the first element, if it exists
 * @param CBUF the address of the circbuf
 */
#define CIRCBUF_POP_HEAD(DEST, CBUF) (                              \
    (CIRCBUF_ISEMPTY(CBUF))?(                                       \
        false                                                       \
    ):(                                                             \
        /* move the first element into the destination */           \
        *(DEST) = (CBUF)->elems[(CBUF)->head],                      \
                                                                    \
        /* rotate the first element's index over to the right */    \
        (CBUF)->head = ROTATE_RIGHT((CBUF)->head, (CBUF)->limit),   \
                                                                    \
        true                                                        \
    )                                                               \
)

/**
 * @brief Removes the last element of a circular buffer
 *
 * Same behavior as CIRCBUF_PEEK_TAIL, except CIRCBUF_POP_TAIL also removes
 * the last element from the buffer if it exists
 *
 * @param DEST the address where to store the first element, if it exists
 * @param CBUF the address of the circbuf
 */
#define CIRCBUF_POP_TAIL(DEST, CBUF) (                                      \
    (CIRCBUF_ISEMPTY(CBUF))?(                                               \
        false                                                               \
    ):(                                                                     \
        /* move the last element into the destination */                    \
        *(DEST) = (CBUF)->elems[ROTATE_LEFT((CBUF)->tail, (CBUF)->limit)],  \
                                                                            \
        /* rotate the exclusive last index over to the left */              \
        (CBUF)->tail = ROTATE_LEFT((CBUF)->tail, (CBUF)->limit),            \
                                                                            \
        true                                                                \
    )                                                                       \
)

/**
 * @brief Inserts an element at the front of a circular buffer
 *
 * @param CBUF the address of the circular buffer
 * @param ELEM the element
 * @return True iff an element was inserted
 */
#define CIRCBUF_PUSH_HEAD(CBUF, ELEM) (                                         \
    (CIRCBUF_ISFULL(CBUF))?(                                                    \
        false                                                                   \
    ):(                                                                         \
        /* move the new element to the front of the circbuf */                  \
        (CBUF)->elems[ROTATE_LEFT((CBUF)->head, (CBUF)->limit)] = (ELEM),       \
                                                                                \
        /* rotate the front index of the circular buffer over to the left */    \
        (CBUF)->head = ROTATE_LEFT((CBUF)->head, (CBUF)->limit),                \
                                                                                \
        true                                                                    \
    )                                                                           \
)

/**
 * @brief Inserts an element at the back of a circular buffer
 *
 * @param CBUF the address of the circular buffer
 * @param ELEM the element
 * @return True iff an element was inserted
 */
#define CIRCBUF_PUSH_TAIL(CBUF, ELEM) (                                 \
    (CIRCBUF_ISFULL(CBUF))?(                                            \
        false                                                           \
    ):(                                                                 \
        /* move the new element to the rear of the circbuf */           \
        (CBUF)->elems[(CBUF)->tail] = (ELEM),                           \
                                                                        \
        /* rotate the last index of the circular buffer to the right */ \
        (CBUF)->tail = ROTATE_RIGHT((CBUF)->tail, (CBUF)->limit),       \
                                                                        \
        true                                                            \
    )                                                                   \
)

/**
 * @brief Returns whether a circular buffer is empty
 *
 * @param CBUF the address of the circbuf
 *
 * @return Whether a circbuf is empty
 */
#define CIRCBUF_ISEMPTY(CBUF) (                                             \
    CIRCBUF_CHECK(CBUF),                                                    \
                                                                            \
    /* a circbuf is empty when its head and tail indices are the same */    \
    (CBUF)->head == (CBUF)->tail                                            \
)

/**
 * @brief Returns whether a circular buffer is full
 *
 * @param CBUF the address of the circbuf
 *
 * @return Whether a circbuf is full
 */
#define CIRCBUF_ISFULL(CBUF) (                                  \
    CIRCBUF_CHECK(CBUF),                                        \
                                                                \
    /* a circbuf is full when inserting another element
     * would make it "empty" */                                 \
    (CBUF)->head == ROTATE_RIGHT((CBUF)->tail, (CBUF)->limit)   \
)

/**
 * @brief Iterates through all elements of a circular buffer
 *
 * @param CURR the current element in one iteration
 * @param INDEX the index of the current element
 * @param CBUF the address of the circbuf
 */
#define CIRCBUF_FOREACH(CURR, INDEX, CBUF)                          \
    for (CIRCBUF_CHECK(CBUF), (INDEX) = (CBUF)->head;               \
         (CURR) = &(CBUF)->elems[INDEX], (INDEX) != (CBUF)->tail;   \
         (INDEX) = ROTATE_RIGHT(INDEX, (CBUF)->limit))

/**
 * @brief Checks the validity of a circular buffer
 *
 * @param CBUF the address of the circbuf
 */
#define CIRCBUF_CHECK(CBUF) (                                           \
    /* checks that we haven't gotten a NULL circbuf */                  \
    assert((CBUF) != NULL),                                             \
                                                                        \
    /* that it does not have an exclusive limit of zero elements */     \
    assert((CBUF)->limit != 0),                                         \
                                                                        \
    /* and that its head and tail indices are within its bounds */      \
    assert((CBUF)->head < (CBUF)->limit),                               \
    assert((CBUF)->tail < (CBUF)->limit)                                \
)

/**
 * @brief Subtracts one from a value, with wraparound
 *
 * @param VAL the value to rotate
 * @param LIMIT the value to wrap around (exclusive)
 *
 * @return The previous value, accounting for wraparound
 */
#define ROTATE_LEFT(VAL, LIMIT) (                           \
    /* can't have exclusive limits that are zero or less */ \
    assert((LIMIT) > 0),                                    \
                                                            \
    ((LIMIT) + ((VAL) - 1)) % (LIMIT)                       \
)

/**
 * @brief Adds one to a value, with wraparound
 *
 * @param VAL the value to rotate
 * @param LIMIT the value to wrap around (exclusive)
 *
 * @return The next value, accounting for wraparound
 */
#define ROTATE_RIGHT(VAL, LIMIT) (                          \
    /* can't have exclusive limits that are zero or less */ \
    assert((LIMIT) > 0),                                    \
                                                            \
    ((VAL) + 1) % (LIMIT)                                   \
)


#endif
