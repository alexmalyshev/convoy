/** @file queue.h
 *  @brief Function prototypes and structs for a queue data structure.
 *
 *  Implementation of a FIFO queue that is backed by a singly linked list
 *  with a tail reference. The nodes in the linked list store data as
 *  generic pointers (void *) where an element value of NULL cannot be stored.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/** @brief A node in a linked list.
 *
 *  Stores a pointer to an element and a pointer to the next node in the list.
 */
typedef struct qnode_t {
    void *data;
    struct qnode_t *next;
} qnode;

/** @brief A queue.
 *
 *  Implemented as a singly linked list with a tail reference that
 *  also stores its length.
 */
typedef struct {
    qnode *front;
    qnode *back;
    long len;
} queue;

/** @brief Allocates and initializes a new queue.
 *  @return A pointer to a new queue.
 */
queue *queue_init(void);

/** @brief Frees the linked list in q and q itself.
 *
 *  Will not free the elements stored in the nodes of q.
 *
 *  @param q the address of the queue we want to deallocate.
 *  @return Success status.
 */
int queue_destroy(queue *q);

/** @brief Removes the front element of q if it exists and returns it.
 *
 *  Will fail and return NULL if q is NULL.
 *
 *  @param q the address of the queue we want to remove the front element from.
 *  @return The front element of q if it exists, NULL if q is empty.
 */
void *queue_dequeue(queue *q);

/** @brief Inserts elem as the new back of q.
 *
 *  Will fail and return 1 if q is NULL or elem is NULL.
 *
 *  @param q the address of the queue we want to insert elem into.
 *  @param elem the element we want to insert as the new back of q.
 *  @return Success status.
 */
int queue_enqueue(queue *q, void *elem);

/** @brief Returns the front element of q if it exists.
 *
 *  Will return NULL if q is NULL.
 *
 *  @param q the address of the queue we're trying to peek into.
 *  @return The front element of q if it exists, NULL if q is empty.
 */
void *queue_peek(queue *q);

/** @brief Removes all elements from q.
 *
 *  Frees all nodes in the linked list in q, but will not free the
 *  elements in q or q itself.
 *
 *  @param q the address of the queue we're trying to clear out.
 *  @return Success status.
 */
int queue_clear(queue *q);

/** @brief Returns the number of elements in q.
 *
 *  If q is NULL will return -1, otherwise same behavior as q->len.
 *
 *  @param q the address of the queue whose length we want.
 *  @return The number of elements in q.
 */
long queue_len(queue *q);

#endif /* QUEUE_H_ */
