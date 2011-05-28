#ifndef SPLAY_INT_H_
#define SPLAY_INT_H_

/* recursive helper for splay_clear */
static void clear(splaynode *);

/* the god forsaken splay method */
static void splay(splaytree *, void *);

/* BST rotate methods, needed in splay */
static splaynode *rotate_left(splaynode *);
static splaynode *rotate_right(splaynode *);

/* creates a new splaynode with the given element as the data */
static int init_node(splaynode **, void *);

#endif
