#ifndef _IPC_H__
#define _IPC_H__

#define IPC_FTOK_PATH "/tmp/ipc_ftok"
#define IPC_PROJECT_ID 'a'

struct msg_buf {
	long type;
	char data[4096];
};

#endif //_IPC_H__
