#include <stdlib.h>
#include "splay.h"
#include "splay-int.h"

/* splay_init - allocs a new splaytree
 * Fails: tree is NULL or cmp is NULL, or if malloc fails */
int splay_init(splaytree **tree, cmpfun cmp) {
    if (tree == NULL || cmp == NULL)
        return 1;

    if ((*tree = malloc(sizeof(splaytree))) == NULL)
        return 1;
    (*tree)->cmp = cmp;
    (*tree)->root = NULL;
    return 0;
}

/* splay_destroy - frees all nodes of splaytree and the tree struct itself
 * Warning: Will cause memory leaks if the elements in the tree were malloc'd
            and never get free'd after this function call
 * Fails: tree is NULL */
int splay_destroy(splaytree *tree) {
    if (splay_clear(tree))
        return 1;
    free(tree);
    return 0;
}

/* splay_delete - will delete the given element from the tree if it exists
                  and return it, returns NULL if it doesn't
 * Fails: tree is NULL or elem is NULL */
void *splay_delete(splaytree *tree, void *elem) {
    splaynode *temp, *dead;
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

/* splay_insert - inserts the given element into the splay tree
 * Fails: tree is NULL or elem is NULL, or if calloc fails in init_node */
int splay_insert(splaytree *tree, void *elem) {
    splaynode *new;
    int c;

    if (tree == NULL || elem == NULL)
        return 1;

    if (tree->root == NULL) {
        if (init_node(&new, elem))
            return 1;
        tree->root = new;
        return 0;
    }

    splay(tree, elem);
    c = tree->cmp(elem, tree->root->data);
    if (c == 0)
        return 0;

    if (init_node(&new, elem))
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

/* splay_search - checks if the given element is in the tree
 * Fails: tree is NULL or elem is NULL */
void *splay_search(splaytree *tree, void *elem) {
    if (tree == NULL || tree->root == NULL || elem == NULL)
        return NULL;

    splay(tree, elem);
    if (tree->cmp(tree->root, elem) == 0)
        return tree->root->data;
    return NULL;
}

/* splay_clear - clears out the splaytree, frees all nodes
 * Warning: Will cause memory leaks if the elements in the tree were malloc'd
            and never get free'd after this function call
 * Fails: tree is NULL */
int splay_clear(splaytree *tree) {
    if (tree == NULL)
        return 0;
    clear(tree->root);
    return 0;
}

/* clear - recursively clears out a binary tree by freeing all the nodes */
static void clear(splaynode *node) {
    if (node == NULL)
        return;
    clear(node->left);
    clear(node->right);
    free(node);
}

/* splay - if the given element exists in the tree, the node containing it
           will become the new root of the tree. if the element is not in the
           tree, then the new root will either be the greatest element less
           than the given element, or the least element greater than the given
           element.
 * Invariant: tree is not NULL, tree->root is not NULL */
static void splay(splaytree *tree, void *elem) {
    splaynode assembler;
    splaynode *left, *right;
    splaynode *node;
    int c;

    cmpfun cmp = tree->cmp;

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

/* rotate_left - standard BST rotation to the left
 * Invariant: node is an alloc'd node with an alloc'd right child */
static splaynode *rotate_left(splaynode *node) {
    splaynode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

/* rotate_right - standard BST rotation to the right
 * Invariant: node is an alloc'd node with an alloc'd left child */
static splaynode *rotate_right(splaynode *node) {
    splaynode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

/* init_node - allocs a new splaynode with the given element as the data */
static int init_node(splaynode **node, void *elem) {
    if ((*node = malloc(sizeof(splaynode))) == NULL)
        return 1;
    (*node)->data = elem;
    (*node)->left = NULL;
    (*node)->right = NULL;
    return 0;
}
