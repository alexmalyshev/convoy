/**
 * @file splat.h
 * @brief Header for a splay tree data structure
 *
 * @author Alexander Malyshev
 */

#ifndef __SPLAT_H__
#define __SPLAT_H__

#include <assert.h>
#include <stddef.h>


/**
 * @brief Declares a new splay tree type
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * @param SPLAT_TYPE the type of the splay tree
 * @param ELEM_TYPE the type of the tree's elements
 */
#define SPLAT_NEW(SPLAT_TYPE, ELEM_TYPE)    \
    typedef struct SPLAT_TYPE {             \
        struct ELEM_TYPE *root;             \
    } SPLAT_TYPE

/**
 * @brief Declares a link in a struct for use with a splay tree
 *
 * ELEM_TYPE must be the name of a struct type
 *
 * @param ELEM_TYPE the type of the element
 * @param LINK the name of the link field
 */
#define SPLAT_LINK(ELEM_TYPE, LINK) \
    struct {                        \
        struct ELEM_TYPE *prev;     \
        struct ELEM_TYPE *next;     \
    } LINK

/**
 * @brief Initializes a splay tree
 *
 * @param TREE the address of the splay tree
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

/**
 * @brief Initializes the splay tree link of an element
 *
 * @param ELEM the address of the element
 * @param LINK the name of the link field
 */
#define SPLAT_ELEM_INIT(ELEM, LINK) do {    \
    assert((ELEM) != NULL);                 \
                                            \
    (ELEM)->LINK.prev = NULL;               \
    (ELEM)->LINK.next = NULL;               \
} while (0)

/**
 * @brief Defines a new splay tree library
 *
 * @param SPLAT_TYPE the type of the splay tree
 * @param ELEM_TYPE the type of the tree's elements
 * @param KEY_TYPE the type of the elements' keys
 * @param CMP a compare function/macro that works on keys
 * @param LINK the name of the link field
 * @param KEY the name of the key field
 */
#define SPLAT_LIB(SPLAT_TYPE, ELEM_TYPE, KEY_TYPE, CMP, LINK, KEY)          \
                                                                            \
static void SPLAT_TYPE##_splay(SPLAT_TYPE *tree, KEY_TYPE key);             \
static struct ELEM_TYPE *SPLAT_TYPE##_rotate_prev(struct ELEM_TYPE *node);  \
static struct ELEM_TYPE *SPLAT_TYPE##_rotate_next(struct ELEM_TYPE *node);  \
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
        new->LINK.prev = tree->root->LINK.prev;                             \
        new->LINK.next = tree->root;                                        \
        tree->root->LINK.prev = NULL;                                       \
    }                                                                       \
    else {                                                                  \
        new->LINK.next = tree->root->LINK.next;                             \
        new->LINK.prev = tree->root;                                        \
        tree->root->LINK.next = NULL;                                       \
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
    if (tree->root->LINK.prev == NULL)                                      \
        tree->root = tree->root->LINK.next;                                 \
    else {                                                                  \
        temp = tree->root->LINK.next;                                       \
        tree->root = tree->root->LINK.prev;                                 \
        SPLAT_TYPE##_splay(tree, key);                                      \
        tree->root->LINK.next = temp;                                       \
    }                                                                       \
                                                                            \
    return removed;                                                         \
}                                                                           \
                                                                            \
static void SPLAT_TYPE##_splay(SPLAT_TYPE *tree, KEY_TYPE key) {            \
    struct ELEM_TYPE assembler;                                             \
    struct ELEM_TYPE *prev = &assembler;                                    \
    struct ELEM_TYPE *next = &assembler;                                    \
    struct ELEM_TYPE *node;                                                 \
    int c;                                                                  \
                                                                            \
    assert(tree != NULL);                                                   \
                                                                            \
    assembler.LINK.prev = NULL;                                             \
    assembler.LINK.next = NULL;                                             \
                                                                            \
    node = tree->root;                                                      \
    while (1) {                                                             \
        c = CMP(key, node->KEY);                                            \
        if (c < 0) {                                                        \
            if (node->LINK.prev == NULL)                                    \
                break;                                                      \
            if (CMP(key, node->LINK.prev->KEY) < 0) {                       \
                node = SPLAT_TYPE##_rotate_next(node);                      \
                if (node->LINK.prev == NULL)                                \
                    break;                                                  \
            }                                                               \
            /* link next */                                                 \
            next->LINK.prev = node;                                         \
            next = node;                                                    \
            node = node->LINK.prev;                                         \
        }                                                                   \
        else if (c > 0) {                                                   \
            if (node->LINK.next == NULL)                                    \
                break;                                                      \
            if (CMP(key, node->LINK.next->KEY) > 0) {                       \
                node = SPLAT_TYPE##_rotate_prev(node);                      \
                if (node->LINK.next == NULL)                                \
                    break;                                                  \
            }                                                               \
            /* link prev */                                                 \
            prev->LINK.next = node;                                         \
            prev = node;                                                    \
            node = node->LINK.next;                                         \
        }                                                                   \
        else                                                                \
            break;                                                          \
    }                                                                       \
    /* assemble */                                                          \
    prev->LINK.next = node->LINK.prev;                                      \
    next->LINK.prev = node->LINK.next;                                      \
    node->LINK.prev = assembler.LINK.next;                                  \
    node->LINK.next = assembler.LINK.prev;                                  \
                                                                            \
    tree->root = node;                                                      \
}                                                                           \
                                                                            \
static struct ELEM_TYPE *SPLAT_TYPE##_rotate_prev(struct ELEM_TYPE *node) { \
    struct ELEM_TYPE *temp;                                                 \
                                                                            \
    assert(node != NULL);                                                   \
    assert(node->LINK.next != NULL);                                        \
                                                                            \
    temp = node->LINK.next;                                                 \
    node->LINK.next = temp->LINK.prev;                                      \
    temp->LINK.prev = node;                                                 \
                                                                            \
    return temp;                                                            \
}                                                                           \
                                                                            \
static struct ELEM_TYPE *                                                   \
SPLAT_TYPE##_rotate_next(struct ELEM_TYPE *node) {                          \
    struct ELEM_TYPE *temp;                                                 \
                                                                            \
    assert(node != NULL);                                                   \
    assert(node->LINK.prev != NULL);                                        \
                                                                            \
    temp = node->LINK.prev;                                                 \
    node->LINK.prev = temp->LINK.next;                                      \
    temp->LINK.next = node;                                                 \
                                                                            \
    return temp;                                                            \
}


#endif
