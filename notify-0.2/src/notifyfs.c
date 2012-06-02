#include "notify.h"
#include "notifyfs.h"

#include <getopt.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define OPT_ARGS "arhm:"

struct notify *notify = NULL;

struct event_msg event_to_msg[] = {
	{IN_ACCESS, "access", 'e'},
	{IN_ATTRIB, "attrib", 't'},
	{IN_CLOSE_WRITE, "close on write", 'w'},
	{IN_CLOSE_NOWRITE, "close on no write", 'n'},
	{IN_CREATE, "create", 'c'},
	{IN_DELETE, "delete", 'd'},
	{IN_MODIFY, "modify", 'm'},
	{IN_MOVE_SELF, "moved self", 's'},
	{IN_MOVED_FROM, "moved from", 'f'},
	{IN_MOVED_TO, "moved to", 'o'},
	{IN_OPEN, "open", 'p'},
	{IN_ALL_EVENTS, "all event", 'a'}
};


struct option long_opts[] =  {
	{"help", no_argument, NULL, 'h'},
    {"append", no_argument, NULL, 'a'},
    {"recursive", no_argument, NULL, 'r'},
	{0, 0, 0, 0}
};

void sigfun_clear(int signum) {
    printf("terminate notify\n");
    if (notify != NULL) {
        notify_free(notify);
    }
    exit(0);
}

void event_listener(const struct watch_event *event) {
	int i;
	char *msg = NULL;
	//char path[PATH_MAX] = {'\0'};
 
	for (i = 0; i < EVENT_NUM; i ++) {
		if (event_to_msg[i].mode & event->mask) {
			msg = event_to_msg[i].msg;
			break;
		}
	}
	//strcpy(path, event->path);
	//(event->filename[0] == '\0') ? NULL : strcat(path, event->filename);

	printf("%s\t%s\t%s\n", event->path, event->filename, msg);
}

void usage() {
	printf("usage: command [-h] [-a] -m EVENT PATH\n");
}

uint32_t parse_paramenter(const char *para) {
	const char *ptr = para;
	int i = 0;
	uint32_t mode = 0;
	while (*ptr != '\0') {
		for (i = 0; i < EVENT_NUM; i++) {
			if (event_to_msg[i].arg == *para) {
				mode |= event_to_msg[i].mode;	
			}
		}
		ptr++;
	}
	return mode;
}

int main(int argc, char **argv) {
	int opt = 0;
	uint32_t mode = 0;
	int i = 0;
	int longindex = 0;
	int num = 0;
    int append = 0;
	int recursive = 0;

	if (argc <= 1) {
		usage();
		exit(0);
	} 

	while ((opt = getopt_long(argc, argv, OPT_ARGS, long_opts, &longindex)) != -1) {
		switch (opt) {
        case 'a':  //append
            append = 1;
            break;
        case 'r':  //recursive
            recursive = 1;
            break;
		case 'm':  // listened event
			mode = parse_paramenter(optarg);
			break;
		case 'h':
		case '?':
		default:
			usage();
			exit(0);
		}
	}
	num = argc - optind;
	// when terminating program, program can clear the notify
	signal(SIGINT, sigfun_clear);

	printf("Create notify on ");

	notify = notify_new(recursive, append, event_listener);

	if (notify == NULL) {
		printf("error\n");
		exit(1);
	}

	for (i = 0; i < num; i++) {
		printf("%s ", argv[optind + i]);
		if (notify_add_watch(notify, argv[optind + i], mode) < 0) {
			perror("Can not add watch");
			exit(1);
		}
	}

	//printf("%d:%s:%d\n", notify->watch_list->watch, notify->watch_list->path, notify->watch_list->mode);
    printf("\ndir\tfilename\tevent\n");

	while (notify_watch(notify, NULL) > 0) {

	}
	return 0;
}
