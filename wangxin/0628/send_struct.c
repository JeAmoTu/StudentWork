#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>


typedef struct file_info_tag
{
    char opt;
    char name[256];
    int len;
}file_info_t;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("use ./a.out ip port");
        return 0;
    }

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
    
    file_info_t file_info = {.opt = 1,.name = "log.txt",.len = 200};
    int num = write(sockfd,&file_info,sizeof(file_info));
    if(num != sizeof(file_info))
    {
        perror(strerror(errno));
	close(sockfd);
	return 0;
    }
    close(sockfd);
   
    return 0;
}
