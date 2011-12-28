/** @file binaheap.h
 *  @brief Header for a binary heap data structure library.
 *
 *  Implementation of a minimum binary heap backed by a dynamic array.
 *  Elements are stored as generic pointers (<tt>void *</tt>) where an element
 *  value of <tt>NULL</tt> cannot be stored. Elements are compared using a
 *  generic compare function.
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
    void **elems;   /**< the array of elements in the binary heap. */
    cmpfn cmp;      /**< the function for comparing elements. */
    size_t size;    /**< the number of elements in the binary heap. */
    size_t cap;     /**< the number of elements the array can hold. */
} binaheap;

/** @brief Initializes a new <tt>binaheap</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>heap</tt> is <tt>NULL</tt>,
 *  <tt>cmp</tt> is <tt>NULL</tt>, or if <tt>cap</tt> is <tt>0</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> to initialize.
 *  @param cmp the compare function that will be used by <tt>heap</tt>.
 *  @param cap the starting capacity of <tt>heap</tt>.
 *  @return Success status.
 */
int binaheap_init(binaheap *heap, cmpfn cmp, size_t cap);

/** @brief Frees the dynamic array in <tt>heap</tt>.
 *
 *  Will not free the elements stored in <tt>heap</tt>'s array or
 *  <tt>heap</tt> itself.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to deallocate.
 *  @return Success status.
 */
int binaheap_destroy(binaheap *heap);

/** @brief Inserts <tt>elem</tt> into <tt>heap</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>heap</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to insert
 *              <tt>elem</tt> into.
 *  @param elem the element we want to insert into <tt>heap</tt>.
 *  @return Success status.
 */
int binaheap_insert(binaheap *heap, void *elem);

/** @brief Removes the minimum element in <tt>heap</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>heap</tt> is <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> whose min we want to
 *              remove.
 *  @return The minimum element in <tt>heap</tt> if it exists, <tt>NULL</tt>
 *           if <tt>heap</tt> is empty.
 */
void *binaheap_removemin(binaheap *heap);

/** @brief Removes all elements from <tt>heap</tt>.
 *
 *  Will not free the elements stored in <tt>heap</tt>'s array, or truncate
 *  the array. Will fail and return <tt>1</tt> if <tt>heap</tt> is
 *  <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to clear out.
 *  @return Success status.
 */
int binaheap_clear(binaheap *heap);

/** @brief Truncates the capacity of the dynamic array in <tt>heap</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>heap</tt> is <tt>NULL</tt>.
 *  Truncates the array in <tt>heap</tt> to hold exactly the number of elements
 *  stored in <tt>heap</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to truncate.
 *  @return Success status.
 */
int binaheap_trunc(binaheap *heap);

#endif /* BINAHEAP_H_ */
