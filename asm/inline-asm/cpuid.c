#include <stdio.h>

int main(int argc, char **argv) {
	char id[13] = {0};
        int id1;
        int id2;
        int id3;
	asm("movl $0, %%eax \n"
            "cpuid \n"
            "movl %%ebx, %0 \n"
            "movl %%edx, %1 \n"
            "movl %%ecx, %2 \n" :
             "=r" (id1), "=r" (id2), "=r" (id3):: "%eax", "%edx", "%ecx");
        memcpy(id, &id1, 4);
        memcpy(id + 4, &id2, 4);
	memcpy(id + 8, &id3, 4);
	printf("the cpu is %s\n", id);
	return 0;
}
