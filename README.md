# Convoy

This is a collection of data structures/types written in C99. None of the data
structures depend upon each other, so feel free to just pull one out and use
it. The current list of data structures is:

 * binaheap - a binary heap backed by a dynamic array
 * circbuf - a fixed-size circular buffer
 * deque - a deque backed by a linked list
 * hasht - a hash table backed by a dynamic array, uses separate chaining
 * queue - a queue backed by a linked list
 * rbtree - a red black tree with dictionary operations
 * splat - a splay tree with dictionary operations
 * vector - a dynamic array

## Work In Progress

The older data structures implement generics by using void * elements, whereas
the newer ones are created via macro definitions for better performance

## License

All files are released under the terms listed in the LICENSE file found in the
top level convoy folder (3-clause BSD license).

## Documentation

Detailed documentation can be found in the docs/ folder courtesy of doxygen.
