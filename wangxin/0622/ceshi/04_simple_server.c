#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  PORT 1234
#define  QUEUE_LEN 10

int main(int argc, char **argv)
{
	// 1 create socket
	int listenfd = socket(PF_INET, SOCK_STREAM, 0);

        int opt = SO_REUSEADDR;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	// 2 bind
        struct sockaddr_in server;	
	memset(&server, 0, sizeof(server));
	server.sin_family	= AF_INET;
	server.sin_port		= htons(PORT);
	server.sin_addr.s_addr	= htonl(INADDR_ANY);
	bind(listenfd, (struct sockaddr *)&server, sizeof(server));
	
	// 3 listen
	listen(listenfd, QUEUE_LEN);

	// 4 accept
	struct  sockaddr_in client;
	socklen_t addrlen = sizeof(client);
	int connectfd = accept(listenfd, (struct sockaddr*)&client, &addrlen);
	
	// 5 recv data
	char buf=0;
	int num = read(connectfd, &buf, 1);

	// 6 exit handle;
	printf("rcvd %c\n", buf);
	close(connectfd);
	close(listenfd);
	return 0;
}
