/** @file deque.h
 *  @brief Function prototypes and structs for a deque data structure.
 *
 *  Implementation of a double-ended queue(deque) that is backed by a
 *  doubly linked list. The nodes in the linked list store data as
 *  generic pointers (<tt>void *</tt>) where an element value of <tt>NULL</tt>
 *  cannot be stored.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef DEQUE_H_
#define DEQUE_H_

/** @brief A node in a linked list. */
typedef struct dnode_t {
    struct dnode_t *prev;   /**< the previous node in the list. */
    struct dnode_t *next;   /**< the next node in the list. */
    void *elem;             /**< the element stored in the node. */
} dnode;

/** @brief A double-ended queue. */
typedef struct {
    dnode *front;           /**< the first node in the deque. */
    dnode *back;            /**< the last node in the deque. */
    size_t len;             /**< the number of elements in the deque. */
} deque;

/** @brief Initializes a new <tt>deque</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>deq</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to initialize.
 *  @return Success status.
 */
int deque_init(deque *deq);

/** @brief Removes all elements from <tt>deq</tt>.
 *
 *  Frees all nodes in the linked list in <tt>deq</tt> but will not free the
 *  elements in the nodes.
 *
 *  @param deq the address of the <tt>deque</tt> we want to clear out.
 *  @return Success status.
 */
int deque_clear(deque *deq);

/** @brief Inserts <tt>elem</tt> as the new back of <tt>deq</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>deq</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to insert
 *             <tt>elem</tt> into.
 *  @param elem the element we want to insert as the new back of <tt>deq</tt>.
 *  @return Success status.
 */
int deque_insertb(deque *deq, void *elem);

/** @brief Inserts <tt>elem</tt> as the new front element of <tt>deq</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>deq</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to insert
 *             <tt>elem</tt> into.
 *  @param elem the element we want to insert as the new front of <tt>deq</tt>.
 *  @return Success status.
 */
int deque_insertf(deque *deq, void *elem);

/** @brief Returns the back element of <tt>deq</tt> if it exists.
 *
 *  Will return <tt>NULL</tt> if <tt>deq</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to peek into.
 *  @return The back element of <tt>deq</tt> if it exists, <tt>NULL</tt> if
 *          <tt>deq</tt> is empty.
 */
void *deque_peekb(deque *deq);

/** @brief Returns the front element of <tt>deq</tt> if it exists.
 *
 *  Will return <tt>NULL</tt> if <tt>deq</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to peek into.
 *  @return The front element of <tt>deq</tt> if it exists, <tt>NULL</tt> if
 *          <tt>deq</tt> is empty.
 */
void *deque_peekf(deque *deq);

/** @brief Removes the back element of <tt>deq</tt> if it exists and returns
 *         it.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>deq</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to remove the back
 *             from.
 *  @return The back element of <tt>deq</tt> if it exists, <tt>NULL</tt> if
 *          <tt>deq</tt> is empty.
 */
void *deque_removeb(deque *deq);

/** @brief Removes the front element of <tt>deq</tt> if it exists and returns
 *         it.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>deq</tt> is <tt>NULL</tt>.
 *
 *  @param deq the address of the <tt>deque</tt> we want to remove the front
 *             from.
 *  @return The front element of <tt>deq</tt> if it exists, <tt>NULL</tt> if
 *          <tt>deq</tt> is empty.
 */
void *deque_removef(deque *deq);

#endif /* DEQUE_H_ */
