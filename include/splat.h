#ifndef __CONVOY_SPLAT_H__
#define __CONVOY_SPLAT_H__

#ifdef SPLAT_ASSERTS
#include <assert.h>
#define SPLAT_ASSERT(...) assert(__VA_ARGS__)
#else
#define SPLAT_ASSERT(...) ((void)0)
#endif

#include <stddef.h>

/*
 * Declares a new splay tree type.
 *
 * ELEM_TYPE must be the name of a struct type
 */
#define SPLAT_NEW(SPLAT_TYPE, ELEM_TYPE) \
  typedef struct SPLAT_TYPE {            \
    struct ELEM_TYPE* root;              \
  } SPLAT_TYPE

/*
 * Declares a link in a struct for use with a splay tree.
 *
 * ELEM_TYPE must be the name of a struct type.
 */
#define SPLAT_LINK(ELEM_TYPE, LINK) \
  struct {                          \
    struct ELEM_TYPE* prev;         \
    struct ELEM_TYPE* next;         \
  } LINK

/*
 * Initializes a splay tree.
 */
#define SPLAT_INIT(TREE)    \
  do {                      \
    assert((TREE) != NULL); \
                            \
    (TREE)->root = NULL;    \
  } while (0)

/*
 * Statically initializes a splay tree.
 */
#define SPLAT_STATIC_INIT \
  { .root = NULL }

/*
 * Initializes the splay tree link of an element.
 */
#define SPLAT_ELEM_INIT(ELEM, LINK) \
  do {                              \
    assert((ELEM) != NULL);         \
                                    \
    (ELEM)->LINK.prev = NULL;       \
    (ELEM)->LINK.next = NULL;       \
  } while (0)

/*
 * Defines a new splay tree library.
 *
 * @param SPLAT_TYPE the type of the splay tree
 * @param ELEM_TYPE the type of the tree's elements
 * @param KEY_TYPE the type of the elements' keys
 * @param CMP a compare function/macro that works on keys
 * @param LINK the name of the link field
 * @param KEY the name of the key field
 */
