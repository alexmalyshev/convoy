/** @file hasht.h
 *  @brief Header for a hash table library.
 *
 *  A <tt>hasht</tt> is a dynamic array where every element is a linked list of
 *  elements. Elements are stored as generic pointers (<tt>void *</tt>),
 *  however <tt>NULL</tt> cannot be stored. Elements are compared using a
 *  user-specified compare function and hashed using a user-specified hash
 *  function. Inserting into a <tt>hasht</tt> will always succeed provided
 *  there is enough memory on the system. Getting a <tt>NULL</tt> back as an
 *  element from a <tt>hasht</tt> means that key has no mapped value in the
 *  table.
 *
 *  @author Alexander Malyshev
 */


#ifndef __HASHT_H__
#define __HASHT_H__


#include <stddef.h>


#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

#ifndef HASHFN
#define HASHFN
/** @brief A generic hash function */
typedef unsigned long (*hashfn)(void *);
#endif /* HASHFN */


/** @brief The default load factor */
#define HASHT_DEFAULT_LOADFACTOR 0.75

/** @brief The default capacity */
#define HASHT_DEFAULT_CAPACITY 64


/** @brief A hash table entry */
typedef struct hashent_t {
    struct hashent_t *next; /**< the next entry */
    void *elem;             /**< the element */
} hashent;


/** @brief A hash table */
typedef struct {
    hashent **entries;      /**< the array of entries */
    hashfn hash;            /**< the function for hashing elements */
    cmpfn cmp;              /**< the function for comparing elements */
    size_t size;            /**< the number of elements in the array */
    size_t cap;             /**< the number of elements the array can hold */
    size_t limit;           /**< the size where the array has to be resized */
    double loadfactor;      /**< the load factor of the table */
} hasht;


/** @brief Initializes a new <tt>hasht</tt>
 *
 *  @param tab the address of the <tt>hasht</tt>.
 *  @param hash the hash function for <tt>tab</tt>.
 *  @param cmp the compare function for <tt>tab</tt>.
 *  @param lf the load factor of <tt>tab</tt>.
 *  @param cap the desired capacity of <tt>tab</tt>.
 *
 *  @return Success status
 */
int hasht_init(hasht *tab, hashfn hash, cmpfn cmp, double lf, size_t cap);


/** @brief Frees the dynamic array in <tt>tab</tt>
 *
 *  @param tab the address of the <tt>hasht</tt>
 *
 *  @return Success status
 */
int hasht_destroy(hasht *tab);


/** @brief Inserts <tt>elem</tt> into <tt>tab</tt>
 *
 *  If <tt>elem</tt> is already in <tt>tab</tt> then this function does not
 *  modify the table and returns 0
 *
 *  @param tab the address of the <tt>hasht</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int hasht_insert(hasht *tab, void *elem);


/** @brief Removes elem from <tt>tab</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>elem</tt> is not in <tt>tab</tt>
 *
 *  @param tab the address of the <tt>hasht</tt>
 *  @param elem the element
 *
 *  @return The element equal to <tt>elem</tt> in <tt>tab</tt>
 */
void *hasht_remove(hasht *tab, void *elem);


/** @brief Searches <tt>tab</tt> for <tt>elem</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>elem</tt> is not in <tt>tab</tt>
 *
 *  @param tab the address of the <tt>hasht</tt>
 *  @param elem the element
 *
 *  @return The element equal to <tt>elem</tt> in <tt>tab</tt>
 */
void *hasht_search(hasht *tab, void *elem);


/** @brief Removes all elements from <tt>tab</tt>
 *
 *  @param tab the address of the <tt>hasht</tt>
 *
 *  @return Success status
 */
int hasht_clear(hasht *tab);


/** @brief Shrinks the capacity of the dynamic array in <tt>tab</tt>
 *
 *  Shrinks the array in <tt>tab</tt> so the load factor of the array
 *  matches the load factor set for the <tt>tab</tt>
 *
 *  @param tab the address of the <tt>hasht</tt>
 *
 *  @return Success status
 */
int hasht_trunc(hasht *tab);


#endif /* __HASHT_H__ */
