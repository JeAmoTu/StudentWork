#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sqlite3.h>

#define PORT 9666
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

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
    EXIT,
    HELP
};

int status = 0;
int root = 0;
int ban = 0;


typedef struct msg_tag
{
    int action;
    int id;
    char name[100];
    char toname[100];
    char passwd[100];
    char message[1000]; 
    char file_name[100];
    int file_len;
}msg_t;

msg_t msg = {0};

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

int set_disp_mode(int fd, int option)
{
    int err;
    struct termios term;
    if(tcgetattr(fd,&term) == -1)
    {
        perror("cannot get the attribution of the terminal");
        return 1;
    }
    if(option)
    {
        term.c_lflag |= ECHOFLAGS;
    }
    else
    {
        term.c_lflag &= ~ECHOFLAGS;
    }
    err = tcsetattr(fd,TCSAFLUSH,&term);
    if(err == -1 && err == EINTR)
    {
        perror("cannot set the attribution of the terminal");
        return 1;
    }
    return 0;
}

void interface(char *name)
{
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("|               新智聊天室                |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|                                         |\n");
    printf("|               1.登录(log)               |\n");
    printf("|               2.注册(reg)               |\n");
    printf("|               3.退出聊天室(exit)        |\n");
    printf("|                                         |\n");
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("请输入你的选择(log/reg/exit)\n\n");
}

int interface1(char *name)
{
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("|                    新智聊天室                   |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|   1.查看在线用户(show)     2.进行聊天(say)      |\n");
    printf("|   2.群发消息(stoall)       4.快捷消息(/u/img)   |\n");
    printf("|   5.退出登录(off)          6.表情 :) 0.0 ^3^    |\n");
    printf("|   7.修改密码(chg_psd)      8.修改昵称(chg_nam)  |\n");
    printf("|   9.查看帮助(help)         10.退出聊天室(exit)  |\n");
    printf("|                                                 |\n");
    printf("|当前用户为:%-20s                  |\n",name);
    printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");

    if(strcmp(name,"admin") == 0)
    {
        printf("|你是超级用户,可以使用以下功能:                   |\n");
        printf("|                                                 |\n");
        printf("|   1.踢出某人(out)          2.禁言某人(ban)      |\n");
        printf("|   3.解除某人禁言(rmban)                         |\n");
        printf("|                                                 |\n");
        printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("tip:快捷消息方式为/client/message (welcome/like/unhappy)\n");
        printf("请输入你的选择(log/reg/show/say/stoall/off/help/exit)\n\n");
        return 0;
    }
    printf("tip:快捷消息方式为/client/message (welcome/like/unhappy)\n");
    printf("请输入你的选择(log/reg/show/say/stoall/off/chg_psd/chg_nam/help/exit)\n\n");
    return 0;
}

int check_action(char *cmd)
{
    if(cmd[0] == '/')
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return REPLACE;
    }
    if(strcmp(cmd,"log") == 0)
    {
        if(status == 1)
        {
            printf("你已登录！\n\n");
            return 0;
        }
        return LOG;
    }
    if(strcmp(cmd,"reg") == 0)
    {
        if(status == 1)
        {
            printf("你已登录,请离线后载注册！\n\n");
            return 0;
        }
        return REG;
    }    
    if(strcmp(cmd,"show") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return SHOW;
    }
    if(strcmp(cmd,"say") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(ban == 1)
        {
            printf("你已被禁言！\n\n");
            return 0;
        }
        return SAY;
    }
    if(strcmp(cmd,"stoall") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(ban == 1)
        {
            printf("你已被禁言！\n\n");
            return 0;
        }
        return SALL;
    }
    if((strcmp(cmd,":)") == 0) || (strcmp(cmd,"0.0") == 0) || (strcmp(cmd,"^3^") == 0))
    { 
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(ban == 1)
        {
            printf("你已被禁言！\n\n");
            return 0;
        }
        return EXP;
    }
    if(strcmp(cmd,"off") == 0)
    {
        return OFF;
    }
    if(strcmp(cmd,"chg_psd") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return CHG_PSD;
    }
    if(strcmp(cmd,"chg_nam") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(root == 1)
        {
            printf("超级用户昵称不可更改！\n\n");
            return 0;
        }
        return CHG_NAM;
    }
    if(strcmp(cmd,"out") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(root == 0)
        {
            printf("没有超级用户权限！\n\n");
            return 0;
        }
        return OUT;
    }
    if(strcmp(cmd,"yes") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return ACCEPT;
    }
    if(strcmp(cmd,"no") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return REFUSE;
    }
    if(strcmp(cmd,"ban") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(root == 0)
        {
            printf("没有超级用户权限！\n\n");
            return 0;
        }
        return BAN;
    }
    if(strcmp(cmd,"rmban") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        if(root == 0)
        {
            printf("没有超级用户权限！\n\n");
            return 0;
        }
        return RMBAN;
    }
    if(strcmp(cmd,"send") == 0)
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return SEND;
    }
    if(strcmp(cmd,"help") == 0)
    {
        return HELP;
    }
    if(strcmp(cmd,"exit") == 0)
    {
        return EXIT;
    }
    return ERROR;
}

