#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
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
        printf("use ./server ip port!\n");
	return 0;
    }

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
	perror(strerror(errno));
	close(listenfd);
	return 0;
    }

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = bind(listenfd, (struct sockaddr*)&server, sizeof(server));
    
    if(ret < 0)
    {
        perror(strerror(errno));
	close(listenfd);
	return 0;
    }

    listen(listenfd, 10);

    struct sockaddr_in client;
    socklen_t addrlen = sizeof(client);

    while(1)
    {
        int connectfd = accept(listenfd, (struct sockaddr*)&client, &addrlen);

	if(connectfd < 0)
	{
	    perror(strerror(errno));
	    close(listenfd);
	    close(connectfd);
	    return 0;
	}

        msg_t msg = {0};
	int num = read(connectfd, &msg, sizeof(msg));
	if(num != sizeof(msg))
	{
	    perror(strerror(errno));
	    close(listenfd);
	    close(connectfd);
	    return 0;
	}

	char *buf = NULL;

	switch(msg.type)
	{
	    case CMD_PUT:
	    {
		buf = (char*)malloc(msg.len + 1);
		memset(buf, 0, msg.len + 1);
		num = read(connectfd, buf, msg.len);
		if(num != msg.len)
		{
		    perror(strerror(errno));
		    close(listenfd);
		    close(connectfd);
		    return 0;
		}
		printf("put filename: %s\n",buf);
		
		int ack = 1; 
		int ret = write(connectfd,&ack,sizeof(ack));
		if(ret != sizeof(ack))
		{
		    perror(strerror(errno));
		    close(listenfd);
		    close(connectfd);
		    return 0;
		}
		
		free(buf);
		close(connectfd);
		break;
	    }
	    case CMD_GET:
	    {
	        buf = (char*)malloc(msg.len + 1);
		memset(buf, 0, msg.len + 1);
		num = read(connectfd, buf, msg.len);
		if(num != msg.len)
		{
		    perror(strerror(errno));
		    close(listenfd);
		    close(connectfd);
		    return 0;
		}
		printf("get filename: %s\n",buf);
		int ack = 2; 
		int ret = write(connectfd,&ack,sizeof(ack));
		if(ret != sizeof(ack))
		{
		    perror(strerror(errno));
		    close(listenfd);
		    close(connectfd);
		    return 0;
		}
		
		free(buf);
		close(connectfd);
		break;
            }
	    case CMD_DEL:
	    {
	        buf = (char*)malloc(msg.len + 1);
		memset(buf, 0, msg.len + 1);
		num = read(connectfd, buf, msg.len);
		if(num != msg.len)
		{
		    perror(strerror(errno));
		    close(listenfd);
		    close(connectfd);
		    return 0;
		}
		printf("del filename: %s\n",buf);
		
		int ack = 3; 
		int ret = write(connectfd,&ack,sizeof(ack));
		
		if(ret != sizeof(ack))
		{
		    perror(strerror(errno));
		    close(listenfd);
		    close(connectfd);
		    return 0;
		}
		
		free(buf);
		close(connectfd);
		break;
	    }
	    default:
	    {
	        printf("unknow order\n");
		close(connectfd);
		break;
	    }
	}
    }
    
    close(listenfd);
   
    return 0;
}
