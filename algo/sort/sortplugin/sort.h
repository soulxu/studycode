#ifndef SORT_H
#define SORT_H

struct sort_plugin {
	char *name;
	void (*sort_fun)(int *, int);
	struct sort_plugin *next;
	struct sort_plugin *prev;
};

struct sort_list {
	struct sort_plugin *header;
	struct sort_plugin *cur;
};

struct sort_list *get_sort_list(const char *dir);

struct sort_plugin *get_next_plugin(struct sort_list *list);

struct sort_plugin *get_prev_plugin(struct sort_list *list);

void free_sort_list(struct sort_list *list);

void reset_sort_list(struct sort_list *list);

#endif
