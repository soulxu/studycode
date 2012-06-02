#include <stdio.h>
#include <stdlib.h>
char *fun(char *src) {
	char *ret = (char *)malloc(strlen(src) + 1);
	char *s = src + strlen(src) - 1;
	char end = src[0];
	char *e = s;

	memset(ret, 0, sizeof(strlen(src) + 1));

	while (*s != end) {
		if (*s == ' ') {
			if ((e - s) != 0) {
				strncat(ret, s + 1, e - s);
				strcat(ret, " ");
				e = s;
			}
			e--;
		}

		s--;
	}

	strncat(ret, s, e - s + 1);
	return ret;
}

int main() {
	printf("%s\n", fun("how are you doing"));
}
