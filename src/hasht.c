/** @file hasht.c
 *  @brief A hash table library.
 *
 *  We malloc an entry every time we insert a new element into the hash table
 *  and free the entry that wraps around the element returned by
 *  <tt>hasht_remove</tt>. We compare elements using the compare function that
 *  is given as an argument to <tt>hasht_init</tt> and we hash elements using
 *  the hash function that is also given as an argument in <tt>hasht_init</tt>.
 *
 *  @author Alexander Malyshev
 */

#include <assert.h>
#include <stdlib.h>
#include "hasht.h"

static void resize(hasht *tab, size_t newcap);
static void destroy_bucket(hashent *entry);
static hashent *init_entry(void *elem);

void hasht_init(hasht *tab, hashfn hash, cmpfn cmp, double lf, size_t cap) {
    assert(tab != NULL);
    assert(hash != NULL);
    assert(cmp != NULL);
    assert(lf > 0.0);

    if (cap != 0) {
        tab->entries = calloc(cap, sizeof(hashent *));
        assert(tab->entries != NULL);
    } else {
        tab->entries = NULL;
    }

    tab->hash = hash;
    tab->cmp = cmp;
    tab->size = 0;
    tab->cap = cap;
    tab->limit = (size_t)(cap * lf);
    tab->loadfactor = lf;
}

void hasht_destroy(hasht *tab) {
    hasht_clear(tab);
    free(tab->entries);
}

void hasht_insert(hasht *tab, void *elem) {
    hashent *entry;
    size_t index;
    cmpfn cmp;

    assert(tab != NULL);
    assert(elem != NULL);

    if (tab->size == tab->limit)
        resize(tab, 2 * tab->cap);

    index = tab->hash(elem) % tab->cap;
    entry = tab->entries[index];

    if (entry == NULL) {
        entry = init_entry(elem);
        tab->entries[index] = entry;
        ++(tab->size);
        return;
    }

    cmp = tab->cmp;

    while (entry->next != NULL) {
        if (cmp(elem, entry->elem) == 0)
            return;
        entry = entry->next;
    }
    if (cmp(elem, entry->elem) == 0)
        return;

    entry->next = init_entry(elem);
    ++(tab->size);

    return;
}

void *hasht_remove(hasht *tab, void *elem) {
    hashent *entry;
    hashent *dead;
    size_t index;
    cmpfn cmp;
    void *found;

    assert(tab != NULL);
    assert(elem != NULL);

    index = tab->hash(elem) % tab->cap;
    entry = tab->entries[index];
    cmp = tab->cmp;

    if (entry == NULL)
        return NULL;

    if (cmp(elem, entry->elem) == 0) {
        found = entry->elem;
        tab->entries[index] = entry->next;
        free(entry);
        --(tab->size);
        return found;
    }

    while (entry->next != NULL) {
        if (cmp(elem, entry->next) == 0) {
            dead = entry->next;
            entry->next = dead->next;
            found = dead->elem;
            free(dead);
            --(tab->size);
            return found;
        }
        entry = entry->next;
    }

    return NULL;
}

void *hasht_search(hasht *tab, void *elem) {
    hashent *entry;
    size_t index;
    cmpfn cmp;

    assert(tab != NULL);
    assert(elem != NULL);

    index = tab->hash(elem) % tab->cap;
    entry = tab->entries[index];
    cmp = tab->cmp;

    while (entry != NULL) {
        if (cmp(elem, entry->elem) == 0)
            return entry->elem;
        entry = entry->next;
    }

    return NULL;
}

void hasht_clear(hasht *tab) {
    size_t i;

    assert(tab != NULL);

    for (i = 0; i < tab->cap; ++i)
        destroy_bucket((tab->entries)[i]);
}

void hasht_trunc(hasht *tab) {
    size_t newcap;

    assert(tab != NULL);

    newcap = (size_t)(tab->size / tab->loadfactor);
    resize(tab, newcap);
    tab->limit = tab->size;
}

static void resize(hasht *tab, size_t newcap) {
    hashent **entries = tab->entries;
    hashfn hash = tab->hash;
    size_t cap = tab->cap;

    hashent **newentries; 
    hashent *entry;
    hashent *moving;
    size_t i;
    size_t newindex;

    newentries = calloc(newcap, sizeof(hashent *));
    assert(newentries != NULL);

    if (entries == NULL) {
        tab->entries = newentries;
        tab->cap = newcap;
        tab->limit = (size_t)(tab->loadfactor * newcap);
        return;
    }

    for (i = 0; i < cap; ++i) {
        entry = entries[i];
        while (entry != NULL) {
            moving = entry;
            entry = entry->next;
            newindex = hash(moving->elem) % newcap;
            moving->next = newentries[newindex];
            newentries[newindex] = moving;
        }
    }

    tab->entries = newentries;
    tab->cap = newcap;
    tab->limit = (size_t)(tab->loadfactor * newcap);
    free(entries);
}

static void destroy_bucket(hashent *entry) {
    hashent *dead;

    while (entry != NULL) {
        dead = entry;
        entry = entry->next;
        free(dead);
    }
}

static hashent *init_entry(void *elem) {
    hashent *entry = malloc(sizeof(entry));
    assert(entry != NULL);

    entry->elem = elem;
    entry->next = NULL;
    return entry;
}
