/** @file splat.h
 *  @brief Header for a splay tree data structure library.
 *
 *  A <tt>splat</tt> is a binary tree. Elements are stored as generic pointers
 *  (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored. Elements are
 *  compared using a generic compare function. Getting a <tt>NULL</tt> back as
 *  an element from a <tt>splat</tt> means that key has no mapped value in the
 *  tree.
 *
 *  @author Alexander Malyshev
 */


#ifndef __SPLAT_H__
#define __SPLAT_H__


#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */


/** @brief A node in a binary tree */
typedef struct spnode_t {
    struct spnode_t *left;  /**< the left child */
    struct spnode_t *right; /**< the right child */
    void *elem;             /**< the element */
} spnode;


/** @brief A splay tree */
typedef struct splat_t {
    spnode *root;           /**< the root node */
    cmpfn cmp;              /**< the function for comparing elements */
} splat;


/** @brief Initializes a new <tt>splat</tt>
 *
 *  @param tree the address of the <tt>splat</tt>
 *  @param cmp the compare function for <tt>tree</tt>
 *
 *  @return Success status
 */
int splat_init(splat *tree, cmpfn cmp);


/** @brief Removes all elements from <tt>tree</tt>
 *
 *  @param tree the address of the <tt>splat</tt>
 *
 *  @return Success status
 */
int splat_clear(splat *tree);


/** @brief Inserts <tt>elem</tt> into <tt>tree</tt>
 *
 *  @param tree the address of the <tt>splat</tt>
 *  @param elem the element
 *
 *  @return Success status
 */
int splat_insert(splat *tree, void *elem);


/** @brief Removes <tt>elem</tt> from <tt>tree</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>elem</tt> is not in <tt>tree</tt>
 *
 *  @param tree the address of the <tt>splat</tt>
 *  @param elem the element
 *
 *  @return The element equal to <tt>elem</tt> in <tt>tree</tt>
 */
void *splat_remove(splat *tree, void *elem);


/** @brief Searches <tt>tree</tt> for <tt>elem</tt>
 *
 *  Returns <tt>NULL</tt> if <tt>elem</tt> is not in <tt>tree</tt>
 *
 *  @param tree the address of the <tt>splat</tt>
 *  @param elem the element
 *
 *  @return The element equal to <tt>elem</tt> in <tt>tree</tt>
 */
void *splat_search(splat *tree, void *elem);


#endif /* __SPLAT_H__ */
