#include <stdlib.h>
#include "rbtree.h"
#include "rbtree-int.h"

/* rbtree_init - allocs a new red black tree with the given compare function
 * Fails: tree is NULL or cmp is NULL, or if malloc fails */
int rbtree_init(rbtree **tree, cmpfun cmp) {
    if (tree == NULL || cmp == NULL)
        return 1;
    if ((*tree = malloc(sizeof(rbtree))) == NULL)
        return 1;

    (*tree)->root = NULL;
    (*tree)->cmp = cmp;
    return 0;
}

/* rbtree_destroy - empties out the given red black tree and frees all alloc'd
                    nodes and the tree struct itself
 * Warning: Will cause memory leaks if the elements in the tree were malloc'd
            and never get free'd after this function call
 * Fails: tree is NULL */
int rbtree_destroy(rbtree *tree) {
    if (rbtree_clear(tree))
        return 1;
    free(tree);
    return 0;
}

/* rbtree_clear - empties out the given red black tree and frees all alloc'd
                  nodes
 * Warning: Will cause memory leaks if the elements in the tree were malloc'd
            and never get free'd after this function call
 * Fails: tree is NULL */
int rbtree_clear(rbtree *tree) {
    if (tree == NULL)
        return 1;

    clear(tree->root);
    return 0;
}

/* clear - frees the given node and all of its children */
static void clear(rbnode *node) {
    if (node == NULL)
        return;
    if (node->left != NULL)
        clear(node->left);
    if (node->right != NULL)
        clear(node->right);
    free(node);
}

/* rbtree_search - scans the tree and returns element that corresponds to
                   the given item if it exists, otherwise returns NULL
 * Fails: tree is NULL or item is NULL */
void *rbtree_search(rbtree *tree, void *item) {
    rbnode *node;
    cmpfun cmp;
    int c;

    if (tree == NULL || item == NULL)
        return NULL;

    node = tree->root;
    cmp = tree->cmp;
    while (node != NULL) {
        c = cmp(item, node->data);
        if (c < 0)
            node = node->left;
        else if (c > 0)
            node = node->right;
        else
            return node->data;
    }
    return NULL;
}

/* rbtree_insert - inserts the given item into the given red black tree
 * Fails: tree is NULL or item is NULL */
int rbtree_insert(rbtree *tree, void *item) {
    if (tree == NULL || item == NULL)
        return 1;

    tree->root = insert(tree->root, item, tree->cmp);
    tree->root->color = BLACK;
    return 0;
}

/* insert - inserts the given item into the given red black tree
 * Fails: malloc call in init_node fails */
static rbnode *insert(rbnode *node, void *item, cmpfun cmp) {
    rbnode *new;
    int c;

    if (node == NULL) {
        init_node(&new, item);
        return new;
    }

    c = cmp(item, node->data);
    if (c < 0)
        node->left = insert(node->left, item, cmp);
    else if (c > 0)
        node->right = insert(node->right, item, cmp);
    else
        return node;

    return fix(node);
}

/* rbtree_delete - removes the given item from the given rbtree and
                   returns it if it exists, otherwise returns NULL
 * Fails: tree is NULL or item is NULL */
void *rbtree_delete(rbtree *tree, void *item) {
    void *data = NULL;

    if (tree == NULL || item == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;

    tree->root = delete(tree->root, item, tree->cmp, &data);
    if (tree->root != NULL)
        tree->root->color = BLACK;
    return data;
}

/* delete - deletes the given item from the given a red black tree
 * Invariant: node is an alloc'd rbnode */
static rbnode *delete(rbnode *node, void *item, cmpfun cmp, void **data) {
    if (cmp(item, node->data) < 0) {
        if (node->left == NULL)
            return node;
        if (!is_red(node->left) && !is_red(node->left->left))
            node = move_red_left(node);
        node->left = delete(node->left, item, cmp, data);
    } else {
        if (is_red(node->left))
            node = rotate_right(node);
        if (node->right == NULL) {
            if (cmp(item, node->data) == 0) {
                *data = node->data;
                free(node);
                return NULL;
            }
            return node;
        }
        if (!is_red(node->right) && !is_red(node->right->left))
            node = move_red_right(node);
        if (cmp(item, node->data) == 0) {
            *data = node->data;
            node->data = min(node->right);
            node->right = delete_min(node->right);
        } else
            node->right = delete(node->right, item, cmp, data);
    }
    return fix(node);
}

/* min - get the minimum value of a red black tree
 * Invariant: node is an alloc'd rbnode */
static void *min(rbnode *node) {
    while (node->left != NULL)
        node = node->left;
    return node->data;
}

/* fix - maintains the red black tree invariants for the given node and
         for both of its children
 * Invariant: node is an alloc'd rbnode */
static rbnode *fix(rbnode *node) {
    if (is_red(node->right))
        node = rotate_left(node);
    if (is_red(node->left) && is_red(node->left->left))
        node = rotate_right(node);
    if (is_red(node->left) && is_red(node->right))
        color_flip(node);
    return node;
}

/* is_red - 1 if the given node is RED, 0 otherwise */
static int is_red(rbnode *node) {
    if (node == NULL)
        return 0;
    return node->color == RED;
}

/* rotate_left - standard BST rotate to the left
 * Invariant: node is an alloc'd rbnode with an alloc'd right child */
static rbnode *rotate_left(rbnode *node) {
    rbnode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->color = node->color;
    node->color = RED;
    return temp;
}

/* rotate_right - standard BST rotate to the right
 * Invariant: node is an alloc'd rbnode with an alloc'd left child */
static rbnode *rotate_right(rbnode *node) {
    rbnode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->color = node->color;
    node->color = RED;
    return temp;
}

/* color_flip - flips the color of the given node and the colors of both of its
                children
 * Invariant: node is an alloc'd rbnode with two alloc'd children */
static void color_flip(rbnode *node) {
    node->color = FLIP(node->color);
    node->left->color = FLIP(node->left->color);
    node->right->color = FLIP(node->right->color);
}

/* move_red_right - rotate a red link to the right
 * Invariant: node is an alloc'd rbnode with an alloc'd left child */
static rbnode *move_red_right(rbnode *node) {
    color_flip(node);
    if (is_red(node->left->left)) {
        node = rotate_right(node);
        color_flip(node);
    }
    return node;
}

/* delete_min - delete the minimum node in a rbtree by carrying a red link
                down the left side
 * Invariant: node is an alloc'd node, node is RED or node->left is RED,
              and we don't need to worry about node->data becoming a memory
              leak as we've moved it to another node in 'delete' */
static rbnode *delete_min(rbnode *node) {
    if (node->left == NULL) {
        free(node);
        return NULL;
    }
    if (!is_red(node->left) && !is_red(node->left->left))
        node = move_red_left(node);
    node->left = delete_min(node->left);
    return fix(node);
}

/* move_red_left - rotate a red link to the left
 * Invariant: *node is an alloc'd rbnode with an alloc'd right child */
static rbnode *move_red_left(rbnode *node) {
    color_flip(node);
    if (is_red(node->right->left)) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        color_flip(node);
    }
    return node;
}

/* init_node - allocs a new rbnode with the given item as the data
 * Fails: malloc fails */
static int init_node(rbnode **node, void *item) {
    if ((*node = malloc(sizeof(rbnode))) == NULL)
        return 1;
    (*node)->data = item;
    (*node)->color = RED;
    (*node)->left = NULL;
    (*node)->right = NULL;
    return 0;
}
