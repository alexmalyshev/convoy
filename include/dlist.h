#ifndef __CONVOY_DLIST_H__
#define __CONVOY_DLIST_H__

/*
 * Used to give macros a void return value.
 */
#define DLIST_VOID ((void)NULL)

#ifdef DLIST_ASSERTS
#include <assert.h>
#define DLIST_ASSERT(...) assert(__VA_ARGS__)
#else
#define DLIST_ASSERT(...) DLIST_VOID
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
 *   DLIST_DECLARE(point_deque, point);
 */
#define DLIST_DECLARE(LIST_TYPE, ELEM_TYPE) \
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
 *     DLIST_DECLARE_LINK(point, linkname);
 *     int x;
 *     int y;
 *   };
 */
#define DLIST_DECLARE_LINK(ELEM_TYPE, LINK) \
  struct {                                  \
    struct ELEM_TYPE* next;                 \
    struct ELEM_TYPE* prev;                 \
  } LINK

/*
 * Initializes a list.
 */
#define DLIST_INIT(LIST) \
  ((LIST)->front = NULL, \
   (LIST)->back = NULL,  \
                         \
   DLIST_VOID)

/*
 * Statically initializes a list.
 */
#define DLIST_STATIC_INIT \
  { .front = NULL, .back = NULL, }

/*
 * Initializes the list link of an element.
 */
#define DLIST_ELEM_INIT(ELEM, LINK) \
  ((ELEM)->LINK.next = NULL,        \
   (ELEM)->LINK.prev = NULL,        \
                                    \
   DLIST_VOID)

/*
 * Statically initializes the list link of an element.
 */
#define DLIST_LINK_STATIC_INIT \
  { .next = NULL, .prev = NULL }

/*
 * Checks if a list is empty.
 */
#define DLIST_IS_EMPTY(LIST) ((LIST)->front == NULL)

/*
 * Checks if a list has exactly one element.
 */
#define DLIST_IS_SINGLE(LIST) \
  ((LIST)->front != NULL && (LIST)->front == (LIST)->back)

/*
 * Checks if an element is inserted into a list.
 *
 * Does not search any lists, runs in constant time.
 */
#define DLIST_IS_ELEM_INSERTED(ELEM, LINK) \
  (DLIST_CHECK_ELEM(ELEM, LINK),           \
                                           \
   ((ELEM)->LINK.next != NULL) && ((ELEM)->LINK.prev != NULL))

/*
 * Gets the first element in a list.
 */
#define DLIST_PEEK_FRONT(LIST, LINK) \
  (DLIST_CHECK(LIST, LINK),          \
                                     \
   (LIST)->front)

/*
 * Gets the last element in a list.
 */
#define DLIST_PEEK_BACK(LIST, LINK) \
  (DLIST_CHECK(LIST, LINK),         \
                                    \
   (LIST)->back)

/*
 * Inserts an element at the front of a list.
 */
#define DLIST_PUSH_FRONT(LIST, ELEM, LINK)                       \
  (DLIST_CHECK(LIST, LINK),                                      \
   DLIST_ASSERT(!DLIST_IS_ELEM_INSERTED(ELEM, LINK)),            \
                                                                 \
   (!DLIST_IS_EMPTY(LIST)) ? ((LIST)->front->LINK.prev = (ELEM), \
                              (LIST)->back->LINK.next = (ELEM),  \
                                                                 \
                              (ELEM)->LINK.next = (LIST)->front, \
                              (ELEM)->LINK.prev = (LIST)->back)  \
                           : ((ELEM)->LINK.next = (ELEM),        \
                              (ELEM)->LINK.prev = (ELEM),        \
                                                                 \
                              (LIST)->back = (ELEM)),            \
                                                                 \
   /* Point the list's front at our new element. */              \
   (LIST)->front = (ELEM),                                       \
                                                                 \
   DLIST_VOID)

/*
 * Inserts an element at the back of a list.
 */
#define DLIST_PUSH_BACK(LIST, ELEM, LINK)                        \
  (DLIST_CHECK(LIST, LINK),                                      \
   DLIST_ASSERT(!DLIST_IS_ELEM_INSERTED(ELEM, LINK)),            \
                                                                 \
   (!DLIST_IS_EMPTY(LIST)) ? ((LIST)->front->LINK.prev = (ELEM), \
                              (LIST)->back->LINK.next = (ELEM),  \
                                                                 \
                              (ELEM)->LINK.next = (LIST)->front, \
                              (ELEM)->LINK.prev = (LIST)->back)  \
                           : ((ELEM)->LINK.next = (ELEM),        \
                              (ELEM)->LINK.prev = (ELEM),        \
                                                                 \
                              (LIST)->front = (ELEM)),           \
                                                                 \
   /* Point the list's back at our new element. */               \
   (LIST)->back = (ELEM),                                        \
                                                                 \
   DLIST_VOID)

