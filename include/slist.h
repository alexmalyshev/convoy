/**
 * @file slist.h
 * @brief Header for a generic singly-linked list.
 *
 * @author Alexander Malyshev
 */

#ifndef __SLIST_H__
#define __SLIST_H__

#include <assert.h>
#include <stddef.h>

/**
 * @brief The void "value".
 *
 * Used to force macros to have a void return type.
 */
#define SLIST_VOID ((void)NULL)

/**
 * @brief Declares a new list type.
 *
 * ELEM_TYPE must be the name of a struct type with a declared link.
 *
 * Usage:
 *
 * SLIST_DECLARE(point_queue, point);
 *
 * @param LIST_TYPE The type of the list.
 * @param ELEM_TYPE The type of the list's elements.
 */
#define SLIST_DECLARE(LIST_TYPE, ELEM_TYPE)                            \
  typedef struct LIST_TYPE {                                           \
    struct ELEM_TYPE* front; /**< the first element in the list */     \
    struct ELEM_TYPE* back;  /**< the last element in the list */      \
  } LIST_TYPE

/**
 * @brief Declares a link in a struct for use with a list.
 *
 * ELEM_TYPE must be the name of a struct type.
 *
 * Usage:
 *
 * struct point {
 *   SLIST_DECLARE_LINK(point, linkname);
 *   int x;
 *   int y;
 * };
 *
 * @param ELEM_TYPE The type of the element.
 * @param LINK The name of the link field.
 */
#define SLIST_DECLARE_LINK(ELEM_TYPE, LINK) \
  struct ELEM_TYPE* LINK

/**
 * @brief Initializes a list.
 *
 * @param LIST the address of the list.
 */
#define SLIST_INIT(LIST) ( \
  assert((LIST) != NULL),  \
                           \
  (LIST)->front = NULL,    \
  (LIST)->back = NULL,     \
                           \
  SLIST_VOID               \
)

/// @brief Statically initializes a list.
#define SLIST_STATIC_INIT { \
  .front = NULL,            \
  .back = NULL,             \
}

/**
 * @brief Initializes the list link of an element.
 *
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define SLIST_ELEM_INIT(ELEM, LINK) ( \
  assert((ELEM) != NULL),             \
                                      \
  (ELEM)->LINK = NULL,                \
                                      \
  SLIST_VOID                          \
)

/// @brief Statically initializes the list link of an element.
#define SLIST_LINK_STATIC_INIT NULL

/**
 * @brief Whether a list is empty.
 *
 * @param LIST The address of the list.
 *
 * @return Whether the list is empty.
 */
#define SLIST_IS_EMPTY(LIST) ( \
  assert((LIST) != NULL),      \
                               \
  (LIST)->front == NULL        \
)

/**
 * @brief Whether a list has exactly one element.
 *
 * @param LIST The address of the list.
 *
 * @return Whether the list has exactly one element.
 */
#define SLIST_IS_SINGLE(LIST) (                          \
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
#define SLIST_IS_ELEM_INSERTED(ELEM, LINK) ( \
  assert((ELEM) != NULL),                    \
                                             \
  (ELEM)->LINK != NULL                       \
)

/**
 * @brief Returns the first element in a list.
 *
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 *
 * @return The address of the first element, NULL if the list is empty.
 */
#define SLIST_PEEK_FRONT(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->front)

/**
 * @brief Returns the last element in a list.
 *
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 *
 * @return The address of the last element, NULL if the list is empty.
 */
#define SLIST_PEEK_BACK(LIST, LINK) (SLIST_CHECK(LIST, LINK), (LIST)->back)

/**
 * @brief Pops the first element off of a list.
 *
 * Usage:
 *
 * ELEM_TYPE* var;
 * SLIST_POP_FRONT(list, var, linkname);
 *
 * @param LIST The address of the list.
 * @param DEST The location where to store the first element.
 * @param LINK The name of the link field.
 *
 * @return The address of the first element, NULL if the list is empty.
 */
