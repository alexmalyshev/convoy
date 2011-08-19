/** @file splay-int.h
 *  @brief Function prototypes for internal functions in the <tt>splaytree</tt>
 *         library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef SPLAY_INT_H_
#define SPLAY_INT_H_

/** @brief Frees all the nodes in a splay tree, including <tt>node</tt>.
 *  @param node the address of the splay tree we want to clear out.
 *  @return Void.
 */
static void clear(spnode *node);

/** @brief Moves the node in <tt>tree</tt> with the element closest to
 *         <tt>elem</tt> as the <tt>root</tt>.
 *
 *  If <tt>elem</tt> exists in <tt>tree</tt>, the node containing the element
 *  equal to <tt>elem</tt> will be the new root of <tt>tree</tt>. If
 *  <tt>elem</tt> is not in <tt>tree</tt>, then the new root will either be
 *  the greatest element less than <tt>elem</tt>, or the least element greater
 *  than <tt>elem</tt>. <tt>tree</tt> is not <tt>NULL</tt>, <tt>tree->root</tt>
 *  is not <tt>NULL</tt>, and <tt>elem</tt> is not <tt>NULL</tt>.
 *
 *  @param tree the address of the <tt>splaytree</tt> we want to splay using
 *              <tt>elem</tt>.
 *  @param elem the element that will rebalance <tt>tree</tt>.
 *  @return Void.
 */
static void splay(splaytree *tree, void *elem);

/** @brief Rotates <tt>node</tt> over to the left.
 *
 *  <tt>node</tt> is not NULL and <tt>node->right</tt> is not <tt>NULL</tt>.
 *
 *  @param node the address of the splay tree we want to rotate.
 *  @return The new splay tree resulting from rotating <tt>node</tt> to the
 *          left.
 */
static spnode *rotate_left(spnode *node);

/** @brief Rotates <tt>node</tt> over to the right.
 *
 *  <tt>node</tt> is not <tt>NULL</tt> and <tt>node->left</tt> is not
 *  <tt>NULL</tt>.
 *
 *  @param node the address of the splay tree we want to rotate.
 *  @return The new splay tree resulting from rotating <tt>node</tt> to the
 *          right.
 */
static spnode *rotate_right(spnode *node);

/** @brief Allocates a new <tt>spnode</tt> with <tt>elem</tt> as its element.
 *  @param elem the address of the element we want the new node to store.
 *  @return A pointer to a new <tt>spnode</tt>.
 */
static spnode *init_node(void *elem);

#endif /* SPLAY_INT_H_ */
