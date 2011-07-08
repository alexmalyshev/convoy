/** @file rbtree.c
 *  @brief A red black tree library.
 *
 *  We malloc a node every time we insert a new element into the red black tree
 *  and free the node that wraps around the element returned by rbtree_remove.
 *  We compare elements in the tree using the compare function that is
 *  given as an argument to rbtree_init.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "rbtree.h"
#include "rbtree-int.h"

/** @brief Flips RED to BLACK and vice versa. */
#define FLIP(color) (!(color))

rbtree *rbtree_init(cmpfn cmp) {
    rbtree *tree;

    if (cmp == NULL)
        return NULL;

    if ((tree = malloc(sizeof(rbtree))) == NULL)
        return NULL;
    tree->root = NULL;
    tree->cmp = cmp;
    return tree;
}

int rbtree_destroy(rbtree *tree) {
    if (rbtree_clear(tree))
        return 1;

    free(tree);
    return 0;
}

int rbtree_insert(rbtree *tree, void *elem) {
    if (tree == NULL || elem == NULL)
        return 1;

    tree->root = insert(tree->root, elem, tree->cmp);
    if (tree->root == NULL)
        return 1;
    tree->root->color = BLACK;
    return 0;
}

static rbnode *insert(rbnode *node, void *elem, cmpfn cmp) {
    int c;

    if (node == NULL)
        return init_node(elem);

    c = cmp(elem, node->data);
    if (c < 0)
        node->left = insert(node->left, elem, cmp);
    else if (c > 0)
        node->right = insert(node->right, elem, cmp);
    else
        return node;

    return fix(node);
}

void *rbtree_remove(rbtree *tree, void *elem) {
    void *data = NULL;

    if (tree == NULL || elem == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;

    tree->root = remove(tree->root, elem, tree->cmp, &data);
    if (tree->root != NULL)
        tree->root->color = BLACK;
    return data;
}

static rbnode *remove(rbnode *node, void *elem, cmpfn cmp, void **data) {
    if (cmp(elem, node->data) < 0) {
        if (node->left == NULL)
            return node;
        if (!is_red(node->left) && !is_red(node->left->left))
            node = move_red_left(node);
        node->left = remove(node->left, elem, cmp, data);
    } else {
        if (is_red(node->left))
            node = rotate_right(node);
        if (node->right == NULL) {
            if (cmp(elem, node->data) == 0) {
                *data = node->data;
                free(node);
                return NULL;
            }
            return node;
        }
        if (!is_red(node->right) && !is_red(node->right->left))
            node = move_red_right(node);
        if (cmp(elem, node->data) == 0) {
            *data = node->data;
            node->data = min(node->right);
            node->right = remove_min(node->right);
        } else
            node->right = remove(node->right, elem, cmp, data);
    }
    return fix(node);
}

void *rbtree_search(rbtree *tree, void *elem) {
    rbnode *node;
    cmpfn cmp;
    int c;

    if (tree == NULL || elem == NULL)
        return NULL;

    node = tree->root;
    cmp = tree->cmp;
    while (node != NULL) {
        c = cmp(elem, node->data);
        if (c < 0)
            node = node->left;
        else if (c > 0)
            node = node->right;
        else
            return node->data;
    }
    return NULL;
}

int rbtree_clear(rbtree *tree) {
    if (tree == NULL)
        return 1;

    clear(tree->root);
    return 0;
}

static void clear(rbnode *node) {
    if (node == NULL)
        return;
    if (node->left != NULL)
        clear(node->left);
    if (node->right != NULL)
        clear(node->right);
    free(node);
}

static void *min(rbnode *node) {
    while (node->left != NULL)
        node = node->left;
    return node->data;
}

static rbnode *fix(rbnode *node) {
    if (is_red(node->right))
        node = rotate_left(node);
    if (is_red(node->left) && is_red(node->left->left))
        node = rotate_right(node);
    if (is_red(node->left) && is_red(node->right))
        color_flip(node);
    return node;
}

static int is_red(rbnode *node) {
    if (node == NULL)
        return 0;
    return node->color == RED;
}

static rbnode *rotate_left(rbnode *node) {
    rbnode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->color = node->color;
    node->color = RED;
    return temp;
}

static rbnode *rotate_right(rbnode *node) {
    rbnode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->color = node->color;
    node->color = RED;
    return temp;
}

static void color_flip(rbnode *node) {
    node->color = FLIP(node->color);
    node->left->color = FLIP(node->left->color);
    node->right->color = FLIP(node->right->color);
}

static rbnode *move_red_right(rbnode *node) {
    color_flip(node);
    if (is_red(node->left->left)) {
        node = rotate_right(node);
        color_flip(node);
    }
    return node;
}

static rbnode *remove_min(rbnode *node) {
    if (node->left == NULL) {
        free(node);
        return NULL;
    }
    if (!is_red(node->left) && !is_red(node->left->left))
        node = move_red_left(node);
    node->left = remove_min(node->left);
    return fix(node);
}

static rbnode *move_red_left(rbnode *node) {
    color_flip(node);
    if (is_red(node->right->left)) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        color_flip(node);
    }
    return node;
}

static rbnode *init_node(void *elem) {
    rbnode *node;

    if ((node = malloc(sizeof(rbnode))) == NULL)
        return NULL;
    node->data = elem;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    return node;
}
