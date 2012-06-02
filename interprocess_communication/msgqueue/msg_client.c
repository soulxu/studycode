#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>

#include "ipc.h"
int main(int argc, char **argv) {
	key_t ipc_key = ftok(IPC_FTOK_PATH, IPC_PROJECT_ID);
	
	if (ipc_key == -1) {
		perror("can not create ftok key.");
		return -1;
	}

	printf("key: %x\n", ipc_key);

	int msg_id = msgget(ipc_key, S_IRUSR | S_IWUSR);

	if (msg_id < 0) {
		perror("can not get the msg queue");
		return -2;
	}

	printf("msg id: %d\n", msg_id);

	struct msqid_ds msq_stat;

	if (msgctl(msg_id, IPC_STAT, &msq_stat) == -1) {
		perror("can not get queue stat:");
	}

	printf("uid: %d\n", msq_stat.msg_perm.uid);
	printf("gid: %d\n", msq_stat.msg_perm.gid);
	printf("creator uid: %d\n", msq_stat.msg_perm.cuid);
	printf("creator gid: %d\n", msq_stat.msg_perm.cgid);

	struct msg_buf buf;
	buf.type = 1;

	while (gets(buf.data) != EOF) {
		printf("send: %s\n", buf.data);
		if (msgsnd(msg_id, &buf, 
				sizeof(struct msg_buf), 0) == -1) 
		{
			perror("can not send:");
			break;
		}
	}

	return 0;
}
