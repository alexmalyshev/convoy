/** @file deque.c
 *  @brief A deque library.
 *
 *  Implemented as a doubly linked list, we malloc a node every time we insert
 *  a new element into the deque and free the node that wraps around the
 *  front or back element when we call <tt>deque_removeb</tt> or
 *  <tt>deque_removef</tt>.
 *
 *  @author Alexander Malyshev
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

int deque_clear(deque *deq) {
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
    return deq->back->elem;
}

void *deque_peekf(deque *deq) {
    if (deq == NULL || deq->front == NULL)
        return NULL;
    return deq->front->elem;
}

void *deque_removeb(deque *deq) {
    dnode *dead;
    void *elem;

    if (deq == NULL || deq->back == NULL)
        return NULL;

    dead = deq->back;
    elem = dead->elem;
    deq->back = dead->prev;
    if (deq->back == NULL)
        deq->front = NULL;
    else
        deq->back->next = NULL;
    free(dead);
    --(deq->len);
    return elem;
}

void *deque_removef(deque *deq) {
    dnode *dead;
    void *elem;

    if (deq == NULL || deq->front == NULL)
        return NULL;

    dead = deq->front;
    elem = dead->elem;
    deq->front = dead->next;
    if (deq->front == NULL)
        deq->back = NULL;
    else
        deq->front->prev = NULL;
    free(dead);
    --(deq->len);
    return elem;
}

static dnode *init_node(void *elem) {
    dnode *node;

    if ((node = malloc(sizeof(dnode))) == NULL)
        return NULL;

    node->elem = elem;
    return node;
}
