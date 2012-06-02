#include "sort.h"

#include <memory.h>
#include <stdio.h>

#define RADIX_NUM 5

void radix_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "radix sort",
	.sort_fun = radix_sort
};

struct Radix {
	int data;
	struct Radix *next;
	struct Radix *end;
};

static struct Radix *base[10] = {NULL};

void add_radix(struct Radix **head, int data) {
	struct Radix *new = (struct Radix *)malloc(sizeof(struct Radix));
	new->data = data;
	new->end = new;
	new->next = NULL;

	if (*head == NULL) {
		*head = new;
		return;
	}

	(*head)->end->next = new;
	(*head)->end = new;
/*
	struct Radix *p = *head;

	if (p == NULL) {
		*head = new;
		return;
	}

	while (p->next != NULL) {
		p = p->next;
	}

	p->next = new;
*/	
}

void radix_sort(int *data, int num) {
	int i = 0;
	int j = 0;
	int k = 0;
	int radix = 0;
	int l = 0;
	int m = 0;

	struct Radix *head = NULL;
	struct Radix *prev = NULL;

	for (i = 0; i < RADIX_NUM; i++) {
		for (j = 0; j < num; j++) {
			radix = data[j];

			for (k = 0; k < i; k++) {
				radix = radix / 10;
			}
			
			radix = radix % 10;
			//printf("radix: %d\n", radix);

			add_radix(&(base[radix]), data[j]);
		}

		for (l = 9; l >= 0; l--) {
			head = base[l];
			prev = head;
			
			while (head != NULL) {
				data[m] = head->data;
				prev = head;
				head = head->next;
				free(prev);
				m++;
			}
			
			
		}

		m = 0;
		memset(base, 0, sizeof(struct Radix *) * 10);
	}
}
