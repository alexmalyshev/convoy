/** @file circbuf.c
 *  @brief A circular buffer library.
 *
 *  Implemented as a dynamic array with two indices to track the front and
 *  back of the circular buffer. We malloc an array with an extra slot so
 *  as to simplify checking for empty and full circbufs. The circbuf is empty
 *  if its front index is equal to its back index, and it is full if its
 *  back index plus one (with wraparound courtesy of mod) is equal to its
 *  front index.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "circbuf.h"

circbuf *circbuf_init(size_t len) {
    circbuf *cbuf;

    if (len == MAX_LEN)
        return NULL;

    if ((cbuf = malloc(sizeof(circbuf))) == NULL)
        return NULL;
    if ((cbuf->elems = malloc((len + 1) * sizeof(void *))) == NULL)
        return NULL;
    cbuf->front = 0;
    cbuf->back = 0;
    cbuf->len = len + 1;
    return cbuf;
}

int circbuf_destroy(circbuf *cbuf) {
    if (circbuf_clear(cbuf))
        return 1;

    free(cbuf->elems);
    free(cbuf);
    return 0;
}

void *circbuf_dequeue(circbuf *cbuf) {
    void *data;

    if (cbuf == NULL || cbuf->front == cbuf->back)
        return NULL;

    data = cbuf->elems[cbuf->front];
    cbuf->front = (cbuf->front + 1) % cbuf->len;
    return 0;
}

int circbuf_enqueue(circbuf *cbuf, void *elem) {
    if (cbuf == NULL || elem == NULL)
        return 1;

    if ((cbuf->back + 1) % cbuf->len == cbuf->front)
        return 1;
    cbuf->elems[cbuf->back] = elem;
    cbuf->back = (cbuf->back + 1) % cbuf->len;
    return 0;
}

void *circbuf_peek(circbuf *cbuf) {
    if (cbuf == NULL || cbuf->front == cbuf->back)
        return NULL;

    return cbuf->elems[cbuf->front];
}

int circbuf_clear(circbuf *cbuf) {
    if (cbuf == NULL)
        return 1;

    cbuf->front = 0;
    cbuf->back = 0;
    return 0;
}
