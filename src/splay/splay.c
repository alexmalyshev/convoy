/** @file splay.c
 *  @brief A splay tree library.
 *
 *  We malloc a node every time we insert a new element into the splay tree
 *  and free the node that wraps around the element returned by splay_remove.
 *  We compare elements in the tree using the generic compare function that is
 *  given as an argument to splay_init.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "splay.h"
#include "splay-int.h"

int splay_init(splaytree *tree, cmpfn cmp) {
    if (tree == NULL || cmp == NULL)
        return 1;

    tree->cmp = cmp;
    tree->root = NULL;
    return 0;
}

int splay_clear(splaytree *tree) {
    if (tree == NULL)
        return 0;

    clear(tree->root);
    tree->root = NULL;
    return 0;
}

static void clear(spnode *node) {
    if (node == NULL)
        return;

    clear(node->left);
    clear(node->right);
    free(node);
}

int splay_insert(splaytree *tree, void *elem) {
    spnode *new;
    int c;

    if (tree == NULL || elem == NULL)
        return 1;

    if (tree->root == NULL) {
        if ((new = init_node(elem)) == NULL)
            return 1;
        tree->root = new;
        return 0;
    }

    splay(tree, elem);
    c = tree->cmp(elem, tree->root->data);
    if (c == 0)
        return 0;

    if ((new = init_node(elem)) == NULL)
        return 1;

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
    return 0;
}

void *splay_remove(splaytree *tree, void *elem) {
    spnode *temp, *dead;
    void *data;

    if (tree == NULL || tree->root == NULL || elem == NULL)
        return NULL;

    splay(tree, elem);

    if (tree->cmp(elem, tree->root->data) != 0)
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
    data = dead->data;
    free(dead);
    return data;
}

void *splay_search(splaytree *tree, void *elem) {
    if (tree == NULL || tree->root == NULL || elem == NULL)
        return NULL;

    splay(tree, elem);
    if (tree->cmp(tree->root, elem) == 0)
        return tree->root->data;
    return NULL;
}

static void splay(splaytree *tree, void *elem) {
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
    while (1) {
        c = cmp(elem, node->data);
        if (c < 0) {
            if (node->left == NULL)
                break;
            if (cmp(elem, node->left->data) < 0) {
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
            if (cmp(elem, node->right->data) > 0) {
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
    spnode *node;

    if ((node = malloc(sizeof(spnode))) == NULL)
        return NULL;

    node->data = elem;
    node->left = NULL;
    node->right = NULL;
    return node;
}
