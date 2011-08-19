/** @file splay.h
 *  @brief Function prototypes and structs for a splay tree data structure.
 *
 *  Implementation of a splay tree. The nodes in the splay tree store data
 *  as generic pointers (<tt>void *</tt>) where an element value of
 *  <tt>NULL</tt> cannot be stored. Elements are compared using a generic
 *  compare function.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef SPLAY_H_
#define SPLAY_H_

#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function. */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

/** @brief A node in a splay tree. */
typedef struct spnode_t {
    struct spnode_t *left;  /**< the left child of the node. */
    struct spnode_t *right; /**< the right child of the node. */
    void *elem;             /**< the element stored in the node. */
} spnode;

/** @brief A splay tree. */
typedef struct splaytree_t {
    spnode *root;           /**< the root node in the splay tree. */
    cmpfn cmp;              /**< the function for comparing elements. */
} splaytree;

/** @brief Initializes a new <tt>splaytree</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>cmp</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>splaytree</tt> we want to initialize.
 *  @param cmp the compare function that will be used by <tt>tree</tt>.
 *  @return Success status.
 */
int splay_init(splaytree *tree, cmpfn cmp);

/** @brief Removes all elements from <tt>tree</tt>.
 *
 *  Frees all nodes in <tt>tree</tt> but will not free the elements in the
 *  nodes.
 *
 *  @param tree the address of the <tt>splaytree</tt> we want to clear out.
 *  @return Success status.
 */
int splay_clear(splaytree *tree);

/** @brief Inserts <tt>elem</tt> into <tt>tree</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>splaytree</tt> we want to insert
 *              <tt>elem</tt> into.
 *  @param elem the element we want to insert into <tt>tree</tt>.
 *  @return Success status.
 */
int splay_insert(splaytree *tree, void *elem);

/** @brief Removes <tt>elem</tt> from <tt>tree</tt> if it is in <tt>tree</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>splaytree</tt> we want to remove
 *              <tt>elem</tt> from.
 *  @param elem the element we want to remove from <tt>tree</tt>.
 *  @return The element equal to <tt>elem</tt> if it exists in <tt>tree</tt>,
 *          <tt>NULL</tt> otherwise.
 */
void *splay_remove(splaytree *tree, void *elem);

/** @brief Searches <tt>tree</tt> for <tt>elem</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>splaytree</tt> we want to search for
 *              <tt>elem</tt>.
 *  @param elem the element we're searching for in <tt>tree</tt>.
 *  @return The element equal to <tt>elem</tt> if it exists in <tt>tree</tt>,
 *          <tt>NULL</tt> otherwise.
 */
void *splay_search(splaytree *tree, void *elem);

#endif /* SPLAY_H_ */
