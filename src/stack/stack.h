/** @file stack.h
 *  @brief Function prototypes and structs for a stack data structure.
 *
 *  Implementation of a LIFO stack that is backed by a singly linked list.
 *  The nodes in the linked list store data as generic pointers (void *)
 *  where an element value of NULL cannot be stored.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef STACK_H_
#define STACK_H_

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

/** @brief Initializes a new stack.
 *
 *  Will fail and return 1 if stk is NULL.
 *
 *  @param stk the address of the stack we want to initialize.
 *  @return Success status.
 */
int stack_init(stack *stk);

/** @brief Removes all elements from stk.
 *
 *  Frees all the nodes in the linkde list in stk but will not free the
 *  elements in the nodes.
 *
 *  @param stk the address of the stack we want to clear out.
 *  @return Success status.
 */
int stack_clear(stack *stk);

/** @brief Returns the top element of stk if it exists.
 *
 *  Will return NULL if stk is NULL.
 *
 *  @param stk the address of the stack we want to peek into.
 *  @return The top element of stk if it exists, NULL if stk is empty.
 */
void *stack_peek(stack *stk);

/** @brief Removes the top element of stk if it exists and returns it.
 *
 *  Will return NULL if stk is NULL.
 *
 *  @param stk the address of the stack we want to pop the top off.
 *  @return The top element of stk if it exists, NULL if stk is empty.
 */
void *stack_pop(stack *stk);

/** @brief Inserts elem as the new top of stk.
 *
 *  Will fail and return 1 if stk is NULL or elem is NULL.
 *
 *  @param stk the address of the stack we want to push elem onto.
 *  @param elem the element we want to insert as the new top of stk.
 *  @return Success status.
 */
int stack_push(stack *stk, void *elem);

#endif /* STACK_H_ */