#define SLIST_POP_FRONT(LIST, DEST, LINK) (                   \
  SLIST_CHECK(LIST, LINK),                                    \
                                                              \
  (SLIST_IS_EMPTY(LIST))?(                                    \
    (DEST) = NULL                                             \
  ):(SLIST_IS_SINGLE(LIST))?(                                 \
    (DEST) = (LIST)->front,                                   \
                                                              \
    (LIST)->front = NULL,                                     \
    (LIST)->back = NULL,                                      \
                                                              \
    /* Clean up the old node's link. */                       \
    (DEST)->LINK = NULL                                       \
  ):(                                                         \
    (DEST) = (LIST)->front,                                   \
                                                              \
    /* Update the new front of the list. */                   \
    (LIST)->front = (LIST)->front->LINK,                      \
                                                              \
    /* Make the back point to the new front. */               \
    (LIST)->back->LINK = (LIST)->front,                       \
                                                              \
    /* Clean up the old node's link. */                       \
    (DEST)->LINK = NULL                                       \
  ),                                                          \
                                                              \
  SLIST_VOID                                                  \
)

/**
 * @brief Pushes an element onto the front of a list.
 *
 * @param LIST The address of the list.
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define SLIST_PUSH_FRONT(LIST, ELEM, LINK) (       \
  SLIST_CHECK(LIST, LINK),                         \
  assert(!SLIST_IS_ELEM_INSERTED(ELEM, LINK)),     \
                                                   \
  /* Add the element to the front of the list. */  \
  (!SLIST_IS_EMPTY(LIST))?(                        \
    (ELEM)->LINK = (LIST)->front                   \
  ):(                                              \
    (LIST)->back = (ELEM)                          \
  ),                                               \
                                                   \
  /* Update the list's front. */                   \
  (LIST)->front = (ELEM),                          \
                                                   \
  /* Update the back to point to the new front. */ \
  (LIST)->back->LINK = (LIST)->front,              \
                                                   \
  SLIST_VOID                                       \
)

/**
 * @brief Pushes an element onto the back of a list.
 *
 * @param LIST The address of the list.
 * @param ELEM The address of the element.
 * @param LINK The name of the link field.
 */
#define SLIST_PUSH_BACK(LIST, ELEM, LINK) (        \
  SLIST_CHECK(LIST, LINK),                         \
  assert(!SLIST_IS_ELEM_INSERTED(ELEM, LINK)),     \
                                                   \
  /* Add the element to the end of the list. */    \
  (!SLIST_IS_EMPTY(LIST))?(                        \
    (LIST)->back->LINK = (ELEM)                    \
  ):(                                              \
    (LIST)->front = (ELEM)                         \
  ),                                               \
                                                   \
  /* Update the list's back. */                    \
  (LIST)->back = (ELEM),                           \
                                                   \
  /* Update the new back to point to the front. */ \
  (LIST)->back->LINK = (LIST)->front,              \
                                                   \
  SLIST_VOID                                       \
)

/**
 * @brief Iterates through all elements of a list.
 *
 * Usage:
 *
 * SLIST_FOREACH(var, list, linkname, printf("%p\n", var));
 *
 * SLIST_FOREACH(var, list, linkname, {
 *   fn(var);
 *   printf("%p\n", var);
 * });
 *
 * @param CURR The address of the current element in the iteration.
 * @param LIST The address of the list.
 * @param LINK The name of the link field.
 * @param BODY The body of the foreach loop.
 */
#define SLIST_FOREACH(CURR, LIST, LINK, BODY) { \
  (CURR) = (LIST)->front;                       \
  if ((CURR) != NULL) {                         \
    do {                                        \
      BODY;                                     \
      (CURR) = (CURR)->LINK;                    \
    } while ((CURR) != (LIST)->front);          \
  }                                             \
}

/**
 * @brief Checks the validity of a list.
 *
 * @param LIST The address of the list.
 */
#define SLIST_CHECK(LIST, LINK) (                   \
  assert((LIST) != NULL),                           \
                                                    \
  ((LIST)->front == NULL || (LIST)->back == NULL)?( \
    assert((LIST)->front == NULL),                  \
    assert((LIST)->back == NULL)                    \
  ):((LIST)->front == (LIST)->back ||               \
     (LIST)->front->LINK == (LIST)->front ||        \
     (LIST)->back->LINK == (LIST)->back)?(          \
    assert((LIST)->front == (LIST)->back),          \
    assert((LIST)->front->LINK == (LIST)->front)    \
  ):(                                               \
    SLIST_VOID                                      \
  )                                                 \
)

#endif
