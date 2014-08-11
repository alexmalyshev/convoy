/**
 * @file dlist.h
 * @brief Header for a generic doubly-linked list.
 *
 * @author Alexander Malyshev
 */

#ifndef __DLIST_H__
#define __DLIST_H__

#include <assert.h>
#include <stddef.h>

/**
 * @brief The void "value".
 *
 * Used to force macros to have a void return type.
 */
#define DLIST_VOID ((void)NULL)

/**
 * @brief Declares a new list type.
 *
 * ELEM_TYPE must be the name of a struct type with a declared link.
 *
 * Usage:
 *
 * DLIST_DECLARE(point_deque, point);
 *
 * @param LIST_TYPE The type of the list.
 * @param ELEM_TYPE The type of the list's elements.
 */
#define DLIST_DECLARE(LIST_TYPE, ELEM_TYPE)                        \
  typedef struct LIST_TYPE {                                       \
    struct ELEM_TYPE* front; /**< the first element in the list */ \
    struct ELEM_TYPE* back;  /**< the last element in the list */  \
  } LIST_TYPE

/**
 * @brief Declares a link in a struct for use with a list.
 *
 * ELEM_TYPE must be the name of a struct type.
 *
 * Usage:
 *
 * struct point {
 *   DLIST_DECLARE_LINK(point, linkname);
 *   int x;
 *   int y;
 * };
 *
 * @param ELEM_TYPE The type of the element.
 * @param LINK The name of the link field.
 */
#define DLIST_DECLARE_LINK(ELEM_TYPE, LINK) \
  struct {                                  \
    struct ELEM_TYPE* next;                 \
    struct ELEM_TYPE* prev;                 \
  } LINK

/**
 * @brief Initializes a list.
 *
 * @param LIST The address of the list.
 */
#define DLIST_INIT(LIST) ( \
  assert((LIST) != NULL),  \
                           \
  (LIST)->front = NULL,    \
  (LIST)->back = NULL,     \
                           \
  DLIST_VOID               \
)

/// @brief Statically initializes a list.
#define DLIST_STATIC_INIT { \
  .front = NULL,            \
  .back = NULL,             \
}

/**
 * @brief Initializes the list link of an element.
 *
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define DLIST_ELEM_INIT(ELEM, LINK) ( \
  assert((ELEM) != NULL),             \
                                      \
  (ELEM)->LINK.next = NULL,           \
  (ELEM)->LINK.prev = NULL,           \
                                      \
  DLIST_VOID                          \
)

/// @brief Statically initializes the list link of an element.
#define DLIST_LINK_STATIC_INIT { .next = NULL, .prev = NULL }

/**
 * @brief Whether a list if empty.
 *
 * @param LIST The address of the list.
 *
 * @return Whether the list is empty.
 */
#define DLIST_IS_EMPTY(LIST) ( \
  assert((LIST) != NULL),      \
                               \
  (LIST)->front == NULL        \
)

/**
 * @brief Whether a list has exactly one element.
 *
 * @param LIST THe address of the list.
 *
 * @return Whether the list has exactly one element.
 */
#define DLIST_IS_SINGLE(LIST) (                          \
  assert((LIST) != NULL),                                \
                                                         \
  (LIST)->front != NULL && (LIST)->front == (LIST)->back \
)

/**
 * @brief Whether an element is inserted into a list.
 *
 * Does not search any lists, runs in constant time.
 *
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 *
 * @return Whether the element is inserted into a list.
 */
#define DLIST_IS_ELEM_INSERTED(ELEM, LINK) (                  \
  DLIST_CHECK_ELEM(ELEM, LINK),                               \
                                                              \
  ((ELEM)->LINK.next != NULL) && ((ELEM)->LINK.prev != NULL)  \
)

/**
 * @brief Returns the first element in a list
 *
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 *
 * @return The address of the first element, NULL if the list is empty.
 */
#define DLIST_PEEK_FRONT(LIST, LINK) (DLIST_CHECK(LIST, LINK), (LIST)->front)

/**
 * @brief Returns the last element in a list.
 *
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 *
 * @return The address of the last element, NULL if the list is empty.
 */
