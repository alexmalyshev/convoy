/** @file queue-int.h
 *  @brief Function prototypes for internal functions in the <tt>queue</tt>
 *         library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef QUEUE_INT_H_
#define QUEUE_INT_H_

/** @brief Allocates a new <tt>qnode</tt> with <tt>elem</tt> as its element.
 *  @param elem the address of the element we want the new node to store.
 *  @return A pointer to a new <tt>qnode</tt>.
 */
static qnode *init_node(void *elem);

#endif
