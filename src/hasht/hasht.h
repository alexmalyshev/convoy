/** @file hasht.h
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

#ifndef HASHT_H_
#define HASHT_H_

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

/** @brief The default load factor for a hasht. */
#define HASHT_DEFAULT_LOADFACTOR 0.75

/** @brief The default initial capacity for a hasht. */
#define HASHT_DEFAULT_CAPACITY 64

/** @brief An entry in a hasht. */
typedef struct hashent_t {
    struct hashent_t *next; /**< the next entry in the current bucket. */
    void *elem;             /**< the element stored in the entry. */
} hashent;

/** @brief A hash table. */
typedef struct {
    hashent **entries;      /**< the array of elements in the hash table. */
    hashfn hash;            /**< the function for hashing elements. */
    cmpfn cmp;              /**< the function for comparing elements. */
    size_t size;            /**< the number of elements in the table. */
    size_t cap;             /**< the number of elements the array can hold. */
    size_t limit;           /**< the size where the array has to be resized. */
    double loadfactor;      /**< the load factor of the table. */
} hasht;

/** @brief Initializes a new hasht.
 *
 *  Will fail and return NULL if tab is NULL, cmp is NULL, hash is NULL,
 *  or if loadfactor is non-positive.
 *
 *  @param tab the address of the table we want to initialize.
 *  @param hash the hash function that will be used by the table.
 *  @param cmp the compare function that will be used by the table.
 *  @param lf the load factor of the table.
 *  @param cap the starting capacity of the table.
 *  @return Success status.
 */
int hasht_init(hasht *tab, hashfn hash, cmpfn cmp, double lf, size_t cap);

/** @brief Frees the dynamic array in tab.
 *
 *  Will not free the elements stored in tab.
 *
 *  @param tab the address of the hasht we want to deallocate.
 *  @return Success status.
 */
int hasht_destroy(hasht *tab);

/** @brief Inserts elem into tab.
 *
 *  Will fail and return 1 if tab is NULL or elem is NULL.
 *
 *  @param tab the address of the hasht we want to insert elem into.
 *  @param elem the element we want to insert into tab.
 *  @return Success status.
 */
int hasht_insert(hasht *tab, void *elem);

/** @brief Removes elem from tab if it is in map.
 *
 *  Will fail and return NULL if tab is NULL or elem is NULL.
 *
 *  @param tab the address of the hasht we want to remove elem from.
 *  @param elem the element we want to remove from tab.
 *  @return The element equal to elem if it exists in tab, NULL otherwise.
 */
void *hasht_remove(hasht *tab, void *elem);

/** @brief Searches tab for elem.
 *
 *  Will fail and return NULL if tab is NULL or elem is NULL.
 *
 *  @param tab the address of the hasht we want to search for elem.
 *  @param elem the element we're searching for in tab.
 *  @return The element equal to elem if it exists in tab, NULL otherwise.
 */
void *hasht_search(hasht *tab, void *elem);

/** @brief Removes all elements from tab.
 *
 *  Frees all the entries in the buckets of tab, but will not free
 *  the elements in the entries.
 *
 *  @param tab the address of the hasht we want to clear out.
 *  @return Success status.
 */
int hasht_clear(hasht *tab);

/** @brief Truncates the capacity of the dynamic array in tab.
 *
 *  Will fail and return 1 if tab is NULL. Truncates the array in tab
 *  so the load factor of the array matches the load factor of the table.
 *
 *  @param tab the address of the hasht we want to truncate.
 *  @return Success status.
 */
int hasht_trunc(hasht *tab);

#endif /* HASHT_H_ */
