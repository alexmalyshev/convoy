#include "../include/splat.h"

#include <assert.h>
#include <stdio.h>


typedef struct block {
    SPLAT_LINK(block, link);

    int key;
    int val;
} block_t;

SPLAT_NEW(splat, block);

#define CMP(a,b) (((a) <= (b)) ? (-(a < b)) : 1)

SPLAT_LIB(splat, block, int, CMP, link, key)

static splat tree = SPLAT_STATIC_INIT;

static void block_init(block_t *blk, int key, int val) {
    assert(blk != NULL);

    blk->key = key;
    blk->val = val;
    SPLAT_ELEM_INIT(blk, link);
}

static void print(block_t *tree, int depth, int indent) {
    if (tree == NULL)
        return;

    int i;
    for (i = 0; i < depth; ++i)
        putchar(' ');

    printf("key: %d, val: %d\n", tree->key, tree->val);

    print(tree->link.left, depth + indent, indent);
    print(tree->link.right, depth + indent, indent);
}


int main(void) {
    block_t b0;
    block_init(&b0, 1, 0);

    block_t b1;
    block_init(&b1, 2, 0);

    block_t b2;
    block_init(&b2, 0, 2);

    splat_insert(&tree, &b0);
    print(tree.root, 0, 4);
    splat_insert(&tree, &b1);
    print(tree.root, 0, 4);
    splat_insert(&tree, &b2);
    print(tree.root, 0, 4);

    res = splat_search(&tree, 3);

    assert(res == NULL);
    print(tree.root, 0, 4);

    block_t *res = NULL;

    printf("[ ");
    res = splat_remove(&tree, 0);
    printf("(%d,%d) ", res->key, res->val);
    res = splat_remove(&tree, 2);
    printf("(%d,%d) ", res->key, res->val);
    res = splat_remove(&tree, 1);
    printf("(%d,%d) ", res->key, res->val);
    printf("]\n");

    res = splat_remove(&tree, 1);

    assert(res == NULL);

    return 0;
}
