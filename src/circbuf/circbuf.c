/** @file circbuf.c
 *  @brief A circular buffer library.
 *
 *  Implemented as an array with two indices to track the front and
 *  back of the circular buffer. We malloc an array with an extra slot to
 *  simplify checking if a <tt>circbuf</tt> is empty or full. The
 *  <tt>circbuf</tt> is empty if its front index is equal to its back index,
 *  and it is full if its back index plus one (with wraparound courtesy of mod)
 *  is equal to its front index.
 *
 *  @author Alexander Malyshev
 */

#include <stdlib.h>
#include "circbuf.h"

void circbuf_init(circbuf *cbuf, size_t len) {
    assert(cbuf != NULL);

    cbuf->elems = malloc((len + 1) * sizeof(void *));
    assert(cbuf->elems != NULL);

    cbuf->front = 0;
    cbuf->back = 0;
    cbuf->len = len + 1;
}

void circbuf_destroy(circbuf *cbuf) {
    circbuf_clear(cbuf);
    free(cbuf->elems);
}

void *circbuf_dequeue(circbuf *cbuf) {
    void *data;

    assert(cbuf != NULL);
    if (cbuf->front == cbuf->back)
        return NULL;

    data = cbuf->elems[cbuf->front];
    cbuf->front = (cbuf->front + 1) % cbuf->len;
    return data;
}

int circbuf_enqueue(circbuf *cbuf, void *elem) {
    assert(cbuf != NULL);
    assert(elem != NULL);

    if ((cbuf->back + 1) % cbuf->len == cbuf->front)
        return 1;
    cbuf->elems[cbuf->back] = elem;
    cbuf->back = (cbuf->back + 1) % cbuf->len;
    return 0;
}

void *circbuf_peek(circbuf *cbuf) {
    assert(cbuf != NULL);

    if (cbuf->front == cbuf->back)
        return NULL;

    return cbuf->elems[cbuf->front];
}

void circbuf_clear(circbuf *cbuf) {
    assert(cbuf != NULL);

    cbuf->front = 0;
    cbuf->back = 0;
}
