/** @file circbuf.h
 *  @brief Function prototypes and struct for a circular buffer data structure.
 *
 *  Implementation of a fixed-size circular buffer. Elements are stored as
 *  generic pointers (<tt>void *</tt>) where <tt>NULL</tt> cannot be stored,
 *  and the circbuf structure allocates an array of <tt>void *</tt>s with one
 *  extra as it makes it easy to tell the difference between an empty circbuf
 *  and a full circbuf. However this extra slot will never be used to store an
 *  element.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef CIRCBUF_H_
#define CIRCBUF_H_

#include <stddef.h>

#ifndef SIZE_MAX
/** @brief The max number of elements in the circular buffer. */
#define MAX_LEN ((size_t)(-1) - 1)
#else
#define MAX_LEN (SIZE_MAX)
#endif

/** @brief A circular buffer. */
typedef struct {
    void **elems;   /**< the array of elements in the circular buffer. */
    size_t front;   /**< the index of the first element in the array. */
    size_t back;    /**< the index of the last element in the array. */
    size_t len;     /**< the number of elements in the buffer plus one. */
} circbuf;

/** @brief Initializes a new circbuf.
 *
 *  Will fail and return <tt>1</tt> if <tt>cbuf</tt> is <tt>NULL</tt> or if
 *  <tt>len</tt> is <tt>MAX_LEN</tt>. <tt>cbuf</tt> will be able to store a
 *  max of <tt>len</tt> elements, but the inner array will have size
 *  <tt>len + 1</tt>.
 *
 *  @param cbuf the address of the <tt>circbuf</tt> we want to initialize.
 *  @param len the length of <tt>cbuf</tt>.
 *  @return Success status.
 */
int circbuf_init(circbuf *cbuf, size_t len);

/** @brief Frees the array in <tt>cbuf</tt>.
 *
 *  Will not free the elements stored in the nodes of <tt>cbuf</tt>.
 *
 *  @param cbuf the address of the <tt>circbuf</tt> we want to deallocate.
 *  @return Success status.
 */
int circbuf_destroy(circbuf *cbuf);

/** @brief Removes the front element of <tt>cbuf</tt> if it exists and returns
 *         it.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>cbuf</tt> is NULL.
 *
 *  @param cbuf the address of the <tt>circbuf</tt> we want to remove the
 *              front from.
 *  @return The front element of <tt>cbuf</tt> if it exists, <tt>NULL</tt> if
 *          <tt>cbuf</tt> is empty.
 */
void *circbuf_dequeue(circbuf *cbuf);

/** @brief Inserts <tt>elem</tt> as the new back element of <tt>cbuf</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>cbuf</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>, or if <tt>cbuf</tt> is full.
 *
 *  @param cbuf the address of the <tt>circbuf</tt> we want to insert
 *              <tt>elem</tt> into.
 *  @param elem the element we want to insert as the new back of <tt>cbuf</tt>.
 *  @return Success status.
 */
int circbuf_enqueue(circbuf *cbuf, void *elem);

/** @brief Returns the front element of <tt>cbuf</tt> if it exists.
 *
 *  Will return <tt>NULL</tt> if <tt>cbuf</tt> is <tt>NULL</tt>.
 *
 *  @param cbuf the address of the <tt>circbuf</tt> we want to peek into.
 *  @return The front element of <tt>cbuf</tt> if it exists, <tt>NULL</tt>
 *          if <tt>cbuf</tt> is empty.
 */
void *circbuf_peek(circbuf *cbuf);

/** @brief Removes all elements from <tt>cbuf</tt>.
 *
 *  Will not free the elements in <tt>cbuf</tt>.
 *
 *  @param cbuf the address of the <tt>circbuf</tt> we want to clear out.
 *  @return Success status.
 */
int circbuf_clear(circbuf *cbuf);

#endif /* CIRCBUF_H_ */
