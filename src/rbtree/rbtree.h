/** @file rbtree.h
 *  @brief Function prototypes and structs for a red black tree data structure.
 *
 *  Implementation of a left leaning red black tree. The nodes in the red black
 *  tree store data as generic pointers (void *) where an element value of NULL
 *  cannot be stored. Elements are compared using a generic compare function.
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
    void *data;             /**< the element of data stored in the node. */
    int color;              /**< the color of the node. */
} rbnode;

/** @brief A red black tree. */
typedef struct {
    rbnode *root;           /**< the root node in the red black tree. */
    cmpfn cmp;              /**< the function for comparing elements. */
} rbtree;

/** @brief Initializes a new rbtree.
 *
 *  Will fail and return NULL if tree is NULL or cmp is NULL.
 *
 *  @param tree the address of the rbtree we want to initialize.
 *  @param cmp the compare function that will be used by the tree.
 *  @return Success status.
 */
int rbtree_init(rbtree *tree, cmpfn cmp);

/** @brief Removes all elements from tree.
 *
 *  Frees all the nodes in tree but will not free the elements in the nodes.
 *
 *  @param tree the address of the rbtree we want to clear out.
 *  @return Success status.
 */
int rbtree_clear(rbtree *tree);

/** @brief Inserts elem into tree.
 *
 *  Will fail and return 1 if tree is NULL or elem is NULL. If elem is already
 *  in tree will do nothing but return successfully.
 *
 *  @param tree the address of the rbtree we want to insert elem into.
 *  @param elem the element we want to insert into tree.
 *  @return Success status.
 */
int rbtree_insert(rbtree *tree, void *elem);

/** @brief Removes elem from tree if it is in tree.
 *
 *  Will fail and return NULL if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the rbtree we want to remove elem from.
 *  @param elem the element we want to remove from tree.
 *  @return The element equal to elem if it exists in tree, NULL otherwise.
 */
void *rbtree_remove(rbtree *tree, void *elem);

/** @brief Searches tree for elem.
 *
 *  Will fail and return NULL if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the rbtree we want to search for elem.
 *  @param elem the element we're searching for in tree.
 *  @return The element equal to elem if it exists in tree, NULL otherwise.
 */
void *rbtree_search(rbtree *tree, void *elem);

#endif /* RBTREE_H_ */
