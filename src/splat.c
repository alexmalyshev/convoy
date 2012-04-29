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


#include "splat.h"

#include <assert.h>
#include <stdlib.h>


static void clear(spnode *node);

static void splay(splat *tree, void *elem);

static spnode *rotate_left(spnode *node);
static spnode *rotate_right(spnode *node);

static spnode *init_node(void *elem);


int splat_init(splat *tree, cmpfn cmp) {
    if (tree == NULL || cmp == NULL)
        return -1;

    tree->cmp = cmp;
    tree->root = NULL;

    return 0;
}


int splat_clear(splat *tree) {
    if (tree == NULL)
        return -1;

    clear(tree->root);

    tree->root = NULL;

    return 0;
}


static void clear(spnode *node) {
    spnode *left;
    spnode *right;

    if (node == NULL)
        return;

    left = node->left;
    right = node->right;

    free(node);

    clear(left);
    clear(right);
}


int splat_insert(splat *tree, void *elem) {
    spnode *new;
    int c;

    if (tree == NULL || elem == NULL)
        return -1;

    if (tree->root == NULL) {
        new = init_node(elem);
        if (new == NULL)
            return -1;

        tree->root = new;
        return 0;
    }

    splay(tree, elem);

    c = tree->cmp(elem, tree->root->elem);

    /* if the element is already in the tree, just return */
    if (c == 0)
        return 0;

    new = init_node(elem);
    if (new == NULL)
        return -1;

    if (c < 0) {
        new->left = tree->root->left;
        new->right = tree->root;
        tree->root->left = NULL;
    }
    else {
        new->right = tree->root->right;
        new->left = tree->root;
        tree->root->right = NULL;
    }

    tree->root = new;

    return 0;
}


void *splat_remove(splat *tree, void *elem) {
    spnode *temp;
    spnode *dead;
    void *removed;

    if (tree == NULL || elem == NULL)
        return NULL;

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
    if (tree == NULL || elem == NULL)
        return NULL;

    if (tree->root == NULL)
        return NULL;

    splay(tree, elem);

    if (tree->cmp(tree->root->elem, elem) == 0)
        return tree->root->elem;

    return NULL;
}


static void splay(splat *tree, void *elem) {
    spnode assembler;
    spnode *left = &assembler;
    spnode *right = &assembler;
    spnode *node;
    int c;

    assembler.left = NULL;
    assembler.right = NULL;

    assert(tree != NULL);
    assert(elem != NULL);

    node = tree->root;
    while (1) {
        c = tree->cmp(elem, node->elem);
        if (c < 0) {
            if (node->left == NULL)
                break;
            if (tree->cmp(elem, node->left->elem) < 0) {
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
            if (tree->cmp(elem, node->right->elem) > 0) {
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
    spnode *temp;

    assert(node != NULL);
    assert(node->right != NULL);

    temp = node->right;
    node->right = temp->left;
    temp->left = node;

    return temp;
}

static spnode *rotate_right(spnode *node) {
    spnode *temp;

    assert(node != NULL);
    assert(node->left != NULL);

    temp = node->left;
    node->left = temp->right;
    temp->right = node;

    return temp;
}

static spnode *init_node(void *elem) {
    spnode *new;

    assert(elem != NULL);

    new = malloc(sizeof(spnode));
    if (new == NULL)
        return NULL;

    new->elem = elem;
    new->left = NULL;
    new->right = NULL;

    return new;
}
