#ifndef CIRCBUF_H_
#define CIRCBUF_H_

/*
    Alexander Malyshev - circbuf.h

    Implementation of a fixed-size circular buffer. This structure allocates
    one more void * than the size argument in circbuf_init for performance
    reasons (easy to tell the difference between an empty circbuf and a full
    circbuf) but that extra slot is never used to store an element.
*/

/* a circbuf holds onto an array of items. the indices for the front and back,
   and the length of the array plus one */
typedef struct {
    void **items;
    long front;
    long back;
    long len;
} circbuf;

/* set up */
int circbuf_init(circbuf **, long);
int circbuf_destroy(circbuf *);

/* standard queue methods */
void *circbuf_dequeue(circbuf *);
int circbuf_enqueue(circbuf *, void *);
void *circbuf_peek(circbuf *);

/* auxiliary */
int circbuf_clear(circbuf *);

#endif
