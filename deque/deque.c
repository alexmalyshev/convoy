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

deque *deque_init(void) {
    return calloc(1, sizeof(deque));
}

int deque_destroy(deque *d) {
    if (deque_clear(d))
        return 1;
    free(d);
    return 0;
}

int deque_insertb(deque *d, void *elem) {
    dnode *new;

    if (d == NULL || elem == NULL)
        return 1;

    if ((new = init_node(elem)) == NULL)
        return 1;
    new->prev = d->back;
    new->next = NULL;
    d->back = new;
    if (d->front == NULL)
        d->front = new;
    else
        new->prev->next = new;
    ++(d->len);
    return 0;
}

int deque_insertf(deque *d, void *elem) {
    dnode *new;

    if (d == NULL || elem == NULL)
        return 1;

    if ((new = init_node(elem)) == NULL)
        return 1;
    new->next = d->front;
    new->prev = NULL;
    d->front = new;
    if (d->back == NULL)
        d->back = new;
    else
        new->next->prev = new;
    ++(d->len);
    return 0;
}

void *deque_peekb(deque *d) {
    if (d == NULL || d->back == NULL)
        return NULL;
    return d->back->data;
}

void *deque_peekf(deque *d) {
    if (d == NULL || d->front == NULL)
        return NULL;
    return d->front->data;
}

void *deque_removeb(deque *d) {
    dnode *dead;
    void *data;

    if (d == NULL || d->back == NULL)
        return NULL;

    dead = d->back;
    data = dead->data;
    d->back = dead->prev;
    if (d->back == NULL)
        d->front = NULL;
    else
        d->back->next = NULL;
    --(d->len);
    return data;
}

void *deque_removef(deque *d) {
    dnode *dead;
    void *data;

    if (d == NULL || d->front == NULL)
        return NULL;

    dead = d->front;
    data = dead->data;
    d->front = dead->next;
    if (d->front == NULL)
        d->back = NULL;
    else
        d->front->prev = NULL;
    --(d->len);
    return data;
}

int deque_clear(deque *d) {
    dnode *dead, *node;

    if (d == NULL)
        return 1;

    node = d->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }
    d->len = 0;
    d->front = NULL;
    d->back = NULL;
    return 0;
}

static dnode *init_node(void *elem) {
    dnode *node;

    if ((node = malloc(sizeof(dnode))) == NULL)
        return NULL;

    node->data = elem;
    return node;
}
