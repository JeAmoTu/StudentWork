#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sqlite3.h>

#define PORT 9666
#define QUEUE_LEN 10
#define MAX_LINE 80

enum{
    ERROR = -1,
    LOG = 1,
    LOG_SUCSF,
    LOG_NOEXIST,
    LOG_ONLINE,
    LOG_FAILED,
    REG,
    REG_ERROR,
    REG_SUCSF,
    SHOW,
    SAY,
    SAY_FAILED,
    SAY_TOSUCSF,
    SAY_SUCSF,
    SALL,
    STOALL,
    EXP,
    REPLACE,
    OFF,
    OUT,
    OUTO,
    OUT_FAILED,
    BAN,
    BANTO,
    BAN_FAILED,
    RMBAN,
    RMBANTO,
    RMFAILED,
    CHG_PSD,
    CHG_PSD_FAILED,
    CHG_NAM,
    CHG_NAM_FAILED,
    SEND,
    SENDTO,
    SEND_FAILED,
    ACCEPT,
    ACCEPTO,
    ACCSUF,
    REFUSE,
    REFUSETO,
    EXIT
};

typedef struct msg_tag
{
    int action;
    int id;
    char name[100];
    char toname[100];
    char passwd[100];
    char message[1000];
    char file_name[100];
    char file_len;
}msg_t;

char back[100];
char online[100];
int count = 0;
char name[100];
char toname[100];
char file_name[100];
char aim_file_name[100];
int file_len;

static int callback(void *not_used, int argc, char **argv, char **col_name)
{
    int i;

    for(i = 0; i < argc; i++)
    {
        sprintf(back,"%s",argv[0]);

        sprintf(online+count,"%s ",argv[0]);

        count = count + strlen(argv[0]) + 1;
    }
    return 0;
}

int block_write(int fd, char* buf, int len)
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

int block_read(int fd, char* buf, int len)
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

