/** @file binaheap-int.h
 *  @brief Function prototypes for internal functions in the binaheap library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef BINAHEAP_INT_H_
#define BINAHEAP_INT_H_

/** @brief Resizes the array in <tt>heap</tt> to hold <tt>newcap</tt> elements.
 *
 *  <tt>heap</tt> is not <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to resize.
 *  @param newcap the new capacity of the array in <tt>heap</tt>.
 *  @return Success status.
 */
static int resize(binaheap *heap, size_t newcap);

/** @brief Percolates the last element in <tt>heap</tt> up until heap
 *         invariants are met.
 *
 *  <tt>heap</tt> is not <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to 'heapify'.
 *  @return Void.
 */
static void percolate_up(binaheap *heap);

/** @brief Percolates the first element in <tt>heap</tt> down until invariants
 *         are met.
 *
 *  <tt>heap</tt> is not <tt>NULL</tt>.
 *
 *  @param heap the address of the <tt>binaheap</tt> we want to 'heapify'.
 *  @return Void.
 */
static void percolate_down(binaheap *heap);

/** @brief Swaps two elements of an array.
 *
 *  <tt>elems</tt> is not <tt>NULL</tt>, and <tt>i</tt> and <tt>j</tt> are not
 *  out of bounds for indices of <tt>elems</tt>.
 *
 *  @param elems an array of elements.
 *  @param i the index of an element in <tt>elems</tt>.
 *  @param j the index of an element in <tt>elems</tt>.
 *  @return Void.
 */
static void swap(void **elems, long i, long j);

#endif /* BINAHEAP_INT_H_ */
