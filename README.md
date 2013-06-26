# Convoy

This is a collection of simple generic data structures written in C99. None of
the data structures depend upon each other, so feel free to just pull one out
and use it. The current list of data structures is:

 * circbuf - a fixed-size circular buffer
 * dlist - a circular, doubly linked list
 * slist - a circular, singly-linked list
 * splat - a splay tree

## Usage

Most of the data structures are used completely via macros. splat is a little
odd in that it is mainly a very large macro that generates a bunch of C
functions.

## License

All files are released under the terms listed in the LICENSE file found in the
top level convoy folder (3-clause BSD license).

## Documentation

All files have doxygen documentation.
