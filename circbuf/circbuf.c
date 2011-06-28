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

circbuf *circbuf_init(long len) {
    circbuf *cb;

    if (len <= 0)
        return NULL;
    if ((cb = malloc(sizeof(circbuf))) == NULL)
        return NULL;
    if ((cb->items = malloc((len + 1) * sizeof(void *))) == NULL)
        return NULL;
    cb->front = 0;
    cb->back = 0;
    cb->len = len + 1;
    return cb;
}

int circbuf_destroy(circbuf *cb) {
    if (circbuf_clear(cb))
        return 1;
    free(cb->items);
    free(cb);
    return 0;
}

void *circbuf_dequeue(circbuf *cb) {
    void *data;

    if (cb == NULL || cb->front == cb->back)
        return NULL;

    data = cb->items[cb->front];
    cb->front = (cb->front + 1) % cb->len;
    return 0;
}

int circbuf_enqueue(circbuf *cb, void *elem) {
    if (cb == NULL || elem == NULL)
        return 1;

    if ((cb->back + 1) % cb->len == cb->front)
        return 1;
    cb->items[cb->back] = elem;
    cb->back = (cb->back + 1) % cb->len;
    return 0;
}

void *circbuf_peek(circbuf *cb) {
    if (cb == NULL || cb->front == cb->back)
        return NULL;
    return cb->items[cb->front];
}

int circbuf_clear(circbuf *cb) {
    if (cb == NULL)
        return 1;
    cb->front = 0;
    cb->back = 0;
    return 0;
}
