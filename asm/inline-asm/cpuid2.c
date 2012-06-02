#include <stdio.h>

int main(int argc, char **argv) {
	char id[13] = {0};
	asm("movl $0, %%eax \n"
            "cpuid \n"
            "movl %%ebx, %0 \n"
            "movl %%edx, %1 \n"
            "movl %%ecx, %2 \n" :
             "=m" (*(id)), "=m" (*((id) + 4)), "=m" (*((id) + 8)):: "%eax", "%edx", "%ecx");
	printf("the cpu is %s\n", id);
	return 0;
}
