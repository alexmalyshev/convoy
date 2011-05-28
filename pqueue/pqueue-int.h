#ifndef PQUEUE_INT_H_
#define PQUEUE_INT_H_

static int resize(pqueue *);
static void percolate_up(pqueue *);
static void percolate_down(pqueue *);
static void swap(void **, long, long);

#endif
