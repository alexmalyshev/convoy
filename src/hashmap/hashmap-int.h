/** @file hashmap-int.h
 *  @brief Function prototypes for internal functions in the hashmap library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef HASHMAP_INT_H_
#define HASHMAP_INT_H_

/** @brief Doubles the size of map's array and rehashes all elements.
 *
 *  map is not NULL.
 *
 *  @param map the address of the hashmap we want to resize and rehash.
 *  @return Void.
 */
static void rehash(hashmap *map);

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

#endif /* HASHMAP_INT_H_ */
