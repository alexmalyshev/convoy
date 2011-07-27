/** @file deque.c
 *  @brief A deque library.
 *
 *  Implemented as a doubly linked list, we malloc a node every time we insert
 *  a new element into the deque and free the node that wraps around the
 *  front or back element when we call deque_removeb or deque_removef.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "deque.h"
#include "deque-int.h"

int deque_init(deque *deq) {
    if (deq == NULL)
        return 1;

    deq->front = NULL;
    deq->back = NULL;
    deq->len = 0;
    return 0;
}

int deque_destroy(deque *deq) {
    dnode *dead, *node;

    if (deq == NULL)
        return 1;

    node = deq->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    deq->len = 0;
    deq->front = NULL;
    deq->back = NULL;
    return 0;
}

int deque_insertb(deque *deq, void *elem) {
    dnode *new;

    if (deq == NULL || elem == NULL)
        return 1;

    if ((new = init_node(elem)) == NULL)
        return 1;
    new->prev = deq->back;
    new->next = NULL;
    deq->back = new;
    if (deq->front == NULL)
        deq->front = new;
    else
        new->prev->next = new;
    ++(deq->len);
    return 0;
}

int deque_insertf(deque *deq, void *elem) {
    dnode *new;

    if (deq == NULL || elem == NULL)
        return 1;

    if ((new = init_node(elem)) == NULL)
        return 1;
    new->next = deq->front;
    new->prev = NULL;
    deq->front = new;
    if (deq->back == NULL)
        deq->back = new;
    else
        new->next->prev = new;
    ++(deq->len);
    return 0;
}

void *deque_peekb(deque *deq) {
    if (deq == NULL || deq->back == NULL)
        return NULL;
    return deq->back->data;
}

void *deque_peekf(deque *deq) {
    if (deq == NULL || deq->front == NULL)
        return NULL;
    return deq->front->data;
}

void *deque_removeb(deque *deq) {
    dnode *dead;
    void *data;

    if (deq == NULL || deq->back == NULL)
        return NULL;

    dead = deq->back;
    data = dead->data;
    deq->back = dead->prev;
    if (deq->back == NULL)
        deq->front = NULL;
    else
        deq->back->next = NULL;
    --(deq->len);
    return data;
}

void *deque_removef(deque *deq) {
    dnode *dead;
    void *data;

    if (deq == NULL || deq->front == NULL)
        return NULL;

    dead = deq->front;
    data = dead->data;
    deq->front = dead->next;
    if (deq->front == NULL)
        deq->back = NULL;
    else
        deq->front->prev = NULL;
    --(deq->len);
    return data;
}

static dnode *init_node(void *elem) {
    dnode *node;

    if ((node = malloc(sizeof(dnode))) == NULL)
        return NULL;

    node->data = elem;
    return node;
}