int deal_action(msg_t * msg, int c_fd)
{
    sqlite3 *db = NULL;
    time_t timep;
    char rcd_time[100];
    char rcd[1024];
    int rc = sqlite3_open("user.db",&db);        
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
    }

    char *err_msg = NULL;

    char *sql_select_user = (char *)malloc(200);
    char *sql_select_user_name = (char *)malloc(200);
    char *sql_select_id = (char *)malloc(200);
    char *sql_select_user_status = (char *)malloc(200);
    char *sql_insert_user = (char *)malloc(200);
    char *sql_insert_user_rcd = (char *)malloc(1024);
    char *sql_insert_user_status = (char *)malloc(200);
    char *sql_select_passwd = (char *)malloc(200);
    char *sql_update_passwd = (char *)malloc(200);
    char *sql_update_name = (char *)malloc(200);
    char *sql_delete_status = (char *)malloc(200);
    char *sql_select_toname = (char *)malloc(200);
    char *sql_select_tofd = (char *)malloc(200);
    char *sql_select_toallfd = (char *)malloc(200);
    char *sql_delete_tostatus = (char *)malloc(200);
    char *sql_select_ban = (char *)malloc(200);

    memset(rcd_time,0,100);
    memset(rcd,0,1024);
    memset(sql_select_user,0,200);
    memset(sql_select_user_name,0,200);
    memset(sql_select_id,0,200);
    memset(sql_select_user_status,0,200);
    memset(sql_insert_user,0,200);
    memset(sql_insert_user_rcd,0,1024);
    memset(sql_insert_user_status,0,200);
    memset(sql_select_passwd,0,200);
    memset(sql_update_passwd,0,200);
    memset(sql_update_name,0,200);
    memset(sql_delete_status,0,200);
    memset(sql_delete_tostatus,0,200);
    memset(sql_select_toname,0,200);
    memset(sql_select_tofd,0,200);
    memset(sql_select_toallfd,0,200);
    memset(sql_select_ban,0,200);

    char *sql_select_status = "select name from status;";
    char *sql_create_user = "create table user(\
                             id INTEGER,\
                             name TEXT,\
                             passwd TEXT,\
                             primary key(name)\
                             );";
    char *sql_create_user_status = "create table status(\
                                    id INTEGER,\
                                    name TEXT,\
                                    fd INTEGER,\
                                    primary key(name)\
                                    );";
    char *sql_create_user_rcd = "create table usr_rcd(name TEXT, time TEXT, rcd TEXT);";

    sprintf(sql_select_toallfd,"select fd from status;");
    sprintf(sql_select_toname,"select name from status where name = \"%s\";",msg->toname);
    sprintf(sql_select_tofd,"select fd from status where name = \"%s\";",msg->toname);
    sprintf(sql_select_ban,"select name from status where name = \"%s\";",msg->toname);
    sprintf(sql_select_user,"select name from user where name = \"%s\";",msg->name);
    sprintf(sql_select_user_name,"select name from user where id = %d;",msg->id);
    sprintf(sql_select_id,"select id from user where id = %d;",msg->id);
    sprintf(sql_select_user_status,"select name from status where name = \"%s\";",msg->name);
    sprintf(sql_delete_status,"delete from status where name = \"%s\";",msg->name);
    sprintf(sql_delete_tostatus,"delete from status where name = \"%s\";",msg->toname);

    switch(msg->action)
    {

        case LOG:
            {
                while(1)
                {
                    memset(back,0,100);
                    int rc = sqlite3_exec(db,sql_select_id,callback,0,&err_msg);

                    if(atoi(back) == msg->id)
                    {
                        memset(back,0,100);
                        rc = sqlite3_exec(db,sql_select_user_name,callback,0,&err_msg);
                        strcpy(msg->name,back);
                        memset(back,0,100);
                        rc = sqlite3_exec(db,sql_select_user_status,callback,0,&err_msg);
                        if(rc == SQLITE_ERROR)
                        {
                            sqlite3_exec(db,sql_create_user_status,NULL,0,&err_msg);
                            continue;
                        }
                        if(strcmp(back,msg->name) == 0)
                        {

                            msg->action = LOG_ONLINE;
                            sqlite3_close(db);
                            return 0;
                        }

                        memset(back,0,100);
                        sprintf(sql_select_passwd,"select passwd from user where name = \"%s\";",msg->name);
                        rc = sqlite3_exec(db,sql_select_passwd,callback,0,&err_msg);
                        if(strcmp(back,msg->passwd) != 0)
                        {
                            msg->action = LOG_FAILED;
                            sqlite3_close(db);
                            return 0;
                        }

                        msg->action = LOG_SUCSF;
                        sprintf(sql_insert_user_status,"insert into status(id,name,fd)values(%d,'%s',%d);",msg->id,msg->name,c_fd);
                        rc = sqlite3_exec(db,sql_insert_user_status,NULL,0,&err_msg);
                        time(&timep);
                        sprintf(rcd_time,"%s",ctime(&timep));
                        sprintf(rcd,"%s 登录成功！\n",msg->name);
                        sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                        while(1)
                        {
                            int rc = sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                            if(rc == SQLITE_ERROR)
                            {
                                sqlite3_exec(db,sql_create_user_rcd,NULL,0,&err_msg);
                                continue;
                            }
                            break;
                        }
                        sqlite3_close(db);
                        return 0;
                    }
                    msg->action = LOG_NOEXIST;
                    sqlite3_close(db);
                    return 0;
                }
            }
        case REG:
            {
                while(1)
                {   
                    int rc = sqlite3_exec(db,sql_select_user,callback,0,&err_msg);

                    if(strcmp(back,msg->name) == 0)
                    {
                        memset(back,0,100);
                        msg->action = REG_ERROR;
                        sqlite3_close(db);
                        return 0;
                    }
                    srandom((unsigned)time(&timep));
                    msg->id = random();
                    sprintf(sql_insert_user,"insert into user(id,name,passwd)values(%d,'%s','%s');",msg->id,msg->name,msg->passwd);
                    rc = sqlite3_exec(db,sql_insert_user,NULL,0,&err_msg);

                    if(rc == SQLITE_ERROR)
                    {
                        rc = sqlite3_exec(db,sql_create_user,NULL,0,&err_msg);
                        continue;
                    }

                    if(rc == SQLITE_OK)
                    {
                        msg->action = REG_SUCSF;
                        sprintf(rcd_time,"%s",ctime(&timep));
                        sprintf(rcd,"%s 注册成功！\n",msg->name);
                        sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                        while(1)
                        {
                            int rc = sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                            if(rc == SQLITE_ERROR)
                            {
                                sqlite3_exec(db,sql_create_user_rcd,NULL,0,&err_msg);
                                continue;
                            }
                            break;
                        }
                        sqlite3_close(db);
                    }
                    break;
                }
                break;
            }
        case SHOW:
            {
                count = 0;
                memset(online,0,100);
                sqlite3_exec(db,sql_select_status,callback,0,&err_msg);
                msg->action = SHOW;
                strcpy(msg->message,online);

                sqlite3_close(db);
                break;
            }
        case SAY:
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg);
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = SAY_FAILED;
                    sqlite3_close(db);
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                msg->action = SAY_SUCSF;
                write(atoi(back),msg,sizeof(msg_t));
                msg->action = SAY_TOSUCSF;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 对 %s 悄悄说 %s\n",msg->name,msg->toname,msg->message);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case SALL:
            {
                count = 0;
                int i = 0;
                int len = 0;
                char tem[5];
                memset(tem,0,5);
                memset(online,0,100);
                sqlite3_exec(db,sql_select_toallfd,callback,0,&err_msg);
                msg->action = STOALL;
                while('\0' != *(online + len))
                {
                    if(*(online + len) == ' ')
                    {
                        if(atoi(tem) != c_fd)
                        {
                            write(atoi(tem),msg,sizeof(msg_t));
                        }
                        memset(tem,0,5);
                        i = 0;
                        len++;
                    }

                    strncpy(tem + i, online + len, 1);
                    i++;
                    len++;
                }
                msg->action = SALL;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 对大家说 %s\n",msg->name,msg->message);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case EXP:
            {
                count = 0;
                int i = 0;
                int len = 0;
                char tem[5];
                memset(tem,0,5);
                memset(online,0,100);
                sqlite3_exec(db,sql_select_toallfd,callback,0,&err_msg);
                msg->action = STOALL;
                while('\0' != *(online + len))
                {
                    if(*(online + len) == ' ')
                    {
                        if(atoi(tem) != c_fd)
                        {
                            write(atoi(tem),msg,sizeof(msg_t));
                        }
                        memset(tem,0,5);
                        i = 0;
                        len++;
                    }

                    strncpy(tem + i, online + len, 1);
                    i++;
                    len++;
                }
                msg->action = SALL;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 对大家 %s\n",msg->name,msg->message);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case OFF:
            {
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg);
                msg->action = OFF;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 离线成功！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case OUT:
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg);
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = OUT_FAILED;
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                msg->action = OUT;
                write(atoi(back),msg,sizeof(msg_t));
                msg->action = OUTO;
                sqlite3_exec(db,sql_delete_tostatus,NULL,0,&err_msg);
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 已被踢出聊天室！\n",msg->toname);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case CHG_PSD:
            {
                memset(back,0,100);
                sprintf(sql_select_passwd,"select passwd from user where name = \"%s\";",msg->name);
                sqlite3_exec(db,sql_select_passwd,callback,0,&err_msg);
                if(strcmp(back,msg->passwd) != 0)
                {
                    msg->action = CHG_PSD_FAILED;
                    return 0;
                }
                
                sprintf(sql_update_passwd,"update user set passwd = \"%s\" where name = \"%s\";",msg->message,msg->name);
                sqlite3_exec(db,sql_update_passwd,NULL,0,&err_msg);
                msg->action = CHG_PSD;
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg);
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 修改密码成功！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case CHG_NAM:
            {
                memset(back,0,100);
                sprintf(sql_select_user,"select name from user where name = \"%s\";",msg->message);
                sqlite3_exec(db,sql_select_user,callback,0,&err_msg);
                if(strcmp(back,msg->message) == 0)
                {
                    msg->action = CHG_NAM_FAILED;
                    return 0;
                }
                msg->action = CHG_NAM;
                sprintf(sql_update_name,"update user set name = \"%s\" where name = \"%s\";",msg->message,msg->name);
                sqlite3_exec(db,sql_update_name,NULL,0,&err_msg);
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg);
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 更改新昵称 %s 成功！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case BAN:
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg);
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = BAN_FAILED;
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                msg->action = BAN;
                write(atoi(back),msg,sizeof(msg_t));
                msg->action = BANTO;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 已被禁言！\n",msg->toname);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case RMBAN:
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg);
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = RMFAILED;
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                msg->action = RMBAN;
                write(atoi(back),msg,sizeof(msg_t));
                msg->action = RMBANTO;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 已被解除禁言！\n",msg->toname);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
            }
        case SEND:
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg);
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = SEND_FAILED;
                    sqlite3_close(db);
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                
                msg->action = SEND;
                write(atoi(back),msg,sizeof(msg_t));
                msg->action = SENDTO;
                strcpy(name,msg->name);
                strcpy(toname,msg->toname);
                strcpy(file_name,msg->file_name);
                file_len = msg->file_len;
                break;
            }
        case ACCEPT:
            {
                strcpy(aim_file_name,msg->file_name);
                strcpy(msg->name,name);
                strcpy(msg->toname,toname);
                strcpy(msg->file_name,file_name);
                msg->file_len = file_len;
                sprintf(sql_select_tofd,"select fd from status where name = \"%s\";",msg->name);
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                
                msg->action = ACCEPT;
                printf("%s %s",msg->name,msg->toname);
                write(atoi(back),msg,sizeof(msg_t));
                char * data = (char *)malloc(file_len + 1);
                memset(data,0,file_len + 1);
                block_read(atoi(back),data,file_len);
                msg->action = ACCEPTO;
                strcpy(msg->file_name,aim_file_name);
                write(c_fd,msg,sizeof(msg_t));
                block_write(c_fd,data,file_len);
                msg->action = ACCSUF;
                break;
            }
        case REFUSE:
            {
                strcpy(msg->name,name);
                strcpy(msg->toname,toname);
                sprintf(sql_select_tofd,"select fd from status where name = \"%s\";",msg->name);
                
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);
                
                msg->action = REFUSE;
                write(atoi(back),msg,sizeof(msg_t));
                msg->action = REFUSETO;
                break;
            }
        case EXIT:
            {
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg);
                msg->action = EXIT;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 退出聊天室！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                sqlite3_close(db);
                return EXIT;
            }
    }

    return 0;
}

void *send_msg(void * arg)
{
    msg_t msg = {0};
    int connectfd = *(int *)arg;

    while(1)
    {
        memset(&msg,0,sizeof(msg_t));

        int ret = read(connectfd,&msg,sizeof(msg_t));

        if(ret != sizeof(msg_t))
        {
            perror(strerror(errno));
        }

        if(deal_action(&msg,connectfd) == EXIT)
        {
            close(connectfd);
            break;
        }
    }
    return NULL;
}

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
    sin.sin_family=AF_INET;                 //
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
                    rc = sqlite3_exec(db,sql_delete_sfd,NULL,0,&err_msg);
                    sqlite3_close(db);

                    printf("the other side has been closed. \n");
                    fflush(stdout);                                    /* 刷新 输出终端 */
                    close(sfd);
                    
                    FD_CLR(sfd, &allset);                        /*清空连接描述符数组*/
                    client[i] = -1;
                }
                else
                {
                    /* 将客户端地址转换成字符串 */
                    inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
                    addr_p[strlen(addr_p)] = '\0';

                    int ret = deal_action(&msg,sfd);
                    n = write(sfd, &msg, sizeof(msg_t));
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
