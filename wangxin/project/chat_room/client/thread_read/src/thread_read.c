#include"../../include/my_head.h"

extern int status;
extern int root;
extern int ban;
extern msg_t msg;

void *thread_read(int *arg)
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;

    int sockfd = *arg;  
    time_t timep;       //时间
    msg_t msg1 = {0};

    char rcd[512];    //消息
    char rcd_time[100];  //记录时间

    int rc = sqlite3_open("user_rcd.db",&db);  //打开聊天记录文件
    
    char *sql_insert_rcd = (char *)malloc(1024);   //插入聊天记录
    char *sql_create_rcd = (char *)malloc(1024);   //创建聊天记录表
    
    
    while(1)
    {
        memset(rcd,0,200);
        memset(rcd_time,0,100);
        memset(sql_insert_rcd,0,1024);
        memset(sql_create_rcd,0,1024);
        memset(&msg1,0,sizeof(msg_t));
        int ret = read(sockfd,&msg1,sizeof(msg_t));  //从连接描述符中读取结构体

        switch(msg1.action)
        {
            case LOG_ONLINE:  //用户在线
                {
                    printf("用户已登录，请勿重复登录！\n\n");
                    break;
                }
            case LOG_NOEXIST: //用户不存在
                {
                    printf("用户不存在,请先创建！\n\n");
                    break;
                }
            case LOG_FAILED:  //登录密码错误
                {
                    printf("\n用户密码错误！\n\n");
                    break;
                }
            case LOG_SUCSF:   //登录成功
                {
                    status = 1;  //状态置1
                    system("reset");  //清屏
                    strcpy(msg.name,msg1.name);  //取得用户昵称
                    interface1(msg1.name);   //调用登录成功界面
                    time(&timep);   //取得当前时间
                    printf("\n%s",ctime(&timep)); 
                    if(strcmp(msg1.name,"admin") == 0)
                    {
                        root = 1;
                        printf("超级用户");   //超级用户
                    }
                    printf("登录成功,当前用户为: %s\n\n",msg1.name);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"登录成功!\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    sprintf(sql_create_rcd,"create table %s(name TEXT,time TEXT,rcd TEXT);",msg1.name);
                    //创建语句
                    while(1)
                    {
                        int rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);//插入聊天记录
                        if(rc == SQLITE_ERROR)  //插入失败
                        {
                            sqlite3_exec(db,sql_create_rcd,NULL,0,&err_msg);  //创建表
                            continue;   //重新插入
                        }
                        break;
                    }
                    
                    break;
                }
            case REG_ERROR:  //注册用户已存在
                {
                    printf("用户已存在~\n\n");
                    break;
                }
            case REG_SUCSF:  //注册成功
                {
                    printf("注册成功~");
                    printf("你的id为:\033[40;31m%d\033[0m,请牢记！\n\n",msg1.id);
                    break;
                }
            case SHOW:  //查看在线用户
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("当前在线用户有 %s\n\n",msg1.message);
                    break;
                }
            case SAY_FAILED:  //发送失败
                {
                    printf("发送失败,没有该用户或对方不在线\n\n");
                    break;
                }
            case SAY_TOSUCSF:  //发送消息成功
                {
                    time(&timep); //取得当前时间
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
                    
                    usleep(300000);   //延时,不能同时对数据库进行写操作
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你对 %s 悄悄说: %s\n",msg1.toname,msg1.message);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case SAY_SUCSF:
                {
                    time(&timep);    //取时间
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
                    sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);   //插入聊天记录
                    break;
                }
            case SALL:  //群发消息
                {
                    time(&timep);  //取时间
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
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case STOALL:  //对所有人说
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
            case OFF:  //离线
                {
                    status =  0;   //状态置0
                    ban = 0;      //禁言置0
                    system("reset");   //清屏
                    interface(msg1.name);   //调用登录界面
                    time(&timep);   //取时间
                    printf("\n%s",ctime(&timep));
                    printf("%s 离线成功！\n\n",msg1.name);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 离线成功！\n",msg1.name);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);// 插入聊天记录
                    break;
                }
            case OUT:   //踢人
                {
                    status = 0;   //状态置0
                    ban = 0;     //禁言置0
                    system("reset");   //清屏
                    interface(msg1.name);  //调用登录界面
                    time(&timep);   //取时间
                    printf("\n%s",ctime(&timep));
                    printf("你已被踢出聊天室！请重新登录！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你已被踢出聊天室！请重新登录！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    usleep(300000);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);   //插入聊天记录
                    break;
                }
            case CHG_PSD:   //修改密码
                {
                    status = 0;   //状态置离线
                    ban = 0;     //禁言置0
                    system("reset");  //清屏
                    interface(msg1.name);   //调用登录界面
                    time(&timep);    //取时间
                    printf("\n%s",ctime(&timep));
                    printf("你已修改密码成功！请重新登录！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"修改密码成功！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case CHG_PSD_FAILED:   //修改密码失败
                {
                    printf("原密码不正确,请确认你的原密码！\n\n");
                    break;
                }
            case CHG_NAM:   //修改昵称
                {  
                    status = 0;   //状态置0
                    ban = 0;   //禁言置0
                    system("reset");   //清屏
                    interface(msg1.name);   //调用登录界面
                    time(&timep);   //取时间
                    printf("\n%s",ctime(&timep));
                    printf("你已成功修改昵称！新昵称为 %s！请重新登录！\n\n",msg1.message);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"修改昵称成功！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case CHG_NAM_FAILED:  //修改昵称失败
                {
                    printf("已有该昵称用户！\n\n");
                    break;
                }
            case OUTO:   //踢出成功
                { 
                    time(&timep);   //取时间
                    printf("\n%s",ctime(&timep));
                    printf("%s 已被踢出该聊天室！\n\n",msg1.toname);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 已被踢出聊天室！\n",msg1.toname);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case OUT_FAILED:  //踢人失败
                {
                    printf("%s 不在线或没有该用户！\n\n",msg1.toname);
                    break;
                }
            case BAN:   //被禁言成功
                { 
                    ban = 1;   //禁言置1
                    time(&timep);  //取时间
                    printf("\n%s",ctime(&timep));
                    printf("你已被禁言！管理员号码为:13291275280,请自行联系解决！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你已被禁言！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    usleep(300000);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case BANTO:  //禁言成功
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("%s 已被禁言！\n\n",msg1.toname);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 已被禁言！\n",msg1.toname);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录成功
                    break;
                }
            case BAN_FAILED:  //禁言失败
                {
                    printf("%s 不在线或没有该用户！\n\n",msg1.toname);
                    break;
                }
            case RMBAN:   //被解除禁言
                {
                    ban = 0;   //禁言置0
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("你已被解除禁言！\n\n");
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"你已被解除禁言！\n");
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.toname,msg1.name,rcd_time,rcd);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);   //插入聊天记录
                    break;
                }
            case RMBANTO:    //解除禁言
                {
                    time(&timep);
                    printf("\n%s",ctime(&timep));
                    printf("%s 已被解除禁言！\n\n",msg1.toname);
                    sprintf(rcd_time,"%s",ctime(&timep));
                    sprintf(rcd,"%s 已被解除禁言！\n",msg1.toname);
                    sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                    usleep(300000);
                    rc = sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);  //插入聊天记录
                    break;
                }
            case RMFAILED:   //解除禁言失败
                {
                    printf("%s 不在线或没有该用户！\n\n",msg1.toname);
                    break;
                }
            case EXIT:   //退出程序
                {
                    close(sockfd);  //关闭连接描述符
                    system("reset");  //清屏
                    if(status == 1)   //如果有用户在线
                    {
                        time(&timep);  //取时间
                        printf("\n%s",ctime(&timep)); 
                        //打印用户退出成功
                        printf("%s 用户退出聊天室成功！\n\n感谢您使用新智聊天室软件~^.^~\n\n",msg1.name);
                        sprintf(rcd_time,"%s",ctime(&timep));
                        sprintf(rcd,"%s 用户退出聊天室成功！\n",msg1.name);
                        sprintf(rcd_time,"%s",ctime(&timep));
                        sprintf(sql_insert_rcd,"insert into %s(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg1.name,msg1.name,rcd_time,rcd);
                        sqlite3_exec(db,sql_insert_rcd,NULL,0,&err_msg);
                        sqlite3_close(db);  //关闭数据库
                        exit(0);  //   退出程序
                    }
                    
                    sqlite3_close(db);  //关闭数据库
                    printf("\n退出聊天室成功！\n\n感谢您使用新智聊天室软件~^.^~\n\n");
                    exit(0);  //退出程序
                }
        }
    }
}
