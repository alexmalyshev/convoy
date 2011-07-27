/** @file rbtree-int.h
 *  @brief Function prototypes for internal functions in the rbtree library.
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#ifndef RBTREE_INT_H_
#define RBTREE_INT_H_

/** @brief Frees all the nodes in a red black tree, including node.
 *  @param node the address of the red black tree we want to clear out.
 *  @return Void.
 */
static void clear(rbnode *node);

/** @brief Inserts elem into node.
 *
 *  elem is not NULL and cmp is not NULL. 
 *
 *  @param node the address of the red black tree we want to insert elem into.
 *  @param elem the element we want to insert into node.
 *  @param cmp the compare function used to compare elements in node with elem.
 *  @return The resulting red black tree after inserting elem into node.
 */
static rbnode *insert(rbnode *node, void *elem, cmpfn cmp);

/** @brief Removes elem from node if it is in node.
 *
 *  None of the arguments are NULL. If the element is found in node its
 *  address will be stored in data.
 *
 *  @param node the address of the red black tree we want to remove elem from.
 *  @param elem the element we want to remove from node.
 *  @param cmp the compare function used to compare elements in node with elem.
 *  @param removed the address where to store the removed element.
 *  @return The resulting red black tree after removing elem from node.
 */
static rbnode *remove(rbnode *node, void *elem, cmpfn cmp, void **removed);

/** @brief Maintains the red black tree invariants.
 *
 *  Will either rotate the red black tree at node or flip the color of the
 *  node and both its children.
 *
 *  @param node the address of the red black tree we want to fix.
 *  @return The resulting red black tree after fixing node.
 */
static rbnode *fix(rbnode *node);

/** @brief Checks if a node is red.
 *
 *  If node is NULL it returns 0.
 *
 *  @param node the address of a node whose color we want to check.
 *  @return 1 if node is red, 0 otherwise.
 */
static int is_red(rbnode *node);

/** @brief Rotates a red black tree to the left.
 *
 *  node is not NULL and has a non-NULL right child.
 *
 *  @param node the address of the red black tree we want to rotate.
 *  @return The resulting red black tree after rotating node.
 */
static rbnode *rotate_left(rbnode *node);

/** @brief Rotates a red black tree to the right.
 *
 *  node is not NULL and has a non-NULL left child.
 *
 *  @param node the address of the red black tree we want to rotate.
 *  @return The resulting red black tree after rotating node.
 */
static rbnode *rotate_right(rbnode *node);

/** @brief Flips the colors of node and both its children.
 *
 *  node is not NULL both of its children are non-NULL.
 *
 *  @param node the address of the node we want to flip the color of.
 *  @return Void.
 */
static void color_flip(rbnode *node);

/** @brief Returns the minimum value of a red black tree.
 *
 *  node is not NULL.
 *
 *  @param the address of the red black tree whose min we want.
 *  @return The minimum element in node.
 */
static void *min(rbnode *node);

/** @brief Rotates a red link to the right.
 *
 *  node is not NULL and has a non-NULL left child.
 *
 *  @param node the address of the red black tree we want to move.
 *  @return The resulting red black tree after moving node.
 */
static rbnode *move_red_right(rbnode *node);

/** @brief Removes the minimum element in node.
 *
 *  node is not NULL, node is red or the left child of node is red.
 *  We don't need to worry about node->data becoming a leak as it's
 *  been moved to another node in 'remove'.
 *
 *  @param node the address of the red black tree whose min we want to remove.
 *  @return The resulting red black tree after deleting the min from node.
 */
static rbnode *remove_min(rbnode *node);

/** @brief Rotates a red link to the left.
 *
 *  node is not NULL and has a non-NULL right child.
 *
 *  @param node the address of the red black tree we want to move.
 *  @return The resulting red black tree after moving node.
 */
static rbnode *move_red_left(rbnode *node);

/** @brief Allocates a new rbnode with elem as its element.
 *  @param elem the address of the element we want the new node to store.
 *  @return A pointer to a new rbnode.
 */
static rbnode *init_node(void *elem);

#endif /* RBTREE_INT_H_ */
