/*
 * Implementation of a generic circular buffer.  The buffer's size is static,
 * and determined by the type produced by CIRCBUF_DECLARE().  The elements in
 * the buffer are stored in-place, and can be any size.
 */

#ifndef __CONVOY_CIRCBUF_H__
#define __CONVOY_CIRCBUF_H__

#include <stdbool.h>
#include <stddef.h>

/*
 * Used to give macros a void return value.
 */
#define CIRCBUF_VOID ((void)0)

#ifdef CIRCBUF_ASSERTS
#include <assert.h>
#define CIRCBUF_ASSERT(...) assert(__VA_ARGS__)
#else
#define CIRCBUF_ASSERT(...) CIRCBUF_VOID
#endif

/*
 * Declares a new circular buffer type.
 *
 * CBUF_TYPE is the name of the new type.  ELEM_TYPE is the type name of the
 * elements to store in the circbuf.  LIMIT is the length of the
 * circbuf (exclusive).
 */
#define CIRCBUF_DECLARE(CBUF_TYPE, ELEM_TYPE, LIMIT) \
  typedef struct CBUF_TYPE {                         \
    ELEM_TYPE elems[LIMIT];                          \
    size_t front;                                    \
    size_t back;                                     \
    size_t limit;                                    \
  } CBUF_TYPE

/*
 * Initializes a circular buffer.
 */
#define CIRCBUF_INIT(CBUF, LIMIT) \
  ((CBUF)->front = 0,             \
   (CBUF)->back = 0,              \
   (CBUF)->limit = (LIMIT),       \
                                  \
   CIRCBUF_VOID)

/*
 * Statically initializes a circular buffer.
 */
#define CIRCBUF_STATIC_INIT(LIMIT) \
  { .front = 0, .back = 0, .limit = (LIMIT) }

/*
 * Gets the first element in a circular buffer.
 *
 * If the buffer is non-empty, then this will set *DEST equal to the first
 * element of the buffer and return true, otherwise this will just return false.
 */
#define CIRCBUF_PEEK_FRONT(DEST, CBUF) \
  ((CIRCBUF_ISEMPTY(CBUF)) ? (false)   \
                           : (*(DEST) = (CBUF)->elems[(CBUF)->front], true))

/*
 * Gets the last element in a circular buffer.
 *
 * If the buffer is non-empty, then this will set *DEST equal to the last
 * element of the buffer and return true, otherwise this will just return false.
 */
#define CIRCBUF_PEEK_BACK(DEST, CBUF)                                      \
  ((CIRCBUF_ISEMPTY(CBUF))                                                 \
     ? (false)                                                             \
     : (*(DEST) = (CBUF)->elems[ROTATE_LEFT((CBUF)->back, (CBUF)->limit)], \
        true))

/*
 * Removes the first element of a circular buffer.
 *
 * Same behavior as CIRCBUF_PEEK_FRONT, except CIRCBUF_POP_FRONT also removes
 * the first element from the buffer if it exists.
 */
#define CIRCBUF_POP_FRONT(DEST, CBUF)                               \
  ((CIRCBUF_ISEMPTY(CBUF))                                          \
     ? (false)                                                      \
     : (/* Move the first element into the destination. */          \
        *(DEST) = (CBUF)->elems[(CBUF)->front],                     \
                                                                    \
        /* Rotate the first element's index over to the right. */   \
        (CBUF)->front = ROTATE_RIGHT((CBUF)->front, (CBUF)->limit), \
                                                                    \
        true))

/*
 * Removes the last element of a circular buffer.
 *
 * Same behavior as CIRCBUF_PEEK_BACK, except CIRCBUF_POP_BACK also removes
 * the last element from the buffer if it exists.
 */
