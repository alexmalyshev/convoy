#ifndef __CONVOY_SLIST_H__
#define __CONVOY_SLIST_H__

/*
 * Used to give macros a void return value.
 */
#define SLIST_VOID ((void)0)

#ifdef SLIST_ASSERTS
#include <assert.h>
#define SLIST_ASSERT(...) assert(__VA_ARGS__)
#else
#define SLIST_ASSERT(...) SLIST_VOID
#endif

#include <stddef.h>

/*
 * Declares a new list type.
 *
 * ELEM_TYPE must be the name of a struct type with a declared link.
 *
 * Usage:
 *
 *   struct point { ... };
 *   SLIST_DECLARE(point_queue, point);
 */
#define SLIST_DECLARE(LIST_TYPE, ELEM_TYPE) \
  typedef struct LIST_TYPE {                \
    struct ELEM_TYPE* front;                \
    struct ELEM_TYPE* back;                 \
  } LIST_TYPE

/*
 * Declares a link in a struct for use with a list.
 *
 * ELEM_TYPE must be the name of a struct type.
 *
 * Usage:
 *
 *   struct point {
 *     SLIST_DECLARE_LINK(point, linkname);
 *     int x;
 *     int y;
 *   };
 */
#define SLIST_DECLARE_LINK(ELEM_TYPE, LINK) struct ELEM_TYPE* LINK

/*
 * Initializes a list.
 */
#define SLIST_INIT(LIST) \
  ((LIST)->front = NULL, \
   (LIST)->back = NULL,  \
                         \
   SLIST_VOID)

/*
 * Statically initializes a list.
 */
#define SLIST_STATIC_INIT \
  { .front = NULL, .back = NULL, }

/*
 * Initializes the list link of an element.
 */
#define SLIST_ELEM_INIT(ELEM, LINK) \
  ((ELEM)->LINK = NULL,             \
                                    \
   SLIST_VOID)

/*
 * Statically initializes the list link of an element.
 */
#define SLIST_LINK_STATIC_INIT NULL

/*
 * Checks whether a list is empty.
 */
#define SLIST_IS_EMPTY(LIST) ((LIST)->front == NULL)

/*
 * Checks whether a list has exactly one element.
 */
#define SLIST_IS_SINGLE(LIST) \
  ((LIST)->front != NULL && (LIST)->front == (LIST)->back)

/*
 * Checks if an element is inserted into an list.
 *
 * Does not search any lists, runs in constant time.
 */
#define SLIST_IS_ELEM_INSERTED(ELEM, LINK) ((ELEM)->LINK != NULL)

/*
 * Gets the first element in a list.  Returns NULL if the list is empty.
 *
 * Usage:
 *
 *   ELEM_TYPE* var = SLIST_PEEK_FRONT(list, linkname);
 */
#define SLIST_PEEK_FRONT(LIST, LINK) \
  (SLIST_CHECK(LIST, LINK),          \
                                     \
   (LIST)->front)

/*
 * Gets the last element in a list.  Returns NULL if the list is empty.
 *
 * Usage:
 *
 *   ELEM_TYPE* var = SLIST_PEEK_BACK(list, linkname);
 */
#define SLIST_PEEK_BACK(LIST, LINK) \
  (SLIST_CHECK(LIST, LINK),         \
                                    \
   (LIST)->back)

/*
 * Pops the first element off of a list.
 *
 * Usage:
 *
 *   ELEM_TYPE* var;
 *   SLIST_POP_FRONT(list, var, linkname);
 */
