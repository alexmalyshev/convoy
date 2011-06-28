** @file stack.h
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

/** @brief A node in a linked list.
 *
 *  Stores a pointer to an element and a pointer to the next node in the list.
 */
typedef struct snode_t {
    void *data;             /**< the element of data stored in this node */
    struct snode_t *next;   /**< pointer to the next node in the list */
} snode;

/** @brief A stack.
 *
 *  Implemented as a singly linked list that stores its length.
 */
typedef struct {
    snode *top;     /**< the top node in the stack */
    long len;       /**< the number of elements in the stack */
} stack;

/** @brief Allocates and initializes a new stack.
 *  @return A pointer to a new stack.
 */
stack *stack_init(void);

/** @brief Frees the linked list in s and s itself.
 *
 *  Will not free the elements stored in the nodes of s.
 *
 *  @param s the address of the stack we want to deallocate.
 *  @return Success status.
 */
int stack_destroy(stack *s);

/** @brief Returns the top element of s if it exists.
 *
 *  Will return NULL if s is NULL.
 *
 *  @param s the address of the stack we want to peek into.
 *  @return The top element of s if it exists, NULL if s is empty.
 */
void *stack_peek(stack *s);

/** @brief Removes the top element of s if it exists and returns it.
 *
 *  Will return NULL if s is NULL.
 *
 *  @param s the address of the stack we want to pop the top off.
 *  @return The top element of s if it exists, NULL if s is empty.
 */
void *stack_pop(stack *s);

/** @brief Inserts elem as the new top of s.
 *
 *  Will fail and return 1 if s is NULL or elem is NULL.
 *
 *  @param s the address of the stack we want to push elem onto.
 *  @param elem the element we want to insert as the new top of s.
 *  @return Success status.
 */
int stack_push(stack *s, void *elem);

/** @brief Removes all elements from s.
 *
 *  Frees all nodes in the linked list in s,
 *  but will not free the elements in s.
 *
 *  @param s the address of the stack we want to clear out.
 *  @return Success status.
 */
int stack_clear(stack *s);

/** @brief Returns the number of elements in s
 *
 *  If s is NULL will return -1, otherwise same behavior as s->len.
 *
 *  @param s the address of the stack whose length we want.
 *  @return The number of elements in s.
 */
long stack_len(stack *s);

#endif /* STACK_H_ */
