#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>

int g_count = 0;
char *buf = NULL;

void *thread_handle0(void *arg)
{
    char a = buf[0];

    int i = 0;
    while(i < 50)
    {
	printf("g_count = %d\n",g_count);
	g_count++;
	i++;
	usleep(300000);
    }
    //return NULL;
    printf("thread[0] exit!\n");
}//线程函数体

void *thread_handle1(void *arg)
{
    char a = buf[0];

    int i = 0;
    while(i < 50)
    {
        printf("g_count = %d\n",g_count);
	g_count--;
	i++;
	usleep(500000);
    }
    //return NULL;
    printf("thread[1] exit!\n");
}//线程函数体

int main(int argc, char **argv)
{
    pthread_t pid;
    
    buf = (char*)malloc(16);

    int ret = pthread_create(&pid,NULL,thread_handle0,NULL);
    if(0 != ret)
    {
        perror(strerror(errno));
	return 1;
    }
    pthread_detach(pid);

    ret = pthread_create(&pid,NULL,thread_handle1,NULL);
    if(0 != ret)
    {
        perror(strerror(errno));
	return 1;
    }
    pthread_detach(pid);
    
    //pthread_join(pid,NULL);//同步，子线和主线。善后处理，释放子线程资源

    sleep(30);
    printf("man thread exit!\n");
    return 0;
}
