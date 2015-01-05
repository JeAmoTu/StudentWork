#include"../../include/my_head.h"

extern char back[100];
extern char online[100];
extern int count;

int callback(void *not_used, int argc, char **argv, char **col_name)  //回调函数
{
    int i;

    for(i = 0; i < argc; i++)
    {
        sprintf(back,"%s",argv[0]);  //将select的返回输入到back中

        sprintf(online+count,"%s ",argv[0]);  //得到的用户名存入online

        count = count + strlen(argv[0]) + 1;  //跳格
    }
    return 0;
}