int create_msg(msg_t *msg,char *cmd)
{
    switch(msg->action)
    {
        case LOG:
            {
                printf("请输入你的id:");
                while(1)
                {
                    int rc = scanf("%d",&(msg->id));
                    if(rc != 1)
                    {
                        printf("错误的id,请重新选择！\n\n");
                        setbuf(stdin,NULL);
                        return ERROR;
                    }
                    break;
                }
                printf("请输入你的密码:");
                set_disp_mode(STDIN_FILENO,0);
                scanf("%s",msg->passwd);
                set_disp_mode(STDIN_FILENO,1);
                break;
            }
        case REG:
            {
                char tem[100];
                memset(tem,0,100);

                while(1)
                {
                    setbuf(stdin,NULL);

                    printf("请输入你要注册的昵称:");
                    scanf("%s",msg->name);

                    setbuf(stdin,NULL);
                    printf("请输入你的密码:");
                    scanf("%s",msg->passwd);

                    setbuf(stdin,NULL);
                    printf("请确认你的密码:");
                    scanf("%s",tem);

                    if(strcmp(msg->passwd,tem) != 0)
                    {
                        printf("两次密码不一致,请重新注册!\n\n");
                        continue;
                    }

                    break;
                }

                break;
            }
        case SHOW:
            {
                break;
            }
        case SAY:
            {
                printf("请输入你要聊天的对象的昵称:");
                scanf("%s",msg->toname);
                printf("请输入你要发的消息:");
                getchar();
                gets(msg->message);
                break;
            }
        case SALL:
            {
                printf("请输入你要发的消息:");
                getchar();
                gets(msg->message);
                break;
            }
        case EXP:
            {
                strcpy(msg->message,cmd);
                break;
            }
        case REPLACE:
            {
                int i = 0;
                int k = 0;
                char toname[30];
                memset(toname,0,30);
                memset(msg->message,0,100);

                for(i = 0; i < 30; i++)
                {
                    if(cmd[i + 1] != '/')
                    {
                        strncpy(toname + i, cmd + i + 1, 1);
                        continue;
                    }
                    strcpy(msg->toname,toname);
                    i++;
                    break;
                }
                while(cmd[i] != '\0')
                {
                    strncpy(msg->message + k,cmd + i, 1);
                    k++;
                    i++;
                }
                msg->action = SAY;
                break;
            }
        case OFF:
            {
                break;
            }
        case OUT:
            {
                printf("请输入你要踢出的用户昵称:");
                scanf("%s",msg->toname);
                break;
            }
        case CHG_PSD:
            {
                char passwd[100];
                printf("请输入你的原密码:");
                scanf("%s",msg->passwd);
                while(1)
                {
                    memset(passwd,0,100);
                    memset(msg->message,0,1000);
                    printf("请输入你的新密码:");
                    scanf("%s",msg->message);
                    printf("请确认你的新密码:");
                    scanf("%s",passwd);
                    if(strcmp(passwd,msg->message) != 0)
                    {
                        printf("两次密码不一致,请重新输入！\n");
                        setbuf(stdin,NULL);
                        continue;
                    }
                    break;
                }
                break;
            }
        case CHG_NAM:
            {
                memset(msg->message,0,1000);
                printf("请输入你的新昵称:");
                scanf("%s",msg->message);
                break;
            }
        case BAN:
            {
                printf("请输入你要禁言的用户昵称:");
                scanf("%s",msg->toname);
                break;
            }
        case RMBAN:
            {
                printf("请输入你要解除禁言的用户昵称:");
                scanf("%s",msg->toname);
                break;
            }
        case SEND:
            {
                printf("请输入你要发送文件对象的昵称:");
                scanf("%s",msg->toname);
                printf("请输入你要发送发送的文件名:");
                getchar();
                gets(msg->file_name);
                printf("name = %s\n",msg->file_name);
                int fd = open(msg->file_name,O_RDONLY);
                if(fd < 0)
                {
                    return ERROR;
                }

                msg->file_len = lseek(fd,0,SEEK_END);
                lseek(fd,0,SEEK_SET);
                close(fd);
                break;
            }
        case ACCEPT:
            {
                break;
            }
        case REFUSE:
            {
                break;
            }
        case EXIT:
            {
                break;
            }
    }
}

