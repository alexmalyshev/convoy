/** @file splay-int.h
 *  @brief Function prototypes for internal functions in the splaytree library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef SPLAY_INT_H_
#define SPLAY_INT_H_

/** @brief Frees all the nodes in a splay tree, including node.
 *  @param node the address of the splay tree we want to clear out.
 *  @return Void.
 */
static void clear(spnode *node);

/** @brief Moves the node in tree with the element closest to elem as the root.
 *
 *  If elem exists in tree, the node containing the element equal to elem will
 *  be the new root of tree. If elem is not in tree, then the new root will
 *  either be the greatest element less than elem, or the least element greater
 *  than elem. tree is not NULL, tree->root is not NULL, and elem is not NULL.
 *
 *  @param tree the address of the splaytree we want to splay using elem.
 *  @param elem the element that will rebalance tree.
 *  @return Void.
 */
static void splay(splaytree *tree, void *elem);

/** @brief Rotates node over to the left.
 *
 *  node is not NULL and node->right is not NULL.
 *
 *  @param node the address of the splay tree we want to rotate.
 *  @return The new splay tree resulting from rotating node to the left.
 */
static spnode *rotate_left(spnode *node);

/** @brief Rotates node over to the right.
 *
 *  node is not NULL and node->left is not NULL.
 *
 *  @param node the address of the splay tree we want to rotate.
 *  @return The new splay tree resulting from rotating node to the right.
 */
static spnode *rotate_right(spnode *node);

/** @brief Allocates a new spnode with elem as its element.
 *  @param elem the address of the data we want the new node to store.
 *  @return A pointer to a new spnode.
 */
static spnode *init_node(void *elem);

#endif /* SPLAY_INT_H_ */
