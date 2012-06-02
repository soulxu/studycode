#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int sk = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);

	if (sk == -1) {
		return -1;
	}

	struct sockaddr_nl addr;

	memset(&addr, 0, sizeof(addr));
	
	addr.nl_family = AF_NETLINK;
	addr.nl_pid = getpid();
	addr.nl_groups = 0xffffffff;

	if (bind(sk, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		fprintf(stderr, "can not bind.\n");
		return -1;
	}

	int len = 0;
	char buf[4096];

	while ((len = recv(sk, buf, 4096, 0)) > 0) {
		buf[len] = '\0';
		printf("uevent: %s\n", buf);
	}

	close(sk);

	
	return 0;
}
