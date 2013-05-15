#include "../include/queue.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    QUEUE_LINK(block, next);

    int elem;
} block_t;

QUEUE_NEW(queue, block);

static queue qu = QUEUE_STATIC_INIT;


static void block_init(block_t *blk, int elem) {
    assert(blk != NULL);

    blk->elem = elem;
    QUEUE_ELEM_INIT(blk, next);
}


int main(void) {
    block_t b0;
    block_init(&b0, 0);

    block_t b1;
    block_init(&b1, 1);

    block_t b2;
    block_init(&b2, 2);

    QUEUE_ENQUEUE(&qu, &b0, next);
    QUEUE_ENQUEUE(&qu, &b1, next);
    QUEUE_ENQUEUE(&qu, &b2, next);

    block_t *res = NULL;
    QUEUE_FOREACH(res, &qu, next) {
        block_t *head = QUEUE_PEEK(&qu);
        (void)head;

        res->elem += 1;
    }

    printf("[ ");
    QUEUE_DEQUEUE(res, &qu, next);
    printf("%d ", res->elem);
    QUEUE_DEQUEUE(res, &qu, next);
    printf("%d ", res->elem);
    QUEUE_DEQUEUE(res, &qu, next);
    printf("%d ", res->elem);
    printf("]\n");

    return 0;
}
