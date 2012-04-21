/** @file stack.h
 *  @brief Header for a stack data structure library.
 *  @author Alexander Malyshev
 */


#ifndef __STACK_H__
#define __STACK_H__


#include <assert.h>
#include <stddef.h>


#define STACK_NEW(STK_TYPE, ELEM_TYPE)  \
    typedef struct STK_TYPE {           \
        struct ELEM_TYPE *top;          \
        size_t len;                     \
    } STK_TYPE


#define STACK_LINK(ELEM_TYPE, NEXT) \
    struct ELEM_TYPE *NEXT


#define STACK_INIT(STK) do {    \
    assert((STK) != NULL);      \
                                \
    (STK)->top = NULL;          \
    (STK)->len = 0;             \
} while (0)


#define STACK_STATIC_INIT { \
    .top = NULL,            \
    .len = 0                \
}


#define STACK_ELEM_INIT(ELEM, NEXT) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->NEXT = NULL;                    \
} while (0)


#define STACK_PEEP(DEST, STK) do {  \
    CHECK_STACK(STK);               \
                                    \
    (DEST) = (STK)->top;            \
} while (0)


#define STACK_POP(DEST, STK, NEXT) do { \
    CHECK_STACK(STK);                   \
                                        \
    (DEST) = (STK)->top;                \
                                        \
    (STK)->top = (STK)->top->NEXT;      \
                                        \
    (STK)->len -= 1;                    \
} while (0)


#define STACK_PUSH(STK, ELEM, NEXT) do {    \
    CHECK_STACK(STK);                       \
    assert((ELEM) != NULL);                 \
    assert((ELEM)->NEXT == NULL);           \
                                            \
    (ELEM)->NEXT = (STK)->top;              \
                                            \
    (STK)->top = (ELEM);                    \
                                            \
    (STK)->len += 1;                        \
} while (0)


#define CHECK_STACK(STK) do {                                       \
    /* check that we haven't gotten a NULL stack */                 \
    assert((STK) != NULL);                                          \
                                                                    \
    /* and that our length makes sense with regards to our top */   \
    if ((STK)->top == NULL)                                         \
        assert((STK)->len == 0);                                    \
    else                                                            \
        assert((STK)->len != 0);                                    \
} while (0)


#endif /* __STACK_H__ */
