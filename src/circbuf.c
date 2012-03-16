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

#include "circbuf.h"

#include <assert.h>
#include <stdlib.h>


int circbuf_init(circbuf *cbuf, size_t len) {
    if (cbuf == NULL)
        return -1;

    /* allocate one extra slot */
    cbuf->elems = malloc((len + 1) * sizeof(void *));
    if (cbuf->elems == NULL)
        return -1;

    /* set the circbuf's fields to empty */
    cbuf->front = 0;
    cbuf->back = 0;

    /* length of the buffer is one too many */
    cbuf->len = len + 1;

    return 0;
}


int circbuf_destroy(circbuf *cbuf) {
    if (circbuf_clear(cbuf))
        return -1;

    free(cbuf->elems);

    return 0;
}


void *circbuf_dequeue(circbuf *cbuf) {
    void *elem;

    if (cbuf == NULL)
        return NULL;

    /* if the buffer is empty, just return NULL */
    if (cbuf->front == cbuf->back)
        return NULL;

    /* grab the front of the buffer */
    elem = cbuf->elems[cbuf->front];

    /* update the index of the buffer's front element */
    cbuf->front = (cbuf->front + 1) % cbuf->len;

    return elem;
}


int circbuf_enqueue(circbuf *cbuf, void *elem) {
    if (cbuf == NULL || elem == NULL)
        return -1;

    /* if cbuf is full just return 1 */
    if ((cbuf->back + 1) % cbuf->len == cbuf->front)
        return 1;

    /* otherwise insert 'elem' at the back of the buffer */
    cbuf->elems[cbuf->back] = elem;

    /* and update the index where to insert the next element */
    cbuf->back = (cbuf->back + 1) % cbuf->len;

    return 0;
}


void *circbuf_peek(circbuf *cbuf) {
    if (cbuf == NULL)
        return NULL;

    /* if the buffer is empty then just return NULL */
    if (cbuf->front == cbuf->back)
        return NULL;

    /* otherwise return the front element */
    return cbuf->elems[cbuf->front];
}


int circbuf_clear(circbuf *cbuf) {
    if (cbuf == NULL)
        return -1;

    /* reset the front and back indices to zero */
    cbuf->front = 0;
    cbuf->back = 0;

    return 0;
}
