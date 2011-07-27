/** @file splay.h
 *  @brief Function prototypes and structs for a splay tree data structure.
 *
 *  Implementation of a splay tree. The nodes in the splay tree store data
 *  as generic pointers (void *) where an element value of NULL cannot be
 *  stored. Elements are compared using a generic compare function.
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

/** @brief Initializes a new splaytree.
 *
 *  Will fail and return NULL if tree is NULL or cmp is NULL.
 *
 *  @param tree the address of the splaytree we want to initialize.
 *  @param cmp the compare function that will be used by the tree.
 *  @return Success status.
 */
int splay_init(splaytree *tree, cmpfn cmp);

/** @brief Removes all elements from tree.
 *
 *  Frees all nodes in tree but will not free the elements in the nodes.
 *
 *  @param tree the address of the splaytree we want to clear out.
 *  @return Success status.
 */
int splay_clear(splaytree *tree);

/** @brief Inserts elem into tree.
 *
 *  Will fail and return 1 if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the splaytree we want to insert elem into.
 *  @param elem the element we want to insert into tree.
 *  @return Success status.
 */
int splay_insert(splaytree *tree, void *elem);

/** @brief Removes elem from tree if it is in tree.
 *
 *  Will fail and return NULL if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the splaytree we want to remove elem from.
 *  @param elem the element we want to remove from tree.
 *  @return The element equal to elem if it exists in tree, NULL otherwise.
 */
void *splay_remove(splaytree *tree, void *elem);

/** @brief Searches tree for elem.
 *
 *  Will fail and return NULL if tree is NULL or elem is NULL.
 *
 *  @param tree the address of the splaytree we want to search for elem.
 *  @param elem the element we're searching for in tree.
 *  @return The element equal to elem if it exists in tree, NULL otherwise.
 */
void *splay_search(splaytree *tree, void *elem);

#endif /* SPLAY_H_ */
