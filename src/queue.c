/** @file queue.c
 *  @brief A queue library.
 *
 *  Implemented as a singly linked list with a tail reference, we malloc a node
 *  every time we enqueue a new element onto the queue and free the node that
 *  wraps around the front element when we call <tt>queue_dequeue</tt>.
 *
 *  @author Alexander Malyshev
 */

#include "queue.h"

#include <assert.h>
#include <stdlib.h>

static qnode *init_node(void *elem);


void queue_init(queue *qu) {
    assert(qu != NULL);

    /* set the queue's fields to be empty */
    qu->front = NULL;
    qu->back = NULL;
    qu->len = 0;
}

void queue_clear(queue *qu) {
    qnode *node;
    qnode *dead;

    assert(qu != NULL);

    /* loop through all nodes in the queue and free them */
    node = qu->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }

    /* set the queue's fields to be empty */
    qu->front = NULL;
    qu->back = NULL;
    qu->len = 0;
}

void *queue_dequeue(queue *qu) {
    qnode *dead;
    void *elem;

    assert(qu != NULL);

    /* "good" empty queue means we return NULL */
    if (qu->front == NULL || qu->back == NULL || qu->len == 0) {
        assert(qu->front == NULL && qu->back == NULL && qu->len == 0);
        return NULL;
    }

    /* pull out the front node */
    dead = qu->front;
    qu->front = dead->next;

    /* if the queue only had one element, then make
     * sure to set its back node to NULL */
    if (qu->front == NULL)
        qu->back = NULL;

    /* get the front element */
    elem = dead->elem;

    /* free the front node */
    free(dead);

    /* update length */
    --(qu->len);

    return elem;
}

void queue_enqueue(queue *qu, void *elem) {
    qnode *new;

    assert(qu != NULL);
    assert(elem != NULL);

    /* make our new node */
    new = init_node(elem);

    /* if the queue is non-empty, set its back node's next pointer to be our
     * new node. otherwise, set the queue's front pointer to our new node */
    if (qu->front != NULL)
        qu->back->next = new;
    else
        qu->front = new;

    /* our new node is the new back node of the queue */
    qu->back = new;

    /* update length */
    ++(qu->len);
}

void *queue_peek(queue *qu) {
    assert(qu != NULL);

    /* "good" empty queue means we return NULL */
    if (qu->front == NULL || qu->back == NULL || qu->len == 0) {
        assert(qu->front == NULL && qu->back == NULL && qu->len == 0);
        return NULL;
    }

    /* otherwise return the front element */
    return qu->front->elem;
}

static qnode *init_node(void *elem) {
    assert(elem != NULL);

    qnode *node = malloc(sizeof(qnode));
    assert(node != NULL);

    /* initialize the node's element to 'elem' and its next pointer to NULL */
    node->elem = elem;
    node->next = NULL;

    return node;
}
