#define DLIST_ASSERTS

#include "dlist.h"

#include <assert.h>
#include <stdio.h>

typedef struct block {
  DLIST_DECLARE_LINK(block, link);
  int elem;
} block_t;

#define BLOCK_STATIC_INIT(ELEM) { \
  .link = DLIST_LINK_STATIC_INIT, \
  .elem = (ELEM)                  \
}

DLIST_DECLARE(deque, block);

static void pushf(deque* deq, block_t* blk) {
  DLIST_PUSH_FRONT(deq, blk, link);
}

static void pushb(deque* deq, block_t* blk) {
  DLIST_PUSH_BACK(deq, blk, link);
}

static block_t* peekf(deque* deq) {
  return DLIST_PEEK_FRONT(deq, link);
}

static block_t* peekb(deque* deq) {
  return DLIST_PEEK_BACK(deq, link);
}

static void rem(deque* deq, block_t* blk) {
  DLIST_REMOVE(deq, blk, link);
}

static block_t* popf(deque* deq) {
  block_t* blk;
  DLIST_POP_FRONT(deq, blk, link);
  return blk;
}

static block_t* popb(deque* deq) {
  block_t* blk;
  DLIST_POP_BACK(deq, blk, link);
  return blk;
}

int main(void) {
  deque d = DLIST_STATIC_INIT;
  deque* deq = &d;

  assert(DLIST_IS_EMPTY(deq));
  assert(!DLIST_IS_SINGLE(deq));
  assert(peekf(deq) == NULL);
  assert(peekb(deq) == NULL);
  assert(popf(deq) == NULL);
  assert(popb(deq) == NULL);

  block_t b0 = BLOCK_STATIC_INIT(0);
  block_t b1 = BLOCK_STATIC_INIT(1);
  block_t b2 = BLOCK_STATIC_INIT(2);

  pushf(deq, &b0);
  assert(!DLIST_IS_EMPTY(deq));
  assert(DLIST_IS_SINGLE(deq));
  assert(peekf(deq) == &b0);
  assert(peekb(deq) == &b0);

  pushf(deq, &b1);
  assert(!DLIST_IS_EMPTY(deq));
  assert(!DLIST_IS_SINGLE(deq));
  assert(peekf(deq) == &b1);
  assert(peekb(deq) == &b0);

  pushb(deq, &b2);
  assert(!DLIST_IS_EMPTY(deq));
  assert(!DLIST_IS_SINGLE(deq));
  assert(peekf(deq) == &b1);
  assert(peekb(deq) == &b2);

  block_t* res = NULL;
  block_t* peekr = NULL;

  DLIST_FOREACH(res, deq, link, {
    block_t* _ = peekf(deq);
    _ = peekb(deq);
    (void)_;

    res->elem += 1;
  });

  printf("[ ");

  rem(deq, &b0);
  assert(peekf(deq) == &b1);
  assert(peekb(deq) == &b2);
  assert(!DLIST_IS_EMPTY(deq));
  assert(!DLIST_IS_SINGLE(deq));
  printf("%d ", b0.elem);

  peekr = peekb(deq);
  res = popb(deq);
  assert(res == &b2);
  assert(res == peekr);
  assert(peekf(deq) == &b1);
  assert(peekb(deq) == &b1);
  assert(!DLIST_IS_EMPTY(deq));
  assert(DLIST_IS_SINGLE(deq));
  printf("%d ", res->elem);

  peekr = peekf(deq);
  res = popf(deq);
  assert(res == &b1);
  assert(res == peekr);
  assert(peekf(deq) == NULL);
  assert(peekb(deq) == NULL);
  assert(DLIST_IS_EMPTY(deq));
  assert(!DLIST_IS_SINGLE(deq));
  printf("%d ", res->elem);

  printf("]\n");

  return 0;
}
