/** @file stack.h
 *  @brief Header for a stack data structure library.
 *  @author Alexander Malyshev
 */


#ifndef __STACK_H__
#define __STACK_H__


#include <assert.h>
#include <stddef.h>


/** @def STACK_NEW(STK_TYPE, ELEM_TYPE)
 *
 *  @brief Declares a new stack type
 *
 *  ELEM_TYPE must be the name of a struct type
 *
 *  @param STK_TYPE the type of the stack
 *  @param ELEM_TYPE the type of the stack's elements
 */
#define STACK_NEW(STK_TYPE, ELEM_TYPE)  \
    typedef struct STK_TYPE {           \
        struct ELEM_TYPE *top;          \
        size_t len;                     \
    } STK_TYPE


/** @def STACK_LINK(ELEM_TYPE, NEXT)
 *
 *  @brief Declares a link in a struct for use with a stack
 *
 *  ELEM_TYPE must be the name of a struct type
 *
 *  @param ELEM_TYPE the type of the element
 *  @param NEXT the name of the link field
 */
#define STACK_LINK(ELEM_TYPE, NEXT) \
    struct ELEM_TYPE *NEXT


/** @def STACK_INIT(STK)
 *
 *  @brief Initializes a stack
 *
 *  @param STK the address of the stack
 */
#define STACK_INIT(STK) do {    \
    assert((STK) != NULL);      \
                                \
    (STK)->top = NULL;          \
    (STK)->len = 0;             \
} while (0)


/** @def STACK_STATIC_INIT
 *
 *  @brief Statically initializes a stack
 */
#define STACK_STATIC_INIT { \
    .top = NULL,            \
    .len = 0                \
}


/** @def STACK_ELEM_INIT(ELEM, NEXT)
 *
 *  @brief Initializes the stack link of an element
 *
 *  @param ELEM the address of the stack element
 *  @param NEXT the name of the link field
 */
#define STACK_ELEM_INIT(ELEM, NEXT) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->NEXT = NULL;                    \
} while (0)


/** @def STACK_PEEP(DEST, STK)
 *
 *  @brief Returns the top element in a stack
 *
 *  Sets DEST to NULL if the stack is empty
 *
 *  @param DEST the variable where to store the top reference
 *  @param STK the address of the stack
 */
#define STACK_PEEP(DEST, STK) do {  \
    CHECK_STACK(STK);               \
                                    \
    (DEST) = (STK)->top;            \
} while (0)


/** @def STACK_POP(DEST, STK, NEXT)
 *
 *  @brief Pops off the top element of a stack
 *
 *  Sets DEST to NULL if the stack is empty
 *
 *  @param DEST the variable where to store the top reference
 *  @param STK the address of the stack
 *  @param NEXT the name of the link field
 */
#define STACK_POP(DEST, STK, NEXT) do {                     \
    CHECK_STACK(STK);                                       \
                                                            \
    /* return NULL if the stack is empty */                 \
    if ((STK)->len == 0) {                                  \
        (DEST) = NULL;                                      \
        break;                                              \
    }                                                       \
                                                            \
    /* otherwise set our destination as the top element */  \
    (DEST) = (STK)->top;                                    \
                                                            \
    /* the top element is now the old top's next element */ \
    (STK)->top = (STK)->top->NEXT;                          \
                                                            \
    /* clear out the old top's next reference */            \
    (DEST)->NEXT = NULL;                                    \
                                                            \
    (STK)->len -= 1;                                        \
} while (0)


/** @def STACK_PUSH(STK, ELEM, NEXT)
 *
 *  @brief Pushes an element on a stack
 *
 *  @param STK the address of the stack
 *  @param ELEM the address of the stack element
 *  @param NEXT the name of the link field
 */
#define STACK_PUSH(STK, ELEM, NEXT) do {            \
    CHECK_STACK(STK);                               \
    assert((ELEM) != NULL);                         \
    assert((ELEM)->NEXT == NULL);                   \
                                                    \
    /* our new top points to our old top */         \
    (ELEM)->NEXT = (STK)->top;                      \
                                                    \
    /* the stack's top is now our new element */    \
    (STK)->top = (ELEM);                            \
                                                    \
    (STK)->len += 1;                                \
} while (0)


/** @def STACK_FOREACH(CURR, STK, NEXT)
 *
 *  @brief Iterates through all the elements of a stack
 *
 *  @param CURR a reference to the current element in one iteration
 *  @param STK the address of the stack
 *  @param NEXT the name of the link field
 */
#define STACK_FOREACH(CURR, STK, NEXT)                  \
    for (assert((STK) != NULL), (CURR) = (STK)->top;    \
         (CURR) != NULL;                                \
         (CURR) = (CURR)->NEXT)


/** @def CHECK_STACK(STK)
 *
 *  @brief Checks the validity of a stack
 *
 *  @param STK the address of the stack
 */
#define CHECK_STACK(STK) do {                                       \
    /* check that we haven't gotten a NULL stack */                 \
    assert((STK) != NULL);                                          \
                                                                    \
    /* and that our length makes sense with regards to our top */   \
    if ((STK)->top == NULL || (STK)->len == 0) {                    \
        assert((STK)->top == NULL);                                 \
        assert((STK)->len == 0);                                    \
    }                                                               \
} while (0)


#endif /* __STACK_H__ */
