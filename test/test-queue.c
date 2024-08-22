#define SLIST_ASSERTS

#include "slist.h"

#include <assert.h>
#include <stdio.h>

typedef struct block {
  SLIST_DECLARE_LINK(block, next);
  int elem;
} block_t;

SLIST_DECLARE(queue, block);

static queue qu = SLIST_STATIC_INIT;

int main(void) {
  block_t b0 = { .next = SLIST_LINK_STATIC_INIT, .elem = 0 };
  block_t b1 = { .next = SLIST_LINK_STATIC_INIT, .elem = 1 };
  block_t b2 = { .next = SLIST_LINK_STATIC_INIT, .elem = 2 };

  SLIST_PUSH_BACK(&qu, &b0, next);
  SLIST_PUSH_BACK(&qu, &b1, next);
  SLIST_PUSH_BACK(&qu, &b2, next);

  block_t* res = NULL;
  block_t* front = NULL;

  SLIST_FOREACH(res, &qu, next, {
    front = SLIST_PEEK_FRONT(&qu, next);
    (void)front;

    res->elem += 1;
  });

  printf("[ ");

  SLIST_POP_FRONT(&qu, res, next);
  printf("%d ", res->elem);

  SLIST_POP_FRONT(&qu, res, next);
  printf("%d ", res->elem);

  SLIST_POP_FRONT(&qu, res, next);
  printf("%d ", res->elem);

  printf("]\n");

  return 0;
}
