#include <clist.h>

#include <memory.h>

#include <c_debug.h>
#include <assert.h>

#define CACHE 20

struct _node {
	void *data;
	struct _node *next;
};

void _clist_construct(CList *thiz) {
	assert(thiz != NULL);
//	DPRINT("construct");
	thiz->head = NULL;
	Container *parent = (Container *)thiz;
	parent->size = 0;
}

void _clist_destruct(CList *thiz) {
	assert(thiz != NULL);
//	DPRINT("destruct");
	struct _node *p = thiz->head;
	struct _node *q = thiz->head;

	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}

	ctype_destruct_parent(CList, thiz);
}

CTYPE_CLASS(CList, Container, _clist_construct, _clist_destruct);

void _clist_append(CList *thiz, void *data) {
	assert(thiz != NULL);
	
	struct _node *n = (struct _node *)malloc(sizeof(struct _node));
	n->data = data;
	n->next = NULL;

	if (thiz->head == NULL) {
		thiz->head = n;
	}
	else {
		struct _node *p = thiz->head;

		while (p->next != NULL) {
			p = p->next;
		}
	
		p->next = n;
	}

	Container *parent = (Container *)thiz;
	parent->size = parent->size + 1;
}

void _clist_insert(CList *thiz, void *data, int pos) {
	struct _node *p =thiz->head;
	struct _node *q = NULL;
	int i;

	for (i = 0; (i < pos) && (p != NULL); i++) {
		q = p;
		p = p->next;
	}

	if (i != pos) {
		return;	
	}
	
	struct _node *n = (struct _node *)malloc(sizeof(struct _node));
	n->data = data;
	n->next = p;

	if (q == NULL) {
		thiz->head = n;		
	}
	else {
		q->next = n;
	}

	Container *parent = (Container *)thiz;
	parent->size += 1;
}

void *_clist_get(CList *thiz, int pos) {
	int i;
	struct _node *p = thiz->head;

	for (i = 0; (i < pos) && (p != NULL); i++) {
		p = p->next;
	}

	if (p != NULL) {
		return p->data;
	}

	return NULL;
}

void *_clist_remove(CList *thiz, void *data) {
	struct _node *p = thiz->head;
	struct _node *q = NULL;

	while (p != NULL) {
		if (p->data == data) {
			break;
		}
		q = p;
		p = p->next;
	}

	if (p == NULL) {	
		return NULL;
	}

	void *r = p->data;

	if (q == NULL) {
		thiz->head = p->next;
		free(p);
	}
	else {
		free(p);
		q->next = p->next;
	}
	
	Container *parent = (Container *)thiz;
	parent->size -= 1;	
	return r;
}

void *_clist_remove_at(CList *thiz, int pos) {
	int i;
	struct _node *p = thiz->head;
	struct _node *q = NULL;

	for (i = 0; (i < pos) && (p != NULL); i++) {
		q = p;
		p = p->next;
	}

	if (p == NULL) {
		return NULL;
	}

	void *d = p->data;

	if (q != NULL) {		
		q->next = p->next;
		free(p);
	}
	else {
		thiz->head = p->next;
		free(p);
	}

	Container *parent = (Container *)thiz;

	parent->size -= 1;

	return d;
}

void _clist_foreach(CList *thiz, void (*func)(void *)) {
	struct _node *p = thiz->head;

	while (p != NULL) {
		func(p->data);
		p = p->next;
	}
}

void clist_foreach(CList *thiz, void (*func)(void *)) {
	thiz->parent.foreach(thiz, func);
}

void clist_finalize(CList *thiz) {
	assert(thiz != NULL);
	((Container *)thiz)->destruct((void *)thiz);
	ctype_delete(thiz);
}

void *clist_get(CList *thiz, int pos) {
	return ((Container *)thiz)->get(thiz, pos);
}

void clist_append(CList *thiz, void *data) {
	((Container *)thiz)->append(thiz, data);
}

void clist_insert(CList *thiz, void *data, int pos) {
	((Container *)thiz)->insert(thiz, data, pos);
}

CList *clist_new() {
	CList *n = ctype_new(CList);
	Container *parent = (Container *)n;
	
	parent->destruct = (void (*)(Container *))_clist_destruct;
	parent->append = _clist_append;
	parent->get = _clist_get;
	parent->insert = _clist_insert;
	parent->foreach = _clist_foreach;
	parent->remove = _clist_remove;
	parent->remove_at = _clist_remove_at;
	
	return n;
}
