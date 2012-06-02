#ifndef _CLIST_H_
#define _CLIST_H_

#include <container.h>

typedef struct _CList CList;

struct _node;

CTYPE_CLASS_DECLARE(CList);

struct _CList {
	Container parent;
	struct _node *head;
};

CList *clist_new();
void clist_append(CList *thiz, void *data);
void *clist_get(CList *thiz, int pos);
void clist_insert(CList *thiz, void *data, int pos);
void *clist_remove_at(CList *thiz, int pos);
void *clist_remove(CList *thiz, void *data);
void clist_finalize(CList *thiz);
void clist_foreach(CList *thiz, void (*func)(void *));
#endif
