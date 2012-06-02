#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "ipc.h"

#define SHM_SIZE (1024 * 1024 * 10)

int main(int argc, char **argv) {
        //用来服务器与客户端共享的辨识
	key_t ipc_key = ftok(IPC_FTOK_PATH, IPC_PROJECT_ID);
	
	if (ipc_key == -1) {
		perror("can not create ftok key.");
		return -1;
	}

	printf("key: %x\n", ipc_key);

	// server 必须指定权限
	int shm_id = shmget(ipc_key, SHM_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);

	if (shm_id < 0) {
		perror("can not get the msg queue");
		return -2;
	}

	//将共享内存映射到当前进程地址空间当中
	char *shm_addr = (char *)shmat(shm_id, NULL, 0);

	if (shm_addr == -1) {
		perror("can not get the msg queue");
		return -3;
	}

	strcpy(shm_addr, "this is copy from server.");

	getchar();

	//断开链接地址
	shmdt(shm_addr);

 	//删除该共享内存空间，存在引用计数，当没有任何进程引用时，才会被实际删除
	shmctl(shm_id, IPC_RMID, NULL);

	return 0;
}
