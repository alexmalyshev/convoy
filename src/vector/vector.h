#ifndef VECTOR_H_
#define VECTOR_H_

#define VECTOR_DEFAULT_CAP 32
#define VECTOR_GROW_CAP(cap) (3*(cap)/2)

typedef struct {
    void **elems;
    size_t cap;
    size_t last;
} vector;

void vector_init(vector *vec, size_t cap);
void vector_destroy(vector *vec);

void *vector_at(vector *vec, size_t i);
void vector_clear(vector *vec);
void *vector_insert(vector *vec, size_t i, void *elem);
void *vector_pop(vector *vec);
void vector_push(vector *vec, void *elem);
void *vector_remove(vector *vec, size_t i);
void vector_resize(vector *vec, size_t cap);
void vector_trim(vector *vec);

#endif /* VECTOR_H_ */
