#ifndef HASHMAP_INT_H_
#define HASHMAP_INT_H_

static void rehash(hashmap *map);

static void destroy_bucket(hashentry *entry);

static hashentry *init_entry(void *elem);

#endif /* HASHMAP_INT_H_ */
