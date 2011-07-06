#ifndef HASHMAP_H_
#define HASHMAP_H_

#ifndef CMPFN
#define CMPFN
typedef int (*cmpfn)(void *, void *);
#endif /* CMPFN */

#ifndef HASHFN
#define HASHFN
typedef unsigned long (*hashfn)(void *);
#endif /* HASHFN */

#define DEFAULT_LOAD_FACTOR 0.75
#define DEFAULT_INITIAL_CAPACITY 64

typedef struct hashentry_t {
    void *elem;
    struct hashentry_t *next;
} hashentry;

typedef struct {
    hashentry **entries;
    hashfn hash;
    cmpfn cmp;
    size_t size;
    size_t cap;
    size_t limit;
    double loadfactor;
} hashmap;

hashmap *hashmap_init(hashfn hash, cmpfn cmp, double loadfactor, size_t cap);

int hashmap_destroy(hashmap *map);

int hashmap_insert(hashmap *map, void *elem);

void *hashmap_remove(hashmap *map, void *elem);

void *hashmap_search(hashmap *map, void *elem);

int hashmap_clear(hashmap *map);


#endif /* HASHMAP_H_ */