/*
 * Inserts a new element NEW after an existing list element INS.
 */
#define DLIST_INSERT_NEXT(LIST, INS, NEW, LINK)                         \
  (DLIST_CHECK(LIST, LINK),                                             \
   DLIST_ASSERT(DLIST_IS_ELEM_INSERTED(INS, LINK)),                     \
   DLIST_ASSERT(!DLIST_IS_ELEM_INSERTED(NEW, LINK)),                    \
                                                                        \
   /* List is supposed to be non-empty. */                              \
   DLIST_ASSERT(!DLIST_IS_EMPTY(LIST)),                                 \
                                                                        \
   /* Have the new element point to its new neighbors. */               \
   (NEW)->LINK.prev = (INS),                                            \
   (NEW)->LINK.next = (INS)->LINK.next,                                 \
                                                                        \
   /* Update the back of the list if we inserted after the old back. */ \
   ((INS) == (LIST)->back) ? ((LIST)->back = (NEW)) : (NULL),           \
                                                                        \
   /* Splice in the new element into the list. */                       \
   (INS)->LINK.next->LINK.prev = (NEW),                                 \
   (INS)->LINK.next = (NEW),                                            \
                                                                        \
   DLIST_VOID)

/*
 * Inserts a new element NEW before an existing list element INS.
 */
#define DLIST_INSERT_PREV(LIST, INS, NEW, LINK)                            \
  (DLIST_CHECK(LIST, LINK),                                                \
   DLIST_ASSERT(DLIST_IS_ELEM_INSERTED(INS, LINK)),                        \
   DLIST_ASSERT(!DLIST_IS_ELEM_INSERTED(NEW, LINK)),                       \
                                                                           \
   /* List is supposed to be non-empty. */                                 \
   DLIST_ASSERT(!DLIST_IS_EMPTY(LIST)),                                    \
                                                                           \
   /* Have the new element point to its new neighbors. */                  \
   (NEW)->LINK.prev = (INS)->LINK.prev,                                    \
   (NEW)->LINK.next = (INS),                                               \
                                                                           \
   /* Update the front of the list if we inserted before the old front. */ \
   ((INS) == (LIST)->front) ? ((LIST)->front = (NEW)) : (NULL),            \
                                                                           \
   /* splice in the new element into the list/ */                          \
   (INS)->LINK.prev->LINK.next = (NEW),                                    \
   (INS)->LINK.prev = (NEW),                                               \
                                                                           \
   DLIST_VOID)

/*
 * Pops the first element off of LIST and sets it to DEST.
 *
 * Usage:
 *
 *   ELEM_TYPE* var;
 *   SLIST_POP_FRONT(list, var, linkname);
 */
#define DLIST_POP_FRONT(LIST, DEST, LINK)                                     \
  (DLIST_CHECK(LIST, LINK),                                                   \
                                                                              \
   (DLIST_IS_EMPTY(LIST))                                                     \
     ? ((DEST) = NULL,                                                        \
                                                                              \
        DLIST_VOID)                                                           \
     : (DLIST_IS_SINGLE(LIST)) ? ((DEST) = (LIST)->front,                     \
                                                                              \
                                  (LIST)->front = NULL,                       \
                                  (LIST)->back = NULL,                        \
                                                                              \
                                  /* Clean up the old node's link. */         \
                                  DLIST_ELEM_INIT(DEST, LINK))                \
                               : ((DEST) = (LIST)->front,                     \
                                                                              \
                                  /* Update the new front of the list. */     \
                                  (LIST)->front = (LIST)->front->LINK.next,   \
                                  (LIST)->front->LINK.prev = (LIST)->back,    \
                                                                              \
                                  /* Make the back point to the new front. */ \
                                  (LIST)->back->LINK.next = (LIST)->front,    \
                                                                              \
                                  /* Clean up the old node's link. */         \
                                  DLIST_ELEM_INIT(DEST, LINK)))

/*
 * Pops the last element off of LIST and sets it to DEST.
 */
