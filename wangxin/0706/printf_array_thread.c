#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>

//int g_count = 0;
//char *buf = NULL;

void *thread_handle0(void *arg)
{
    sleep(3);
    int num = *((int *)arg);
    //char a = buf[0];

    int i = 0;
    while(i < 50)
    {
	printf("in thread[%d] = %d\n",num,i);
	i++;
	sleep(1);
    }
    return NULL;
}//线程函数体

int main(int argc, char **argv)
{
    pthread_t pid[2] = {0};
    
    int ret;
    int i = 0;
    int thread_num[2]; 
    //buf = (char*)malloc(16);

    for(i = 0; i < 2; i++)
    {
        thread_num[i] = i;
	ret = pthread_create(&pid[i],NULL,thread_handle0,(void *)&thread_num[i]);
        if(0 != ret)
        {
            perror(strerror(errno));
	    return 1;
        }
        sleep(1);
    }
    
    int j = 0;
    for(j = 0; j < 50; j++)
    {
        printf("in main = %d\n",j);
	sleep(2);
    }

    int k = 0;
    for(k = 0; k < i; k++)
    {
        pthread_join(pid[k],NULL);
    }

    return 0;
}
