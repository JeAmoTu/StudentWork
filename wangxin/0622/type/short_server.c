#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define PORT 1234  //同一ip不同的接收点
#define QUEUE_LEN 10

int main(int argc, char **argv)
{
    //1 creat socket  创建socket(套接字)
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    //set addr reuse
    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //2 bind 将自己的IP和端口绑定起来(门牌号,地址)
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    bind(listenfd, (struct sockaddr *)&server, sizeof(server));

    //3 listen (开门)监听
    listen(listenfd, QUEUE_LEN);

    //4 accept  正式接收数据(叫号)
    struct sockaddr_in client;
    socklen_t addrlen = sizeof(client);
    int connectfd = accept(listenfd, (struct sockaddr*)&client, &addrlen);
    
    //5 recv data  
    unsigned short buf;
    int num = read(connectfd, &buf, sizeof(buf));
    
    //6 exit handle
    printf("num %d recv %x\n", num, buf);
    close(connectfd);
    close(listenfd);
    
    return 0;
}
