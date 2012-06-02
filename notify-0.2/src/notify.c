#include "notify.h"

#include <sys/inotify.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <time.h>
#include <sys/select.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>


struct notify *notify_new(int recursive, int append, void (*fun)(const struct watch_event *)) {
	assert (fun != NULL);
	struct notify *new_notify = (struct notify *)malloc(sizeof(struct notify));

	if (new_notify == NULL) {
		return NULL;
	}

	new_notify->fd = inotify_init();	

	if (new_notify->fd == -1) {
		free(new_notify);
		return NULL;
	}

	new_notify->watch_list = (struct watch *)malloc(sizeof(struct watch));
	if (new_notify->watch_list == NULL) {
		free(new_notify);
		return NULL;
	}
	memset(new_notify->watch_list, 0, sizeof(struct watch));
	new_notify->fun = fun;
	new_notify->recursive = recursive;
	new_notify->append = append;
	return new_notify;
}

int _add_watch(struct notify *notify, struct watch *watch) {
	int ret = 0;
	int new_wd = inotify_add_watch(notify->fd, watch->path, watch->mode);

	if (new_wd == -1) {
		ret = -1;
	}
	else {
		watch->wd = new_wd;
		watch->next = notify->watch_list;
		notify->watch_list = watch;
	}

	return ret;
}

int notify_add_watch(struct notify *notify, const char *path, uint32_t mode) {
	assert(notify != NULL && path != NULL);
	int new_wd = 0;
	struct stat stat_buf = {0};
	struct watch *new_watch = NULL;
	struct watch *list = notify->watch_list;
	DIR *dir_ptr = NULL;
	struct dirent *dirent_ptr = NULL;
	char path_tmp[PATH_MAX] = {'\0'};

	while (list->next != NULL) {
		if (!strcmp(list->path, path)) {
			return 0;
		}
		list = list->next;
	}

	new_watch = (struct watch *)malloc(sizeof(struct watch));
	strcpy(new_watch->path, path);
	new_watch->mode = mode;
	
	if (_add_watch(notify, new_watch) == -1) {
		return -1;
	}

	stat(path, &stat_buf);
	if (notify->recursive && S_ISDIR(stat_buf.st_mode))  {
		if ((dir_ptr = opendir(path)) != NULL) {
			while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
				if (!strcmp(dirent_ptr->d_name, ".") || !strcmp(dirent_ptr->d_name, "..")) {
					continue;
				}
				strcpy(path_tmp, path);
				strcat(path_tmp, "/");
				strcat(path_tmp, dirent_ptr->d_name);
				stat(path_tmp, &stat_buf);
				if (S_ISDIR(stat_buf.st_mode)) {
					if (notify_add_watch(notify, path_tmp, mode) == -1) {
						break;
					}
				}
			}	
			closedir(dir_ptr);
		}
	}
	
	return 0;
}

void notify_free(struct notify *notify) {
	assert(notify != NULL);
	struct watch *list = notify->watch_list;
	struct watch *old = NULL;

	while (list->next != NULL) {
		inotify_rm_watch(notify->fd, list->wd);
		old = list;
		list = list->next;
		free(old);		
	}

	free(list);
	free(notify);
}

int notify_watch(struct notify *notify, struct timeval *timeout) {
	int ret = 0;
	int len = 0;
	char event_buf[EVENT_BUFSIZE] = {'\0'};
	struct inotify_event *i_event = NULL;
	struct watch *list = notify->watch_list;
	struct watch_event event = {'\0'};
	char path_buf[PATH_MAX] = {'\0'};
	fd_set read_set;
	FD_ZERO(&read_set);
	FD_SET(notify->fd, &read_set);
	
	for (;;) {
		ret = select(FD_SETSIZE, &read_set, NULL, NULL, timeout);

		if (ret < 0 && errno != EINTR) {
			return ret;
		}
		else if (ret < 0 && errno == EINTR) {
			continue;
		}
		else if (ret == 0) {
			return 0;
		}
		break;
	}
	ret = read(notify->fd, event_buf, EVENT_BUFSIZE);
	if (ret <= 0) {
		return ret;
	}
		
	while (len < ret) {
		i_event = (struct inotify_event *)(event_buf + len);
        
		while (list->next != NULL) {
			if (list->wd == i_event->wd) {
				break;
			}
			list = list->next;
		}

        if (notify->append && (i_event->mask & IN_ISDIR) && (i_event->mask & IN_CREATE)) {
            memset(path_buf, 0, PATH_MAX);
            strcpy(path_buf, list->path);
            strcat(path_buf, "/");
            strcat(path_buf, i_event->name);
			strcat(path_buf, "/");
            notify_add_watch(notify, path_buf, list->mode);
        } 

		memset(&event, 0, sizeof(struct watch_event));
        strcpy(event.filename, i_event->name);
        strcpy(event.path, list->path);
        event.mask = i_event->mask;
        event.fd = notify->fd;
        event.wd = i_event->wd;
		notify->fun(&event);
		len += sizeof(struct inotify_event) + i_event->len;
		list = notify->watch_list;
	}

	return ret;
}


