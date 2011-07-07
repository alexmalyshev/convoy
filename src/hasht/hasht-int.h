/** @file hasht-int.h
 *  @brief Function prototypes for internal functions in the hasht library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef HASHT_INT_H_
#define HASHT_INT_H_

/** @brief Doubles the size of tab's array and rehashes all elements.
 *
 *  tab is not NULL.
 *
 *  @param tab the address of the hasht we want to resize and rehash.
 *  @return Void.
 */
static void rehash(hasht *tab);

/** @brief Frees all the entries in a bucket.
 *
 *  Will not free the elements stored in the entries.
 *
 *  @param entry the address of the first entry in the bucket.
 *  @return Void.
 */
static void destroy_bucket(hashentry *entry);

/** @brief Allocates a new hashentry with elem as it's element.
 *  @param elem the address of the element we want the new entry to store.
 *  @return A pointer to a new hashentry.
 */
static hashentry *init_entry(void *elem);

#endif /* HASHT_INT_H_ */
