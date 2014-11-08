//fork函数的使用
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
 
int main(int argc,char* argv[])
{
    pid_t pid=fork();
    if(pid<0)
    {
        fprintf(stderr,"错误！");
    }
    else if(pid==0)
    {
        printf("这是子进程！");
        exit(0);
    }
    else
    {
    printf("这是父进程！子进程的进程标记为=%d",pid);
    }
    //可能需要时候wait或waitpid函数等待子进程的结束并获取结束状态
    exit(0);
}
