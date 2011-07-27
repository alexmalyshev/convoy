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

/** @brief A node in a linked list. */
typedef struct qnode_t {
    void *data;             /**< the element of data stored in the node. */
    struct qnode_t *next;   /**< the next node in the list. */
} qnode;

/** @brief A queue. */
typedef struct {
    qnode *front;           /**< the first node in the queue. */
    qnode *back;            /**< the last node in the queue. */
    size_t len;             /**< the number of elements in the queue. */
} queue;

/** @brief Initializes a new queue.
 *
 *  Will fail and return 1 if qu is NULL.
 *
 *  @param qu the address of the queue we want to initialize.
 *  @return Success status.
 */
int queue_init(queue *qu);

/** @brief Removes all the elements from qu.
 *
 *  Frees all nodes in the linked list in qu but will not free the
 *  elements in the nodes.
 *
 *  @param qu the address of the queue we want to clear out.
 *  @return Success status.
 */
int queue_clear(queue *qu);

/** @brief Removes the front element of qu if it exists and returns it.
 *
 *  Will fail and return NULL if qu is NULL.
 *
 *  @param qu the address of the queue we want to remove the front from.
 *  @return The front element of qu if it exists, NULL if qu is empty.
 */
void *queue_dequeue(queue *qu);

/** @brief Inserts elem as the new back of qu.
 *
 *  Will fail and return 1 if qu is NULL or elem is NULL.
 *
 *  @param qu the address of the queue we want to insert elem into.
 *  @param elem the element we want to insert as the new back of qu.
 *  @return Success status.
 */
int queue_enqueue(queue *qu, void *elem);

/** @brief Returns the front element of qu if it exists.
 *
 *  Will return NULL if qu is NULL.
 *
 *  @param qu the address of the queue we want to peek into.
 *  @return The front element of qu if it exists, NULL if qu is empty.
 */
void *queue_peek(queue *qu);

#endif /* QUEUE_H_ */
