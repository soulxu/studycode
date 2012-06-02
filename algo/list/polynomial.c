#include <stdio.h>
#include <clist.h>
#include <assert.h>

struct Polynomial {
	int coefficient;
	int exponent;
};

int create_poly(Container *c, const char *input) {
	assert((c != NULL) && (input != NULL));
	FILE *in = fopen(input, "r");

	if (in == NULL) {
		perror("can not open input file.");
		return -1;
	}

	int coefficient = 0;
	int exponent = 0;
	struct Polynomial *new_poly = NULL;

	while (!feof(in)) {
		if (fscanf(in, "%dX^%d", &coefficient, &exponent) <= 0) {
			break;
		}

		new_poly = malloc(sizeof(struct Polynomial));
		new_poly->coefficient = coefficient;
		new_poly->exponent = exponent;
		container_append(c, new_poly);
//		printf("%dX^%d\n", coefficient, exponent);
	}

	fclose(in);		
	return 0;
}

void _print_poly(struct Polynomial *poly) {
	assert(poly != NULL);
	printf("%dX^%d+", poly->coefficient, poly->exponent);
}
void print_polynomial(Container *c) {
	assert(c != NULL);
	container_foreach(c, _print_poly);
	putchar('\n');
}

void _free_poly(struct Polynomial *poly) {
	assert(poly != NULL);
	free(poly);
}

void free_poly(Container *c) {
	assert(c != NULL);
	container_foreach(c, _free_poly);
}

Container *polynomial_add(Container *poly1, Container *poly2, Container *out) {
	assert((poly1 != NULL) && (poly2 != NULL) && (out != NULL));
	struct Polynomial *left = NULL;
	struct Polynomial *right = NULL;
	struct Polynomial *ret = NULL;
	int i = 0;
	int j = 0;

	for (i = 0, j = 0; (i < container_get_size(poly1)) && (j < container_get_size(poly2)); ) {
		left = (struct Polynomial *)container_get(poly1, i);
		right = (struct Polynomial *)container_get(poly2, j);

		if (left->exponent == right->exponent) {
			ret = (struct Polynomial *)malloc(sizeof(struct Polynomial));
			ret->exponent = left->exponent;
			ret->coefficient = left->coefficient + right->coefficient;
			i++;
			j++;
		}
		else if (left->exponent > right->exponent) {
			ret = left;
			i++;
		}
		else {
			ret = right;
			j++;
		}

		container_append(out, ret);
	}

	struct Polynomial *tmp = NULL;	
	for (;i < container_get_size(poly1); i++) {
		tmp = (struct Polynomial *)malloc(sizeof(struct Polynomial));
		memcpy(tmp, container_get(poly1, i), sizeof(struct Polynomial));
		container_append(out, tmp);
	}

	for (;j < container_get_size(poly2); j++) {
		tmp = (struct Polynomial *)malloc(sizeof(struct Polynomial));
		memcpy(tmp, container_get(poly2, j), sizeof(struct Polynomial));
		container_append(out, tmp);
	}
	
	return out;
}

int main(int argc, char **argv) {
	CList *poly1 = clist_new();
	CList *poly2 = clist_new();

	if (create_poly(poly1, "./poly1.txt") != 0) {
		return -1;
	}

	print_polynomial(poly1);

	if (create_poly(poly2, "./poly2.txt") != 0) {
		return -1;
	}

	print_polynomial(poly2);
	CList *out = clist_new();

	polynomial_add(poly1, poly2, out);

	print_polynomial(out);
	
	free_poly(poly1);
	free_poly(poly2);
	free_poly(out);
	container_finalize(poly1);
	container_finalize(poly2);
	container_finalize(out);
	return 0;
}
