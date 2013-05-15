/** @file splat.h
 *  @brief Header for a splay tree data structure
 *
 *  @author Alexander Malyshev
 */

#ifndef __SPLAT_H__
#define __SPLAT_H__

#include <assert.h>
#include <stddef.h>


/** @brief Declares a new splay tree type
 *
 *  ELEM_TYPE must be the name of a struct type
 *
 *  @param SPLAT_TYPE the type of the splay tree
 *  @param ELEM_TYPE the type of the tree's elements
 */
#define SPLAT_NEW(SPLAT_TYPE, ELEM_TYPE)    \
    typedef struct SPLAT_TYPE {             \
        struct ELEM_TYPE *root;             \
    } SPLAT_TYPE

/** @brief Declares a link in a struct for use with a splay tree
 *
 *  ELEM_TYPE must be the name of a struct type
 *
 *  @param ELEM_TYPE the type of the element
 *  @param LINK the name of the link field
 */
#define SPLAT_LINK(ELEM_TYPE, LINK) \
    struct {                        \
        struct ELEM_TYPE *left;     \
        struct ELEM_TYPE *right;    \
    } LINK

/** @brief Initializes a splay tree
 *
 *  @param TREE the address of the splay tree
 */
#define SPLAT_INIT(TREE) do {   \
    assert((TREE) != NULL);     \
                                \
    (TREE)->root = NULL;        \
} while (0)

/// @brief Statically initializes a splay tree
#define SPLAT_STATIC_INIT { \
    .root = NULL            \
}

/** @brief Initializes the splay tree link of an element
 *
 *  @param ELEM the address of the element
 *  @param LINK the name of the link field
 */
#define SPLAT_ELEM_INIT(ELEM, LINK) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->LINK.left = NULL;               \
    (ELEM)->LINK.right = NULL;              \
} while (0)


/** @brief Defines a new splay tree library
 *
 *  @param SPLAT_TYPE the type of the splay tree
 *  @param ELEM_TYPE the type of the tree's elements
 *  @param KEY_TYPE the type of the elements' keys
 *  @param CMP a compare function/macro that works on keys
 *  @param LINK the name of the link field
 *  @param KEY the name of the key field
 */
#define SPLAT_LIB(SPLAT_TYPE, ELEM_TYPE, KEY_TYPE, CMP, LINK, KEY)          \
                                                                            \
static void SPLAT_TYPE##_splay(SPLAT_TYPE *tree, KEY_TYPE key);             \
static struct ELEM_TYPE *SPLAT_TYPE##_rotate_left(struct ELEM_TYPE *node);  \
static struct ELEM_TYPE *SPLAT_TYPE##_rotate_right(struct ELEM_TYPE *node); \
                                                                            \
                                                                            \
void SPLAT_TYPE##_insert(SPLAT_TYPE *tree, struct ELEM_TYPE *new) {         \
    int c;                                                                  \
                                                                            \
    assert(tree != NULL);                                                   \
    assert(new != NULL);                                                    \
                                                                            \
    if (tree->root == NULL) {                                               \
        tree->root = new;                                                   \
        return;                                                             \
    }                                                                       \
                                                                            \
    SPLAT_TYPE##_splay(tree, new->KEY);                                     \
                                                                            \
    c = CMP(new->KEY, tree->root->KEY);                                     \
                                                                            \
    if (c == 0)                                                             \
        return;                                                             \
                                                                            \
    if (c < 0) {                                                            \
        new->LINK.left = tree->root->LINK.left;                             \
        new->LINK.right = tree->root;                                       \
        tree->root->LINK.left = NULL;                                       \
    }                                                                       \
    else {                                                                  \
        new->LINK.right = tree->root->LINK.right;                           \
        new->LINK.left = tree->root;                                        \
        tree->root->LINK.right = NULL;                                      \
    }                                                                       \
                                                                            \
    tree->root = new;                                                       \
}                                                                           \
                                                                            \
struct ELEM_TYPE *SPLAT_TYPE##_search(SPLAT_TYPE *tree, KEY_TYPE key) {     \
    assert(tree != NULL);                                                   \
                                                                            \
    if (tree->root == NULL)                                                 \
        return NULL;                                                        \
                                                                            \
    SPLAT_TYPE##_splay(tree, key);                                          \
                                                                            \
    if (CMP(key, tree->root->KEY) == 0)                                     \
        return tree->root;                                                  \
                                                                            \
    return NULL;                                                            \
}                                                                           \
                                                                            \
