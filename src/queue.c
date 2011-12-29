/** @file queue.c
 *  @brief A queue library.
 *
 *  Implemented as a singly linked list with a tail reference, we malloc a node
 *  every time we enqueue a new element onto the queue and free the node that
 *  wraps around the front element when we call <tt>queue_dequeue</tt>.
 *
 *  @author Alexander Malyshev
 */

#include <assert.h>
#include <stdlib.h>
#include "queue.h"

static qnode *init_node(void *elem);

void queue_init(queue *qu) {
    assert(qu != NULL);

    qu->front = NULL;
    qu->back = NULL;
    qu->len = 0;
}

void queue_clear(queue *qu) {
    qnode *node, *dead;

    assert(qu != NULL);

    node = qu->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    qu->front = NULL;
    qu->back = NULL;
    qu->len = 0;
}

void *queue_dequeue(queue *qu) {
    qnode *dead;
    void *elem;

    assert(qu != NULL);

    if (qu->front == NULL)
        return NULL;

    dead = qu->front;
    qu->front = dead->next;
    if (qu->front == NULL)
        qu->back = NULL;
    elem = dead->elem;
    free(dead);
    --(qu->len);
    return elem;
}

void queue_enqueue(queue *qu, void *elem) {
    qnode *new;

    assert(qu != NULL);
    assert(elem != NULL);

    new = init_node(elem);

    if (qu->front != NULL)
        qu->back->next = new;
    else
        qu->front = new;
    qu->back = new;
    ++(qu->len);
}

void *queue_peek(queue *qu) {
    assert(qu != NULL);

    if (qu->front == NULL)
        return NULL;

    return qu->front->elem;
}

static qnode *init_node(void *elem) {
    qnode *node = malloc(sizeof(qnode));
    assert(node != NULL);

    node->elem = elem;
    node->next = NULL;
    return node;
}
