/** @file rbtree.h
 *  @brief Function prototypes and structs for a red black tree data structure.
 *
 *  Implementation of a left leaning red black tree. The nodes in the red black
 *  tree store data as generic pointers (<tt>void *</tt>) where an element
 *  value of <tt>NULL</tt> cannot be stored. Elements are compared using a
 *  generic compare function.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef RBTREE_H_
#define RBTREE_H_

/** @brief The color value for red nodes. */
#define RED 0

/** @brief The color value for black nodes. */
#define BLACK 1

#ifndef CMPFN
#define CMPFN
/** @brief A generic compare function. */
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

/** @brief A node in a red black tree. */
typedef struct rbnode_t {
    struct rbnode_t *left;  /**< the left child of the node. */
    struct rbnode_t *right; /**< the right child of the node. */
    void *elem;             /**< the element stored in the node. */
    char color;             /**< the color of the node. */
} rbnode;

/** @brief A red black tree. */
typedef struct {
    rbnode *root;           /**< the root node in the red black tree. */
    cmpfn cmp;              /**< the function for comparing elements. */
} rbtree;

/** @brief Initializes a new <tt>rbtree</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tree</tt> is <tt>NULL</tt>
 *  or <tt>cmp</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt> we want to initialize.
 *  @param cmp the compare function that will be used by <tt>tree</tt>.
 *  @return Success status.
 */
int rbtree_init(rbtree *tree, cmpfn cmp);

/** @brief Removes all elements from <tt>tree</tt>.
 *
 *  Frees all the nodes in <tt>tree</tt> but will not free the elements in
 *  the nodes.
 *
 *  @param tree the address of the <tt>rbtree</tt> we want to clear out.
 *  @return Success status.
 */
int rbtree_clear(rbtree *tree);

/** @brief Inserts <tt>elem</tt> into <tt>tree</tt>.
 *
 *  Will fail and return <tt>1</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>. If <tt>elem</tt> is already in
 *  <tt>tree</tt> will simply return <tt>0</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt> we want to insert
 *              <tt>elem</tt> into.
 *  @param elem the element we want to insert into <tt>tree</tt>.
 *  @return Success status.
 */
int rbtree_insert(rbtree *tree, void *elem);

/** @brief Removes <tt>elem</tt> from <tt>tree</tt> if it is in <tt>tree</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt> we want to remove
 *              <tt>elem</tt> from.
 *  @param elem the element we want to remove from <tt>tree</tt>.
 *  @return The element equal to <tt>elem</tt> if it exists in <tt>tree</tt>,
 *          <tt>NULL</tt> otherwise.
 */
void *rbtree_remove(rbtree *tree, void *elem);

/** @brief Searches <tt>tree</tt> for <tt>elem</tt>.
 *
 *  Will fail and return <tt>NULL</tt> if <tt>tree</tt> is <tt>NULL</tt> or
 *  <tt>elem</tt> is <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt> we want to search for
 *              <tt>elem</tt>.
 *  @param elem the element we're searching for in <tt>tree</tt>.
 *  @return The element equal to <tt>elem</tt> if it exists in <tt>tree</tt>,
 *          <tt>NULL</tt> otherwise.
 */
void *rbtree_search(rbtree *tree, void *elem);

#endif /* RBTREE_H_ */
