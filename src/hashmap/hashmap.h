/** @file hashmap.h
 *  @brief Function prototypes and structs for a hash table.
 *
 *  Implementation of a hash table that is backed by a dynamic array and
 *  uses separate chaining to resolve collisions. Elements are stored as
 *  generic pointers (void *) where an element value of NULL cannot be
 *  stored. Elements are compared using a user-specified compare function
 *  and hashed using a user-specified hash function.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function. */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

#ifndef HASHFN
#define HASHFN
/** @brief A generic hash function. */
typedef unsigned long (*hashfn)(void *);
#endif /* HASHFN */

/** @brief The default load factor for a hashmap. */
#define DEFAULT_LOAD_FACTOR 0.75

/** @brief The default initial capacity for a hashmap. */
#define DEFAULT_INITIAL_CAPACITY 64

/** @brief An entry in a hashmap. */
typedef struct hashentry_t {
    void *elem;                 /**< the element stored in the entry. */
    struct hashentry_t *next;   /**< the next entry in the current bucket. */
} hashentry;

/** @brief A hash table. */
typedef struct {
    hashentry **entries;    /**< the array of elements in the hash table. */
    hashfn hash;            /**< the function for hashing elements. */
    cmpfn cmp;              /**< the function for comparing elements. */
    size_t size;            /**< the number of elements in the table. */
    size_t cap;             /**< the number of elements the array can hold. */
    size_t limit;           /**< the size where the array has to be resized. */
    double loadfactor;      /**< the load factor of the table. */
} hashmap;

/** @brief Allocates and initializes a new hashmap.
 *
 *  Will fail and return NULL if cmp is NULL, hash is NULL, or if loadfactor
 *  is non-positive.
 *
 *  @param hash the hash function that will be used by the table.
 *  @param cmp the compare function that will be used by the table.
 *  @param loadfactor the load factor of the table.
 *  @param cap the capacity of the table.
 *  @return A pointer to a new hashmap.
 */
hashmap *hashmap_init(hashfn hash, cmpfn cmp, double loadfactor, size_t cap);

/** @brief Frees the dynamic array in map and map itself.
 *
 *  Will not free the elements stored in map.
 *
 *  @param map the address of the hashmap we want to deallocate.
 *  @return Success status.
 */
int hashmap_destroy(hashmap *map);

/** @brief Inserts elem into map.
 *
 *  Will fail and return 1 if map is NULL or elem is NULL.
 *
 *  @param map the address of the hashmap we want to insert elem into.
 *  @elem the element we want to insert into map.
 *  @return Success status.
 */
int hashmap_insert(hashmap *map, void *elem);

/** @brief Removes elem from map if it is in map.
 *
 *  Will fail and return NULL if map is NULL or elem is NULL.
 *
 *  @param map the address of the hashmap we want to remove elem from.
 *  @param elem the element we want to remove from map.
 *  @return The element equal to elem if it exists in map, NULL otherwise.
 */
void *hashmap_remove(hashmap *map, void *elem);

/** @brief Searches map for elem.
 *
 *  Will fail and return NULL if map is NULL or elem is NULL.
 *
 *  @param map the address of the hashmap we want to search for elem.
 *  @param elem the element we're searching for in map.
 *  @return The element equal to elem if it exists in map, NULL otherwise.
 */
void *hashmap_search(hashmap *map, void *elem);

/** @brief Removes all elements from map.
 *
 *  Frees all the entries in the buckets of map, but will not free
 *  the elements in the entries.
 *
 *  @param map the address of the hashmap we want to clear out.
 *  @return Success status.
 */
int hashmap_clear(hashmap *map);

#endif /* HASHMAP_H_ */
