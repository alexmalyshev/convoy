#ifndef QUEUE_H_
#define QUEUE_H_

/*
    Alexander Malyshev - queue.h

    Implementation of a FIFO queue. Pointers to elements are stored in
    nodes and the entire queue is represented by a singly-linked list
    with a tail reference. NULL cannot be stored.
*/

/* a qnode holds onto the data given to the queue as well as a pointer to
   the next node */
typedef struct qnode_t {
    void *data;
    struct qnode_t *next;
} qnode;

/* a queue is just a linked list of nodes, where front is the first element
   and back is the last */
typedef struct {
    qnode *front;
    qnode *back;
    long len;
} queue;

/* set up */
int queue_init(queue **);
int queue_destroy(queue *);

/* standard queue methods */
void *queue_dequeue(queue *);
int queue_enqueue(queue *, void *);
void *queue_peek(queue *);

/* auxiliary */
int queue_clear(queue *);
long queue_len(queue *);

#endif