struct ELEM_TYPE *SPLAT_TYPE##_remove(SPLAT_TYPE *tree, KEY_TYPE key) {     \
    struct ELEM_TYPE *temp;                                                 \
    struct ELEM_TYPE *removed = SPLAT_TYPE##_search(tree, key);             \
                                                                            \
    if (removed == NULL)                                                    \
        return NULL;                                                        \
                                                                            \
    if (tree->root->LINK.left == NULL)                                      \
        tree->root = tree->root->LINK.right;                                \
    else {                                                                  \
        temp = tree->root->LINK.right;                                      \
        tree->root = tree->root->LINK.left;                                 \
        SPLAT_TYPE##_splay(tree, key);                                      \
        tree->root->LINK.right = temp;                                      \
    }                                                                       \
                                                                            \
    return removed;                                                         \
}                                                                           \
                                                                            \
static void SPLAT_TYPE##_splay(SPLAT_TYPE *tree, KEY_TYPE key) {            \
    struct ELEM_TYPE assembler;                                             \
    struct ELEM_TYPE *left = &assembler;                                    \
    struct ELEM_TYPE *right = &assembler;                                   \
    struct ELEM_TYPE *node;                                                 \
    int c;                                                                  \
                                                                            \
    assert(tree != NULL);                                                   \
                                                                            \
    assembler.LINK.left = NULL;                                             \
    assembler.LINK.right = NULL;                                            \
                                                                            \
    node = tree->root;                                                      \
    while (1) {                                                             \
        c = CMP(key, node->KEY);                                            \
        if (c < 0) {                                                        \
            if (node->LINK.left == NULL)                                    \
                break;                                                      \
            if (CMP(key, node->LINK.left->KEY) < 0) {                       \
                node = SPLAT_TYPE##_rotate_right(node);                     \
                if (node->LINK.left == NULL)                                \
                    break;                                                  \
            }                                                               \
            /* link right */                                                \
            right->LINK.left = node;                                        \
            right = node;                                                   \
            node = node->LINK.left;                                         \
        }                                                                   \
        else if (c > 0) {                                                   \
            if (node->LINK.right == NULL)                                   \
                break;                                                      \
            if (CMP(key, node->LINK.right->KEY) > 0) {                      \
                node = SPLAT_TYPE##_rotate_left(node);                      \
                if (node->LINK.right == NULL)                               \
                    break;                                                  \
            }                                                               \
            /* link left */                                                 \
            left->LINK.right = node;                                        \
            left = node;                                                    \
            node = node->LINK.right;                                        \
        }                                                                   \
        else                                                                \
            break;                                                          \
    }                                                                       \
    /* assemble */                                                          \
    left->LINK.right = node->LINK.left;                                     \
    right->LINK.left = node->LINK.right;                                    \
    node->LINK.left = assembler.LINK.right;                                 \
    node->LINK.right = assembler.LINK.left;                                 \
                                                                            \
    tree->root = node;                                                      \
}                                                                           \
                                                                            \
static struct ELEM_TYPE *SPLAT_TYPE##_rotate_left(struct ELEM_TYPE *node) { \
    struct ELEM_TYPE *temp;                                                 \
                                                                            \
    assert(node != NULL);                                                   \
    assert(node->LINK.right != NULL);                                       \
                                                                            \
    temp = node->LINK.right;                                                \
    node->LINK.right = temp->LINK.left;                                     \
    temp->LINK.left = node;                                                 \
                                                                            \
    return temp;                                                            \
}                                                                           \
                                                                            \
static struct ELEM_TYPE *                                                   \
SPLAT_TYPE##_rotate_right(struct ELEM_TYPE *node) {                         \
    struct ELEM_TYPE *temp;                                                 \
                                                                            \
    assert(node != NULL);                                                   \
    assert(node->LINK.left != NULL);                                        \
                                                                            \
    temp = node->LINK.left;                                                 \
    node->LINK.left = temp->LINK.right;                                     \
    temp->LINK.right = node;                                                \
                                                                            \
    return temp;                                                            \
}


#endif