#define DLIST_PEEK_BACK(LIST, LINK) (DLIST_CHECK(LIST, LINK), (LIST)->back)

/**
 * @brief Inserts an element at the front of a list.
 *
 * @param LIST The address of the list.
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define DLIST_PUSH_FRONT(LIST, ELEM, LINK) (       \
  DLIST_CHECK(LIST, LINK),                         \
  assert(!DLIST_IS_ELEM_INSERTED(ELEM, LINK)),     \
                                                   \
  (!DLIST_IS_EMPTY(LIST))?(                        \
    (LIST)->front->LINK.prev = (ELEM),             \
    (LIST)->back->LINK.next = (ELEM),              \
                                                   \
    (ELEM)->LINK.next = (LIST)->front,             \
    (ELEM)->LINK.prev = (LIST)->back               \
  ):(                                              \
    (ELEM)->LINK.next = (ELEM),                    \
    (ELEM)->LINK.prev = (ELEM),                    \
                                                   \
    (LIST)->back = (ELEM)                          \
  ),                                               \
                                                   \
  /* Point the list's front at our new element. */ \
  (LIST)->front = (ELEM),                          \
                                                   \
  DLIST_VOID                                       \
)

/**
 * @brief Inserts an element at the back of a list.
 *
 * @param LIST The address of the list.
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define DLIST_PUSH_BACK(LIST, ELEM, LINK) (       \
  DLIST_CHECK(LIST, LINK),                        \
  assert(!DLIST_IS_ELEM_INSERTED(ELEM, LINK)),    \
                                                  \
  (!DLIST_IS_EMPTY(LIST))?(                       \
    (LIST)->front->LINK.prev = (ELEM),            \
    (LIST)->back->LINK.next = (ELEM),             \
                                                  \
    (ELEM)->LINK.next = (LIST)->front,            \
    (ELEM)->LINK.prev = (LIST)->back              \
  ):(                                             \
    (ELEM)->LINK.next = (ELEM),                   \
    (ELEM)->LINK.prev = (ELEM),                   \
                                                  \
    (LIST)->front = (ELEM)                        \
  ),                                              \
                                                  \
  /* Point the list's back at our new element. */ \
  (LIST)->back = (ELEM),                          \
                                                  \
  DLIST_VOID                                      \
)

/**
 * @brief Inserts an element after an existing list element.
 *
 * @param LIST The address of the list.
 * @param INS The address of the element already in the list.
 * @param NEW The address of the new element to insert.
 * @param LINK The name of the link field.
 */
#define DLIST_INSERT_NEXT(LIST, INS, NEW, LINK) (                      \
  DLIST_CHECK(LIST, LINK),                                             \
  assert(DLIST_IS_ELEM_INSERTED(INS, LINK)),                           \
  assert(!DLIST_IS_ELEM_INSERTED(NEW, LINK)),                          \
                                                                       \
  /* List is supposed to be non-empty. */                              \
  assert(!DLIST_IS_EMPTY(LIST)),                                       \
                                                                       \
  /* Have the new element point to its new neighbors. */               \
  (NEW)->LINK.prev = (INS),                                            \
  (NEW)->LINK.next = (INS)->LINK.next,                                 \
                                                                       \
  /* Update the back of the list if we inserted after the old back. */ \
  ((INS) == (LIST)->back)?(                                            \
    (LIST)->back = (NEW)                                               \
  ):(                                                                  \
    NULL                                                               \
  ),                                                                   \
                                                                       \
  /* Splice in the new element into the list. */                       \
  (INS)->LINK.next->LINK.prev = (NEW),                                 \
  (INS)->LINK.next = (NEW),                                            \
                                                                       \
  DLIST_VOID                                                           \
)

/**
 * @brief Inserts an element before an existing list element.
 *
 * @param LIST The address of the list.
 * @param INS The address of the element already in the list.
 * @param NEW The address of the new element to insert.
 * @param LINK The name of the link field.
 */
