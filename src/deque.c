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

#include "deque.h"

#include <assert.h>
#include <stdlib.h>

static dnode *init_node(void *elem);


void deque_init(deque *deq) {
    assert(deq != NULL);

    /* set the deque's fields to be empty */
    deq->front = NULL;
    deq->back = NULL;
    deq->len = 0;
}

void deque_clear(deque *deq) {
    dnode *dead;
    dnode *node;

    assert(deq != NULL);

    /* loop through all nodes in the deque and free them */
    node = deq->front;
    while (node != NULL) {
        dead = node;
        node = node->next;
        free(dead);
    }

    /* set the deque's fields to be empty */
    deq->len = 0;
    deq->front = NULL;
    deq->back = NULL;
}

void deque_insertb(deque *deq, void *elem) {
    dnode *new;

    assert(deq != NULL);
    assert(elem != NULL);

    /* make our new node */
    new = init_node(elem);

    /* set our new node as the new back node of the deque */
    new->prev = deq->back;
    new->next = NULL;
    deq->back = new;

    /* if the deque is non-empty, set the old back node's next pointer to our
     * new node. otherwise, set the deque's front pointer to our new node */
    if (deq->front != NULL)
        new->prev->next = new;
    else
        deq->front = new;

    /* update length */
    ++(deq->len);
}

void deque_insertf(deque *deq, void *elem) {
    dnode *new;

    assert(deq != NULL);
    assert(elem != NULL);

    /* make our new node */
    new = init_node(elem);

    /* set our new node as the new front node of the deque */
    new->next = deq->front;
    new->prev = NULL;
    deq->front = new;

    /* if the deque is non-empty, set the old front node's prev pointer to our
     * new node. otherwise, set the deque's back pointer to our new node */
    if (deq->back != NULL)
        new->next->prev = new;
    else
        deq->back = new;

    /* update length */
    ++(deq->len);
}

void *deque_peekb(deque *deq) {
    assert(deq != NULL);

    /* "good" empty deque means we return NULL */
    if (deq->front == NULL || deq->back == NULL || deq->len == 0) {
        assert(deq->front == NULL && deq->back == NULL && deq->len == 0);
        return NULL;
    }

    /* otherwise return the back element */
    return deq->back->elem;
}

void *deque_peekf(deque *deq) {
    assert(deq != NULL);

    /* "good" empty deque means we return NULL */
    if (deq->front == NULL || deq->back == NULL || deq->len == 0) {
        assert(deq->front == NULL && deq->back == NULL && deq->len == 0);
        return NULL;
    }

    /* otherwise return the front element */
    return deq->front->elem;
}

void *deque_removeb(deque *deq) {
    dnode *dead;
    void *elem;

    assert(deq != NULL);

    /* "good" empty deque means we return NULL */
    if (deq->front == NULL || deq->back == NULL || deq->len == 0) {
        assert(deq->front == NULL && deq->back == NULL && deq->len == 0);
        return NULL;
    }

    /* pull out the back node */
    dead = deq->back;
    deq->back = dead->prev;

    /* if the deque only had one element, then make sure to set its front
     * node to NULL. otherwise set its new back node's next pointer to NULL */
    if (deq->back == NULL)
        deq->front = NULL;
    else
        deq->back->next = NULL;

    /* get the back element */
    elem = dead->elem;

    /* free the back node */
    free(dead);

    /* update length */
    --(deq->len);

    return elem;
}

void *deque_removef(deque *deq) {
    dnode *dead;
    void *elem;

    assert(deq != NULL);

    /* "good" empty deque means we return NULL */
    if (deq->front == NULL || deq->back == NULL || deq->len == 0) {
        assert(deq->front == NULL && deq->back == NULL && deq->len == 0);
        return NULL;
    }

    /* pull out the front node */
    dead = deq->front;
    deq->front = dead->next;

    /* if the deque only had one element, then make sure to set its back
     * node to NULL. otherwise set its new front node's prev pointer to NULL */
    if (deq->front == NULL)
        deq->back = NULL;
    else
        deq->front->prev = NULL;

    /* get the front element */
    elem = dead->elem;

    /* free the front node */
    free(dead);

    /* update length */
    --(deq->len);

    return elem;
}

static dnode *init_node(void *elem) {
    assert(elem != NULL);

    dnode *node = malloc(sizeof(dnode));
    assert(node != NULL);

    /* initialize the node's element to 'elem' and its prev
     * and next pointers to NULL */
    node->elem = elem;
    node->prev = NULL;
    node->next = NULL;

    return node;
}
