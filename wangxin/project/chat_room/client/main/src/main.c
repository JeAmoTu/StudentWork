#include"../../include/my_head.h"

int status = 0;
int ban = 0;
int root = 0;
msg_t msg = {0};  //定义一个全局结构体

void *thread_write(int *arg);
void *thread_read(int *arg);

int main(int argc, char *argv[])
{
    int i;
    pthread_t pid[2];  //创建两个线程id

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);   //创建socket文件描述符
    if(sockfd < 0)
    {
        perror(strerror(errno));
        close(sockfd);
        return 0;
    }

    struct sockaddr_in server;   //结构体赋值
    memset(&server,0,sizeof(server));   
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(sockfd,(struct sockaddr *)&server,sizeof(server));  //连接客户端
    if(ret < 0)
    {
        perror(strerror(errno));
        close(sockfd);
        return 0;
    }


    pthread_create(&pid[0],NULL,thread_write,&sockfd); //创建线程
    pthread_create(&pid[1],NULL,thread_read,&sockfd);  //创建线程

    for(i = 0; i < 2; i++)
    {
        pthread_join(pid[i],NULL);   //等待线程结束
    }
    close(sockfd);   //关闭连接描述符

    return 0;
}
