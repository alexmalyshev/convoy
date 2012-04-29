/** @file stack.h
 *  @brief Header for a stack data structure library
 *  @author Alexander Malyshev
 */


#ifndef __STACK_H__
#define __STACK_H__


#include <assert.h>
#include <stddef.h>


/** @brief Declares a new stack type
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


/** @brief Declares a link in a struct for use with a stack
 *
 *  ELEM_TYPE must be the name of a struct type
 *
 *  @param ELEM_TYPE the type of the element
 *  @param NEXT the name of the link field
 */
#define STACK_LINK(ELEM_TYPE, NEXT) \
    struct ELEM_TYPE *NEXT


/** @brief Initializes a stack
 *
 *  @param STK the address of the stack
 */
#define STACK_INIT(STK) do {    \
    assert((STK) != NULL);      \
                                \
    (STK)->top = NULL;          \
    (STK)->len = 0;             \
} while (0)


/** @brief Statically initializes a stack */
#define STACK_STATIC_INIT { \
    .top = NULL,            \
    .len = 0                \
}


/** @brief Initializes the stack link of an element
 *
 *  @param ELEM the address of the stack element
 *  @param NEXT the name of the link field
 */
#define STACK_ELEM_INIT(ELEM, NEXT) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->NEXT = NULL;                    \
} while (0)


/** @brief Returns the top element in a stack
 *
 *  Sets DEST to NULL if the stack is empty
 *
 *  @param DEST the variable where to store the top reference
 *  @param STK the address of the stack
 */
#define STACK_PEEK(DEST, STK) do {  \
    STACK_CHECK(STK);               \
                                    \
    (DEST) = (STK)->top;            \
} while (0)


/** @brief Pops off the top element of a stack
 *
 *  Sets DEST to NULL if the stack is empty
 *
 *  @param DEST the variable where to store the top reference
 *  @param STK the address of the stack
 *  @param NEXT the name of the link field
 */
#define STACK_POP(DEST, STK, NEXT) do {                     \
    STACK_CHECK(STK);                                       \
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


/** @brief Pushes an element on a stack
 *
 *  @param STK the address of the stack
 *  @param ELEM the address of the stack element
 *  @param NEXT the name of the link field
 */
#define STACK_PUSH(STK, ELEM, NEXT) do {            \
    STACK_CHECK(STK);                               \
    STACK_CHECK_NEW_ELEM(ELEM, NEXT);               \
                                                    \
    /* our new top points to our old top */         \
    (ELEM)->NEXT = (STK)->top;                      \
                                                    \
    /* the stack's top is now our new element */    \
    (STK)->top = (ELEM);                            \
                                                    \
    (STK)->len += 1;                                \
} while (0)


/** @brief Iterates through all the elements of a stack
 *
 *  @param CURR a reference to the current element in one iteration
 *  @param STK the address of the stack
 *  @param NEXT the name of the link field
 */
#define STACK_FOREACH(CURR, STK, NEXT)                  \
    for (assert((STK) != NULL), (CURR) = (STK)->top;    \
         (CURR) != NULL;                                \
         (CURR) = (CURR)->NEXT)


/** @brief Checks the validity of a stack
 *
 *  @param STK the address of the stack
 */
#define STACK_CHECK(STK) do {                                       \
    /* check that we haven't gotten a NULL stack */                 \
    assert((STK) != NULL);                                          \
                                                                    \
    /* and that our length makes sense with regards to our top */   \
    if ((STK)->top == NULL || (STK)->len == 0) {                    \
        assert((STK)->top == NULL);                                 \
        assert((STK)->len == 0);                                    \
    }                                                               \
} while (0)


/** @brief Checks the validity of a new, uninserted stack element
 *
 *  @param ELEM the address of the stack element
 *  @param NEXT the name of the link field
 */
#define STACK_CHECK_NEW_ELEM(ELEM, NEXT) do {           \
    /* check that we haven't gotten a NULL element */   \
    assert((ELEM) != NULL);                             \
                                                        \
    /* and that it isn't inserted in a stack already */ \
    assert((ELEM)->NEXT == NULL);                       \
} while (0)


#endif /* __STACK_H__ */
