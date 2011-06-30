/** @file queue.c
 *  @brief A queue library.
 *
 *  Implemented as a singly linked list with a tail reference, we malloc a node
 *  every time we enqueue a new element onto the queue and free the node that
 *  wraps around the front element when we call queue_dequeue.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "queue.h"
#include "queue-int.h"

queue *queue_init(void) {
    return calloc(1, sizeof(queue));
}

int queue_destroy(queue *q) {
    if (queue_clear(q))
        return 1;

    free(q);
    return 0;
}

void *queue_dequeue(queue *q) {
    qnode *dead;
    void *data;

    if (q == NULL || q->front == NULL)
        return NULL;

    dead = q->front;
    q->front = dead->next;
    if (q->front == NULL)
        q->back = NULL;
    data = dead->data;
    free(dead);
    --(q->len);
    return data;
}

int queue_enqueue(queue *q, void *elem) {
    qnode *new;

    if (q == NULL || elem == NULL)
        return 1;

    if ((new = init_node(elem)) == NULL)
        return 1;
    if (q->front != NULL)
        q->back->next = new;
    else
        q->front = new;
    q->back = new;
    ++(q->len);
    return 0;
}

void *queue_peek(queue *q) {
    if (q == NULL || q->front == NULL)
        return NULL;

    return q->front->data;
}

int queue_clear(queue *q) {
    qnode *node, *dead;

    if (q == NULL)
        return 1;

    node = q->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    q->front = NULL;
    q->back = NULL;
    q->len = 0;
    return 0;
}

long queue_len(queue *q) {
    if (q == NULL)
        return -1;

    return q->len;
}

static qnode *init_node(void *elem) {
    qnode *node;

    if ((node = malloc(sizeof(qnode))) == NULL)
        return NULL;

    node->data = elem;
    return node;
}
