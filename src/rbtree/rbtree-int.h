/** @file rbtree-int.h
 *  @brief Function prototypes for internal functions in the <tt>rbtree</tt>
 *         library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef RBTREE_INT_H_
#define RBTREE_INT_H_

/** @brief Frees all the nodes in a red black tree, including <tt>node</tt>.
 *  @param node the address of the red black tree we want to clear out.
 *  @return Void.
 */
static void clear(rbnode *node);

/** @brief Inserts <tt>elem</tt> into <tt>node</tt>.
 *
 *  <tt>elem</tt> is not <tt>NULL</tt> and <tt>cmp</tt> is not <tt>NULL</tt>.
 *
 *  @param node the address of the red black tree we want to insert
 *              <tt>elem</tt> into.
 *  @param elem the element we want to insert into <tt>node</tt>.
 *  @param cmp the compare function used to compare elements in <tt>node</tt>
 *             with <tt>elem</tt>.
 *  @return The resulting red black tree after inserting <tt>elem</tt> into
 *          <tt>node</tt>.
 */
static rbnode *insert(rbnode *node, void *elem, cmpfn cmp);

/** @brief Removes <tt>elem</tt> from <tt>node</tt> if it is in <tt>node</tt>.
 *
 *  None of the arguments are <tt>NULL</tt>. If the element is found in
 *  <tt>node</tt> its address will be stored in <tt>removed</tt>.
 *
 *  @param node the address of the red black tree we want to remove
 *              <tt>elem</tt> from.
 *  @param elem the element we want to remove from <tt>node</tt>.
 *  @param cmp the compare function used to compare elements in <tt>node</tt>
 *             with <tt>elem</tt>.
 *  @param removed the address where to store the removed element.
 *  @return The resulting red black tree after removing <tt>elem</tt> from
 *          <tt>node</tt>.
 */
static rbnode *remove(rbnode *node, void *elem, cmpfn cmp, void **removed);

/** @brief Maintains the red black tree invariants.
 *
 *  Will either rotate the red black tree at <tt>node</tt> or flip the color
 *  of <tt>node</tt> and both its children.
 *
 *  @param node the address of the red black tree we want to fix.
 *  @return The resulting red black tree after fixing <tt>node</tt>.
 */
static rbnode *fix(rbnode *node);

/** @brief Checks if a node is red.
 *
 *  If <tt>node</tt> is <tt>NULL</tt> it returns <tt>0</tt>.
 *
 *  @param node the address of a node whose color we want to check.
 *  @return <tt>1</tt> if <tt>node</tt> is red, <tt>0</tt> otherwise.
 */
static int is_red(rbnode *node);

/** @brief Rotates a red black tree to the left.
 *
 *  <tt>node</tt> is not <tt>NULL</tt> and has a non-<tt>NULL</tt> right child.
 *
 *  @param node the address of the red black tree we want to rotate.
 *  @return The resulting red black tree after rotating <tt>node</tt>.
 */
static rbnode *rotate_left(rbnode *node);

/** @brief Rotates a red black tree to the right.
 *
 *  <tt>node</tt> is not NULL and has a non-<tt>NULL</tt> left child.
 *
 *  @param node the address of the red black tree we want to rotate.
 *  @return The resulting red black tree after rotating <tt>node</tt>.
 */
static rbnode *rotate_right(rbnode *node);

/** @brief Flips the colors of <tt>node</tt> and both its children.
 *
 *  <tt>node</tt> is not <tt>NULL</tt> both of its children are
 *  non-<tt>NULL</tt>.
 *
 *  @param node the address of the node we want to flip the color of.
 *  @return Void.
 */
static void color_flip(rbnode *node);

/** @brief Returns the minimum value of a red black tree.
 *
 *  <tt>node</tt> is not <tt>NULL</tt>.
 *
 *  @param the address of the red black tree whose min we want.
 *  @return The minimum element in <tt>node</tt>.
 */
static void *min(rbnode *node);

/** @brief Rotates a red link to the right.
 *
 *  <tt>node</tt> is not <tt>NULL</tt> and has a non-<tt>NULL</tt> left child.
 *
 *  @param node the address of the red black tree we want to move.
 *  @return The resulting red black tree after moving <tt>node</tt>.
 */
static rbnode *move_red_right(rbnode *node);

/** @brief Removes the minimum element in <tt>node</tt>.
 *
 *  <tt>node</tt> is not <tt>NULL</tt>, <tt>node</tt> is red or the left child
 *  of node is red. We don't need to worry about <tt>node->data</tt> becoming
 *  a leak as it's been moved to another node in <tt>remove</tt>.
 *
 *  @param node the address of the red black tree whose min we want to remove.
 *  @return The resulting red black tree after deleting the min from
 *          <tt>node</tt>.
 */
static rbnode *remove_min(rbnode *node);

/** @brief Rotates a red link to the left.
 *
 *  <tt>node</tt> is not <tt>NULL</tt> and has a non-<tt>NULL</tt> right child.
 *
 *  @param node the address of the red black tree we want to move.
 *  @return The resulting red black tree after moving <tt>node</tt>.
 */
static rbnode *move_red_left(rbnode *node);

/** @brief Allocates a new <tt>rbnode</tt> with <tt>elem</tt> as its element.
 *  @param elem the address of the element we want the new node to store.
 *  @return A pointer to a new <tt>rbnode</tt>.
 */
static rbnode *init_node(void *elem);

#endif /* RBTREE_INT_H_ */
