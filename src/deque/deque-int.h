/** @file deque-int.h
 *  @brief Function prototypes for internal functions in the <tt>deque</tt>
 *         library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef DEQUE_INT_H_
#define DEQUE_INT_H_

/** @brief Allocates a new <tt>dnode</tt> with <tt>elem</tt> as its element.
 *  @param elem the address of the element we want the new node to store.
 *  @return A pointer to a new <tt>dnode</tt>.
 */
static dnode *init_node(void *elem);

#endif /* DEQUE_INT_H_ */
