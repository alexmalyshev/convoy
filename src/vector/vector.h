/** @file vector.h
 *  @brief Header for a dynamic array data structure library.
 *
 *  A <tt>vector</tt> is a dynamic array. Inserts and pushes into the
 *  <tt>vector</tt> will always succeed provided there is enough memory on the
 *  system. Elements are stored as generic pointers (<tt>void *</tt>), however
 *  <tt>NULL</tt> cannot be stored. Getting a <tt>NULL</tt> back as an element
 *  from the <tt>vector</tt> means that position in the <tt>vector</tt> was
 *  empty.
 *
 *  @author Alexander Malyshev
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>

/** @brief The default capacity of a new <tt>vector</tt>. */
#define VECTOR_DEFAULT_CAP 32

/** @brief The default rate used when resizing. */
#define VECTOR_GROW_CAP(cap) (3*(cap)/2)

/** @brief A dynamic array. */
typedef struct {
    void **elems; /**< the array of elements. */
    size_t cap;   /**< total capacity of the array. */
    size_t last;  /**< index of the last stored element. */
} vector;

/** @brief Initializes a new <tt>vector</tt>.
 *
 *  Asserts that <tt>vec</tt> is not NULL.
 *  If <tt>cap</tt> is 0, then no allocations will occur.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @param cap the desired capacity.
 */
void vector_init(vector *vec, size_t cap);

/** @brief Frees the dynamic array in <tt>vec</tt>/
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  A vector that has been destroyed needs to be reinitialized if
 *  it is to be used again.
 *
 *  @param vec the address of the <tt>vector</tt>.
 */
void vector_destroy(vector *vec);

/** @brief Returns the element at position <tt>i</tt>.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Trying to access an out-of-bounds element returns <tt>NULL</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @param i the index.
 *  @return The element at <tt>vec[i]</tt>.
 */
void *vector_at(vector *vec, size_t i);

/** @brief Clears out <tt>vec</tt>.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Will not resize <tt>vec</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 */
void vector_clear(vector *vec);

/** @brief Compacts all the elements in <tt>vec</tt> to the left.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Will not resize <tt>vec</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 */
void vector_compact(vector *vec);

/** @brief Inserts <tt>elem</tt> at <tt>vec[i]</tt>.
 *
 *  Asserts that <tt>vec</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *  Will resize <tt>vec</tt> if <tt>i</tt> is out-of-bounds.
 *  Does not shift over elements.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @param i the index.
 *  @param elem the element.
 *  @return The old element at <tt>vec[i]</tt>.
 */
void *vector_insert(vector *vec, size_t i, void *elem);

/** @brief Removes the last element from <tt>vec</tt>.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Equivalent to <tt>vector_remove(vec, vec->last)</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @return The last element in <tt>vec</tt>.
 */
void *vector_pop(vector *vec);

/** @brief Adds <tt>elem</tt> as the last element of <tt>vec</tt>.
 *
 *  Asserts that <tt>vec</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *  Equivalent to <tt>vector_insert(vec, vec->last + 1, elem)</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @param elem the element.
 */
void vector_push(vector *vec, void *elem);

/** @brief Removes <tt>vec[i]</tt>.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Will not resize <tt>vec</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @param i the index.
 *  @return The element at <tt>vec[i]</tt>.
 */
void *vector_remove(vector *vec, size_t i);

/** @brief Resizes <tt>vec</tt> to capacity <tt>cap</tt>.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Can shrink or grow <tt>vec</tt>, and resizing to capacity 0 will free
 *  its dynamic array.
 *
 *  @param vec the address of the <tt>vector</tt>.
 *  @param cap the desired capacity.
 */
void vector_resize(vector *vec, size_t cap);

/** @brief Swaps <tt>vec[i]</tt> with <tt>vec[j]</tt>
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Will resize <tt>vec</tt> if either <tt>i</tt> or <tt>j</tt> is
 *  out-of-bounds, but not if both are.
 *
 */
void vector_swap(vector *vec, size_t i, size_t j);

/** @brief Shrinks <tt>vec</tt> as much as possible without losing elements.
 *
 *  Asserts that <tt>vec</tt> is not <tt>NULL</tt>.
 *  Equivalent to <tt>vector_resize(vec, vec->last + 1)</tt>.
 *
 *  @param vec the address of the <tt>vector</tt>.
 */
void vector_trim(vector *vec);

#endif /* VECTOR_H_ */
