#include "container.h"
#include "carray.h"
#include "clist.h"

#include <assert.h>
#include <stdio.h>

void print_int(int *p) {
	printf("%d\n", *p);
}

int main(int argc, char **argv) {
	CArray *l = carray_new();
	int i = 0;
	Container *c = (Container *)l;

	for (i = 0; i < 10; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		container_append(c, p);
	}

	container_foreach(c, print_int);
/*
	for (i = 0; i < container_get_size(c); i++) {
		printf("%d\n", *((int *)container_get(c, i)));
	}
*/
	container_finalize((Container *)l);

	CList *cl = clist_new();
	int x1 = 11;
	int x2 = 22;
	int x3 = 33;
	clist_insert(cl, &x1, 0);

	assert(1 == container_get_size(cl));

	for (i = 0; i < 10; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		clist_append(cl, p);
	}

	assert(11 == container_get_size(cl));

	clist_insert (cl, &x2, 0);

	assert(12 == container_get_size(cl));

	clist_insert(cl, &x3, 12);

	assert(13 == container_get_size(cl));
/*
	for (i = 0; i < container_get_size(cl); i++) {
		printf("%d\n", *(int *)container_get(cl, i));
	}
*/

	container_foreach(cl, print_int);
/*
	printf("remove last\n");

	container_remove(cl, &x3);

	container_foreach(cl, print_int);	

	printf("remove one\n");

	container_remove(cl, &x1);

	container_foreach(cl, print_int);

	printf("remove first\n");

	container_remove(cl, &x2);

	container_foreach(cl, print_int);
*/

	printf("remove first\n");

	container_remove_at(cl, 0);
	
	container_foreach(cl, print_int);

	printf("remove last\n");

	container_remove_at(cl, container_get_size(cl) - 1);
	container_foreach(cl, print_int);
	clist_finalize(cl);
	return 0;
};
