/** @file hasht.h
 *  @brief Function prototypes and structs for a hash table.
 *
 *  Implementation of a hash table that is backed by a dynamic array and
 *  uses separate chaining to resolve collisions. Elements are stored as
 *  generic pointers (<tt>void *</tt>) where an element value of <tt>NULL</tt>
 *  cannot be stored. Elements are compared using a user-specified compare
 *  function and hashed using a user-specified hash function.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef HASHT_H_
#define HASHT_H_

#include <stddef.h>

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

/** @brief The default load factor for a <tt>hasht</tt>. */
#define HASHT_DEFAULT_LOADFACTOR 0.75

/** @brief The default initial capacity for a <tt>hasht</tt>. */
#define HASHT_DEFAULT_CAPACITY 64

/** @brief An entry in a <tt>hasht</tt>. */
typedef struct hashent_t {
    struct hashent_t *next; /**< the next entry in the current bucket. */
    void *elem;             /**< the element stored in the entry. */
} hashent;

/** @brief A hash table. */
typedef struct {
    hashent **entries;      /**< the array of entries in the hash table. */
    hashfn hash;            /**< the function for hashing elements. */
    cmpfn cmp;              /**< the function for comparing elements. */
    size_t size;            /**< the number of elements in the table. */
    size_t cap;             /**< the number of elements the array can hold. */
    size_t limit;           /**< the size where the array has to be resized. */
    double loadfactor;      /**< the load factor of the table. */
} hasht;

/** @brief Initializes a new <tt>hasht</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tab</tt> is <tt>NULL</tt>,
 *  <tt>cmp</tt> is <tt>NULL</tt>, <tt>hash</tt> is <tt>NULL</tt>, or if
 *  <tt>lf</tt> is non-positive.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to initialize.
 *  @param hash the hash function that will be used by <tt>tab</tt>.
 *  @param cmp the compare function that will be used by <tt>tab</tt>.
 *  @param lf the load factor of <tt>tab</tt>.
 *  @param cap the starting capacity of <tt>tab</tt>.
 *  @return Success status.
 */
int hasht_init(hasht *tab, hashfn hash, cmpfn cmp, double lf, size_t cap);

/** @brief Frees the dynamic array in <tt>tab</tt>.
 *
 *  Will not free the elements stored in <tt>tab</tt>.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to deallocate.
 *  @return Success status.
 */
int hasht_destroy(hasht *tab);

/** @brief Inserts <tt>elem</tt> into <tt>tab</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>tab</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>. If <tt>elem</tt> is already in <tt>tab</tt>
 *  then will simply return <tt>0</tt>.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to insert
 *             <tt>elem</tt> into.
 *  @param elem the element we want to insert into <tt>tab</tt>.
 *  @return Success status.
 */
int hasht_insert(hasht *tab, void *elem);

/** @brief Removes elem from <tt>tab</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tab</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to remove
 *             <tt>elem</tt> from.
 *  @param elem the element we want to remove from <tt>tab</tt>.
 *  @return The element equal to <tt>elem</tt> if it exists in <tt>tab</tt>,
 *          <tt>NULL</tt> otherwise.
 */
void *hasht_remove(hasht *tab, void *elem);

/** @brief Searches <tt>tab</tt> for <tt>elem</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tab</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to search for
 *             <tt>elem</tt>.
 *  @param elem the element we're searching for in <tt>tab</tt>.
 *  @return The element equal to <tt>elem</tt> if it exists in <tt>tab</tt>,
 *          <tt>NULL</tt> otherwise.
 */
void *hasht_search(hasht *tab, void *elem);

/** @brief Removes all elements from <tt>tab</tt>.
 *
 *  Frees all the entries in the buckets of <tt>tab</tt>, but will not free
 *  the elements in the entries.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to clear out.
 *  @return Success status.
 */
int hasht_clear(hasht *tab);

/** @brief Truncates the capacity of the dynamic array in <tt>tab</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>tab</tt> is <tt>NULL</tt>.
 *  Truncates the array in <tt>tab</tt> so the load factor of the array
 *  matches the load factor set for the <tt>tab</tt>.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to truncate.
 *  @return Success status.
 */
int hasht_trunc(hasht *tab);

#endif /* HASHT_H_ */
