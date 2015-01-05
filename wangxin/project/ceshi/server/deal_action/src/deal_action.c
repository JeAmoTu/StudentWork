#include"../../include/my_head.h"

extern char back[100];
extern char online[100];
extern int count;
int callback(void *not_used, int argc, char **argv, char **col_name);

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

int deal_action(msg_t * msg, int c_fd)  //传入结构体和连接描述符
{
    sqlite3 *db = NULL;
    time_t timep;
    char rcd_time[100];
    char rcd[1024];
    int rc = sqlite3_open("user.db",&db); //打开用户表       
    if(rc != SQLITE_OK)
    {
        fprintf(stderr,"open falied %s\n",sqlite3_errmsg(db));
    }

    char *err_msg = NULL;

    char *sql_select_user = (char *)malloc(200);  //定义语句
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

    memset(rcd_time,0,100);  //清空语句
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
    
    //创建语句
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
    sprintf(sql_delete_status,"delete from status where name = \"%s\";",msg->name);
    sprintf(sql_delete_tostatus,"delete from status where name = \"%s\";",msg->toname);

    switch(msg->action) //判断命令
    {

        case LOG: //登录
            {
                while(1)
                {
                    memset(back,0,100); //查找id
                    int rc = sqlite3_exec(db,sql_select_id,callback,0,&err_msg);

                    if(atoi(back) == msg->id) //比较id
                    {
                        memset(back,0,100);
                        rc = sqlite3_exec(db,sql_select_user_name,callback,0,&err_msg);
                        strcpy(msg->name,back);//取出用户昵称
                        memset(back,0,100);
                        sprintf(sql_select_user_status,"select name from status where name = \"%s\";",msg->name);
                        rc = sqlite3_exec(db,sql_select_user_status,callback,0,&err_msg);
                        //查看用户表
                        if(rc == SQLITE_ERROR)
                        {
                            sqlite3_exec(db,sql_create_user_status,NULL,0,&err_msg);
                            continue;//无表创建
                        }

                        if(strcmp(back,msg->name) == 0) //判断是否在线
                        {

                            msg->action = LOG_ONLINE;
                            sqlite3_close(db);
                            return 0;
                        }

                        memset(back,0,100);
                        sprintf(sql_select_passwd,"select passwd from user where name = \"%s\";",msg->name);
                        rc = sqlite3_exec(db,sql_select_passwd,callback,0,&err_msg);
                        if(strcmp(back,msg->passwd) != 0)//判断密码是否正确
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
                                sqlite3_exec(db,sql_create_user_rcd,NULL,0,&err_msg);//无记录表创建
                                continue;
                            }   //插入聊天记录
                            break;
                        }
                        sqlite3_close(db);
                        return 0;
                    }
                    msg->action = LOG_NOEXIST; //用户不存在
                    sqlite3_close(db);
                    return 0;
                }
            }
        case REG:  //注册
            {
                while(1)
                {   
                    int rc = sqlite3_exec(db,sql_select_user,callback,0,&err_msg);

                    if(strcmp(back,msg->name) == 0)  //判断是否重名
                    {
                        memset(back,0,100);
                        msg->action = REG_ERROR;
                        sqlite3_close(db);
                        return 0;
                    }
                    srandom((unsigned)time(&timep));  //随机生成id
                    msg->id = random();
                    sprintf(sql_insert_user,"insert into user(id,name,passwd)values(%d,'%s','%s');",msg->id,msg->name,msg->passwd);
                    rc = sqlite3_exec(db,sql_insert_user,NULL,0,&err_msg); //插入用户表

                    if(rc == SQLITE_ERROR)
                    {
                        rc = sqlite3_exec(db,sql_create_user,NULL,0,&err_msg);
                        continue; //无表创建,重新插入
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
                                continue; //注册成功,插入聊天记录,无表创建
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
                count = 0;  //初始化计数
                memset(online,0,100);
                sqlite3_exec(db,sql_select_status,callback,0,&err_msg);//查找在线用户昵称
                msg->action = SHOW;
                strcpy(msg->message,online);  //赋给消息

                sqlite3_close(db);
                break;
            }
        case SAY:  //私聊
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg); //查找对象
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = SAY_FAILED;  //无此在线对象
                    sqlite3_close(db);
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg); //查找对象cfd
                msg->action = SAY_SUCSF;  
                write(atoi(back),msg,sizeof(msg_t));  //写给对象结构体
                msg->action = SAY_TOSUCSF;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 对 %s 悄悄说 %s\n",msg->name,msg->toname,msg->message);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);  //插入聊天记录
                break;
            }
        case SALL:  //群发消息
            {
                count = 0;  //计数置0
                int i = 0;  
                int len = 0;
                char tem[5];
                memset(tem,0,5);
                memset(online,0,100);
                sqlite3_exec(db,sql_select_toallfd,callback,0,&err_msg); //取出所有在线人cfd
                msg->action = STOALL;
                while('\0' != *(online + len))
                {
                    if(*(online + len) == ' ')
                    {
                        if(atoi(tem) != c_fd)
                        {
                            write(atoi(tem),msg,sizeof(msg_t)); //一个一个取出来写过去结构体
                        }
                        memset(tem,0,5);
                        i = 0;
                        len++;
                    }

                    strncpy(tem + i, online + len, 1);  //cfd赋给tem
                    i++;
                    len++;
                }
                msg->action = SALL;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 对大家说 %s\n",msg->name,msg->message);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);  //写入聊天记录
                break;
            }
        case EXP:  //表情
            {
                count = 0;
                int i = 0;
                int len = 0;
                char tem[5];
                memset(tem,0,5);
                memset(online,0,100);
                sqlite3_exec(db,sql_select_toallfd,callback,0,&err_msg); //找出所有人cfd
                msg->action = STOALL;
                while('\0' != *(online + len))
                {
                    if(*(online + len) == ' ')
                    {
                        if(atoi(tem) != c_fd)
                        {
                            write(atoi(tem),msg,sizeof(msg_t));  //写入结构体
                        }
                        memset(tem,0,5);
                        i = 0;
                        len++;
                    }

                    strncpy(tem + i, online + len, 1); //cfd赋给tem
                    i++;
                    len++;
                }
                msg->action = SALL;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 对大家 %s\n",msg->name,msg->message);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg); //写入聊天记录
                break;
            }
        case OFF: //离线
            {
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg); //将此人从在线表删除
                msg->action = OFF;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 离线成功！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg); //写入聊天记录
                break;
            }
        case OUT:  //踢人
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg); //查找要踢的对象
                if(strcmp(back,msg->toname) != 0) //无次对象报错
                {
                    msg->action = OUT_FAILED;  
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg);  //查找cfd
                msg->action = OUT;
                write(atoi(back),msg,sizeof(msg_t)); //写给被踢人
                msg->action = OUTO;
                sqlite3_exec(db,sql_delete_tostatus,NULL,0,&err_msg);
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 已被踢出聊天室！\n",msg->toname);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg); //写入聊天记录
                break;
            }
        case CHG_PSD:  //修改密码
            { 
                memset(back,0,100);
                sprintf(sql_select_passwd,"select passwd from user where name = \"%s\";",msg->name);
                sqlite3_exec(db,sql_select_passwd,callback,0,&err_msg);//查找密码
                if(strcmp(back,msg->passwd) != 0)  //密码不正确
                {
                    msg->action = CHG_PSD_FAILED;
                    return 0;
                }
                
                sprintf(sql_update_passwd,"update user set passwd = \"%s\" where name = \"%s\";",msg->message,msg->name);
                sqlite3_exec(db,sql_update_passwd,NULL,0,&err_msg); //更新密码
                msg->action = CHG_PSD;
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg); //从在线表删除
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 修改密码成功！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg); //写入聊天记录
                break;
            }
        case CHG_NAM:  //修改昵称
            {
                memset(back,0,100);
                sprintf(sql_select_user,"select name from user where name = \"%s\";",msg->message);
                sqlite3_exec(db,sql_select_user,callback,0,&err_msg); //查看是否有相同昵称
                if(strcmp(back,msg->message) == 0)
                {
                    msg->action = CHG_NAM_FAILED;  //相同则重名报错
                    return 0;
                }
                msg->action = CHG_NAM;
                sprintf(sql_update_name,"update user set name = \"%s\" where name = \"%s\";",msg->message,msg->name);
                sqlite3_exec(db,sql_update_name,NULL,0,&err_msg); //更新昵称
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg); //从在线表删除
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 更改新昵称 %s 成功！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);  //写入聊天记录
                break;
            }
        case BAN:  //禁言
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg); //查找禁言对象
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = BAN_FAILED;  //无则报错
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg); //找到对象cfd
                msg->action = BAN;
                write(atoi(back),msg,sizeof(msg_t));  //写入消息结构体
                msg->action = BANTO;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 已被禁言！\n",msg->toname);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);  //写入聊天记录
                break;
            }
        case RMBAN: //解除禁言
            {
                memset(back,0,100);
                sqlite3_exec(db,sql_select_toname,callback,0,&err_msg); //找到对象
                if(strcmp(back,msg->toname) != 0)
                {
                    msg->action = RMFAILED;  //无则报错
                    return 0;
                }
                memset(back,0,100);
                sqlite3_exec(db,sql_select_tofd,callback,0,&err_msg); //找到对象cfd
                msg->action = RMBAN;
                write(atoi(back),msg,sizeof(msg_t));  //写给被踢对象
                msg->action = RMBANTO;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 已被解除禁言！\n",msg->toname);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);  //插入聊天记录
                break;
            }
        case SEND:
            {
                char buf[10];
                char file_name[100];
                int file_len;

                memset(buf,0,10);
                memset(file_name,0,100);
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
                
                msg->action = SENDTO;
                write(c_fd,msg,sizeof(msg_t));
                printf("waiting!!!\n");
                read(c_fd,&buf,10);
                if(strcmp(buf,"ok") != 0)
                {
                    break;
                }
                msg->action = SEND;
                read(c_fd,&file_name,100);
                write(atoi(back),msg,sizeof(msg_t));
                memset(buf,0,10);
                read(atoi(back),&buf,100);
                if(strcmp(buf,"yes") != 0)
                {
                    write(c_fd,&buf,10);
                    break;
                }
                write(c_fd,&buf,10);
                read(c_fd,&file_len,sizeof(file_len));

                char * data = (char *)malloc(file_len + 1);
                memset(data,0,file_len + 1);

                block_read(c_fd,data,file_len);
                write(atoi(back),&file_len,sizeof(file_len));
                block_write(atoi(back),data,file_len);
                
                //sprintf(rcd_time,"%s",ctime(&timep));
                //sprintf(rcd,"%s 对 %s 悄悄说 %s\n",msg->name,msg->toname,msg->message);
                //sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                //sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);
                break;
                
            }
        case EXIT:  //退出
            {
                sqlite3_exec(db,sql_delete_status,NULL,0,&err_msg);  //在线表中删除
                msg->action = EXIT;
                sprintf(rcd_time,"%s",ctime(&timep));
                sprintf(rcd,"%s 退出聊天室！\n",msg->name);
                sprintf(sql_insert_user_rcd,"insert into usr_rcd(name,time,rcd)values(\"%s\",\"%s\",\"%s\");",msg->name,rcd_time,rcd);
                sqlite3_exec(db,sql_insert_user_rcd,NULL,0,&err_msg);  //插入聊天记录
                sqlite3_close(db);  //关闭数据库文件
                return EXIT;  //退出
            }
    }

    return 0;

}
