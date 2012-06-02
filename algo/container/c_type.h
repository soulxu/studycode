#ifndef _CTYPE_H_
#define _CTYPE_H_

#include <stdlib.h>

typedef struct _CType CType;

struct _CType { 
	CType *parent_type; 
	char *class_name; 
	void (*construct)(void *);
	void (*destruct)(void *); 
}; 

#define CTYPE_CLASS_DECLARE(name) \
extern CType class_##name

extern CType class_NullType;

#define CTYPE_CLASS(name, parent, construct_fun, destruct_fun) \
CType class_##name = { \
	.parent_type = &class_##parent, \
	.class_name = #name, \
	.construct = (void (*)(void *))construct_fun, \
	.destruct = (void (*)(void *))destruct_fun \
}

#define CTYPE_GET_CLASS(name) class_##name

void *construct_all(CType *type, void *_i); 

#define ctype_new(name) \
(name *)construct_all(&class_##name, malloc(sizeof(name)))

#define ctype_delete(instant) \
free(instant)

#define c_virtual

void destruct_all(CType *type, void *_i);

#define ctype_destruct_all(name, parent, instant) \
((parent *)instant)->destruct(instant); \
if (class_##name.parent_type->class_name != NULL) { \
destruct_all(class_##name.parent_type, instant); \
}

#define ctype_destruct_parent(name, instant) \
class_##name.parent_type->destruct(instant);

#endif
