#include"../../include/my_head.h"

extern msg_t msg;
extern status;

void *thread_write(int *arg)
{
    int sockfd = *arg;     //取得连接描述符
    char cmd[30];

    interface(msg.name);   //调用界面
    memset(&msg,0,sizeof(msg_t));  //清空结构体

    while(1)
    {
        gets(cmd);   //取得命令

        msg.action = check_action(cmd);  //检查命令

        if(msg.action == 0)
        {
            continue;   //返回零继续
        }

        if(msg.action == ERROR)   //返回错误命令有错
        {
            printf("输入有误,请重新输入！\n\n");
            continue;
        }

        if(msg.action == HELP)   //清屏
        {
            system("reset");
            if(status == 0)
            {
                interface(msg.name);   //调用界面
            }
            if(status == 1)
            {
                interface1(msg.name);  //调用界面
            }
            continue;
        }

        switch(msg.action)   //判断命令
        {
            case LOG:
                {
                    if(create_msg(&msg,cmd) == ERROR)
                    {
                        continue;  //输入有误
                    }
                    break;
                }
            case REG:
                {
                    if(create_msg(&msg,cmd) == ERROR)  //创建消息
                    {
                        continue;
                    }
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
                    if(strcmp(msg.toname,msg.name) == 0)  //不能提出自己
                    {
                        printf("你不能踢出自己！\n\n");
                        continue;
                    }
                    break;
                }
            case CHG_PSD:
                {
                    if(create_msg(&msg,cmd) == ERROR)
                    {
                        continue;
                    }
                    break;
                }
            case CHG_NAM:
                {
                    create_msg(&msg,cmd);
                    if(strcmp(msg.name,msg.message) == 0)  //判断新旧昵称是否一样
                    {
                        printf("新昵称和原昵称一致,无须修改！\n\n");
                        continue;
                    }
                    break;
                }
            case BAN:
                {
                    create_msg(&msg,cmd);
                    if(strcmp(msg.toname,msg.name) == 0)   //不能禁言自己
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
            case EXIT:
                {
                    create_msg(&msg,cmd);
                    break;
                }
        }
        int rc = write(sockfd,&msg,sizeof(msg));  //将结构体写到连接描述符中
        setbuf(stdin,NULL); 
    }
}
