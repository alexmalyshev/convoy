/** @file deque.h
 *  @brief Function prototypes and structs for a deque data structure.
 *
 *  Implementation of a double-ended queue(deque) that is backed by a
 *  doubly linked list. The nodes in the linked list store data as
 *  generic pointers (void *) where an element value of NULL cannot be stored.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef DEQUE_H_
#define DEQUE_H_

/** @brief A node in a linked list.
 *
 *  Stores a pointer to an element and pointers to the previous node and next
 *  node in the list.
 */
typedef struct dnode_t {
    struct dnode_t *prev;
    struct dnode_t *next;
    void *data;
} dnode;

/** @brief A double-ended queue.
 *
 *  Implemented as a doubly linked list that stores its length.
 */
typedef struct {
    dnode *front;
    dnode *back;
    long len;
} deque;

/** @brief Allocates and initializes a new deque.
 *  @return A pointer to a new deque.
 */
deque *deque_init(void);

/** @brief Frees the linked list in d and d itself.
 *
 *  Will not free the elements stored in the nodes of d.
 *
 *  @param d the address of the deque we want to deallocate.
 *  @return Success status.
 */
int deque_destroy(deque *d);

/** @brief Inserts elem as the new back of d.
 *
 *  Will fail and return 1 if d is NULL or elem is NULL.
 *
 *  @param d the address of the deque we want to insert elem into.
 *  @param elem the element we want to insert as the new back of d.
 *  @return Success status.
 */
int deque_insertb(deque *d, void *elem);

/** @brief Inserts elem as the new front of d.
 *
 *  Will fail and return 1 if d is NULL or elem is NULL.
 *
 *  @param d the address of the deque we want to insert elem into.
 *  @param elem the element we want to insert as the new front of d.
 *  @return Success status.
 */
int deque_insertf(deque *d, void *elem);

/** @brief Returns the back element of d if it exists.
 *
 *  Will return NULL if d is NULL.
 *
 *  @param d the address of the deque we want to peek into.
 *  @return The back element of d if it exists, NULL if d is empty.
 */
void *deque_peekb(deque *d);

/** @brief Returns the front element of d if it exists.
 *
 *  Will return NULL if d is NULL.
 *
 *  @param d the address of the deque we want to peek into.
 *  @return The front element of d if it exists, NULL if d is empty.
 */
void *deque_peekf(deque *d);

/** @brief Removes the back element of d if it exists and returns it.
 *
 *  Will fail and return NULL if d is NULL.
 *
 *  @param d the address of the deque we want to remove the back element from.
 *  @return The back element of d if it exists, NULL if d is empty.
 */
void *deque_removeb(deque *d);

/** @brief Removes the front element of d if it exists and returns it.
 *
 *  Will fail and return NULL if d is NULL.
 *
 *  @param d the address of the deque we want to remove the front element from.
 *  @return The front element of d if it exists, NULL if d is empty.
 */
void *deque_removef(deque *d);

/** @brief Removes all elements from d.
 *
 *  Frees all nodes in the linked list in d but will not free the
 *  elements in the nodes.
 *
 *  @param d the address of the deque we want to clear out.
 *  @return Success status.
 */
int deque_clear(deque *d);

/** @brief Returns the number of elements in d.
 *
 *  If d is NULL will return -1, otherwise same behavior as d->len.
 *
 *  @param d the address of the deque whose length we want.
 *  @return The number of elements in d.
 */
long deque_len(deque *d);

#endif /* DEQUE_H_ */
