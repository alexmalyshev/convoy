/** @file hasht-int.h
 *  @brief Function prototypes for internal functions in the <tt>hasht</tt>
 *         library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef HASHT_INT_H_
#define HASHT_INT_H_

/** @brief Resizes <tt>tab</tt>'s array and rehashes all elements.
 *
 *  <tt>tab</tt> is not <tt>NULL</tt>.
 *
 *  @param tab the address of the <tt>hasht</tt> we want to resize and rehash.
 *  @param newcap the new capacity of the array in <tt>tab</tt>.
 *  @return Success status.
 */
static int resize(hasht *tab, size_t newcap);

/** @brief Frees all the entries in a bucket.
 *
 *  Will not free the elements stored in the entries.
 *
 *  @param entry the address of the first entry in the bucket.
 *  @return Void.
 */
static void destroy_bucket(hashent *entry);

/** @brief Allocates a new <tt>hashent</tt> with <tt>elem</tt> as it's element.
 *  @param elem the address of the element we want the new entry to store.
 *  @return A pointer to a new <tt>hashent</tt>.
 */
static hashent *init_entry(void *elem);

#endif /* HASHT_INT_H_ */
