#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

#include <c_type.h>
#include <container.h>

typedef struct _CArray CArray;

CTYPE_CLASS_DECLARE(CArray);

struct _CArray {
	Container parent;
	void **storage;
	ssize_t storage_size;
	ssize_t storage_inflate_size;
};

CArray *carray_new();
void carray_append(CArray *thiz, void *data);
void *carray_get(CArray *thiz, int pos);
void *carray_remove(CArray *thiz, void *data);
void *carray_remove_at(CArray *thiz, int pos);
void carray_insert(CArray *thiz, void *data, int pos);
void carray_finalize(CArray *thiz);
void carray_foreach(CArray *thiz, void (*)(void *));
#endif
