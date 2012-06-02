#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

int run = 1;

void timeout(int sig) {
	if (run) {
		run = 0;
	}
}

int main(int argc, char **argv) {
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int l = 0;

	struct itimerval itimer;

	if (argc != 2) {
		fprintf(stderr, "usage: cpu percent\n");
		return -1;
	}
	
	itimer.it_interval.tv_sec = 1;
	itimer.it_interval.tv_usec = 0;

	itimer.it_value.tv_sec = 1;
	itimer.it_value.tv_usec = 0;

	signal(SIGALRM, timeout);

	setitimer(ITIMER_REAL, &itimer, NULL);

	while (run);

	run = 1;

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 500000; j++) {
			if (!run) {
				break;
			}
		}

		if (!run) {
			break;
		}
	}

	int per = atoi(argv[1]);
	float percent = per / 100.0;
	printf("%d, %d, %d\n", i, j, (int)(i * percent));

	while (1) {
		for (k = 0; k < (int)(i * percent); k++) {
			for (l = 0; l < 500000 - 10000; l++) {
				//if (run) { j++; } else {}
				j++;
			}
		}
		//printf("pause\n");
		pause();
	}
	return 0;
}
