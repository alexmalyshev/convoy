/** @file queue.c
 *  @brief A queue library.
 *
 *  Implemented as a singly linked list with a tail reference, we malloc a node
 *  every time we enqueue a new element onto the queue and free the node that
 *  wraps around the front element when we call <tt>queue_dequeue</tt>.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "queue.h"
#include "queue-int.h"

int queue_init(queue *qu) {
    if (qu == NULL)
        return 1;

    qu->front = NULL;
    qu->back = NULL;
    qu->len = 0;
    return 0;
}

int queue_clear(queue *qu) {
    qnode *node, *dead;

    if (qu == NULL)
        return 1;

    node = qu->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    qu->front = NULL;
    qu->back = NULL;
    qu->len = 0;
    return 0;
}

void *queue_dequeue(queue *qu) {
    qnode *dead;
    void *elem;

    if (qu == NULL || qu->front == NULL)
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

int queue_enqueue(queue *qu, void *elem) {
    qnode *new;

    if (qu == NULL || elem == NULL)
        return 1;

    if ((new = init_node(elem)) == NULL)
        return 1;
    if (qu->front != NULL)
        qu->back->next = new;
    else
        qu->front = new;
    qu->back = new;
    ++(qu->len);
    return 0;
}

void *queue_peek(queue *qu) {
    if (qu == NULL || qu->front == NULL)
        return NULL;

    return qu->front->elem;
}

static qnode *init_node(void *elem) {
    qnode *node;

    if ((node = malloc(sizeof(qnode))) == NULL)
        return NULL;

    node->elem = elem;
    node->next = NULL;
    return node;
}
