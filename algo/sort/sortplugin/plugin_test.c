#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv) {
	struct sort_list *list = get_sort_list("./");

	if (list == NULL) {
		fprintf(stderr, "can not get plugin list");
		exit(1);
	}

	struct sort_plugin *plugin = NULL;

	while ((plugin = get_next_plugin(list)) != NULL) {
		printf("plugin: %s\n", plugin->name);
	}

	printf(".\n");

	while ((plugin = get_prev_plugin(list)) != NULL) {
		printf("plugin: %s\n", plugin->name);
	}	

	printf(".\n");

	while ((plugin = get_next_plugin(list)) != NULL) {
		printf("plugin: %s\n", plugin->name);
	}

	free_sort_list(list);
	return 0;
}
