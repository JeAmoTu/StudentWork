#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>

static int g_count = 0;

static pthread_mutex_t g_mutex;

void *thread_handle(void *arg)
{

    int i = 0;
    pthread_mutex_lock(&g_mutex);
    printf("in thread before \t g_count %d\n",g_count);
    g_count++;
    sleep(4);
    printf("in thread after\t\t g_count %d\n",g_count);
    pthread_mutex_unlock(&g_mutex);
    return NULL;
}//线程函数体

int main(int argc, char **argv)
{
    pthread_mutex_init(&g_mutex,NULL);
    pthread_t pid;

    int ret = pthread_create(&pid,NULL,thread_handle,NULL);
    if(0 != ret)
    {
        perror(strerror(errno));
	return 1;
    }
    pthread_mutex_lock(&g_mutex);
    sleep(2);
    g_count++;
    pthread_mutex_unlock(&g_mutex);
    
    pthread_join(pid,NULL);//同步，子线和主线。善后处理，释放子线程资源
    
    pthread_mutex_destroy(&g_mutex);
    printf("man thread exit!\n");
    return 0;
}
