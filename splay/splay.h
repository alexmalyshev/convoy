#ifndef SPLAY_H_
#define SPLAY_H_

/*
    Alexander Malyshev - splay.h

    Implementation of a splay tree. NULL cannot be stored.
*/

typedef int (*cmpfun)(void *, void *);

/* a splaynode holds onto a data pointer, along with pointers to its two
   children */
typedef struct splaynode_t {
    struct splaynode_t *left;
    struct splaynode_t *right;
    void *data;
} splaynode;

/* a splaytree has a root splaynode that is the actual representation of the
   binary search tree, as well as a compare function that is passed in through
   splay_init so that we can compare elements */
typedef struct splaytree_t {
    splaynode *root;
    cmpfun cmp;
} splaytree;

/* creating/destroying a splaytree */
int splay_init(splaytree **, cmpfun);
int splay_destroy(splaytree *);

/* standard BST methods */
void *splay_delete(splaytree *, void *);
int splay_insert(splaytree *, void *);
void *splay_search(splaytree *, void *);

/* auxiliary */
int splay_clear(splaytree *);

#endif
