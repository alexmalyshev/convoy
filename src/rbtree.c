/** @file rbtree.c
 *  @brief A red black tree library.
 *
 *  We malloc a node every time we insert a new element into the red black tree
 *  and free the node that wraps around the element returned by
 *  <tt>rbtree_remove</tt>. We compare elements in the tree using the compare
 *  function that is given as an argument to <tt>rbtree_init</tt>. This is a
 *  left-leaning red black tree there are fewer cases than usual.
 *
 *  @author Alexander Malyshev
 */

#include "rbtree.h"

#include <assert.h>
#include <stdlib.h>

static void clear(rbnode *node);
static rbnode *insert(rbnode *node, void *elem, cmpfn cmp);
static rbnode *remove(rbnode *node, void *elem, cmpfn cmp, void **removed);
static rbnode *fix(rbnode *node);
static int is_red(rbnode *node);
static rbnode *rotate_left(rbnode *node);
static rbnode *rotate_right(rbnode *node);
static void color_flip(rbnode *node);
static void *min(rbnode *node);
static rbnode *move_red_right(rbnode *node);
static rbnode *remove_min(rbnode *node);
static rbnode *move_red_left(rbnode *node);
static int flip(int color);
static rbnode *init_node(void *elem);


void rbtree_init(rbtree *tree, cmpfn cmp) {
    assert(tree != NULL);
    assert(cmp != NULL);

    tree->root = NULL;
    tree->cmp = cmp;
}

void rbtree_clear(rbtree *tree) {
    assert(tree != NULL);

    clear(tree->root);
    tree->root = NULL;
}

static void clear(rbnode *node) {
    void *left;
    void *right;

    if (node == NULL)
        return;

    left = node->left;
    right = node->right;

    free(node);

    clear(left);
    clear(right);
}

void rbtree_insert(rbtree *tree, void *elem) {
    assert(tree != NULL);
    assert(elem != NULL);

    tree->root = insert(tree->root, elem, tree->cmp);
    tree->root->color = BLACK;
}

static rbnode *insert(rbnode *node, void *elem, cmpfn cmp) {
    int c;

    assert(elem != NULL);
    assert(cmp != NULL);

    if (node == NULL)
        return init_node(elem);

    c = cmp(elem, node->elem);
    if (c < 0)
        node->left = insert(node->left, elem, cmp);
    else if (c > 0)
        node->right = insert(node->right, elem, cmp);
    else
        return node;

    return fix(node);
}

void *rbtree_remove(rbtree *tree, void *elem) {
    void *removed = NULL;

    assert(tree != NULL);
    assert(elem != NULL);

    if (tree->root == NULL)
        return NULL;

    tree->root = remove(tree->root, elem, tree->cmp, &removed);

    if (tree->root != NULL)
        tree->root->color = BLACK;

    return removed;
}

static rbnode *remove(rbnode *node, void *elem, cmpfn cmp, void **removed) {
    assert(node != NULL);
    assert(elem != NULL);
    assert(cmp != NULL);
    assert(removed != NULL);

    if (cmp(elem, node->elem) < 0) {
        if (node->left == NULL)
            return node;
        if (!is_red(node->left) && !is_red(node->left->left))
            node = move_red_left(node);
        node->left = remove(node->left, elem, cmp, removed);
    } else {
        if (is_red(node->left))
            node = rotate_right(node);
        if (node->right == NULL) {
            if (cmp(elem, node->elem) == 0) {
                *removed = node->elem;
                free(node);
                return NULL;
            }
            return node;
        }
        if (!is_red(node->right) && !is_red(node->right->left))
            node = move_red_right(node);
        if (cmp(elem, node->elem) == 0) {
            *removed = node->elem;
            node->elem = min(node->right);
            node->right = remove_min(node->right);
        } else
            node->right = remove(node->right, elem, cmp, removed);
    }

    return fix(node);
}

void *rbtree_search(rbtree *tree, void *elem) {
    rbnode *node;
    cmpfn cmp;
    int c;

    assert(tree != NULL);
    assert(elem != NULL);

    node = tree->root;
    cmp = tree->cmp;
    while (node != NULL) {
        c = cmp(elem, node->elem);
        if (c < 0)
            node = node->left;
        else if (c > 0)
            node = node->right;
        else
            return node->elem;
    }

    return NULL;
}

static void *min(rbnode *node) {
    assert(node != NULL);

    while (node->left != NULL)
        node = node->left;

    return node->elem;
}

static rbnode *fix(rbnode *node) {
    assert(node != NULL);

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
    rbnode *temp;

    assert(node != NULL);

    temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->color = node->color;
    node->color = RED;

    return temp;
}

static rbnode *rotate_right(rbnode *node) {
    rbnode *temp;

    assert(node != NULL);

    temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->color = node->color;
    node->color = RED;

    return temp;
}

static void color_flip(rbnode *node) {
    assert(node != NULL);

    node->color = flip(node->color);
    node->left->color = flip(node->left->color);
    node->right->color = flip(node->right->color);
}

static rbnode *move_red_right(rbnode *node) {
    assert(node != NULL);

    color_flip(node);

    if (is_red(node->left->left)) {
        node = rotate_right(node);
        color_flip(node);
    }

    return node;
}

static rbnode *remove_min(rbnode *node) {
    assert(node != NULL);

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
    assert(node != NULL);

    color_flip(node);

    if (is_red(node->right->left)) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        color_flip(node);
    }

    return node;
}

static int flip(int color) {
    return !color;
}

static rbnode *init_node(void *elem) {
    rbnode *node;

    assert(elem != NULL);

    node = malloc(sizeof(rbnode));
    assert(node != NULL);

    node->elem = elem;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;

    return node;
}
