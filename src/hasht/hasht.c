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

#include <stdlib.h>
#include "hasht.h"
#include "hasht-int.h"

int hasht_init(hasht *tab, hashfn hash, cmpfn cmp, double lf, size_t cap) {
    if (tab == NULL || hash == NULL || cmp == NULL || lf <= 0.0)
        return 1;

    if ((tab->entries = calloc(cap, sizeof(hashent *))) == NULL)
        return 1;

    tab->hash = hash;
    tab->cmp = cmp;
    tab->size = 0;
    tab->cap = cap;
    tab->limit = (size_t)(cap * lf);
    tab->loadfactor = lf;
    return 0;
}

int hasht_destroy(hasht *tab) {
    if (hasht_clear(tab))
        return 1;

    free(tab->entries);
    return 0;
}

int hasht_insert(hasht *tab, void *elem) {
    hashent *entry;
    size_t index;
    cmpfn cmp;

    if (tab == NULL || elem == NULL)
        return 1;

    if (tab->size == tab->limit)
        resize(tab, 2 * tab->cap);

    index = tab->hash(elem) % tab->cap;
    entry = tab->entries[index];

    if (entry == NULL) {
        entry = init_entry(elem);
        tab->entries[index] = entry;
        ++(tab->size);
        return 0;
    }

    cmp = tab->cmp;

    while (entry->next != NULL) {
        if (cmp(elem, entry->elem) == 0)
            return 0;
        entry = entry->next;
    }
    if (cmp(elem, entry->elem) == 0)
        return 0;

    entry->next = init_entry(elem);
    ++(tab->size);

    return 0;
}

void *hasht_remove(hasht *tab, void *elem) {
    hashent *entry;
    hashent *dead;
    size_t index;
    cmpfn cmp;
    void *found;

    if (tab == NULL || elem == NULL)
        return NULL;

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

    if (tab == NULL || elem == NULL)
        return NULL;

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

int hasht_clear(hasht *tab) {
    size_t i;

    if (tab == NULL)
        return 1;

    for (i = 0; i < tab->cap; ++i)
        destroy_bucket((tab->entries)[i]);

    return 0;
}

int hasht_trunc(hasht *tab) {
    size_t newcap;

    if (tab == NULL)
        return 1;

    newcap = (size_t)(tab->size / tab->loadfactor);
    resize(tab, newcap);
    tab->limit = tab->size;
    return 0;
}

static int resize(hasht *tab, size_t newcap) {
    hashent **entries = tab->entries;
    hashfn hash = tab->hash;
    size_t cap = tab->cap;

    hashent **newentries; 
    hashent *entry;
    hashent *moving;
    size_t i;
    size_t newindex;

    if ((newentries = calloc(newcap, sizeof(hashent *))) == NULL)
        return 1;

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
    return 0;
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
    hashent *entry;

    if ((entry = malloc(sizeof(entry))) == NULL)
        return NULL;

    entry->elem = elem;
    entry->next = NULL;
    return entry;
}
