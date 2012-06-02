#ifndef NOTIFY_H
#define NOTIFY_H

#include <sys/inotify.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <glib.h>
#define EVENT_BUFSIZE 1024

struct watch {
	int wd;
	char path[PATH_MAX];
	uint32_t mode;
	struct watch *next;
};

struct watch_event {
    int fd;
    int wd;
    char path[PATH_MAX];
    char filename[PATH_MAX];
    uint32_t mask;
};

struct notify {
	int fd;
	int recursive;
	int append;
	struct watch *watch_list;
	void (*fun)(const struct watch_event *);
};

struct notify *notify_new(int recursive, int append, void (*fun)(const struct watch_event *));

int notify_add_watch(struct notify *notify, const char *path, uint32_t mode);

void notify_free(struct notify *notify);

int notify_watch(struct notify *notify, struct timeval *timeout);

#endif
