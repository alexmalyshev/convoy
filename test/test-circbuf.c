#include "../include/circbuf.h"

#include <stdio.h>


#define CBUF_LEN 32


CIRCBUF_NEW(circbuf, int, CBUF_LEN);

static circbuf cbuf = CIRCBUF_STATIC_INIT(CBUF_LEN);


int main(void) {
    CIRCBUF_PUSH_HEAD(&cbuf, 0);
    CIRCBUF_PUSH_HEAD(&cbuf, 1);
    CIRCBUF_PUSH_TAIL(&cbuf, 2);

    int *ref;
    size_t i;
    CIRCBUF_FOREACH(ref, i, &cbuf) {
        *ref += 1;
    }

    int res;

    printf("[ ");
    CIRCBUF_POP_HEAD(res, &cbuf);
    printf("%d ", res);
    CIRCBUF_POP_TAIL(res, &cbuf);
    printf("%d ", res);
    CIRCBUF_POP_HEAD(res, &cbuf);
    printf("%d ", res);
    printf("]\n");

    res = -13;
    assert(CIRCBUF_ISEMPTY(&cbuf));
    CIRCBUF_POP_HEAD(res, &cbuf);
    assert(res == -13);
    assert(CIRCBUF_ISEMPTY(&cbuf));
    CIRCBUF_POP_TAIL(res, &cbuf);
    assert(res == -13);
    assert(CIRCBUF_ISEMPTY(&cbuf));

    return 0;
}
