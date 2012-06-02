#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stdlib.h>

#include <c_type.h>

typedef struct _Container Container;

CTYPE_CLASS_DECLARE(Container);

struct _Container {
	size_t size;
	c_virtual void (*destruct)(Container *);
	c_virtual void (*append)(Container *, const void *);
	c_virtual void (*insert)(Container *, const void *, int);
	c_virtual void *(*remove_at)(Container *, int);
	c_virtual void *(*remove)(Container *, const void *);
	c_virtual void *(*get)(Container *, int);
	c_virtual void *(*foreach)(Container *, void (*)(void *));
};

Container *container_new();
void container_append(Container *thiz, const void *data);
void container_insert(Container *thiz, const void *data, int pos);
void *container_remove_at(Container *thiz, int pos);
void *container_remove(Container *thiz, const void *data);
void container_finalize(Container *thiz);
size_t container_get_size(Container *thiz);
void container_set_size(Container *thiz, size_t size);
void *container_get(Container *thiz, int pos);
void container_foreach(Container *thiz, void (*func)(void *));

#endif
