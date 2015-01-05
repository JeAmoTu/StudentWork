#include"../../include/my_head.h"

extern int status;
extern int ban;
extern int root;

int check_action(char *cmd)
{
    if(cmd[0] == '/')   //快捷消息
    {
        if(status == 0)  
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return REPLACE;
    }
    if(strcmp(cmd,"log") == 0)  //登录
    {
        if(status == 1)
        {
            printf("你已登录！\n\n");
            return 0;
        }
        return LOG;
    }
    if(strcmp(cmd,"reg") == 0)  //注册
    {
        if(status == 1)
        {
            printf("你已登录,请离线后载注册！\n\n");
            return 0;
        }
        return REG;
    }    
    if(strcmp(cmd,"show") == 0)  //查看在线用户
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return SHOW;
    }
    if(strcmp(cmd,"say") == 0)  //单人聊天
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
    if(strcmp(cmd,"stoall") == 0)  //群聊
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
    if((strcmp(cmd,":)") == 0) || (strcmp(cmd,"0.0") == 0) || (strcmp(cmd,"^3^") == 0)) //表情
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
    if(strcmp(cmd,"off") == 0)  //离线
    {
        return OFF;
    }
    if(strcmp(cmd,"chg_psd") == 0)  //修改密码
    {
        if(status == 0)
        {
            printf("请先登录！\n\n");
            return 0;
        }
        return CHG_PSD;
    }
    if(strcmp(cmd,"chg_nam") == 0)  //修改昵称
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
    if(strcmp(cmd,"out") == 0)  //踢人
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
    if(strcmp(cmd,"ban") == 0)  //禁言
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
    if(strcmp(cmd,"rmban") == 0)  //解除禁言
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
    if(strcmp(cmd,"help") == 0) //清屏
    {
        return HELP;
    }
    if(strcmp(cmd,"exit") == 0)  //退出程序
    {
        return EXIT;
    }
    return ERROR;
}
