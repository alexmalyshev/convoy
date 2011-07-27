/** @file queue-int.h
 *  @brief Function prototypes for internal functions in the queue library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef QUEUE_INT_H_
#define QUEUE_INT_H_

/** @brief Allocates a new qnode with elem as its element.
 *  @param elem the address of the element we want the new node to store.
 *  @return A pointer to a new qnode.
 */
static qnode *init_node(void *elem);

#endif
