#include <stdio.h>

#include <carray.h>
#include <container.h>
#include <clist.h>
#include <assert.h>


void print_int(int *p) {
	printf("%d\n", *p);
}

void test_append(Container *a) {
	int i = 0;
	int *p = NULL;

	for (i = 0; i < 10; i++) {
		p = malloc(sizeof(int));
		*p = i;

		container_append(a, p);
	}

	assert(container_get_size(a) == 10);
}

void test_get(Container *a) {
	int i = 0;
	int *p = NULL;

	for(i = 0; i < 10; i++) {
		p = (int *)container_get((Container *)a, i);
		assert(i == *p);
		//p = (int *)carray_get((Container *)a, i);
		//assert(i == *p);
	}
}	

void test_insert(Container *a) {
	int n1 = 5;
	int n2 = 6;
	container_insert(a, &n1, 0);
	assert(container_get_size((Container *)a) == 11);
	container_insert(a, &n2, 10);
	assert(container_get_size((Container *)a) == 12);

	int *p = 0;
	p = (int *)container_get((Container *)a, 0);
	assert(n1 == *p);
	p = (int *)container_get((Container *)a, 10);
	assert(n2 == *p);

	int i = 0;

	for (i = 1; i < 10; i++) {
		assert((i - 1) == *(int *)container_get((Container *)a, i)); 
	}
}


void test_remove(Container *a) {
	container_remove_at(a, 0);
	assert(container_get_size(a) == 11);
	container_remove_at(a, 10);
	assert(container_get_size(a) == 10);
}

int main(int argc, char **argv) {
	CArray *a = carray_new();

	test_append(a);
	test_get(a);
	test_insert(a);
	test_remove(a);
	carray_finalize(a);

	CList *l = clist_new();
	test_append(l);
	test_get(l);
	test_insert(l);
	test_remove(l);
	clist_finalize(l);
	return 0;
}
