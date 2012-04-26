#include "../include/circbuf.h"

#include <stdio.h>


#define CBUF_LEN 32


CIRCBUF_NEW(circbuf, int, CBUF_LEN);

static circbuf cbuf = CIRCBUF_STATIC_INIT(CBUF_LEN);


int main(void) {
    CIRCBUF_ENQUEUE(&cbuf, 0);
    CIRCBUF_ENQUEUE(&cbuf, 1);
    CIRCBUF_ENQUEUE(&cbuf, 2);

    int *ref;
    size_t i;
    CIRCBUF_FOREACH(ref, i, &cbuf) {
        *ref += 1;
    }

    int res;

    printf("[ ");
    CIRCBUF_DEQUEUE(res, &cbuf);
    printf("%d ", res);
    CIRCBUF_DEQUEUE(res, &cbuf);
    printf("%d ", res);
    CIRCBUF_DEQUEUE(res, &cbuf);
    printf("%d ", res);
    printf("]\n");

    return 0;
}