#define SLIST_POP_FRONT(LIST, DEST, LINK)                                     \
  (SLIST_CHECK(LIST, LINK),                                                   \
                                                                              \
   (SLIST_IS_EMPTY(LIST))                                                     \
     ? ((DEST) = NULL,                                                        \
                                                                              \
        SLIST_VOID)                                                           \
     : (SLIST_IS_SINGLE(LIST)) ? ((DEST) = (LIST)->front,                     \
                                                                              \
                                  (LIST)->front = NULL,                       \
                                  (LIST)->back = NULL,                        \
                                                                              \
                                  /* Clean up the old node's link. */         \
                                  SLIST_ELEM_INIT(DEST, LINK))                \
                               : ((DEST) = (LIST)->front,                     \
                                                                              \
                                  /* Update the new front of the list. */     \
                                  (LIST)->front = (LIST)->front->LINK,        \
                                                                              \
                                  /* Make the back point to the new front. */ \
                                  (LIST)->back->LINK = (LIST)->front,         \
                                                                              \
                                  /* Clean up the old node's link. */         \
                                  SLIST_ELEM_INIT(DEST, LINK)))

/*
 * Pushes an element onto the front of a list.
 *
 * Usage:
 *
 *   ELEM_TYPE* var = ...;
 *   SLIST_PUSH_FRONT(list, var, linkname);
 */
#define SLIST_PUSH_FRONT(LIST, ELEM, LINK)                  \
  (SLIST_CHECK(LIST, LINK),                                 \
   SLIST_ASSERT(!SLIST_IS_ELEM_INSERTED(ELEM, LINK)),       \
                                                            \
   /* Add the element to the front of the list. */          \
   (!SLIST_IS_EMPTY(LIST)) ? ((ELEM)->LINK = (LIST)->front) \
                           : ((LIST)->back = (ELEM)),       \
                                                            \
   /* Update the list's front. */                           \
   (LIST)->front = (ELEM),                                  \
                                                            \
   /* Update the back to point to the new front. */         \
   (LIST)->back->LINK = (LIST)->front,                      \
                                                            \
   SLIST_VOID)

/*
 * Pushes an element onto the back of a list.
 *
 * Usage:
 *
 *   ELEM_TYPE* var = ...;
 *   SLIST_PUSH_BACK(list, var, linkname);
 */
#define SLIST_PUSH_BACK(LIST, ELEM, LINK)                  \
  (SLIST_CHECK(LIST, LINK),                                \
   SLIST_ASSERT(!SLIST_IS_ELEM_INSERTED(ELEM, LINK)),      \
                                                           \
   /* Add the element to the end of the list. */           \
   (!SLIST_IS_EMPTY(LIST)) ? ((LIST)->back->LINK = (ELEM)) \
                           : ((LIST)->front = (ELEM)),     \
                                                           \
   /* Update the list's back. */                           \
   (LIST)->back = (ELEM),                                  \
                                                           \
   /* Update the new back to point to the front. */        \
   (LIST)->back->LINK = (LIST)->front,                     \
                                                           \
   SLIST_VOID)

/*
 * Iterates through all elements of a list.
 *
 * Usage:
 *
 *   SLIST_FOREACH(var, list, linkname, printf("%p\n", var));
 *
 *   SLIST_FOREACH(var, list, linkname, {
 *     fn(var);
 *     printf("%p\n", var);
 *   });
 */
#define SLIST_FOREACH(CURR, LIST, LINK, BODY) \
  {                                           \
    (CURR) = (LIST)->front;                   \
    if ((CURR) != NULL) {                     \
      do {                                    \
        BODY;                                 \
        (CURR) = (CURR)->LINK;                \
      } while ((CURR) != (LIST)->front);      \
    }                                         \
  }

/*
 * Checks the validity of a list.
 */
#define SLIST_CHECK(LIST, LINK)                               \
  (((LIST)->front == NULL || (LIST)->back == NULL)            \
     ? (SLIST_ASSERT((LIST)->front == NULL),                  \
        SLIST_ASSERT((LIST)->back == NULL))                   \
     : ((LIST)->front == (LIST)->back ||                      \
        (LIST)->front->LINK == (LIST)->front ||               \
        (LIST)->back->LINK == (LIST)->back)                   \
       ? (SLIST_ASSERT((LIST)->front == (LIST)->back),        \
          SLIST_ASSERT((LIST)->front->LINK == (LIST)->front)) \
       : (SLIST_VOID))

#endif
