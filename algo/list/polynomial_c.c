#include <stdio.h>

struct Polynomial {
	int coefficient;
	int exponent;
	struct Polynomial *next;
};

void create_poly(struct Polynomial **list, const char *input) {
	FILE *in = fopen(input, "r");

	if (in == NULL) {
		perror("can not open input file.");
		return;
	}

	int coefficient = 0;
	int exponent = 0;
	struct Polynomial *new; // = (struct Polynomial *)malloc(sizeof(struct Polynomial));
	struct Polynomial *p = *list;

	while (fscanf(in, "%dX^%d", &coefficient, &exponent) > 0) {
		new = (struct Polynomial *)malloc(sizeof(struct Polynomial));
		new->coefficient = coefficient;
		new->exponent = exponent;
		new->next = NULL;

		if (p == NULL) {
			*list = new;
			p = *list;
		}
		else {
			p->next = new;
			p = new;			
		}	
	}
}

void print_poly(const struct Polynomial *list) {
	struct Polynomial *p = list;

	while (p != NULL) {
		printf("%dX^%d+", p->coefficient, p->exponent);
		p = p->next;
	}

	putchar('\n');
}	

struct Polynomial *poly_add(const struct Polynomial *poly1, const struct Polynomial *poly2, struct Polynomial **out) {
	struct Polynomial *tmp = NULL;
	struct Polynomial *ret = *out;

	while ((poly1 != NULL) && (poly2 != NULL)) {
		tmp = (struct Polynomial *)malloc(sizeof(struct Polynomial));

		if (poly1->exponent > poly2->exponent) {
			tmp->exponent = poly1->exponent;
			tmp->coefficient = poly1->coefficient;
			poly1 = poly1->next;
		}
		else if (poly1->exponent < poly2->exponent) {
			tmp->exponent = poly2->exponent;
			tmp->coefficient = poly2->coefficient;
			poly2 = poly2->next;
		}
		else {
			tmp->exponent = poly1->exponent;
			tmp->coefficient = poly1->coefficient + poly2->coefficient;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		tmp->next = NULL;

		if (ret == NULL) {
			*out = tmp;
			ret = tmp;
		}
		else {
			ret->next = tmp;
			ret = tmp;
		}
	}

	while (poly1 != NULL) {
		tmp = (struct Polynomial *)malloc(sizeof(struct Polynomial));
		tmp->exponent = poly1->exponent;
		tmp->coefficient = poly1->coefficient;
		tmp->next = NULL;
		ret->next = tmp;
		ret = tmp;
		poly1 = poly1->next;
	}

	while (poly2 != NULL) {
		tmp = (struct Polynomial *)malloc(sizeof(struct Polynomial));
		tmp->exponent = poly2->exponent;
		tmp->coefficient = poly2->coefficient;
		tmp->next = NULL;
		ret->next = tmp;
		ret = tmp;
		poly2 = poly2->next;
	}

	return *out;
}

void free_poly(struct Polynomial *poly) {
	struct Polynomial *p = poly;

	while (poly != NULL) {
		p = poly;
		poly = poly->next;
		free(p);
	}
}

int main(int argc, char **argv) {
	struct Polynomial *poly1 = NULL;
	struct Polynomial *poly2 = NULL;
	struct Polynomial *poly3 = NULL;

	create_poly(&poly1, "./poly1.txt");
	print_poly(poly1);
	create_poly(&poly2, "./poly2.txt");
	print_poly(poly2);

	poly_add(poly1, poly2, &poly3);
	print_poly(poly3);	

	free_poly(poly1);
	free_poly(poly2);
	free_poly(poly3);
	return 0;
}
