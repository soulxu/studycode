#include <container.h>

#include <c_type.h>

#include <c_debug.h>
#include <assert.h>

void _container_construct(Container *c);
void _container_destruct(Container *c);

CTYPE_CLASS(Container, NullType, _container_construct, _container_destruct);

void _container_append(Container *c, const void *d) {
	assert(c != NULL);
//	DPRINT("append");
}

void _container_insert(Container *c, const void *d, int p) {

}

void *_container_remove_at(Container *c, int p) {

}

void *_container_remove(Container *c, const void *d) {

}

void *_container_get(Container *c, int pos) {
	return NULL;
}

void _container_foreach(Container *c, void (*func)(void *)) {
	return;
}

Container *container_new() {
	Container *n = ctype_new(Container);
	return n;	
}

void container_append(Container *thiz, const void *data) {
	thiz->append(thiz, data);
}

void container_insert(Container *thiz, const void *data, int pos) {
	thiz->insert(thiz, data, pos);
}

void *container_remove_at(Container *thiz, int pos) {
	return thiz->remove_at(thiz, pos);
}

void *container_remove(Container *thiz, const void *data) {
	return thiz->remove(thiz, data);
}

size_t container_get_size(Container *thiz) {
	return thiz->size;
}

void container_set_size(Container *thiz, size_t size) {
	thiz->size = size;
}

void *container_get(Container *thiz, int pos) {
	return thiz->get(thiz, pos);
}

void container_finalize(Container *thiz) {
	assert(thiz != NULL);
	thiz->destruct(thiz);
	ctype_delete(thiz);
}

void container_foreach(Container *thiz, void (*func)(void *)) {
	thiz->foreach(thiz, func);
}

void _container_construct(Container *c) {
//	DPRINT("construct");
	c->destruct = _container_destruct;
	c->append = _container_append;
	c->insert = _container_insert;
	c->remove_at = _container_remove_at;
	c->remove = _container_remove;
	c->get = _container_get;
	c->foreach = _container_foreach;
	c->size = 0;
}

void _container_destruct(Container *c) {
//	DPRINT("destruct");
}
