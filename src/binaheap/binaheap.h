/** @file binaheap.h
 *  @brief Function prototypes and struct for a binary heap data structure.
 *
 *  Implementation of a minimum binary heap backed by a dynamic array.
 *  Elements are stored as generic pointers (void *) where an element value 
 *  of NULL cannot be stored. Elements are compared using a generic compare
 *  function
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef BINAHEAP_H_
#define BINAHEAP_H_

#include <limits.h> /* LONG_MAX */

/** @brief The number of elements a new binaheap can store. */
#define INITIAL_CAPACITY 10

#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function. */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

/** @brief A binary heap
 *
 *  Stores an array of elements, the capacity of the array and the number
 *  of elements currently in it, as well as a compare function.
 */
typedef struct {
    void **elems;   /**< the array of elements in the binary heap */
    cmpfn cmp;      /**< the function for comparing elements */
    size_t size;    /**< the number of elements in the binary heap */
    size_t cap;     /**< the number of elements the array can hold */
} binaheap;

/** @brief Allocates and initializes a new binaheap.
 *  @param cmp the compare function that will be used by the tree.
 *  @return A pointer to a new binaheap.
 */
binaheap *binaheap_init(cmpfn cmp);

/** @brief Frees the dynamic array in heap and heap itself.
 *
 *  Will not free the elements stored in heap's array.
 *
 *  @param heap the address of the binaheap we want to deallocate.
 *  @return Success status.
 */
int binaheap_destroy(binaheap *heap);

/** @brief Inserts elem into heap.
 *
 *  Will fail and return 1 if tree is NULL or elem is NULL
 *
 *  @param heap the address of the binaheap we want to insert elem into.
 *  @param elem the element we want to insert into heap.
 *  @return Success status.
 */
int binaheap_insert(binaheap *heap, void *elem);

/** @brief Removes the minimum element in heap.
 *
 *  Will fail and return NULL if heap is NULL.
 *
 *  @param heap the address of the binaheap whose min we want to remove.
 *  @return The minimum element in heap if it exists, NULL if heap is empty.
 */
void *binaheap_removemin(binaheap *heap);

/** @brief Removes all elements from heap.
 *
 *  Will not free the elements stored in heap's array, or truncate the array.
 *
 *  @param heap the address of the binaheap we want to clear out.
 *  @return Success status.
 */
int binaheap_clear(binaheap *heap);

#endif /* BINAHEAP_H_ */
