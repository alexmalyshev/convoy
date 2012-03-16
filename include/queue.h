/** @file queue.h
 *  @brief Header for a queue data structure library.
 *
 *  A <tt>queue</tt> is a singly linked list with a tail reference. Elements
 *  are stored as generic pointers (<tt>void *</tt>), however <tt>NULL</tt>
 *  cannot be stored. Getting a <tt>NULL</tt> back as an element from a
 *  <tt>queue</tt> means that the <tt>queue</tt> is empty or that there was an
 *  error.
 *
 *  @author Alexander Malyshev
 */


#ifndef __QUEUE_H__
#define __QUEUE_H__


#include <stddef.h>


/** @brief A node in a singly linked list */
typedef struct qnode_t {
    struct qnode_t *next;   /**< the next node */
    void *elem;             /**< the element */
} qnode;


/** @brief A queue */
typedef struct {
    qnode *front;           /**< the first node */
    qnode *back;            /**< the last node */
    size_t len;             /**< the number of elements */
} queue;


/** @brief Initializes a new <tt>queue</tt>
 *
 *  @param qu the address of the <tt>queue</tt>
 *
 *  @return Success status
 */
int queue_init(queue *qu);


/** @brief Removes all the elements from <tt>qu</tt>
 *
 *  @param qu the address of the <tt>queue</tt>
 *
 *  @return Success status
 */
int queue_clear(queue *qu);


/** @brief Removes the front element of <tt>qu</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>qu</tt> is empty
 *
 *  @param qu the address of the <tt>queue</tt>
 *
 *  @return The front element of <tt>qu</tt>
 */
void *queue_dequeue(queue *qu);


/** @brief Inserts <tt>elem</tt> as the new back of <tt>qu</tt>
 *
 *  @param qu the address of the <tt>queue</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int queue_enqueue(queue *qu, void *elem);


/** @brief Returns the front element of <tt>qu</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>qu</tt> is empty
 *
 *  @param qu the address of the <tt>queue</tt>
 *
 *  @return The front element of <tt>qu</tt>
 */
void *queue_peek(queue *qu);


#endif /* __QUEUE_H__ */
