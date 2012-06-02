#include "sort.h"

#include <assert.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

struct sort_plugin *load_plugin(const char *file) {
	assert (file != NULL);
	void *dl = dlopen(file, RTLD_NOW);

	if (dl == NULL) {
		return NULL;
	}

	struct sort_plugin *plugin = dlsym(dl, "plugin");

	return plugin;
}

struct sort_plugin *get_next_plugin(struct sort_list *list) {
	assert(list != NULL);
	
	if (list->header == NULL) {
		return NULL;
	}

	if (list->cur == NULL) {
		list->cur = list->header;
		return list->cur;
	}

	if (list->cur->next == NULL) {
		return NULL;
	}
		
	list->cur = list->cur->next;

	return list->cur;
}

struct sort_plugin *get_prev_plugin(struct sort_list *list) {
	assert(list != NULL);

	if (list->header == NULL) {
		return NULL;
	}

	if (list->cur == NULL) {
		return NULL;
	}	

	list->cur = list->cur->prev;

	return list->cur;
}

void free_sort_list(struct sort_list *list) {
	assert(list != NULL);
	//fix me: release all dl.
	free(list);
}

void reset_sort_list(struct sort_list *list) {
	assert(list != NULL);
	list->cur = list->header;
}

struct sort_list *get_sort_list(const char *dir) {
	assert (dir != NULL);
	
	struct sort_plugin *header = NULL;
	struct sort_plugin *cur = NULL;

	DIR *d = opendir(dir);

	if (d == NULL) {
		return NULL;
	}

	struct dirent *ent = readdir(d);
	char filename[PATH_MAX] = {0};
	struct sort_plugin *plugin = NULL;

	while (ent != NULL) {
		char *index = strstr(ent->d_name, ".so");		

		if (index != NULL) {
			memset(filename, 0, PATH_MAX);
			strcat(filename, dir);
			strcat(filename, "/");
			strcat(filename, ent->d_name);
			plugin = load_plugin(filename);

			if (plugin != NULL) {
				//printf("load plugin: %s\n", plugin->name);
				plugin->next = NULL;
				plugin->prev = cur;
		
				if (header == NULL) {
					header = plugin;			
				}
				else {
					cur->next =plugin;
				}
			
				cur = plugin;
			}
		}

		ent = readdir(d);
	}

	closedir(d);

	if (header == NULL) {
		return NULL;
	}

	struct sort_list *ret = (struct sort_list *)malloc(sizeof(struct sort_list));

	ret->header = header;
	ret->cur = NULL;
	return ret;
}

void print_sort_list(int *data, int num) {
	int i = 0;

	for (i = 0; i < num; i++) {
		printf("%d ", data[i]);
	}

	printf("\n");
}

