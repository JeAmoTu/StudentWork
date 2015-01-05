#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

enum{CMD_PUT = 1,CMD_GET,CMD_DEL};

typedef struct msg_tag
{
    int type;
    int len;
}msg_t;

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("use ./a.out ip port");
		return 0;
	}

	while(1)
	{
		int sockfd = socket(PF_INET,SOCK_STREAM,0);
		if(sockfd < 0)
		{
			perror(strerror(errno));
			close(sockfd);
			return 0;
		}

		struct sockaddr_in server;
		memset(&server,0,sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(atoi(argv[2]));
		server.sin_addr.s_addr = inet_addr(argv[1]);

		int ret = connect(sockfd,(struct sockaddr *)&server,sizeof(server));
		if(ret < 0)
		{
			perror(strerror(errno));
			close(sockfd);
			return 0;
		}

		msg_t msg = {0};
		char buf[20];
		char cmd[20];

		memset(buf,0,strlen(buf));
		memset(cmd,0,strlen(cmd));
		setbuf(stdin,NULL);
		scanf("%s %s",cmd,buf);

		if(strcmp(cmd,"put") == 0)
		{
			msg.type = CMD_PUT;
		}
		if(strcmp(cmd,"get") == 0)
		{
			msg.type = CMD_GET;
		}
		if(strcmp(cmd,"del") == 0)
		{
			msg.type = CMD_DEL;
		}
		msg.len = strlen(buf);
		int num = write(sockfd,&msg,sizeof(msg));

		if(num != sizeof(msg))
		{
			perror(strerror(errno));
			close(sockfd);
			return 0;
		}
		num = write(sockfd,buf,strlen(buf));
		if(num != strlen(buf))
		{
			perror(strerror(errno));
			close(sockfd);
			return 0;
		}
		close(sockfd);
	}


	return 0;
}
