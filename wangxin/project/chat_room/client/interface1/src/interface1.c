#include"../../include/my_head.h"

int interface1(char *name) //登录成功界面
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

    if(strcmp(name,"admin") == 0)  //超级用户多出功能
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
