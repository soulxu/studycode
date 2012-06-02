#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MEM_SIZE 4096

int main() {
	//可以通过该设备创建匿名内存共享区
	int fd = open("/dev/zero", O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);

	if (fd < 0) {
		perror("can not open /dev/zero:");
		return -1;
	}

/*      普通文件要用mmap返回的指针访问超过文件大小的位置，会产生SIGBUS信号, 因此可以通过lseek来扩大文件
	if (lseek(fd, MEM_SIZE, SEEK_SET) == -1) {
		perror("can not seek file:");
		return -3;
	}

	write(fd, "", 1);
*/
	char *addr = (char *)mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (addr == -1) {
		perror("can not map mem:");
		return -2;
	}

	strcpy(addr, "this is copy from parent");

	if (fork() > 0) {
		printf("memory content is: %s\n", addr);
	}
	else {
		getchar();
	}	

	return 0;
}
