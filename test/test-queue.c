#include "../include/queue.h"

#include <stdio.h>


typedef struct block {
    QUEUE_LINK(block, next);

    int elem;
} block_t;

QUEUE_NEW(queue, block);

queue qu = QUEUE_STATIC_INIT;


int main(void) {
    block_t b0;
    b0.elem = 0;
    QUEUE_ELEM_INIT(&b0, next);

    block_t b1;
    b1.elem = 1;
    QUEUE_ELEM_INIT(&b1, next);

    block_t b2;
    b2.elem = 2;
    QUEUE_ELEM_INIT(&b2, next);

    QUEUE_ENQUEUE(&qu, &b0, next);
    QUEUE_ENQUEUE(&qu, &b1, next);
    QUEUE_ENQUEUE(&qu, &b2, next);

    block_t *res;

    QUEUE_FOREACH(res, &qu, next) {
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