#define DLIST_INSERT_PREV(LIST, INS, NEW, LINK) (                         \
  DLIST_CHECK(LIST, LINK),                                                \
  assert(DLIST_IS_ELEM_INSERTED(INS, LINK)),                              \
  assert(!DLIST_IS_ELEM_INSERTED(NEW, LINK)),                             \
                                                                          \
  /* List is supposed to be non-empty. */                                 \
  assert(!DLIST_IS_EMPTY(LIST)),                                          \
                                                                          \
  /* Have the new element point to its new neighbors. */                  \
  (NEW)->LINK.prev = (INS)->LINK.prev,                                    \
  (NEW)->LINK.next = (INS),                                               \
                                                                          \
  /* Update the front of the list if we inserted before the old front. */ \
  ((INS) == (LIST)->front)?(                                              \
    (LIST)->front = (NEW)                                                 \
  ):(                                                                     \
    NULL                                                                  \
  ),                                                                      \
                                                                          \
  /* splice in the new element into the list/ */                          \
  (INS)->LINK.prev->LINK.next = (NEW),                                    \
  (INS)->LINK.prev = (NEW),                                               \
                                                                          \
  DLIST_VOID                                                              \
)

/**
 * @brief Pops the first element off of a list.
 *
 * Usage:
 *
 * ELEM_TYPE* var;
 * SLIST_POP_FRONT(list, var, linkname);
 *
 * @param LIST The address of the list
 @ @param DEST The location where to store the first element.
 * @param LINK The name of the link field.
 *
 * @return The address of the first element, NULL if the list is empty.
 */
#define DLIST_POP_FRONT(LIST, DEST, LINK) (                       \
  DLIST_CHECK(LIST, LINK),                                        \
                                                                  \
  (DLIST_IS_EMPTY(LIST))?(                                        \
    (DEST) = NULL,                                                \
                                                                  \
    DLIST_VOID                                                    \
  ):(DLIST_IS_SINGLE(LIST))?(                                     \
    (DEST) = (LIST)->front,                                       \
                                                                  \
    (LIST)->front = NULL,                                         \
    (LIST)->back = NULL,                                          \
                                                                  \
    /* Clean up the old node's link. */                           \
    DLIST_ELEM_INIT(DEST, LINK)                                   \
  ):(                                                             \
    (DEST) = (LIST)->front,                                       \
                                                                  \
    /* Update the new front of the list. */                       \
    (LIST)->front = (LIST)->front->LINK.next,                     \
    (LIST)->front->LINK.prev = (LIST)->back,                      \
                                                                  \
    /* Make the back point to the new front. */                   \
    (LIST)->back->LINK.next = (LIST)->front,                      \
                                                                  \
    /* Clean up the old node's link. */                           \
    DLIST_ELEM_INIT(DEST, LINK)                                   \
  )                                                               \
)

/**
 * @brief Pops the last element off of a list.
 *
 * @param LIST The address of the list.
 * @param DEST The location where to store the last element.
 * @param LINK The name of the link field.
 *
 * @return The address of the last element, NULL if the list is empty.
 */
#define DLIST_POP_BACK(LIST, DEST, LINK) (   \
  DLIST_CHECK(LIST, LINK),                   \
                                             \
  (DLIST_IS_EMPTY(LIST))?(                   \
    (DEST) = NULL,                           \
                                             \
    DLIST_VOID                               \
  ):(DLIST_IS_SINGLE(LIST))?(                \
    (DEST) = (LIST)->front,                  \
                                             \
    /* Clean up the old node's link. */      \
    DLIST_ELEM_INIT(DEST, LINK)              \
  ):(                                        \
    (DEST) = (LIST)->back,                   \
                                             \
    /* Update the new back of the list. */   \
    (LIST)->back = (LIST)->back->LINK.prev,  \
    (LIST)->front->LINK.prev = (LIST)->back, \
    (LIST)->back->LINK.next = (LIST)->front, \
                                             \
    /* Clean up the old node's link. */      \
    DLIST_ELEM_INIT(DEST, LINK)              \
  )                                          \
)

/**
 * @brief Removes an element from a list.
 *
 * @param LIST The address of the list.
 * @param ELEM The address of the inserted element.
 * @param LINK The name of the link field.
 */
