#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int sk = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);

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
/*
	struct sockaddr_nl dest_addr;
	struct nlmsghdr *nlhdr = NULL;
	struct msghdr msg;

	struct iovec iov;
	char buf[4096];
	iov.iov_base = (void *)buf;

	iov.iov_len = sizeof(buf);

	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	int len = 0;

	printf("start recv msg.\n");
	len = recvmsg(sk, &msg, 0);
	printf("end recv msg.\n");

	for (nlhdr = (struct nlmsghdr *)buf; NLMSG_OK(nlhdr, len); nlhdr = NLMSG_NEXT(nlhdr, len)) {
		if (nlhdr->nlmsg_type == NLMSG_DONE) {
			break;
		}
		else if (nlhdr->nlmsg_type == NLMSG_ERROR) {

		}

		printf("%s\n", NLMSG_DATA(nlhdr));
	}
*/
	int len = 0;
	char buf[4096];

	while ((len = recv(sk, buf, 4096, 0)) > 0) {
		buf[len] = '\0';
		printf("%s\n", buf);
	}
	close(sk);

	
	return 0;
}
