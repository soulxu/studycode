#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

void usage() {
	fprintf(stderr, "Usage: \n"
				"\tgen number output isunique\n");
}

int main(int argc, char **argv) {
	char *tmp = NULL;
	int unique = 0;
	
	if (argc != 4) {
		usage();
		exit(1);	
	}

	srand((uint)time(NULL));

	int num = atoi(argv[1]);
	int i = 0;
	
	FILE *out = fopen(argv[2], "w");

	if (atoi(argv[3]) == 0) {
		unique = 0;
	}
	else {
		unique = 1;
	}

	if (unique) {
		tmp = (char *)malloc(num);
		memset(tmp, 0, num);
	}

	if (out == NULL) {
		fprintf(stderr, "can not open output file.\n");
		exit(1);
	}

	for (i = 0; i < num;) {
		int data = rand() % num;

		if (unique) {
			if (tmp[data] == 1) {
				continue;
			}

			tmp[data] = 1;
		}
		fprintf(out, "%.7d\n", data);
		i++;
	}

	if (unique) {
		free(tmp);
	}

	fclose(out);
	return 0;
}
