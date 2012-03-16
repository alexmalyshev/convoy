/** @file binaheap.h
 *  @brief Header for a binary heap data structure library.
 *
 *  A <tt>binaheap</tt> is a dynamic array. Elements are stored as generic
 *  pointers (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored.
 *  Elements are compared using a generic compare function. Getting a
 *  <tt>NULL</tt> back as an element from a <tt>binaheap</tt> means that the
 *  <tt>binaheap</tt> is empty or that there was an error.
 *
 *  @author Alexander Malyshev
 */

#ifndef __BINAHEAP_H__
#define __BINAHEAP_H__

#include <stddef.h>

/** @brief The default number of elements a new <tt>binaheap</tt> can store */
#define BINAHEAP_DEFAULT_CAPACITY 32

#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

/** @brief A binary heap */
typedef struct {
    void **elems;   /**< the array of elements */
    cmpfn cmp;      /**< the function for comparing elements */
    size_t size;    /**< the number of elements in the array */
    size_t cap;     /**< the number of elements the array can hold */
} binaheap;


/** @brief Initializes a new <tt>binaheap</tt>
 *
 *  @param heap the address of the <tt>binaheap</tt>
 *  @param cmp the compare function for <tt>heap</tt>
 *  @param cap the desired capacity of <tt>heap</tt>
 *
 *  @return Success status
 */
int binaheap_init(binaheap *heap, cmpfn cmp, size_t cap);


/** @brief Frees the dynamic array in <tt>heap</tt>
 *
 *  @param heap the address of the <tt>binaheap</tt>
 *
 *  @return Success status
 */
int binaheap_destroy(binaheap *heap);


/** @brief Inserts <tt>elem</tt> into <tt>heap</tt>
 *
 *  @param heap the address of the <tt>binaheap</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int binaheap_insert(binaheap *heap, void *elem);


/** @brief Removes the minimum element in <tt>heap</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>heap</tt> is empty
 *
 *  @param heap the address of the <tt>binaheap</tt>
 *
 *  @return The minimum element in <tt>heap</tt>
 */
void *binaheap_removemin(binaheap *heap);


/** @brief Removes all elements from <tt>heap</tt>
 *
 *  Asserts that <tt>heap</tt> is not <tt>NULL</tt>
 *  Will not resize the array in <tt>heap</tt>
 *
 *  @param heap the address of the <tt>binaheap</tt>
 *
 *  @return Success status
 */
int binaheap_clear(binaheap *heap);


/** @brief Shrinks the capacity of the dynamic array in <tt>heap</tt>
 *
 *  Truncates the array in <tt>heap</tt> to hold exactly the number of
 *  elements stored in <tt>heap</tt>
 *
 *  @param heap the address of the <tt>binaheap</tt>
 *
 *  @return Success status
 */
int binaheap_trunc(binaheap *heap);


#endif /* __BINAHEAP_H__ */
