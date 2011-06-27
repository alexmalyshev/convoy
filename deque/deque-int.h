/** @file deque-int.h
 *  @brief Function prototypes for internal functions in the deque library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef DEQUE_INT_H_
#define DEQUE_INT_H_

/** @brief Allocates a new dnode with elem as its data.
 *  @param elem the address of the data we want the new node to store.
 *  @return A pointer to a new dnode.
 */
static dnode *init_node(void *elem);

#endif /* DEQUE_INT_H_ */
