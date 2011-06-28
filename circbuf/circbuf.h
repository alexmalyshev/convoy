/** @file circbuf.h
 *  @brief Function prototypes and struct for a circular buffer data structure.
 *
 *  Implementation of a fixed-size circular buffer. Elements are stored as
 *  generic pointers (void *) where NULL cannot be stored, and the circbuf
 *  structure allocates an array of void *s with one extra as it makes it
 *  easy to tell the difference between an empty circbuf and a full circbuf.
 *  However this extra slot will never be used to store an element.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef CIRCBUF_H_
#define CIRCBUF_H_

/** @brief A circular buffer.
 *
 *  Implemented as an fixed-size array, holding onto the indices for the front
 *  and back as well as the length of the array plus one.
 */
typedef struct {
    void **items;
    long front;
    long back;
    long len;
} circbuf;

/** @brief Allocates and initializes a new circbuf.
 *  @param size the desired size of the circbuf.
 *  @return A pointer to a new circbuf of the given size.
 */
circbuf *circbuf_init(long size);

/** @brief Frees the array in cb and cb itself.
 *
 *  Will not free the elements stored in the nodes of cb.
 *
 *  @param cb the address of the circbuf we want to deallocate.
 *  @return Success status.
 */
int circbuf_destroy(circbuf *cb);

/** @brief Removes the front element of cb if it exists and returns it.
 *
 *  Will fail and return NULL if cb is NULL.
 *
 *  @param cb the address of the circbuf we want to remove the front from.
 *  @return The front element of cb if it exists, NULL if cb is empty.
 */
void *circbuf_dequeue(circbuf *cb);

/** @brief Inserts elem as the new back of cb.
 *
 *  Will fail and return 1 if cb is NULL or elem is NULL, or if cb is full.
 *
 *  @param cb the address of the circbuf we want to insert elem into.
 *  @param elem the element we want to insert as the new back of cb.
 *  @return Success status.
 */
int circbuf_enqueue(circbuf *cb, void *elem);

/** @brief Returns the front element of cb if it exists.
 *
 *  Will return NULL if cb is NULL.
 *
 *  @param cb the address of the circbuf we want to peek into.
 *  @return The front element of cb if it exists, NULL if cb is empty.
 */
void *circbuf_peek(circbuf *cb);

/** @brief Removes all elements from cb.
 *
 *  Will not free the elements in cb.
 *
 *  @param cb the address of the circbuf we want to clear out.
 *  @return Success status.
 */
int circbuf_clear(circbuf *cb);

#endif /* CIRCBUF_H_ */
