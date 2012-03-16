/** @file circbuf.h
 *  @brief Header for a circular buffer data structure library.
 *
 *  A <tt>circbuf</tt> is a fixed-size array. Elements are stored as generic
 *  pointers (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored. The
 *  circbuf structure allocates an array of <tt>void *</tt>s with one extra as
 *  it makes it easy to tell the difference between an empty circbuf and a full
 *  circbuf. However this extra slot will never be used to store an element. A
 *  <tt>circbuf</tt> will not resize when trying to enqueue on an element when
 *  it is full, the enqueue will simply fail and return 1. Getting a
 *  <tt>NULL</tt> back as an element from a <tt>circbuf</tt> means that the
 *  <tt>circbuf</tt> is empty or that there was an error.
 *
 *  @author Alexander Malyshev
 */


#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__


#include <stddef.h>


/** @brief A circular buffer */
typedef struct {
    void **elems;   /**< the array of elements */
    size_t front;   /**< the index of the first element */
    size_t back;    /**< the index of the last element */
    size_t len;     /**< the number of elements plus one */
} circbuf;


/** @brief Initializes a new circbuf
 *
 *  Allocates one slot more than <tt>len</tt> behind the scenes
 *
 *  @param cbuf the address of the <tt>circbuf</tt>
 *  @param len the desired length
 *
 *  @return Success status
 */
int circbuf_init(circbuf *cbuf, size_t len);


/** @brief Frees the array in <tt>cbuf</tt>
 *
 *  @param cbuf the address of the <tt>circbuf</tt>
 *
 *  @return Success status
 */
int circbuf_destroy(circbuf *cbuf);


/** @brief Removes the front element of <tt>cbuf</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>cbuf</tt> is empty
 *
 *  @param cbuf the address of the <tt>circbuf</tt>
 *
 *  @return The front element of <tt>cbuf</tt>
 */
void *circbuf_dequeue(circbuf *cbuf);


/** @brief Inserts <tt>elem</tt> as the new back element of <tt>cbuf</tt>
 *
 *  If <tt>cbuf</tt> is full, then this function does nothing and returns 1
 *
 *  @param cbuf the address of the <tt>circbuf</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int circbuf_enqueue(circbuf *cbuf, void *elem);


/** @brief Returns the front element of <tt>cbuf</tt>
 *
 *  Will return <tt>NULL</tt> if <tt>cbuf</tt> is empty
 *
 *  @param cbuf the address of the <tt>circbuf</tt>
 *
 *  @return The front element of <tt>cbuf</tt>
 */
void *circbuf_peek(circbuf *cbuf);


/** @brief Removes all elements from <tt>cbuf</tt>
 *
 *  @param cbuf the address of the <tt>circbuf</tt>
 *
 *  @return Success status
 */
int circbuf_clear(circbuf *cbuf);


#endif /* __CIRCBUF_H__ */
