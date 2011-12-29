/** @file splat.c
 *  @brief A splay tree library.
 *
 *  We malloc a node every time we insert a new element into the splay tree
 *  and free the node that wraps around the element returned by
 *  <tt>splay_remove</tt>.  We compare elements in the tree using the generic
 *  compare function that is given as an argument to <tt>splay_init</tt>.
 *
 *  @author Alexander Malyshev
 */

#include <assert.h>
#include <stdlib.h>
#include "splat.h"

static void clear(spnode *node);
static void splay(splat *tree, void *elem);
static spnode *rotate_left(spnode *node);
static spnode *rotate_right(spnode *node);
static spnode *init_node(void *elem);

void splat_init(splat *tree, cmpfn cmp) {
    assert(tree != NULL);
    assert(cmp != NULL);

    tree->cmp = cmp;
    tree->root = NULL;
}

void splat_clear(splat *tree) {
    assert(tree != NULL);

    clear(tree->root);
    tree->root = NULL;
}

static void clear(spnode *node) {
    if (node == NULL)
        return;

    clear(node->left);
    clear(node->right);
    free(node);
}

void splat_insert(splat *tree, void *elem) {
    spnode *new;
    int c;

    assert(tree != NULL);
    assert(elem != NULL);

    if (tree->root == NULL) {
        new = init_node(elem);
        tree->root = new;
        return;
    }

    splay(tree, elem);
    c = tree->cmp(elem, tree->root->elem);
    if (c == 0)
        return;

    new = init_node(elem);

    if (c < 0) {
        new->left = tree->root->left;
        new->right = tree->root;
        tree->root->left = NULL;
    } else {
        new->right = tree->root->right;
        new->left = tree->root;
        tree->root->right = NULL;
    }
    tree->root = new;
}

void *splat_remove(splat *tree, void *elem) {
    spnode *temp, *dead;
    void *removed;

    assert(tree != NULL);
    assert(elem != NULL);

    if (tree->root == NULL)
        return NULL;

    splay(tree, elem);

    if (tree->cmp(elem, tree->root->elem) != 0)
        return NULL;

    dead = tree->root;
    if (tree->root->left == NULL)
        tree->root = tree->root->right;
    else {
        temp = tree->root->right;
        tree->root = tree->root->left;
        splay(tree, elem);
        tree->root->right = temp;
    }
    removed = dead->elem;
    free(dead);
    return removed;
}

void *splat_search(splat *tree, void *elem) {
    assert(tree != NULL);
    assert(elem != NULL);

    if (tree->root == NULL)
        return NULL;

    splay(tree, elem);
    if (tree->cmp(tree->root->elem, elem) == 0)
        return tree->root->elem;
    return NULL;
}

static void splay(splat *tree, void *elem) {
    spnode assembler;
    spnode *left, *right;
    spnode *node;
    int c;

    cmpfn cmp = tree->cmp;

    assembler.left = NULL;
    assembler.right = NULL;

    left = &assembler;
    right = &assembler;

    node = tree->root;
    for (;;) {
        c = cmp(elem, node->elem);
        if (c < 0) {
            if (node->left == NULL)
                break;
            if (cmp(elem, node->left->elem) < 0) {
                node = rotate_right(node);
                if (node->left == NULL)
                    break;
            }
            /* link right */
            right->left = node;
            right = node;
            node = node->left;
        }
        else if (c > 0) {
            if (node->right == NULL)
                break;
            if (cmp(elem, node->right->elem) > 0) {
                node = rotate_left(node);
                if (node->right == NULL)
                    break;
            }
            /* link left */
            left->right = node;
            left = node;
            node = node->right;
        }
        else
            break;
    }
    /* assemble */
    left->right = node->left;
    right->left = node->right;
    node->left = assembler.right;
    node->right = assembler.left;
    tree->root = node;
}

static spnode *rotate_left(spnode *node) {
    spnode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

static spnode *rotate_right(spnode *node) {
    spnode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

static spnode *init_node(void *elem) {
    spnode *node = malloc(sizeof(spnode));
    assert(node != NULL);

    node->elem = elem;
    node->left = NULL;
    node->right = NULL;
    return node;
}
