#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "ipc.h"

int main(int argc, char **argv) {
	key_t ipc_key = ftok(IPC_FTOK_PATH, IPC_PROJECT_ID);

	if (ipc_key == -1) {
		perror("can not get ftok key:");
		return -1;
	}

	// 客户端不用指定大小，和权限
	int shm_id = shmget(ipc_key, 0, 0);

	if (shm_id < 0) {
		perror("can not get the shm:");
		return -2;
	}

	char *shm_addr = (char *)shmat(shm_id, 0, SHM_RDONLY);

	if (shm_addr < 0) {
		perror("can not map address:");
		return -3;
	}

	printf("content in address: %s\n", shm_addr);

	shmdt(shm_addr);

	return 0;
}
