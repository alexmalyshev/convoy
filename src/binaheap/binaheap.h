/** @file binaheap.h
 *  @brief Header for a binary heap data structure library.
 *
 *  A <tt>binaheap</tt> is a dynamic array. Elements are stored as generic
 *  pointers (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored.
 *  Elements are compared using a generic compare function. Inserting into a
 *  <tt>binaheap</tt> will always succeed provided there is enough memory on
 *  the system. Getting a <tt>NULL</tt> back as an element from a
 *  <tt>binaheap</tt> means that the <tt>binaheap</tt> is empty.
 *
 *  @author Alexander Malyshev
 */

#ifndef BINAHEAP_H_
#define BINAHEAP_H_

#include <stddef.h>

/** @brief The default number of elements a new <tt>binaheap</tt> can store. */
#define BINAHEAP_DEFAULT_CAPACITY 32

#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function. */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

/** @brief A binary heap. */
typedef struct {
    void **elems;   /**< the array of elements. */
    cmpfn cmp;      /**< the function for comparing elements. */
    size_t size;    /**< the number of elements in the array. */
    size_t cap;     /**< the number of elements the array can hold. */
} binaheap;

/** @brief Initializes a new <tt>binaheap</tt>.
 *
 *  Asserts that <tt>heap</tt> and <tt>cmp</tt> are not <tt>NULL</tt>,
 *  and that <tt>cap</tt> is not <tt>0</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt>.
 *  @param cmp the compare function for <tt>heap</tt>.
 *  @param cap the desired capacity of <tt>heap</tt>.
 */
void binaheap_init(binaheap *heap, cmpfn cmp, size_t cap);

/** @brief Frees the dynamic array in <tt>heap</tt>.
 *
 *  Asserts that <tt>heap</tt> is not <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt>.
 */
void binaheap_destroy(binaheap *heap);

/** @brief Inserts <tt>elem</tt> into <tt>heap</tt>.
 *
 *  Asserts that <tt>heap</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt>.
 *  @param elem the element.
 */
void binaheap_insert(binaheap *heap, void *elem);

/** @brief Removes the minimum element in <tt>heap</tt>.
 *
 *  Asserts that <tt>heap</tt> is not <tt>NULL</tt>.
 *  Returns <tt>NULL</tt> if <tt>heap</tt> is empty.
 *
 *  @param heap the address of the <tt>binaheap</tt>.
 *  @return The minimum element in <tt>heap</tt>.
 */
void *binaheap_removemin(binaheap *heap);

/** @brief Removes all elements from <tt>heap</tt>.
 *
 *  Asserts that <tt>heap</tt> is not <tt>NULL</tt>.
 *  Will not resize the array in <tt>heap</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt>.
 */
void binaheap_clear(binaheap *heap);

/** @brief Shrinks the capacity of the dynamic array in <tt>heap</tt>.
 *
 *  Asserts that <tt>heap</tt> is not <tt>NULL</tt>.
 *  Truncates the array in <tt>heap</tt> to hold exactly the number of elements
 *  stored in <tt>heap</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt>.
 */
void binaheap_trunc(binaheap *heap);

#endif /* BINAHEAP_H_ */
