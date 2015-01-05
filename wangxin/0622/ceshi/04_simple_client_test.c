#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  PORT 1234
#define  BACKLOG 1

int main(int argc, char *argv[])
{
	// 1 create socket
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);

	// 2 connect server
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(sockfd, (struct sockaddr*)&server, sizeof(server));

	// 3 send data
	char buf = '!';
	int num = write(sockfd, &buf, 1);

	// 4 exit handle
	close(sockfd);
	return 0;
}
