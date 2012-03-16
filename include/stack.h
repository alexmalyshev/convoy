/** @file stack.h
 *  @brief Header for a stack data structure library.
 *
 *  A <tt>stack</tt> is a singly linked list. Elements are stored as generic
 *  pointers (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored.
 *  Inserting into a <tt>stack</tt> will always succeed provided there is
 *  enough memory on the system. Getting a <tt>NULL</tt> back as an element from
 *  a <tt>stack</tt> means that the <tt>stack</tt> is empty.
 *
 *  @author Alexander Malyshev
 */


#ifndef __STACK_H__
#define __STACK_H__


#include <stddef.h>


/** @brief A node in a singly linked list */
typedef struct snode_t {
    struct snode_t *next;   /**< the next node */
    void *elem;             /**< the element */
} snode;


/** @brief A stack */
typedef struct {
    snode *top;             /**< the top node */
    size_t len;             /**< the number of elements */
} stack;


/** @brief Initializes a new <tt>stack</tt>
 *
 *  @param stk the address of the <tt>stack</tt>
 *
 *  @return Success status
 */
int stack_init(stack *stk);


/** @brief Removes all elements from <tt>stk</tt>
 *
 *  @param stk the address of the <tt>stack</tt>
 *
 *  @return Success status
 */
int stack_clear(stack *stk);


/** @brief Returns the top element of <tt>stk</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>stk</tt> is empty
 *
 *  @param stk the address of the <tt>stack</tt>
 *
 *  @return The top element of <tt>stk</tt>
 */
void *stack_peek(stack *stk);


/** @brief Removes the top element of <tt>stk</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>stk</tt> is empty
 *
 *  @param stk the address of the <tt>stack</tt>
 *
 *  @return The top element of <tt>stk</tt>
 */
void *stack_pop(stack *stk);


/** @brief Inserts <tt>elem</tt> as the new top of <tt>stk</tt>
 *
 *  @param stk the address of the <tt>stack</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int stack_push(stack *stk, void *elem);


#endif /* __STACK_H__ */