void *thread_write(int *arg)
{
    int sockfd = *arg;
    char cmd[30];

    interface(msg.name);
    memset(&msg,0,sizeof(msg_t));

    while(1)
    {
        scanf("%s",cmd);

        msg.action = check_action(cmd);

        if(msg.action == 0)
        {
            continue;
        }

        if(msg.action == ERROR)
        {
            printf("输入有误,请重新输入！\n\n");
            continue;
        }

        if(msg.action == HELP)
        {
            system("reset");
            if(status == 0)
            {
                interface(msg.name);
            }
            if(status == 1)
            {
                interface1(msg.name);
            }
            continue;
        }

        switch(msg.action)
        {
            case LOG:
                {
                    if(create_msg(&msg,cmd) == ERROR)
                    {
                        continue;
                    }
                    break;
                }
            case REG:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case SAY:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case EXP:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case SALL:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case SHOW:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case REPLACE:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case OFF:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case OUT:
                {
                    create_msg(&msg,cmd);
                    if(strcmp(msg.toname,msg.name) == 0)
                    {
                        printf("你不能踢出自己！\n\n");
                        continue;
                    }
                    break;
                }
            case CHG_PSD:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case CHG_NAM:
                {
                    create_msg(&msg,cmd);
                    if(strcmp(msg.name,msg.message) == 0)
                    {
                        printf("新昵称和原昵称一致,无须修改！\n\n");
                        continue;
                    }
                    break;
                }
            case BAN:
                {
                    create_msg(&msg,cmd);
                    if(strcmp(msg.toname,msg.name) == 0)
                    {
                        printf("你不能禁言自己！\n\n");
                        continue;
                    }
                    break;
                }
            case RMBAN:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case SEND:
                {
                    if(create_msg(&msg,cmd) == ERROR)
                    {
                        printf("本地没有此文件！\n\n");
                        continue;
                    }
                    break;
                }
            case ACCEPT:
                {
                    create_msg(&msg,cmd);
                    printf("请输入你要另存的文件路径:\n\n");
                    while(1)
                    {
                        getchar();
                        gets(msg.file_name);
                        printf("%s\n",msg.file_name);
                        
                        int fd = open(msg.file_name,O_RDWR|O_CREAT,0666);
                        if(fd < 0)
                        {
                            printf("路径有误,请重新输入！\n\n");
                            continue;
                        }
                        close(fd);
                        break;
                    }
                    break;
                }
            case REFUSE:
                {
                    create_msg(&msg,cmd);
                    break;
                }
            case EXIT:
                {
                    create_msg(&msg,cmd);
                    break;
                }
        }
        int rc = write(sockfd,&msg,sizeof(msg));
        setbuf(stdin,NULL);
    }
}

