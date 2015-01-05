#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define QUEUE_LEN  10

typedef struct file_info_tag
{
    char opt;
    char name[256];
    int len;
}file_info_t;

int block_read(int fd, char*buf, int len)
{
    int read_size = 0;
    int n = 0;
    
    while(read_size < len)
    {
        n = read(fd, buf + read_size,len-read_size);
        if(n < 0)
	{
	    perror(strerror(errno));
	    break;
	}
	else if(0 == n)
	{
	    perror(strerror(errno));
	    break;
	}
	read_size += n;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("use ./a.out ip port\n");
	return 0;
    }

    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    
    if(listenfd < 0)
    {
        perror(strerror(errno));
	close(listenfd);
	return 0;
    }

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    
    int ret = bind(listenfd, (struct sockaddr *)&server, sizeof(server));
    if(ret < 0)
    {
        perror(strerror(errno));
	close(listenfd);
	return 9;
    }

    listen(listenfd, QUEUE_LEN);

    struct sockaddr_in client;
    socklen_t addrlen = sizeof(client);


    int connectfd = accept(listenfd, (struct sockaddr*)&client, &addrlen);

    file_info_t file_info;
    int num = read(connectfd, &file_info, sizeof(file_info));

    printf("opt: %d name: %s len: %d\n",file_info.opt,file_info.name,file_info.len);

    char *data = NULL;
    data = (char *)malloc(file_info.len + 1);
    memset(data,0,file_info.len + 1);
    int fd = open(file_info.name,O_RDWR|O_CREAT|O_APPEND,0664);

    if(fd < 0)
    {
	    perror(strerror(errno));
	    close(fd);
	    return 0;
    }
    block_read(connectfd,data,file_info.len);
    write(fd,data,file_info.len);

    close(fd);
    close(connectfd);
    close(listenfd);

    return 0;

