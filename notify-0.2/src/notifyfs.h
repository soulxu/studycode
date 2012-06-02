#ifndef NOTIFYFS_H
#define NOTIFYFS_H

#include <sys/inotify.h>

struct event_msg {
	uint32_t mode;
	char *msg;
	char arg;
};

#define EVENT_NUM 12
extern struct event_msg event_to_msg[EVENT_NUM];

#endif