#define DLIST_REMOVE(LIST, ELEM, LINK) (                               \
  DLIST_CHECK(LIST, LINK),                                             \
  assert(DLIST_IS_ELEM_INSERTED(ELEM, LINK)),                          \
                                                                       \
  /* Cannot remove an element from an empty list. */                   \
  assert(!DIST_IS_EMPTY(LIST)),                                        \
                                                                       \
  /*
   * If we're removing the front element, then we need to update the
   * list's front reference to the next element. Otherwise we want to
   * update the next reference of the removed element's prev.
   */                                                                  \
  ((LIST)->front == (ELEM))?(                                          \
    (LIST)->front = (ELEM)->LINK.next                                  \
  ):(                                                                  \
    (ELEM)->LINK.prev->LINK.next = (ELEM)->LINK.next                   \
  ),                                                                   \
                                                                       \
  /*
   * Ditto for the back element, and the prev reference of the removed
   * element's next.
   */                                                                  \
  ((LIST)->back == (ELEM))?(                                           \
    (LIST)->back = (ELEM)->LINK.prev                                   \
  ):(                                                                  \
    (ELEM)->LINK.next->LINK.prev = (ELEM)->LINK.prev                   \
  ),                                                                   \
                                                                       \
  (DLIST_IS_SINGLE(LIST))?(                                            \
    (LIST)->front->LINK.prev = (LIST)->back,                           \
    (LIST)->back->LINK.next = (LIST)->front                            \
  ):(                                                                  \
    (LIST)->front = NULL,                                              \
    (LIST)->back = NULL                                                \
  ),                                                                   \
                                                                       \
  /* The element is no longer inserted in the list. */                 \
  DLIST_ELEM_INIT(ELEM, LINK),                                         \
                                                                       \
  DLIST_VOID                                                           \
)

/**
 * @brief Iterates through all elements of a list.
 *
 * @param CURR The address of the current element in the iteration.
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 * @param BODY The body of the foreach loop.
 */
#define DLIST_FOREACH(CURR, LIST, LINK, BODY) { \
  (CURR) = (LIST)->front;                       \
  if ((CURR) != NULL) {                         \
    do {                                        \
      BODY;                                     \
      (CURR) = (CURR)->LINK.next;               \
    } while ((CURR) != (LIST)->front);          \
  }                                             \
}

/**
 * @brief Checks the validity of a list.
 *
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 */
#define DLIST_CHECK(LIST, LINK) (                      \
  assert((LIST) != NULL),                              \
                                                       \
  ((LIST)->front == NULL || (LIST)->back == NULL)?(    \
    assert((LIST)->front == NULL),                     \
    assert((LIST)->back == NULL)                       \
  ):((LIST)->front == (LIST)->back ||                  \
     (LIST)->front->LINK.prev == (LIST)->front ||      \
     (LIST)->front->LINK.next == (LIST)->front ||      \
     (LIST)->back->LINK.prev == (LIST)->back ||        \
     (LIST)->back->LINK.next == (LIST)->back)?(        \
    assert((LIST)->front == (LIST)->back),             \
    assert((LIST)->front->LINK.prev == (LIST)->front), \
    assert((LIST)->front->LINK.next == (LIST)->front), \
    assert((LIST)->back->LINK.prev == (LIST)->back),   \
    assert((LIST)->back->LINK.next == (LIST)->back)    \
  ):(                                                  \
    DLIST_VOID                                         \
  )                                                    \
)

/**
 * @brief Checks the validity of a list element.
 *
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define DLIST_CHECK_ELEM(ELEM, LINK) (                       \
  assert((ELEM) != NULL),                                    \
                                                             \
  ((ELEM)->LINK.next == NULL || (ELEM)->LINK.prev == NULL)?( \
    assert((ELEM)->LINK.next == NULL),                       \
    assert((ELEM)->LINK.prev == NULL)                        \
  ):(                                                        \
    assert((ELEM)->LINK.next != NULL),                       \
    assert((ELEM)->LINK.prev != NULL)                        \
  )                                                          \
)

#endif
