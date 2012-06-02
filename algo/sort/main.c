#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "ktime.h"

void usage() {
	fprintf(stderr, "sort input num output sortmethod\n");
}

int loadfile(char *file, int *data, int num) {
	FILE *input = fopen(file, "r");
	int i = 0;

	if (input == NULL) {
		return -1;
	}

	for (i = 0; i < num; i++) {
		fscanf(input, "%d\n", data + i);
	}

	fclose(input);
	return 0;
}

int writefile(char *file, int *data, int num) {
	FILE *out = fopen(file, "w");

	if (out == NULL) {
		return -1;
	}
	
	int i = 0;

	for (i = 0; i < num; i++) {
		fprintf(out, "%.7d\n", data[i]);
	}

	fclose(out);

	return 0;
}

int main(int argc, char **argv) {
	if (argc < 4) {
		usage();
		exit(1);
	}

	int num = atoi(argv[2]);
	int *data = (int *)malloc(sizeof(int) * num);

	if (loadfile(argv[1], data, num) != 0) {
		fprintf(stderr, "can not load file.\n");
		exit(1);
	}

	struct sort_plugin *plugin = NULL;
	struct sort_list *list = get_sort_list("./sortplugin");
	void (*sort_fun)(int *, int) = NULL;

	if (list == NULL) {
		fprintf(stderr, "can not get sort list.\n");
		exit(1);
	}

	while ((plugin = get_next_plugin(list)) != NULL) {
		printf("find %s\n", plugin->name);

		if (strcmp(plugin->name, argv[4]) == 0) {
			printf("i found\n");
			sort_fun = plugin->sort_fun;
			break;
		}
	}
	
	if (sort_fun == NULL) {
		fprintf(stderr, "can not find specific sort function.\n");
		exit(1);
	}

	START_TIME_;

	sort_fun(data, num);
	printf("%d ", num);
	END_TIME_;

	if (writefile(argv[3], data, num) != 0) {
		fprintf(stderr, "can not write file.\n");
		exit(1);
	}

	free(data);	
	return 0;
}
