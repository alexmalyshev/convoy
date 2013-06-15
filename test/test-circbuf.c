#include "../include/circbuf.h"

#include <stdio.h>

#define INTBUF_LEN 4

CIRCBUF_DECLARE(intbuf, int, INTBUF_LEN);


int main(void) {
    intbuf cbuf = CIRCBUF_STATIC_INIT(INTBUF_LEN);
    bool status = false;

    assert(CIRCBUF_ISEMPTY(&cbuf));
    assert(!CIRCBUF_ISFULL(&cbuf));

    status = CIRCBUF_PUSH_HEAD(&cbuf, 0);
    assert(status);
    assert(!CIRCBUF_ISEMPTY(&cbuf));
    assert(!CIRCBUF_ISFULL(&cbuf));

    status = CIRCBUF_PUSH_HEAD(&cbuf, 1);
    assert(status);
    assert(!CIRCBUF_ISEMPTY(&cbuf));
    assert(!CIRCBUF_ISFULL(&cbuf));

    status = CIRCBUF_PUSH_TAIL(&cbuf, 2);
    assert(status);
    assert(!CIRCBUF_ISEMPTY(&cbuf));
    assert(CIRCBUF_ISFULL(&cbuf));

    status = CIRCBUF_PUSH_HEAD(&cbuf, 3);
    assert(!status);
    assert(!CIRCBUF_ISEMPTY(&cbuf));
    assert(CIRCBUF_ISFULL(&cbuf));

    status = CIRCBUF_PUSH_TAIL(&cbuf, 3);
    assert(!status);
    assert(!CIRCBUF_ISEMPTY(&cbuf));
    assert(CIRCBUF_ISFULL(&cbuf));

    int *ref = NULL;
    size_t i = 0;
    CIRCBUF_FOREACH(ref, i, &cbuf)
        *ref += 1;

    int res = -1;

    printf("[ ");
    status = CIRCBUF_POP_HEAD(&res, &cbuf);
    assert(status);
    printf("%d ", res);

    status = CIRCBUF_POP_TAIL(&res, &cbuf);
    assert(status);
    printf("%d ", res);

    status = CIRCBUF_POP_HEAD(&res, &cbuf);
    assert(status);
    printf("%d ", res);

    res = -13;
    status = CIRCBUF_POP_HEAD(&res, &cbuf);
    assert(!status);
    assert(CIRCBUF_ISEMPTY(&cbuf));
    assert(!CIRCBUF_ISFULL(&cbuf));
    assert(res == -13);

    status = CIRCBUF_POP_TAIL(&res, &cbuf);
    assert(!status);
    assert(CIRCBUF_ISEMPTY(&cbuf));
    assert(!CIRCBUF_ISFULL(&cbuf));
    assert(res == -13);

    printf("]\n");

    return 0;
}
