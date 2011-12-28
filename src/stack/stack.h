/** @file stack.h
 *  @brief Function prototypes and structs for a stack data structure.
 *
 *  Implementation of a LIFO stack that is backed by a singly linked list.
 *  The nodes in the linked list store data as generic pointers
 *  (<tt>void *</tt>) where an element value of <tt>NULL</tt> cannot be stored.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>

/** @brief A node in a linked list. */
typedef struct snode_t {
    struct snode_t *next;   /**< the next node in the list. */
    void *elem;             /**< the element stored in the node. */
} snode;

/** @brief A stack. */
typedef struct {
    snode *top;             /**< the top node in the stack. */
    size_t len;             /**< the number of elements in the stack. */
} stack;

/** @brief Initializes a new <tt>stack</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>stk</tt> is <tt>NULL</tt>.
 *
 *  @param stk the address of the <tt>stack</tt> we want to initialize.
 *  @return Success status.
 */
int stack_init(stack *stk);

/** @brief Removes all elements from <tt>stk</tt>.
 *
 *  Frees all the nodes in the linked list in <tt>stk</tt> but will not free
 *  the elements in the nodes.
 *
 *  @param stk the address of the <tt>stack</tt> we want to clear out.
 *  @return Success status.
 */
int stack_clear(stack *stk);

/** @brief Returns the top element of <tt>stk</tt> if it exists.
 *
 *  Will return <tt>NULL</tt> if <tt>stk</tt> is <tt>NULL</tt>.
 *
 *  @param stk the address of the <tt>stack</tt> we want to peek into.
 *  @return The top element of <tt>stk</tt> if it exists, <tt>NULL</tt> if
 *          <tt>stk</tt> is empty.
 */
void *stack_peek(stack *stk);

/** @brief Removes the top element of <tt>stk</tt> if it exists and returns it.
 *
 *  Will return <tt>NULL</tt> if <tt>stk</tt> is <tt>NULL</tt>.
 *
 *  @param stk the address of the <tt>stack</tt> we want to pop the top off.
 *  @return The top element of <tt>stk</tt> if it exists, <tt>NULL</tt> if
 *          <tt>stk</tt> is empty.
 */
void *stack_pop(stack *stk);

/** @brief Inserts <tt>elem</tt> as the new top of <tt>stk</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>stk</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param stk the address of the <tt>stack</tt> we want to push <tt>elem</tt>
 *             onto.
 *  @param elem the element we want to insert as the new top of <tt>stk</tt>.
 *  @return Success status.
 */
int stack_push(stack *stk, void *elem);

#endif /* STACK_H_ */