#define SPLAT_LIB(SPLAT_TYPE, ELEM_TYPE, KEY_TYPE, CMP, LINK, KEY)            \
                                                                              \
  static struct ELEM_TYPE* SPLAT_TYPE##_rotate_prev(struct ELEM_TYPE* elem) { \
    assert(elem != NULL);                                                     \
    assert(elem->LINK.next != NULL);                                          \
                                                                              \
    struct ELEM_TYPE* temp = elem->LINK.next;                                 \
    elem->LINK.next = temp->LINK.prev;                                        \
    temp->LINK.prev = elem;                                                   \
                                                                              \
    return temp;                                                              \
  }                                                                           \
                                                                              \
  static struct ELEM_TYPE* SPLAT_TYPE##_rotate_next(struct ELEM_TYPE* elem) { \
    assert(elem != NULL);                                                     \
    assert(elem->LINK.prev != NULL);                                          \
                                                                              \
    struct ELEM_TYPE* temp = elem->LINK.prev;                                 \
    elem->LINK.prev = temp->LINK.next;                                        \
    temp->LINK.next = elem;                                                   \
                                                                              \
    return temp;                                                              \
  }                                                                           \
                                                                              \
  static void SPLAT_TYPE##_splay(SPLAT_TYPE* tree, KEY_TYPE key) {            \
    struct ELEM_TYPE assembler;                                               \
    struct ELEM_TYPE* prev = &assembler;                                      \
    struct ELEM_TYPE* next = &assembler;                                      \
                                                                              \
    assert(tree != NULL);                                                     \
                                                                              \
    assembler.LINK.prev = NULL;                                               \
    assembler.LINK.next = NULL;                                               \
                                                                              \
    struct ELEM_TYPE* elem = tree->root;                                      \
    while (1) {                                                               \
      int c = CMP(key, elem->KEY);                                            \
      if (c < 0) {                                                            \
        if (elem->LINK.prev == NULL) {                                        \
          break;                                                              \
        }                                                                     \
        if (CMP(key, elem->LINK.prev->KEY) < 0) {                             \
          elem = SPLAT_TYPE##_rotate_next(elem);                              \
          if (elem->LINK.prev == NULL) {                                      \
            break;                                                            \
          }                                                                   \
        }                                                                     \
        /* Link next. */                                                      \
        next->LINK.prev = elem;                                               \
        next = elem;                                                          \
        elem = elem->LINK.prev;                                               \
      } else if (c > 0) {                                                     \
        if (elem->LINK.next == NULL) {                                        \
          break;                                                              \
        }                                                                     \
        if (CMP(key, elem->LINK.next->KEY) > 0) {                             \
          elem = SPLAT_TYPE##_rotate_prev(elem);                              \
          if (elem->LINK.next == NULL) {                                      \
            break;                                                            \
          }                                                                   \
        }                                                                     \
        /* Link prev. */                                                      \
        prev->LINK.next = elem;                                               \
        prev = elem;                                                          \
        elem = elem->LINK.next;                                               \
      } else {                                                                \
        break;                                                                \
      }                                                                       \
    }                                                                         \
    /* Assemble. */                                                           \
    prev->LINK.next = elem->LINK.prev;                                        \
    next->LINK.prev = elem->LINK.next;                                        \
    elem->LINK.prev = assembler.LINK.next;                                    \
    elem->LINK.next = assembler.LINK.prev;                                    \
                                                                              \
    tree->root = elem;                                                        \
  }                                                                           \
                                                                              \
  void SPLAT_TYPE##_insert(SPLAT_TYPE* tree, struct ELEM_TYPE* elem) {        \
    assert(tree != NULL);                                                     \
    assert(elem != NULL);                                                     \
                                                                              \
    if (tree->root == NULL) {                                                 \
      tree->root = elem;                                                      \
      return;                                                                 \
    }                                                                         \
                                                                              \
    SPLAT_TYPE##_splay(tree, elem->KEY);                                      \
                                                                              \
    int c = CMP(elem->KEY, tree->root->KEY);                                  \
                                                                              \
    if (c == 0) {                                                             \
      return;                                                                 \
    }                                                                         \
    if (c < 0) {                                                              \
      elem->LINK.prev = tree->root->LINK.prev;                                \
      elem->LINK.next = tree->root;                                           \
      tree->root->LINK.prev = NULL;                                           \
    } else {                                                                  \
      elem->LINK.next = tree->root->LINK.next;                                \
      elem->LINK.prev = tree->root;                                           \
      tree->root->LINK.next = NULL;                                           \
    }                                                                         \
                                                                              \
    tree->root = elem;                                                        \
  }                                                                           \
                                                                              \
  struct ELEM_TYPE* SPLAT_TYPE##_search(SPLAT_TYPE* tree, KEY_TYPE key) {     \
    assert(tree != NULL);                                                     \
                                                                              \
    if (tree->root == NULL) {                                                 \
      return NULL;                                                            \
    }                                                                         \
    SPLAT_TYPE##_splay(tree, key);                                            \
                                                                              \
    if (CMP(key, tree->root->KEY) == 0) {                                     \
      return tree->root;                                                      \
    }                                                                         \
    return NULL;                                                              \
  }                                                                           \
                                                                              \
  struct ELEM_TYPE* SPLAT_TYPE##_remove(SPLAT_TYPE* tree, KEY_TYPE key) {     \
    struct ELEM_TYPE* temp;                                                   \
    struct ELEM_TYPE* removed = SPLAT_TYPE##_search(tree, key);               \
                                                                              \
    if (removed == NULL) {                                                    \
      return NULL;                                                            \
    }                                                                         \
    if (tree->root->LINK.prev == NULL) {                                      \
      tree->root = tree->root->LINK.next;                                     \
    } else {                                                                  \
      temp = tree->root->LINK.next;                                           \
      tree->root = tree->root->LINK.prev;                                     \
      SPLAT_TYPE##_splay(tree, key);                                          \
      tree->root->LINK.next = temp;                                           \
    }                                                                         \
                                                                              \
    return removed;                                                           \
  }

#endif
