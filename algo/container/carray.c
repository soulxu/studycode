#include <carray.h>

#include <c_debug.h>
#include <assert.h>


#define DEFAULT_INFLATE_SIZE 20

void _carray_construct(CArray *thiz);
void _carray_destruct(CArray *thiz);

CTYPE_CLASS(CArray, Container, _carray_construct, _carray_destruct);

CArray *carray_new() {
	CArray *n = ctype_new(CArray);
	return n;
}

void _carray_inflate(CArray *thiz) {
	assert(thiz != NULL);
	void **n = (void **)malloc(sizeof(void *) * (thiz->storage_size + thiz->storage_inflate_size));
	memcpy(n, thiz->storage, thiz->storage_size);
	free(thiz->storage);
	thiz->storage = n;
	thiz->storage_size += thiz->storage_inflate_size;
}

void _carray_append(CArray *thiz, void *data) {
	assert(thiz != NULL);

	if (container_get_size((Container *)thiz) >= thiz->storage_size) {
		_carray_inflate(thiz);
	}

	thiz->storage[container_get_size((Container *)thiz)] = data;
	container_set_size((Container *)thiz, container_get_size((Container *)thiz) + 1);
}

void *_carray_get(CArray *thiz, int pos) {
	if (pos >= container_get_size((Container *)thiz)) {
		return NULL;
	}

	return thiz->storage[pos];
}

void *_carray_remove_at(CArray *thiz, int pos);

void *_carray_remove(CArray *thiz, void *data) {
	int i;
	for (i = 0; i < container_get_size((Container *)thiz); i++) {
		if (thiz->storage[i] == thiz) {
			return _carray_remove_at(thiz, i);
		}
	}

	return NULL;
}

void *_carray_remove_at(CArray *thiz, int pos) {
	void *removed = NULL;

	if (container_get_size((Container *)thiz) <= pos) {
		return removed;
	}

	removed = thiz->storage[pos];
	memcpy(thiz->storage + pos, thiz->storage + pos + 1, container_get_size((Container *)thiz) - pos);
	container_set_size(thiz, container_get_size(thiz) - 1);
	return removed;
}

void _carray_insert(CArray *thiz, void *data, int pos) {
	if (pos > container_get_size((Container *)thiz)) {
		return;
	}

	if (container_get_size((Container *)thiz) >= thiz->storage_size) {
		_carray_inflate(thiz);
	}

	container_set_size((Container *)thiz, container_get_size((Container *)thiz) + 1);

	if (container_get_size((Container *)thiz) == pos) {
		thiz->storage[pos] = data;
		return;
	}

	int i = 0;

	for (i = container_get_size((Container *)thiz); i > pos; i--) {
		thiz->storage[i] = thiz->storage[i - 1];
	}

	thiz->storage[pos] = data;
}

void _carray_foreach(CArray *thiz, void (*func)(void *)) {
	int i;

	for (i = 0; i < container_get_size(thiz); i++) {
		func(thiz->storage[i]);
	}
}

void carray_insert(CArray *thiz, void *data, int pos) {
	_carray_insert(thiz, data, pos);
}

void *carray_remove(CArray *thiz, void *data) {
	return thiz->parent.remove(thiz, data);
}

void *carray_remove_at(CArray *thiz, int pos) {
	return thiz->parent.remove_at(thiz, pos);
}

void carray_append(CArray *thiz, void *data) {
	thiz->parent.append(thiz, data);
}

void *carray_get(CArray *thiz, int pos) {
	return thiz->parent.get(thiz, pos);
}

void carray_finalize(CArray *thiz) {
	assert(thiz != NULL);
	((Container *)thiz)->destruct((Container *)thiz);
	ctype_delete(thiz);
}

void carray_foreach(CArray *thiz, void (*func)(void *)) {
	thiz->parent.foreach(thiz, func);
}

void _carray_construct(CArray *thiz) {
	DPRINT("construct");
	Container *parent = (Container *)thiz;
	thiz->storage_inflate_size = DEFAULT_INFLATE_SIZE;

	parent->destruct = (void (*)(Container *))_carray_destruct;
	parent->append = (void (*)(Container *, void *))_carray_append;
	parent->get = (void *(*)(Container *, int))_carray_get;
	parent->remove = (void *(*)(Container *, void *))_carray_remove;
	parent->remove_at = (void *(*)(Container *, int))_carray_remove_at;
	parent->insert = (void (*)(Container *, void *, int))_carray_insert;
	parent->foreach = _carray_foreach;

	thiz->storage = (void **)malloc(sizeof(void *) * thiz->storage_inflate_size);
	thiz->storage_size = thiz->storage_inflate_size;
	container_set_size((Container *)thiz, 0);
}

void _carray_destruct(CArray *thiz) {
	DPRINT("destruct");
	ctype_destruct_parent(CArray, thiz);
}
