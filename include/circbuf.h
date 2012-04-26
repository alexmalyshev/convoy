/** @file circbuf.h
 *  @brief Header for a circular buffer data structure library
 *  @author Alexander Malyshev
 */


#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__


#include <assert.h>
#include <stddef.h>


#define CIRCBUF_NEW(CBUF_TYPE, ELEM_TYPE, LEN)  \
    typedef struct CBUF_TYPE {                  \
        ELEM_TYPE elems[LEN];                   \
        size_t head;                            \
        size_t tail;                            \
        size_t len;                             \
    } CBUF_TYPE


#define CIRCBUF_INIT(CBUF, LEN) do {    \
    assert((CBUF) != NULL);             \
                                        \
    (CBUF)->head = 0;                   \
    (CBUF)->tail = 0;                   \
                                        \
    (CBUF)->len = (LEN);                \
} while (0)


#define CIRCBUF_STATIC_INIT(LEN) {  \
    .head = 0,                      \
    .tail = 0,                      \
    .len = (LEN)                    \
}


#define CIRCBUF_DEQUEUE(DEST, CBUF) do {                    \
    if (CIRCBUF_ISEMPTY(CBUF))                              \
        break;                                              \
                                                            \
    (DEST) = (CBUF)->elems[(CBUF)->head];                   \
                                                            \
    (CBUF)->head = ROTATE_RIGHT((CBUF)->head, (CBUF)->len); \
} while (0)


#define CIRCBUF_ENQUEUE(CBUF, ELEM) do {                    \
    if (CIRCBUF_ISFULL(CBUF))                               \
        break;                                              \
                                                            \
    (CBUF)->elems[(CBUF)->tail] = (ELEM);                   \
                                                            \
    (CBUF)->tail = ROTATE_RIGHT((CBUF)->tail, (CBUF)->len); \
} while (0)


#define CIRCBUF_PEEK(DEST, CBUF) do {       \
    assert(!CIRCBUF_ISEMPTY(CBUF));         \
                                            \
    (DEST) = (CBUF)->elems[(CBUF)->head];   \
} while (0)


#define CIRCBUF_ISEMPTY(CBUF) (     \
    CHECK_CIRCBUF(CBUF),            \
                                    \
    (CBUF)->head == (CBUF)->tail    \
)


#define CIRCBUF_ISFULL(CBUF) (                              \
    CHECK_CIRCBUF(CBUF),                                    \
                                                            \
    (CBUF)->head == ROTATE_RIGHT((CBUF)->tail, (CBUF)->len) \
)


#define CIRCBUF_FOREACH(CURR, INDEX, CBUF)                          \
    for (CHECK_CIRCBUF(CBUF), (INDEX) = (CBUF)->head;               \
         (CURR) = &(CBUF)->elems[INDEX], (INDEX) != (CBUF)->tail;   \
         (INDEX) = ROTATE_RIGHT(INDEX, (CBUF)->len))


#define CHECK_CIRCBUF(CBUF) (           \
    assert((CBUF) != NULL),             \
    assert((CBUF)->len != 0),           \
    assert((CBUF)->head < (CBUF)->len), \
    assert((CBUF)->tail < (CBUF)->len)  \
)


#define ROTATE_RIGHT(VAL, LIMIT) (  \
    assert((LIMIT) > 0),            \
                                    \
    ((VAL) + 1) % (LIMIT)           \
)


#endif /* __CIRCBUF_H__ */
