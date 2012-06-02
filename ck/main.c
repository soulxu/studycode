#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <ConsoleKit/ck-connector/ck-connector.h>


void usage() {
	fprintf(stderr, "ck user\n");
}

int main(int argc, char **argv) {
	char *user = NULL;

	if (argc != 2) {
		usage();
		exit(1);
	}

	user = argv[1];

	struct passwd *pwent = getpwnam(user);	

	if (pwent == NULL) {
		fprintf(stderr, "can not get user entry.\n");
		exit(1);
	}

	printf("uid: %d, euid: %d, sid: %d, pid: %d, pgid: %d\n", getuid(), geteuid(), getsid(0), getpid(), getpgid(0));



	if (setuid(pwent->pw_uid) == -1) {
		fprintf(stderr, "can not set uid.\n");
		exit(1);
	}


	printf("after setuid = uid: %d, euid: %d, sid: %d, pgid: %d\n", getuid(), geteuid(), getsid(0), getpgid(0));


	if (fork() != 0) {
		exit(0);
	}

	if (setsid() == -1) {
		fprintf(stderr, "can not create new session.\n");
		exit(1);
	}

	printf("after setsid = uid: %d, euid: %d, sid: %d, pgid: %d\n", getuid(), geteuid(), getsid(0), getpgid(0));

	if (fork() != 0) {
		while (1) {
			pause();
		}
	}

	DBusError *error = NULL;

	CkConnector *conn = ck_connector_new();


	if (!ck_connector_open_session(conn, error)) {
		fprintf(stderr, "can not open new session with ck.\n");
		exit(1);
	}

	while (1) {
		pause();
	}
	//execl("/bin/bash", NULL);

	fprintf(stderr, "can not run new shell.\n");

	return 0;
}
