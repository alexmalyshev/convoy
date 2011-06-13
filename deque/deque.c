#include <stdlib.h>
#include "deque.h"
#include "deque-int.h"

/* deque_init - allocs a new empty deque at *d
 * Fails: d is NULL, or calloc fails */
int deque_init(deque **d) {
    if (d == NULL)
        return 1;
    if ((*d = calloc(1, sizeof(deque))) == NULL)
        return 1;
    return 0;
}

/* deque_destroy - clears out all elements from d and frees their associated
                   nodes as well as the deque struct itself
 * Warning: Will cause memory leaks if the elements in the deque were malloc'd
            and never get free'd after this function call
 * Fails: d is NULL */
int deque_destroy(deque *d) {
    if (deque_clear(d))
        return 1;
    free(d);
    return 0;
}

/* deque_insertb - inserts elem as the new back of d
 * Fails: d is NULL or elem is NULL, or if malloc in init_node fails */
int deque_insertb(deque *d, void *elem) {
    dnode *new;

    if (d == NULL || elem == NULL)
        return 1;

    if (init_node(&new, elem))
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

/* deque_insertf - inserts elem as the new front of d
 * Fails: d is NULL or elem is NULL, or if malloc in init_node fails */
int deque_insertf(deque *d, void *elem) {
    dnode *new;

    if (d == NULL || elem == NULL)
        return 1;

    if (init_node(&new, elem))
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

/* deque_peekb - returns the back element of d if it exists, NULL if d is
                 empty
 * Fails: d is NULL */
void *deque_peekb(deque *d) {
    if (d == NULL || d->back == NULL)
        return NULL;
    return d->back->data;
}

/* deque_peekf - returns the front element of d if it exists, NULL if d is
                 empty
 * Fails: d is NULL */
void *deque_peekf(deque *d) {
    if (d == NULL || d->front == NULL)
        return NULL;
    return d->front->data;
}

/* deque_removeb - removes the back element of d and returns it if it exists,
                   returns NULL if d is empty
 * Fails: d is NULL */
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

/* deque_removef - removes the front element of d and returns it if it exists,
                   returns NULL if d is empty
 * Fails: d is NULL */
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

/* deque_clear - clears out all elements from d and frees their associated
                 nodes
 * Warning: Will cause memory leaks if the elements in the deque were malloc'd
            and never get free'd after this function call
 * Fails: d is NULL */
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

/* init_node - allocs a new dnode at *node with elem as the data, does not
               specify values of prev or next for node
 * Invariant: node is not NULL, elem is not NULL
 * Fails: if malloc fails */
static int init_node(dnode **node, void *elem) {
    if ((*node = malloc(sizeof(dnode))) == NULL)
        return 1;
    (*node)->data = elem;
    return 0;
}
