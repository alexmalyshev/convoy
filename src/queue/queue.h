/** @file queue.h
 *  @brief Header for a queue data structure library.
 *
 *  A <tt>queue</tt> is a singly linked list with a tail reference. Elements
 *  are stored as generic pointers (<tt>void *</tt>), however <tt>NULL</tt>
 *  cannot be stored. Inserting an element into a <tt>queue</tt> will always
 *  succeed provided there is enough memory on the system. Getting a
 *  <tt>NULL</tt> back as an element from a <tt>queue</tt> means that the
 *  <tt>queue</tt> is empty.
 *
 *  @author Alexander Malyshev
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>

/** @brief A node in a singly linked list. */
typedef struct qnode_t {
    struct qnode_t *next;   /**< the next node. */
    void *elem;             /**< the element. */
} qnode;

/** @brief A queue. */
typedef struct {
    qnode *front;           /**< the first node. */
    qnode *back;            /**< the last node. */
    size_t len;             /**< the number of elements. */
} queue;

/** @brief Initializes a new <tt>queue</tt>.
 *
 *  Asserts that <tt>qu</tt> is not <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt>.
 */
void queue_init(queue *qu);

/** @brief Removes all the elements from <tt>qu</tt>.
 *
 *  Asserts <tt>qu</tt> is not <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt>.
 */
void queue_clear(queue *qu);

/** @brief Removes the front element of <tt>qu</tt>.
 *
 *  Asserts that <tt>qu</tt> is not <tt>NULL</tt>.
 *  Returns <tt>NULL</tt> if <tt>qu</tt> is empty.
 *
 *  @param qu the address of the <tt>queue</tt>.
 *  @return The front element of <tt>qu</tt>.
 */
void *queue_dequeue(queue *qu);

/** @brief Inserts <tt>elem</tt> as the new back of <tt>qu</tt>.
 *
 *  Asserts that <tt>qu</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *
 *  @param qu the address of the <tt>queue</tt>.
 *  @param elem the element.
 */
void queue_enqueue(queue *qu, void *elem);

/** @brief Returns the front element of <tt>qu</tt>.
 *
 *  Asserts that <tt>qu</tt> is not <tt>NULL</tt>.
 *  Returns <tt>NULL</tt> if <tt>qu</tt> is empty.
 *
 *  @param qu the address of the <tt>queue</tt>.
 *  @return The front element of <tt>qu</tt>.
 */
void *queue_peek(queue *qu);

#endif /* QUEUE_H_ */
