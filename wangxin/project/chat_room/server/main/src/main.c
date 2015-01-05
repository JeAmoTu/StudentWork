#include"../../include/my_head.h"

int callback(void *not_used, int argc, char **argv, char**col_name);

char back[100];
char online[100];
int count = 0;

int main()
{
    int lfd;
    int cfd;
    int sfd;
    int rdy;

    struct sockaddr_in sin;
    struct sockaddr_in cin;

    int client[FD_SETSIZE];  /* 客户端连接的套接字描述符数组 */

    int maxi;
    int maxfd;                        /* 最大连接数 */

    fd_set rset;
    fd_set allset;

    socklen_t addr_len;         /* 地址结构长度 */

    int i;
    int n;
    int len;
    int opt = 1;   /* 套接字选项 */

    char addr_p[20];
    msg_t msg = {0};


    /* 对server_addr_in  结构进行赋值  */
    bzero(&sin,sizeof(struct sockaddr_in));   /* 先清零 */
    sin.sin_family=AF_INET;                 //表示地址家族协议
    sin.sin_addr.s_addr=htonl(INADDR_ANY);  //表示接受任何ip地址   将ip地址转换成网络字节序
    sin.sin_port=htons(PORT);         //将端口号转换成网络字节序

    /* 调用socket函数创建一个TCP协议套接口 */
    if((lfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
    {
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        exit(1);
    }


    /*设置套接字选项 使用默认选项*/
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /* 调用bind函数 将serer_addr结构绑定到sockfd上  */
    if(bind(lfd,(struct sockaddr *)(&sin),sizeof(struct sockaddr))==-1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        exit(1);
    }


    /* 开始监听端口   等待客户的请求 */
    if(listen(lfd,20)==-1)
    {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        exit(1);
    }

    printf("Accepting connections .......\n");

    maxfd = lfd;                                /*对最大文件描述符进行初始化*/
    maxi = -1;

    /*初始化客户端连接描述符集合*/
    for(i = 0;i < FD_SETSIZE;i++)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);                     /* 清空文件描述符集合 */
    FD_SET(lfd,&allset);                    /* 将监听字设置在集合内 */


    /* 开始服务程序的死循环 */ 
    while(1)
    {
        
        sqlite3 *db = NULL;
        char *err_msg = NULL;
        int rc = sqlite3_open("user.db",&db);        
        if(rc != SQLITE_OK)
        {
            fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
        }
        char *sql_delete_sfd = (char *)malloc(100);
        memset(sql_delete_sfd,0,100);

        rset = allset;
        /*得到当前可以读的文件描述符数*/
        rdy = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(lfd, &rset))
        {
            addr_len = sizeof(sin);

            /* 接受客户端的请求 */
            if((cfd=accept(lfd,(struct sockaddr *)(&cin),&addr_len))==-1)
            {
                fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                exit(1);
            }

            /*查找一个空闲位置*/
            for(i = 0; i<FD_SETSIZE; i++)
            {       
                if(client[i] <= 0)
                {
                    client[i] = cfd;   /* 将处理该客户端的连接套接字设置到该位置 */
                    break;
                }
            }

            /* 太多的客户端连接   服务器拒绝俄请求  跳出循环 */
            if(i == FD_SETSIZE)
            {
                printf("too many clients");
                exit(1);
            }

            FD_SET(cfd, &allset);     /* 设置连接集合 */

            if(cfd > maxfd)                  /* 新的连接描述符 */
            {
                maxfd = cfd;
            }

            if(i > maxi)
            {
                maxi = i;
            }

            if(--rdy <= 0)                /* 减少一个连接描述符 */
            {
                continue;
            }

        }
        /* 对每一个连接描述符做处理 */
        for(i = 0;i< FD_SETSIZE;i++)
        {   
            if((sfd = client[i]) < 0)
            {
                continue;
            }

            if(FD_ISSET(sfd, &rset))
            {

                n = read(sfd,&msg,sizeof(msg));
                 
                if(n == 0)
                {
                    sprintf(sql_delete_sfd,"delete from status where fd = \"%d\";",sfd);
                    rc = sqlite3_exec(db,sql_delete_sfd,NULL,0,&err_msg);  //将被关闭的终端的用户从表中删除
                    sqlite3_close(db);

                    printf("the other side has been closed. \n");  //一个终端被关闭
                    fflush(stdout);                                    /* 刷新 输出终端 */
                    close(sfd);  //关闭连接描述符
                    
                    FD_CLR(sfd, &allset);                        /*清空连接描述符数组*/
                    client[i] = -1;
                }
                else
                {
                    /* 将客户端地址转换成字符串 */
                    inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
                    addr_p[strlen(addr_p)] = '\0';

                    int ret = deal_action(&msg,sfd);   //处理消息
                    n = write(sfd, &msg, sizeof(msg_t));   //往客户端写消息
                    if(ret == EXIT)
                    {
                        close(sfd);
                        FD_CLR(sfd, &allset);                        /*清空连接描述符数组*/
                        client[i] = -1;
                    }
                    /* 谐函数出错 */
                    if(n == 1)
                    {
                        exit(1);
                    }
                }

                /*如果没有可以读的套接字   退出循环*/
                if(--rdy <= 0)
                {
                    break;
                }

            }
        }

    }

    close(lfd);       /* 关闭链接套接字 */
    return 0;
}
