/** @file rbtree.h
 *  @brief Header for a red black tree data structure library.
 *
 *  An <tt>rbtree</tt> is binary tree. Elements are stored as generic pointers
 *  (<tt>void *</tt>), however <tt>NULL</tt> cannot be stored. Elements are
 *  compared using a generic compare function. Inserting into an
 *  <tt>rbtree</tt> will always succeed provided there is enough memory on the
 *  system. Getting a <tt>NULL</tt> back as an element from an <tt>rbtree</tt>
 *  means that key has no mapped value in the tree.
 *
 *  @author Alexander Malyshev
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
    struct rbnode_t *left;  /**< the left child. */
    struct rbnode_t *right; /**< the right child. */
    void *elem;             /**< the element. */
    char color;             /**< the color. */
} rbnode;

/** @brief A red black tree. */
typedef struct {
    rbnode *root;           /**< the root node. */
    cmpfn cmp;              /**< the function for comparing elements. */
} rbtree;

/** @brief Initializes a new <tt>rbtree</tt>.
 *
 *  Asserts that <tt>tree</tt> and <tt>cmp</tt> are not <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt>.
 *  @param cmp the compare function for <tt>tree</tt>.
 */
void rbtree_init(rbtree *tree, cmpfn cmp);

/** @brief Removes all elements from <tt>tree</tt>.
 *
 *  Asserts that <tt>tree</tt> is not <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt>.
 */
void rbtree_clear(rbtree *tree);

/** @brief Inserts <tt>elem</tt> into <tt>tree</tt>.
 *
 *  Asserts that <tt>tree</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *  If <tt>elem</tt> is already in <tt>tree</tt> then this just returns.
 *
 *  @param tree the address of the <tt>rbtree</tt>.
 *  @param elem the element..
 */
void rbtree_insert(rbtree *tree, void *elem);

/** @brief Removes <tt>elem</tt> from <tt>tree</tt>.
 *
 *  Asserts that <tt>tree</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *  Returns <tt>NULL</tt> if <tt>elem</tt> is not in <tt>tree</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt>.
 *  @param elem the element.
 *  @return The element equal to <tt>elem</tt> in <tt>tree</tt>.
 */
void *rbtree_remove(rbtree *tree, void *elem);

/** @brief Searches <tt>tree</tt> for <tt>elem</tt>.
 *
 *  Asserts that <tt>tree</tt> and <tt>elem</tt> are not <tt>NULL</tt>.
 *  Returns <tt>NULL</tt> if <tt>elem</tt> is not in <tt>tree</tt>.
 *
 *  @param tree the address of the <tt>rbtree</tt>.
 *  @param elem the element.
 *  @return The element equal to <tt>elem</tt> in <tt>tree</tt>.
 */
void *rbtree_search(rbtree *tree, void *elem);

#endif /* RBTREE_H_ */
