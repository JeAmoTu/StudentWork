#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


typedef struct file_info_tag
{
    char opt;
    char name[256];
    int len;
}file_info_t;

int block_write(int fd, char*buf, int len)
{
    int write_size = 0;
    int n = 0;

    while(write_size < len)
    {
        n = write(fd,buf+write_size,len-write_size);
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
	write_size += n;
    }

    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("use ./a.out ip port");
        return 0;
    }

    int count = 0;
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
    
    file_info_t file_info = {.opt = 1,.name = "xinjian.mp4"};
    
    int fd = open(file_info.name,O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    lseek(fd,0,SEEK_SET);
    file_info.len = len;
    int num = write(sockfd,&file_info,sizeof(file_info));
    if(num != sizeof(file_info))
    {
        perror(strerror(errno));
	close(sockfd);
	return 0;
    }
    char *data = NULL;
    
    data = malloc(file_info.len + 1);
    memset(data,0,file_info.len + 1);

    num = read(fd,data,file_info.len);
    block_write(sockfd,data,file_info.len);
    close(sockfd);
   
    return 0;
}
