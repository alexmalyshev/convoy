#ifndef HASHMAP_H_
#define HASHMAP_H_

#ifndef CMPFN
#define CMPFN
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

#ifndef HASHFN
#define HASHFN
typedef unsigned long (*hashfn)(void *)
#endif /* HASHFN */

#define LOAD_FACTOR 0.75

typedef struct {
    void **elems;
    hashfn hash;
    cmpfun cmp;
    size_t size;
    size_t cap;
} hashmap;

hashmap *hashmap_init(hashfn hash, cmpfun cmp);

int hashmap_destroy(hashmap *map);

int hashmap_insert(hashmap *map, void *elem);

void *hashmap_remove(hashmap *map, void *elem);

void *hashmap_search(hashmap *map, void *elem);

int hashmap_clear(hashmap *map);


#endif /* HASHMAP_H_
