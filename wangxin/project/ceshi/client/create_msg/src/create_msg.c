#include"../../include/my_head.h"

int create_msg(msg_t *msg,char *cmd)  //创建消息结构体
{
    switch(msg->action)
    {
        case LOG:
            {
                printf("请输入你的id:");
                while(1)
                {
                    int rc = scanf("%d",&(msg->id));  
                    if(rc != 1)                //错误的输入
                    {
                        printf("错误的id,请重新选择！\n\n");
                        setbuf(stdin,NULL);
                        return ERROR;
                    }
                    break;
                }
                printf("请输入你的密码:");
                set_disp_mode(STDIN_FILENO,0);  //关闭输入回显
                getchar();
                gets(msg->passwd);
                set_disp_mode(STDIN_FILENO,1);
                break;
            }
        case REG:
            {
                char tem[100];  //存储密码
                memset(tem,0,100);


                printf("请输入你要注册的昵称:");
                gets(msg->name);

                int i = 0;
                while(*(msg->name + i) != 0)
                {
                    if(*(msg->name + i) == ' ')
                    {
                        break;
                    }
                    i++;
                }
                if(*(msg->name + i) == ' ')
                {
                    printf("昵称带空格,重新注册！\n\n");
                    return ERROR;
                }

                setbuf(stdin,NULL);
                printf("请输入你的密码:");
                gets(msg->passwd);

                setbuf(stdin,NULL);
                printf("请确认你的密码:");
                gets(tem);

                if(strcmp(msg->passwd,tem) != 0)   //判断两次密码是否一致
                {
                    printf("两次密码不一致,请重新注册!\n\n");
                    return ERROR;          //不一致重新注册
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
                gets(msg->toname);
                printf("请输入你要发的消息:");
                gets(msg->message);
                break;
            }
        case SALL:
            {
                printf("请输入你要发的消息:");
                gets(msg->message);   //取得消息
                break;
            }
        case EXP:
            {
                strcpy(msg->message,cmd);  //表情赋给消息
                break;
            }
        case REPLACE:  //快捷消息
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
                        strncpy(toname + i, cmd + i + 1, 1);  //一个一个取出对象
                        continue;
                    }
                    strcpy(msg->toname,toname);  //赋给msg
                    i++;
                    break;
                }
                while(cmd[i] != '\0')
                {
                    strncpy(msg->message + k,cmd + i, 1); //取出快捷消息
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
                gets(msg->toname);
                break;
            }
        case CHG_PSD:  //修改密码
            {
                char passwd[100];
                printf("请输入你的原密码:");
                gets(msg->passwd);
                memset(passwd,0,100);
                memset(msg->message,0,1000);
                printf("请输入你的新密码:");
                gets(msg->message);
                printf("请确认你的新密码:");
                gets(passwd);
                if(strcmp(passwd,msg->message) != 0)   //比较两次密码是否一致
                {
                    printf("两次密码不一致,请重新输入！\n");
                    setbuf(stdin,NULL);
                    return ERROR;
                }
                break;
            }
        case CHG_NAM:
            {
                memset(msg->message,0,1000);
                printf("请输入你的新昵称:"); //取得新昵称
                gets(msg->message);
                break;
            }
        case BAN:
            {
                printf("请输入你要禁言的用户昵称:");  //输入要禁言的用户昵称
                gets(msg->toname);
                break;
            }
        case RMBAN:
            {
                printf("请输入你要解除禁言的用户昵称:");  //输入你要解禁的用户昵称
                gets(msg->toname);
                break;
            }
        case SEND:
            {
                printf("请输入你要发送文件对象的昵称:");
                gets(msg->toname);
                if(strcmp(msg->toname,msg->name) == 0)
                {
                    printf("不能像自己发送文件！\n\n");
                    return ERROR;
                }
                break;
            }
        case EXIT:
            {
                break;
            }
    }
}