#define DLIST_POP_BACK(LIST, DEST, LINK)                                   \
  (DLIST_CHECK(LIST, LINK),                                                \
                                                                           \
   (DLIST_IS_EMPTY(LIST))                                                  \
     ? ((DEST) = NULL,                                                     \
                                                                           \
        DLIST_VOID)                                                        \
     : (DLIST_IS_SINGLE(LIST)) ? ((DEST) = (LIST)->front,                  \
                                                                           \
                                  /* Clean up the old node's link. */      \
                                  DLIST_ELEM_INIT(DEST, LINK))             \
                               : ((DEST) = (LIST)->back,                   \
                                                                           \
                                  /* Update the new back of the list. */   \
                                  (LIST)->back = (LIST)->back->LINK.prev,  \
                                  (LIST)->front->LINK.prev = (LIST)->back, \
                                  (LIST)->back->LINK.next = (LIST)->front, \
                                                                           \
                                  /* Clean up the old node's link. */      \
                                  DLIST_ELEM_INIT(DEST, LINK)))

/*
 * Removes an element ELEM from LIST.
 */
#define DLIST_REMOVE(LIST, ELEM, LINK)                                       \
  (DLIST_CHECK(LIST, LINK),                                                  \
   DLIST_ASSERT(DLIST_IS_ELEM_INSERTED(ELEM, LINK)),                         \
                                                                             \
   /* Cannot remove an element from an empty list. */                        \
   DLIST_ASSERT(!DLIST_IS_EMPTY(LIST)),                                      \
                                                                             \
   /*                                                                        \
    * If we're removing the front element, then we need to update the list's \
    * front reference to the next element. Otherwise we want to update the   \
    * next reference of the removed element's prev.                          \
    */                                                                       \
   ((LIST)->front == (ELEM))                                                 \
     ? ((LIST)->front = (ELEM)->LINK.next)                                   \
     : ((ELEM)->LINK.prev->LINK.next = (ELEM)->LINK.next),                   \
                                                                             \
   /*                                                                        \
    * Ditto for the back element, and the prev reference of the removed      \
    * element's next.                                                        \
    */                                                                       \
   ((LIST)->back == (ELEM))                                                  \
     ? ((LIST)->back = (ELEM)->LINK.prev)                                    \
     : ((ELEM)->LINK.next->LINK.prev = (ELEM)->LINK.prev),                   \
                                                                             \
   (!DLIST_IS_SINGLE(LIST)) ? ((LIST)->front->LINK.prev = (LIST)->back,      \
                               (LIST)->back->LINK.next = (LIST)->front)      \
                            : ((LIST)->front = NULL, (LIST)->back = NULL),   \
                                                                             \
   /* The element is no longer inserted in the list. */                      \
   DLIST_ELEM_INIT(ELEM, LINK),                                              \
                                                                             \
   DLIST_VOID)

/*
 * Iterates through all elements of a list.
 *
 * CURR will hold the address of the element currently being iterated over.
 * BODY is the code fragment to execute on each iteration.
 */
#define DLIST_FOREACH(CURR, LIST, LINK, BODY) \
  {                                           \
    (CURR) = (LIST)->front;                   \
    if ((CURR) != NULL) {                     \
      do {                                    \
        BODY;                                 \
        (CURR) = (CURR)->LINK.next;           \
      } while ((CURR) != (LIST)->front);      \
    }                                         \
  }

/*
 * Checks the validity of a list.
 */
#define DLIST_CHECK(LIST, LINK)                                    \
  (((LIST)->front == NULL || (LIST)->back == NULL)                 \
     ? (DLIST_ASSERT((LIST)->front == NULL),                       \
        DLIST_ASSERT((LIST)->back == NULL))                        \
     : ((LIST)->front == (LIST)->back ||                           \
        (LIST)->front->LINK.prev == (LIST)->front ||               \
        (LIST)->front->LINK.next == (LIST)->front ||               \
        (LIST)->back->LINK.prev == (LIST)->back ||                 \
        (LIST)->back->LINK.next == (LIST)->back)                   \
       ? (DLIST_ASSERT((LIST)->front == (LIST)->back),             \
          DLIST_ASSERT((LIST)->front->LINK.prev == (LIST)->front), \
          DLIST_ASSERT((LIST)->front->LINK.next == (LIST)->front), \
          DLIST_ASSERT((LIST)->back->LINK.prev == (LIST)->back),   \
          DLIST_ASSERT((LIST)->back->LINK.next == (LIST)->back))   \
       : (DLIST_VOID))

/*
 * Checks the validity of a list element.
 */
#define DLIST_CHECK_ELEM(ELEM, LINK)                        \
  (((ELEM)->LINK.next == NULL || (ELEM)->LINK.prev == NULL) \
     ? (DLIST_ASSERT((ELEM)->LINK.next == NULL),            \
        DLIST_ASSERT((ELEM)->LINK.prev == NULL))            \
     : (DLIST_ASSERT((ELEM)->LINK.next != NULL),            \
        DLIST_ASSERT((ELEM)->LINK.prev != NULL)))

#endif
