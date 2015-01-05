#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>

#define BACKLOG 1

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("use ./a.out dst_ip port!\n");
        return 0;
    }

    //1 creat socket  创建socket
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        perror(strerror(errno));
        close(sockfd);
        return 0;
    }

    //2 connect server  服务端发送连接
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);//htonl(INADDR_ANY)

    int set = connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    if(set < 0)
    {
        perror(strerror(errno));
        close(sockfd);
        return 0;
    }
    //3 send data   发送数据
    char buf[100];
    gets(buf);
    int num = write(sockfd, &buf, 100);

    //4 exit handle
    close(sockfd);

    return 0;
}