void *thread_read(int *arg)
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;

    char cmd[100];
    int sockfd = *arg;
    time_t timep;
    msg_t msg1 = {0};

    char rcd[512];
    char rcd_time[100];

    int rc = sqlite3_open("user_rcd.db",&db);
    
    char *sql_insert_rcd = (char *)malloc(1024);
    char *sql_create_rcd = (char *)malloc(1024);
    
    
    while(1)
    {
        memset(rcd,0,200);
        memset(rcd_time,0,100);
        memset(sql_insert_rcd,0,1024);
        memset(sql_create_rcd,0,1024);
        memset(&msg1,0,sizeof(msg_t));
        int ret = read(sockfd,&msg1,sizeof(msg_t));
        switch(msg1.action)
        {
            case LOG_ONLINE:
                {
                    printf("用户已登录，请勿重复登录！\n\n");
                    break;
                }
            case LOG_NOEXIST:
                {
                    printf("用户不存在,请先创建！\n\n");
                    break;
                }
            case LOG_FAILED:
                {
                    printf("\n用户密码错误！\n\n");
                    break;
                }
            case LOG_SUCSF:
                {
                    status = 1;
                    system("reset");
                    strcpy(msg.name,msg1.name);
                    interface1(msg1.name);
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    if(strcmp(msg1.name,"admin") == 0)
                    {
                        root = 1;
                        printf("超级用户");
                    }
                    printf("登录成功,当前用户为: %s\n\n",msg1.name);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"登录成功!\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    sprintf(sql_create_rcd,"create table %s(name TEXT,time TEXT,rcd TEXT);",msg1.name);
                    while(1)
                    {
                        int rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                        if(rc == SQLITE_ERROR)
                        {
                            sqlite3_exec(db,sql_create_rcd,NULL,0,&err_msg);
                            continue;
                        }
                        break;
                    }
                    
                    break;
                }
            case REG_ERROR:
                {
                    printf("用户已存在~\n\n");
                    break;
                }
            case REG_SUCSF:
                {
                    printf("注册成功~");
                    printf("你的id为:\033[40;31m%d\033[0m,请牢记！\n\n",msg1.id);
                    break;
                }
            case SHOW:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("当前在线用户有 %s\n\n",msg1.message);
                    break;
                }
            case SAY_FAILED:
                {
                    printf("发送失败,没有该用户或对方不在线\n\n");
                    break;
                }
            case SAY_TOSUCSF:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    if(strcmp(msg1.message,"/welcome") == 0)
                    {
                        printf("你对 %s 表达了欢迎！\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,"/like") == 0)
                    {
                        printf("你对 %s 表达了喜欢！\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,"/unhappy") == 0)
                    {
                        printf("你对 %s 表达了不高兴！\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,":)") == 0)
                    {
                        printf("你对 %s 做了个笑脸～\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,"0.0") == 0)
                    {
                        printf("你对 %s 发了个呆～\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,"^3^") == 0)
                    {
                        printf("你对 %s 做了个么么嗒～\n\n",msg1.toname);
                        break;
                    }
                    printf("你对 %s 悄悄说: %s\n\n",msg1.toname,msg1.message);
                    
                    usleep(300000);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你对 %s 悄悄说: %s\n",msg1.toname,msg1.message);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case SAY_SUCSF:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    if(strcmp(msg1.message,"/welcome") == 0)
                    {
                        printf("%s 大侠,欢迎你来到咱们的聊天室！\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,"/like") == 0)
                    {
                        printf("%s,我好喜欢你哦！\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,"/unhappy") == 0)
                    {
                        printf("%s,我一点也不高兴！\n\n",msg1.toname);
                        break;
                    }
                    if(strcmp(msg1.message,":)") == 0)
                    {
                        printf("%s 悄悄对你做了个笑脸～\n\n",msg1.name);
                        break;
                    }
                    if(strcmp(msg1.message,"0.0") == 0)
                    {
                        printf("%s 悄悄对你发了个呆～\n\n",msg1.name);
                        break;
                    }
                    if(strcmp(msg1.message,"^3^") == 0)
                    {
                        printf("%s 悄悄对你做了个么么嗒～\n\n",msg1.name);
                        break;
                    }
                    printf("%s 悄悄对你说: %s\n\n",msg1.name,msg1.message); 
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 悄悄对你说: %s\n",msg1.name,msg1.message);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case SALL:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    if(strcmp(msg1.message,":)") == 0)
                    {
                        printf("你对大家做了个笑脸～\n\n");
                        break;
                    }
                    if(strcmp(msg1.message,"0.0") == 0)
                    {
                        printf("你对大家发了个呆～\n\n");
                        break;
                    }
                    if(strcmp(msg1.message,"^3^") == 0)
                    {
                        printf("你对大家做了个么么嗒～\n\n");
                        break;
                    }
                    printf("你对大家说: %s\n\n",msg1.message);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你对大家说: %s\n",msg1.message);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case STOALL:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    if(strcmp(msg1.message,":)") == 0)
                    {
                        printf("%s 对大家做了个笑脸～\n\n",msg1.name);
                        break;
                    }
                    if(strcmp(msg1.message,"0.0") == 0)
                    {
                        printf("%s 对大家发了个呆～\n\n",msg1.name);
                        break;
                    }
                    if(strcmp(msg1.message,"^3^") == 0)
                    {
                        printf("%s 对大家做了个么么嗒～\n\n",msg1.name);
                        break;
                    }
                    printf("%s 对大家说: %s\n\n",msg1.name,msg1.message);
                    break;
                }
            case OFF:
                {
                    status = 0;
                    ban = 0;
                    system("reset");
                    interface(msg1.name);
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("%s 离线成功！\n\n",msg1.name);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 离线成功！\n",msg1.name);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case OUT:
                {
                    status = 0;
                    ban = 0;
                    system("reset");
                    interface(msg1.name);
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("你已被踢出聊天室！请重新登录！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你已被踢出聊天室！请重新登录！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    usleep(300000);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case CHG_PSD:
                {
                    status = 0;
                    ban = 0;
                    system("reset");
                    interface(msg1.name);
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("你已修改密码成功！请重新登录！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"修改密码成功！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case CHG_PSD_FAILED:
                {
                    printf("原密码不正确,请确认你的原密码！\n\n");
                    break;
                }
            case CHG_NAM:
                {
                    status = 0;
                    ban = 0;
                    system("reset");
                    interface(msg1.name);
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("你已成功修改昵称！新昵称为 %s！请重新登录！\n\n",msg1.message);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"修改昵称成功！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case CHG_NAM_FAILED:
                {
                    printf("已有该昵称用户！\n\n");
                    break;
                }
            case OUTO:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("%s 已被踢出该聊天室！\n\n",msg1.toname);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 已被踢出聊天室！\n",msg1.toname);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case OUT_FAILED:
                {
                    printf("%s 不在线或没有该用户！\n\n",msg1.toname);
                    break;
                }
            case BAN:
                {
                    ban = 1;
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("你已被禁言！管理员号码为:13291275280,请自行联系解决！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你已被禁言！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    usleep(300000);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case BANTO:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("%s 已被禁言！\n\n",msg1.toname);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 已被禁言！\n",msg1.toname);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case BAN_FAILED:
                {
                    printf("%s 不在线或没有该用户！\n\n",msg1.toname);
                    break;
                }
            case RMBAN:
                {
                    ban = 0;
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("你已被解除禁言！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你已被解除禁言！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case RMBANTO:
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("%s 已被解除禁言！\n\n",msg1.toname);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 已被解除禁言！\n",msg1.toname);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    usleep(300000);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                    break;
                }
            case RMFAILED:
                {
                    printf("%s 不在线或没有该用户或未被禁言！\n\n",msg1.toname);
                    break;
                }
            case SENDTO:
                {
                    printf("已发送文件请求,等待对方处理！\n\n");
                    break;
                }
            case SEND:
                {
                    printf("向你发送文件,是否接收？(yes/no)\n");
                    break;
                }
            case SEND_FAILED:
                {
                    printf("无此用户或对方不在线！\n\n");
                    break;
                }
            case ACCEPT:
                {
                    printf("对方开始接收文件！\n");
                    int fd = open(msg1.file_name,O_RDONLY);
                    char * data = (char *)malloc(msg1.file_len + 1);
                    memset(data,0,msg1.file_len + 1);
                    block_read(fd,data,msg1.file_len);
                    block_write(sockfd,data,msg1.file_len);
                    printf("对方已接收文件！\n\n");
                    break;
                }
            case ACCEPTO:
                {
                    printf("开始接受文件！\n");
                    int fd = open(msg1.file_name,O_RDWR|O_CREAT,0666);
                    char * data = (char *)malloc(msg1.file_len + 1);
                    memset(data,0,msg1.file_len + 1);
                    block_read(sockfd,data,msg1.file_len);
                    block_write(fd,data,msg1.file_len);
                    break;
                }
            case ACCSUF:
                {
                    printf("接收文件成功！\n\n");
                    break;
                }
            case REFUSE:
                {
                    printf("对方拒绝接收文件！\n\n");
                    break;
                }
            case REFUSETO:
                {
                    printf("已拒绝接收对方文件!\n\n");
                    break;
                }
            case EXIT:
                {
                    close(sockfd);
                    system("reset");
                    if(status == 1)
                    {
                        time(&timep);
                        printf("\n%s",ctime(&timep));
                        printf("%s 用户退出聊天室成功！\n\n感谢您使用新智聊天室软件~^.^~\n\n",msg1.name);
                        sprintf(rcd_time,"%s",ctime(&timep));
                        sprintf(rcd,"%s 用户退出聊天室成功！\n",msg1.name);
                        sprintf(rcd_time,"%s",ctime(&timep));
                        sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                        sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                        sqlite3_close(db);
                        exit(0);
                    }
                    
                    sqlite3_close(db);
                    printf("\n退出聊天室成功！\n\n感谢您使用新智聊天室软件~^.^~\n\n");
                    exit(0);
                }
        }
    }
}

int main(int argc, char *argv[])
{
    int i;
    pthread_t pid[2];

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror(strerror(errno));
        close(sockfd);
        return 0;
    }

    struct sockaddr_in server;
    memset(&server,0,sizeof(server));   
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(ret < 0)
    {
        perror(strerror(errno));
        close(sockfd);
        return 0;
    }


    pthread_create(&pid[0],NULL,thread_write,&sockfd);
    pthread_create(&pid[1],NULL,thread_read,&sockfd);

    for(i = 0; i < 2; i++)
    {
        pthread_join(pid[i],NULL);
    }
    close(sockfd);

    return 0;
}
