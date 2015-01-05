#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

static int g_num = 0;
static pthread_mutex_t g_mutex;

void *thread_handle0(void *arg)
{
    int i;
    int num = *((int *)arg);
    
    for(i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&g_mutex);
        printf("in thread[%d] before %d\t",num,g_num);
        g_num++;
	printf("in thread[%d] after %d\n",num,g_num);
        pthread_mutex_unlock(&g_mutex);
        sleep(2);
    }
    return NULL;
}

void *thread_handle1(void *arg)
{
    int i;
    int num = *((int *)arg);
    
    for(i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&g_mutex);
        printf("in thread[%d] before %d\t",num,g_num);
        g_num--;
	printf("in thread[%d] after %d\n",num,g_num);
        pthread_mutex_unlock(&g_mutex);
        sleep(2);
    }
    return NULL;
}

int main()
{
    int i;
    int j;
    pthread_t pid[4] = {0};
    pthread_mutex_init(&g_mutex,NULL);
    
    for(i = 1; i < 3; i++)
    {
        int *name = (int *)malloc(sizeof(int));
        
	*name = i;
	
	if(i == 1)
	{
	    pthread_create(&pid[i],NULL,thread_handle0,(void *)name);
        }
	if(i == 2)
	{
	    pthread_create(&pid[i],NULL,thread_handle1,(void *)name);
	}
    }
    
    for(j = 1; j < i; j++)
    {
        pthread_join(pid[j],NULL);
        printf("thread[%d] exit\n",j);
    }
     
    pthread_mutex_destroy(&g_mutex);
    printf("main exit!\n");
    return 0;
}
