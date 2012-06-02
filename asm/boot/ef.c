#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	if (argc < 1) {
		printf("error1");
		return -1;
	}

	int fd = open(argv[1], O_CREAT|O_RDWR);
	if (fd < 0) {
		printf("can not create file\n");
		return -1;
	}

	char buf[2] = {0x55, 0xAA};
	write(fd, &buf, 2);
	close(fd);
}