#define CIRCBUF_POP_BACK(DEST, CBUF)                                       \
  ((CIRCBUF_ISEMPTY(CBUF))                                                 \
     ? (false)                                                             \
     : (/* Move the last element into the destination. */                  \
        *(DEST) = (CBUF)->elems[ROTATE_LEFT((CBUF)->back, (CBUF)->limit)], \
                                                                           \
        /* Rotate the exclusive last index over to the left. */            \
        (CBUF)->back = ROTATE_LEFT((CBUF)->back, (CBUF)->limit),           \
                                                                           \
        true))

/*
 * Inserts an element at the front of a circular buffer.
 *
 * Returns true only if the element was successfully inserted.
 */
#define CIRCBUF_PUSH_FRONT(CBUF, ELEM)                                        \
  ((CIRCBUF_ISFULL(CBUF))                                                     \
     ? (false)                                                                \
     : (/* Move the new element to the front of the circbuf. */               \
        (CBUF)->elems[ROTATE_LEFT((CBUF)->front, (CBUF)->limit)] = (ELEM),    \
                                                                              \
        /* Rotate the front index of the circular buffer over to the left. */ \
        (CBUF)->front = ROTATE_LEFT((CBUF)->front, (CBUF)->limit),            \
                                                                              \
        true))

/*
 * Inserts an element at the back of a circular buffer.
 *
 * Returns true only if the element was successfully inserted.
 */
#define CIRCBUF_PUSH_BACK(CBUF, ELEM)                                    \
  ((CIRCBUF_ISFULL(CBUF))                                                \
     ? (false)                                                           \
     : (/* Move the new element to the rear of the circbuf. */           \
        (CBUF)->elems[(CBUF)->back] = (ELEM),                            \
                                                                         \
        /* Rotate the last index of the circular buffer to the right/ */ \
        (CBUF)->back = ROTATE_RIGHT((CBUF)->back, (CBUF)->limit),        \
                                                                         \
        true))

/*
 * Checks whether a circular buffer is empty.
 */
#define CIRCBUF_ISEMPTY(CBUF)                                             \
  (CIRCBUF_CHECK(CBUF),                                                   \
                                                                          \
   /* A circbuf is empty when its front and back indices are the same. */ \
   (CBUF)->front == (CBUF)->back)

/*
 * Checks whether a circular buffer is full.
 */
#define CIRCBUF_ISFULL(CBUF)                                                   \
  (CIRCBUF_CHECK(CBUF),                                                        \
                                                                               \
   /* A circbuf is full when inserting another element would make it empty. */ \
   (CBUF)->front == ROTATE_RIGHT((CBUF)->back, (CBUF)->limit))

/*
 * Iterates through all elements of a circular buffer.
 *
 * CURR is the name of the variable to use for holding the current element in
 * the iteration, and INDEX will hold the current index.
 */
#define CIRCBUF_FOREACH(CURR, INDEX, CBUF)                      \
  for (CIRCBUF_CHECK(CBUF), (INDEX) = (CBUF)->front;            \
       (CURR) = &(CBUF)->elems[INDEX], (INDEX) != (CBUF)->back; \
       (INDEX) = ROTATE_RIGHT(INDEX, (CBUF)->limit))

/*
 * Checks the validity of a circular buffer.
 */
#define CIRCBUF_CHECK(CBUF)                           \
  (/* The limit is exclusive, so it can't be zero. */ \
   CIRCBUF_ASSERT((CBUF)->limit != 0),                \
                                                      \
   /* Check bounds of the front and back indices. */  \
   CIRCBUF_ASSERT((CBUF)->front < (CBUF)->limit),     \
   CIRCBUF_ASSERT((CBUF)->back < (CBUF)->limit))

/*
 * Subtracts one from a value, with wraparound.
 */
#define ROTATE_LEFT(VAL, LIMIT) \
  (CIRCBUF_ASSERT((LIMIT) > 0), \
                                \
   ((LIMIT) + ((VAL)-1)) % (LIMIT))

/*
 * Adds one to a value, with wraparound.
 */
#define ROTATE_RIGHT(VAL, LIMIT) \
  (CIRCBUF_ASSERT((LIMIT) > 0),  \
                                 \
   ((VAL) + 1) % (LIMIT))

#endif
