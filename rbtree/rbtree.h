/** @file rbtree.h
 *  @brief Function prototypes and structs for a red black tree data structure.
 *
 *  Implementation of a left leaning red black tree. The nodes in the red black
 *  tree store data as generic pointers (void *) where an element of NULL
 *  cannot be stored. Elements are compared using a generic compare function.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef RBTREE_H_
#define RBTREE_H_

/** @brief The color value for red nodes */
#define RED 0

/** @brief The color value for black nodes */
#define BLACK 1

/** @brief A generic compare function */
typedef int (*cmpfun)(void *, void *);

/** @brief A node in a red black tree.
 *
 *  Stores pointers to its left and right child, a data pointer and a color.
 */
typedef struct rbnode_t {
    struct rbnode_t *left;
    struct rbnode_t *right;
    void *data;
    int color;
} rbnode;

/** @brief A red black tree.
 *
 *  Stores the root node of the tree as well as a compare function.
 */
typedef struct {
    rbnode *root;
    cmpfun cmp;
} rbtree;

/** @brief Allocates and initializes a new rbtree.
 *  @param cmp the compare function that will be used by the tree.
 *  @return A pointer to a new rbtree.
 */
rbtree *rbtree_init(cmpfun cmp);

/** @brief Frees the nodes in tree and tree itself.
 *
 *  Will not free the elements stored in the nodes of tree.
 *
 *  @param tree the address of the rbtree we want to deallocate.
 *  @return Success status.
 */
int rbtree_destroy(rbtree *tree);

/** @brief Removes elem from tree if it is in tree.
 *
 *  Will fail and return NULL if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the rbtree we want to remove elem from.
 *  @param elem the element we want to remove from tree.
 *  @return The element equal to elem if it exists in tree, NULL otherwise.
 */
void *rbtree_delete(rbtree *tree, void *elem);

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

/** @brief Searches tree for elem.
 *
 *  Will fail and return NULL if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the rbtree we want to search for elem.
 *  @param elem the element we're searching for in tree.
 *  @return The element equal to elem if it exists in tree, NULL otherwise.
 */
void *rbtree_search(rbtree *tree, void *elem);

/** @brief Removes all elements from tree.
 *
 *  Frees all nodes in tree but will not free the elements in the nodes.
 *
 *  @param tree the address of the rbtree we want to clear out.
 *  @return Success status.
 */
int rbtree_clear(rbtree *tree);

#endif /* RBTREE_H_ */
