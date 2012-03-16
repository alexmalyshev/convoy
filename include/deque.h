/** @file deque.h
 *  @brief Header for a deque (double-ended queue) data structure library.
 *
 *  A <tt>deque</tt> is a doubly linked list. Elements are stored as generic
 *  pointers (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored. Getting
 *  a <tt>NULL</tt> back as an element from a <tt>deque</tt> means that the
 *  <tt>deque</tt> is empty.
 *
 *  @author Alexander Malyshev
 */


#ifndef __DEQUE_H__
#define __DEQUE_H__


#include <stddef.h>


/** @brief A node in a doubly linked list */
typedef struct dnode_t {
    struct dnode_t *prev;   /**< the previous node */
    struct dnode_t *next;   /**< the next node */
    void *elem;             /**< the element */
} dnode;


/** @brief A double-ended queue */
typedef struct {
    dnode *front;           /**< the first node */
    dnode *back;            /**< the last node */
    size_t len;             /**< the number of elements */
} deque;


/** @brief Initializes a new <tt>deque</tt>
 *
 *  @param deq the address of the <tt>deque</tt>
 *
 *  @return Success status
 */
int deque_init(deque *deq);


/** @brief Removes all elements from <tt>deq</tt>
 *
 *  @param deq the address of the <tt>deque</tt>
 *
 *  @return Success status
 */
int deque_clear(deque *deq);


/** @brief Inserts <tt>elem</tt> as the new back of <tt>deq</tt>
 *
 *  @param deq the address of the <tt>deque</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int deque_insertb(deque *deq, void *elem);


/** @brief Inserts <tt>elem</tt> as the new front element of <tt>deq</tt>
 *
 *  @param deq the address of the <tt>deque</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int deque_insertf(deque *deq, void *elem);


/** @brief Returns the back element of <tt>deq</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>deq</tt> is empty
 *
 *  @param deq the address of the <tt>deque</tt>
 *
 *  @return The back element of <tt>deq</tt>
 */
void *deque_peekb(deque *deq);


/** @brief Returns the front element of <tt>deq</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>deq</tt> is empty
 *
 *  @param deq the address of the <tt>deque</tt>
 *
 *  @return The front element of <tt>deq</tt>
 */
void *deque_peekf(deque *deq);


/** @brief Removes the back element of <tt>deq</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>deq</tt> is empty
 *
 *  @param deq the address of the <tt>deque</tt>
 *
 *  @return The back element of <tt>deq</tt>
 */
void *deque_removeb(deque *deq);


/** @brief Removes the front element of <tt>deq</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>deq</tt> is empty
 *
 *  @param deq the address of the <tt>deque</tt>
 *
 *  @return The front element of <tt>deq</tt>
 */
void *deque_removef(deque *deq);


#endif /* __DEQUE_H__ */
