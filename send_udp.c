#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char *argv[])
{
	int sd, n, i, len;
	struct sockaddr_in daddr;
	char buf[128];

	if ( (sd = socket(AF_INET, SOCK_DGRAM, 0) ) < 0 ) {
		perror("socket");
	} else {
		printf("socket descriptor :%d\n", sd);
	}

	daddr.sin_family = AF_INET;
	daddr.sin_port = htons(1234);
	daddr.sin_addr.s_addr = inet_addr("192.168.56.101");

	len = sizeof(struct sockaddr_in);

	sendto(sd, buf, 128, 0, (struct sockaddr *)&daddr, len);

	return 0;
}

