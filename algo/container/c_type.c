#include <c_type.h>

#include <assert.h>

CType class_NullType = {
        .parent_type = NULL,
        .class_name = NULL,
};

void *construct_all(CType *type, void *_i) {
        if (type->parent_type->class_name != NULL) {
                construct_all(type->parent_type, _i);
        }

        type->construct(_i);	
        return _i;
}

void destruct_all(CType *type, void *_i) {
	assert(_i != NULL);
	type->destruct(_i);

	if (type->parent_type->class_name != NULL) {
		construct_all(type->parent_type, _i);
	}
}
