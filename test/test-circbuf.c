#include "../include/circbuf.h"

#include <stdio.h>

#define INTBUF_LEN 4

CIRCBUF_DECLARE(intbuf, int, INTBUF_LEN);


static bool empty(intbuf *buf) { return CIRCBUF_ISEMPTY(buf); }
static bool full(intbuf *buf) { return CIRCBUF_ISFULL(buf); }
static bool pushf(intbuf *buf, int n) { return CIRCBUF_PUSH_FRONT(buf, n); }
static bool pushb(intbuf *buf, int n) { return CIRCBUF_PUSH_BACK(buf, n); }
static bool peekf(int *n, intbuf *buf) { return CIRCBUF_PEEK_FRONT(n, buf); }
static bool peekb(int *n, intbuf *buf) { return CIRCBUF_PEEK_BACK(n, buf); }
static bool popf(int *n, intbuf *buf) { return CIRCBUF_POP_FRONT(n, buf); }
static bool popb(int *n, intbuf *buf) { return CIRCBUF_POP_BACK(n, buf); }


int main(void) {
    intbuf cbuf = CIRCBUF_STATIC_INIT(INTBUF_LEN);
    bool status = false;

    assert(empty(&cbuf));
    assert(!full(&cbuf));

    status = pushf(&cbuf, 0);
    assert(status);
    assert(!empty(&cbuf));
    assert(!full(&cbuf));

    status = pushf(&cbuf, 1);
    assert(status);
    assert(!empty(&cbuf));
    assert(!full(&cbuf));

    status = pushb(&cbuf, 2);
    assert(status);
    assert(!empty(&cbuf));
    assert(full(&cbuf));

    status = pushf(&cbuf, 3);
    assert(!status);
    assert(!empty(&cbuf));
    assert(full(&cbuf));

    status = pushb(&cbuf, 3);
    assert(!status);
    assert(!empty(&cbuf));
    assert(full(&cbuf));

    int *ref = NULL;
    size_t i = 0;
    CIRCBUF_FOREACH(ref, i, &cbuf)
        *ref += 1;

    int res = -1;

    printf("[ ");
    status = popf(&res, &cbuf);
    assert(status);
    printf("%d ", res);

    status = popb(&res, &cbuf);
    assert(status);
    printf("%d ", res);

    status = popf(&res, &cbuf);
    assert(status);
    printf("%d ", res);

    res = -13;
    status = popf(&res, &cbuf);
    assert(!status);
    assert(empty(&cbuf));
    assert(!full(&cbuf));
    assert(res == -13);

    status = popb(&res, &cbuf);
    assert(!status);
    assert(empty(&cbuf));
    assert(!full(&cbuf));
    assert(res == -13);

    status = peekf(&res, &cbuf);
    assert(!status);
    assert(empty(&cbuf));
    assert(!full(&cbuf));
    assert(res == -13);

    status = peekb(&res, &cbuf);
    assert(!status);
    assert(empty(&cbuf));
    assert(!full(&cbuf));
    assert(res == -13);

    printf("]\n");

    return 0;
}
