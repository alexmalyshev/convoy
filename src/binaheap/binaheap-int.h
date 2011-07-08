/** @file binaheap-int.h
 *  @brief Function prototypes for internal functions in the binaheap library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef BINAHEAP_INT_H_
#define BINAHEAP_INT_H_

/** @brief Resizes the array in heap to hold newcap elements.
 *
 *  heap is not NULL.
 *
 *  @param heap the address of the heap we want to resize.
 *  @param newcap the new capacity of the array in heap.
 *  @return Success status.
 */
static int resize(binaheap *heap, size_t newcap);

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
