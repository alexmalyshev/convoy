/** @file binaheap-int.h
 *  @brief Function prototypes for internal functions in the binaheap library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef BINAHEAP_INT_H_
#define BINAHEAP_INT_H_

/** @brief Doubles the size of the array in heap.
 *
 *  heap is not NULL, will only resize until capacity hits BINAHEAP_MAX_ITEMS.
 *
 *  @param heap the address of the heap we want to resize.
 *  @return Success status.
 */
static int resize(binaheap *heap);

/** @brief Percolates the last item in heap up until invariants are met.
 *
 *  heap is not NULL.
 *
 *  @param heap the address of the heap we want to 'heapify'.
 *  @return Void.
 */
static void percolate_up(binaheap *heap);

/** @brief Percolates the first item in heap down until invariants are met.
 *
 *  heap is not NULL.
 *
 *  @param heap the address of the heap we want to 'heapify'.
 *  @return Void.
 */
static void percolate_down(binaheap *heap);

/** @brief Swaps two elements of an array.
 *
 *  elems is not NULL, and i and j are not out of bounds for indices of elems.
 *
 *  @param elems an array of elements
 *  @param i the index of an element in elems
 *  @param j the index of an element in elems
 *  @return Void.
 */
static void swap(void **elems, long i, long j);

#endif /* BINAHEAP_INT_H_ */
