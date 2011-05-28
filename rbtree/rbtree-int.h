#ifndef RBTREE_INT_H_
#define RBTREE_INT_H_

static void clear(rbnode *);
static rbnode *insert(rbnode *, void *, cmpfun);
static rbnode *delete(rbnode *, void *, cmpfun);

static rbnode *fix(rbnode *);
static int is_red(rbnode *);
static rbnode *rotate_left(rbnode *);
static rbnode *rotate_right(rbnode *);
static void color_flip(rbnode *);

static void *min(rbnode *);
static rbnode *move_red_right(rbnode *);
static rbnode *delete_min(rbnode *);
static rbnode *move_red_left(rbnode *);

static int init_node(rbnode **, void *);

#endif
