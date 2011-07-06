/** @file hashmap.c
 *  @brief A hash table library.
 *
 *  We malloc an entry every time we insert a new element into the hash table
 *  and free the entry that wraps around the element returned by
 *  hashmap_remove. We compare elements using the compare function that is
 *  given as an argument to hashmap_init and we hash elements using the hash
 *  function that is also given as an argument in hashmap_init.
 *
 *  @author Alexander Malyshev
 *  @bug No known bugs.
 */

#include <stdlib.h>
#include "hashmap.h"
#include "hashmap-int.h"

hashmap *hashmap_init(hashfn hash, cmpfn cmp, double loadfactor, size_t cap) {
    hashmap *map;

    if (hash == NULL || cmp == NULL || loadfactor <= 0.0)
        return NULL;

    if ((map = malloc(sizeof(hashmap))) == NULL)
        return NULL;
    if ((map->entries = calloc(cap, sizeof(hashentry *))) == NULL)
        return NULL;

    map->hash = hash;
    map->cmp = cmp;
    map->size = 0;
    map->cap = cap;
    map->limit = (size_t)(cap * loadfactor);
    map->loadfactor = loadfactor;
    return map;
}

int hashmap_destroy(hashmap *map) {
    if (hashmap_clear(map))
        return 1;

    free(map->entries);
    free(map);
}

int hashmap_insert(hashmap *map, void *elem) {
    hashentry *entry;
    size_t index;
    cmpfn cmp;

    if (map == NULL || elem == NULL)
        return 1;

    if (map->size == map->limit)
        rehash(map);

    index = map->hash(elem) % map->cap;
    entry = map->entries[index];

    if (entry == NULL) {
        entry = init_entry(elem);
        map->entries[index] = entry;
        return 0;
    }

    cmp = map->cmp;

    while (entry->next != NULL) {
        if (cmp(elem, entry->elem) == 0)
            return 0;
        entry = entry->next;
    }
    if (cmp(elem, entry->elem) == 0)
        return 0;

    entry->next = init_entry(elem);
    ++(map->size);

    return 0;
}

void *hashmap_remove(hashmap *map, void *elem) {
    hashentry *entry;
    hashentry *dead;
    size_t index;
    cmpfn cmp;
    void *found;

    if (map == NULL || elem == NULL)
        return NULL;

    index = map->hash(elem) % map->cap;
    entry = map->entries[index];
    cmp = map->cmp;

    if (entry == NULL)
        return NULL;

    if (cmp(elem, entry->elem) == 0) {
        found = entry->elem;
        map->entries[index] = entry->next;
        free(entry);
        return found;
    }

    while (entry->next != NULL) {
        if (cmp(elem, entry->next) == 0) {
            dead = entry->next;
            entry->next = dead->next;
            found = dead->elem;
            free(dead);
            --(map->size);
            return found;
        }
        entry = entry->next;
    }

    return NULL;
}

void *hashmap_search(hashmap *map, void *elem) {
    hashentry *entry;
    size_t index;
    cmpfn cmp;

    if (map == NULL || elem == NULL)
        return NULL;

    index = map->hash(elem) % map->cap;
    entry = map->entries[index];
    cmp = map->cmp;

    while (entry != NULL) {
        if (cmp(elem, entry->elem) == 0)
            return entry->elem;
        entry = entry->next;
    }

    return NULL;
}

int hashmap_clear(hashmap *map) {
    size_t i;

    if (map == NULL)
        return 1;

    for (i = 0; i < map->cap; ++i)
        destroy_bucket((map->entries)[i]);

    return 0;
}

static void rehash(hashmap *map) {
    hashentry **entries = map->entries;
    hashfn hash = map->hash;
    size_t cap = map->cap;

    size_t newcap = cap * 2;
    hashentry **newentries = calloc(newcap, sizeof(hashentry *));

    hashentry *entry;
    hashentry *moving;
    size_t i;
    size_t newindex;

    for (i = 0; i < cap; ++i) {
        entry = entries[i];
        while (entry != NULL) {
            moving = entry;
            entry = entry->next;
            newindex = hash(moving->elem) % newcap;
            moving->next = newentries[i];
            newentries[i] = moving;
        }
    }

    map->entries = newentries;
    map->cap = newcap;
    map->limit = map->loadfactor * newcap;
    free(entries);
}

static void destroy_bucket(hashentry *entry) {
    hashentry *dead;

    while (entry != NULL) {
        dead = entry;
        entry = entry->next;
        free(dead);
    }
}

static hashentry *init_entry(void *elem) {
    hashentry *entry;

    if ((entry = malloc(sizeof(entry))) == NULL)
        return NULL;

    entry->elem = elem;
    entry->next = NULL;
    return entry;
}
