#ifndef RBTREE_H_
#define RBTREE_H_

/*
    Alexander Malyshev - rbtree.h

    Implementation of a left leaning red black tree. NULL cannot be stored.
*/

#define RED 0
#define BLACK 1

typedef int (*cmpfun)(void *, void *);

/* rbnodes have two children, a pointer to data, and a color */
typedef struct rbnode_t {
    struct rbnode_t *left;
    struct rbnode_t *right;
    void *data;
    int color;
} rbnode;

/* an rbtree just holds onto the root of the red black tree as well as the
   compare function passed in through init */
typedef struct {
    rbnode *root;
    cmpfun cmp;
} rbtree;

/* for creating and destroying a red black tree */
int rbtree_init(rbtree **, cmpfun);
int rbtree_destroy(rbtree *);

/* standard BST methods */
void *rbtree_search(rbtree *, void *);
int rbtree_insert(rbtree *, void *);
void *rbtree_delete(rbtree *, void *);

/* auxiliary */
int rbtree_clear(rbtree *);

#endif
