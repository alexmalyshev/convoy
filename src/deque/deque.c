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

#include <assert.h>
#include <stdlib.h>
#include "deque.h"

static dnode *init_node(void *elem);

void deque_init(deque *deq) {
    assert(deq != NULL);

    deq->front = NULL;
    deq->back = NULL;
    deq->len = 0;
}

void deque_clear(deque *deq) {
    dnode *dead, *node;

    assert(deq != NULL);

    node = deq->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    deq->len = 0;
    deq->front = NULL;
    deq->back = NULL;
}

void deque_insertb(deque *deq, void *elem) {
    dnode *new;

    assert(deq != NULL);
    assert(elem != NULL);

    new = init_node(elem);

    new->prev = deq->back;
    new->next = NULL;
    deq->back = new;
    if (deq->front == NULL)
        deq->front = new;
    else
        new->prev->next = new;
    ++(deq->len);
}

void deque_insertf(deque *deq, void *elem) {
    dnode *new;

    assert(deq != NULL);
    assert(elem != NULL);

    new = init_node(elem);

    new->next = deq->front;
    new->prev = NULL;
    deq->front = new;
    if (deq->back == NULL)
        deq->back = new;
    else
        new->next->prev = new;
    ++(deq->len);
}

void *deque_peekb(deque *deq) {
    assert(deq != NULL);

    if (deq->back != NULL)
        return NULL;
    return deq->back->elem;
}

void *deque_peekf(deque *deq) {
    assert(deq != NULL);

    if (deq->front == NULL)
        return NULL;
    return deq->front->elem;
}

void *deque_removeb(deque *deq) {
    dnode *dead;
    void *elem;

    assert(deq != NULL);

    if (deq->back == NULL)
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

    assert(deq != NULL);

    if (deq->front == NULL)
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
    dnode *node = malloc(sizeof(dnode));
    assert(node != NULL);
    node->elem = elem;
    return node;
}
