#include <stdlib.h>
#include "queue.h"
#include "queue-int.h"

/* queue_clear - removes all the items from the given queue and frees all
                 corresponding nodes
 * Fails: q is NULL */
int queue_clear(queue *q) {
    qnode *node, *deadnode;

    if (q == NULL)
        return 1;

    node = q->front;
    while (node != NULL) {
        deadnode = node;
        node = node->next;
        free(deadnode);
    }
    q->front = NULL;
    q->back = NULL;
    q->len = 0;
    return 0;
}

/* queue_dequeue - removes the item in the front of the given queue and returns
                   it, freeing the node that stored it
 * Fails: q is NULL */
void *queue_dequeue(queue *q) {
    qnode *deadnode;
    void *item;

    if (q == NULL || q->front == NULL)
        return NULL;

    deadnode = q->front;
    q->front = deadnode->next;
    if (q->front == NULL)
        q->back = NULL;
    item = deadnode->data;
    free(deadnode);
    --(q->len);
    return item;
}

/* queue_destroy - clears out the queue of all items, frees all nodes as well
                   as the queue struct itself
 * Fails: q is NULL */
int queue_destroy(queue *q) {
    if (queue_clear(q))
        return 1;
    free(q);
    return 0;
}

/* queue_enqueue - adds the given item to the back of the given queue
 * Fails: q is NULL or item is NULL, or if malloc fails in init_node */
int queue_enqueue(queue *q, void *item) {
    qnode *newnode;

    if (q == NULL || item == NULL)
        return 1;

    if (init_node(&newnode, item))
        return 1;
    if (q->front != NULL)
        q->back->next = newnode;
    else
        q->front = newnode;
    q->back = newnode;
    ++(q->len);
    return 0;
}

/* queue_init - allocs and initializes a new empty queue at *q
 * Fails: q is NULL, or calloc fails */
int queue_init(queue **q) {
    if (q == NULL)
        return 1;
    if ((*q = calloc(1, sizeof(queue))) == NULL)
        return 1;
    return 0;
}

/* queue_peek - returns the first item in the given queue if it exists,
                NULL if the queue is empty
 * Fails: q is NULL or q is empty */
void *queue_peek(queue *q) {
    if (q == NULL || q->front == NULL)
        return NULL;
    return q->front->data;
}

/* init_node - allocs a new qnode with the given item as the data
 * Invariant: node is not NULL, item is not NULL
 * Fails: calloc fails */
static int init_node(qnode **node, void *item) {
    if ((*node = calloc(1, sizeof(qnode))) == NULL)
        return 1;
    (*node)->data = item;
    return 0;
}

/* queue_len - returns the length of the given queue
 * Fails: q is NULL */
long queue_len(queue *q) {
    if (q == NULL)
        return -1;
    return q->len;
}
