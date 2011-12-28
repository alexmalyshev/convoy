/** @file queue.h
 *  @brief Header for a queue data structure library.
 *
 *  Implementation of a FIFO queue that is backed by a singly linked list
 *  with a tail reference. The nodes in the linked list store data as
 *  generic pointers (<tt>void *</tt>) where an element value of <tt>NULL</tt>
 *  cannot be stored.
 *
 *  @author Alexander Malyshev
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>

/** @brief A node in a linked list. */
typedef struct qnode_t {
    struct qnode_t *next;   /**< the next node in the list. */
    void *elem;             /**< the element stored in the node. */
} qnode;

/** @brief A queue. */
typedef struct {
    qnode *front;           /**< the first node in the queue. */
    qnode *back;            /**< the last node in the queue. */
    size_t len;             /**< the number of elements in the queue. */
} queue;

/** @brief Initializes a new <tt>queue</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>qu</tt> is <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt> we want to initialize.
 *  @return Success status.
 */
int queue_init(queue *qu);

/** @brief Removes all the elements from <tt>qu</tt>.
 *
 *  Frees all nodes in the linked list in <tt>qu</tt> but will not free the
 *  elements in the nodes.
 *
 *  @param qu the address of the <tt>queue</tt> we want to clear out.
 *  @return Success status.
 */
int queue_clear(queue *qu);

/** @brief Removes the front element of <tt>qu</tt> if it exists and returns
 *         it.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>qu</tt> is <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt> we want to remove the front
 *            from.
 *  @return The front element of <tt>qu</tt> if it exists, <tt>NULL</tt> if
 *          <tt>qu</tt> is empty.
 */
void *queue_dequeue(queue *qu);

/** @brief Inserts <tt>elem</tt> as the new back of <tt>qu</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>qu</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt> we want to insert
 *            <tt>elem</tt> into.
 *  @param elem the element we want to insert as the new back of <tt>qu</tt>.
 *  @return Success status.
 */
int queue_enqueue(queue *qu, void *elem);

/** @brief Returns the front element of <tt>qu</tt> if it exists.
 *
 *  Will return <tt>NULL</tt> if <tt>qu</tt> is <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt> we want to peek into.
 *  @return The front element of <tt>qu</tt> if it exists, <tt>NULL</tt> if
 *          <tt>qu</tt> is empty.
 */
void *queue_peek(queue *qu);

#endif /* QUEUE_H_ */
