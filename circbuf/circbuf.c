#include <stdlib.h>
#include "circbuf.h"

/* circbuf_init - initializes a new and empty circbuf of length len at *cb
 * Fails: cb is NULL, len <= 0, or malloc fails */
int circbuf_init(circbuf **cb, long len) {
    if (cb == NULL || len <= 0)
        return 1;
    if ((*cb = malloc(sizeof(circbuf))) == NULL)
        return 1;
    if (((*cb)->items = malloc((len + 1) * sizeof(void *))) == NULL)
        return 1;
    (*cb)->front = 0;
    (*cb)->back = 0;
    (*cb)->len = len + 1;
    return 0;
}

/* circbuf_destroy - clears out all the elements of cb and frees the
                     internal array as well as the circbuf struct itself
 * Warning: Will cause memory leaks if the elements in the buffer were malloc'd
            and never get free'd after this function call
 * Fails: cb is NULL */
int circbuf_destroy(circbuf *cb) {
    if (circbuf_clear(cb))
        return 1;
    free(cb->items);
    free(cb);
    return 0;
}


/* circbuf_dequeue - removes the first element of cb if it exists and returns
                     it, returns NULL if cb is empty
 * Fails: cb is NULL */
void *circbuf_dequeue(circbuf *cb) {
    void *data;

    if (cb == NULL || cb->front == cb->back)
        return NULL;

    data = cb->items[cb->front];
    cb->front = (cb->front + 1) % cb->len;
    return 0;
}

/* circbuf_enqueue - adds on elem as the new back of cb if cb is not full,
                     if cb is full then will just return 1 and do nothing else
 * Fails: cb is NULL or elem is NULL */
int circbuf_enqueue(circbuf *cb, void *elem) {
    if (cb == NULL || elem == NULL)
        return 1;

    if ((cb->back + 1) % cb->len == cb->front)
        return 1;
    cb->items[cb->back] = elem;
    cb->back = (cb->back + 1) % cb->len;
    return 0;
}

/* circbuf_peek - returns the front of cb if it exists, returns NULL if cb is
                  empty
 * Fails: cb is NULL */
void *circbuf_peek(circbuf *cb) {
    if (cb == NULL || cb->front == cb->back)
        return NULL;
    return cb->items[cb->front];
}

/* circbuf_clear - clears out all the elements of cb
 * Warning: Will cause memory leaks if the elements in the buffer were malloc'd
            and never get free'd after this function call
 * Fails: cb is NULL */
int circbuf_clear(circbuf *cb) {
    if (cb == NULL)
        return 1;
    cb->front = 0;
    cb->back = 0;
    return 0;
}
