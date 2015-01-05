#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>

char *buf = NULL;

void *thread_handle(void *arg)
{
    char a = buf[0];

    int i;
    for(i = 0; i<50; i++)
    {
        printf("in thread %d\n",i);
	sleep(1);
    }
    return NULL;
}//线程函数体

int main(int argc, char **argv)
{
    pthread_t pid;
    
    buf = (char*)malloc(16);

    int ret = pthread_create(&pid,NULL,thread_handle,NULL);
    if(0 != ret)
    {
        perror(strerror(errno));
	return 1;
    }

    int i = 0;
    for(i = 0; i < 50; i++)
    {
        printf("in main %d\n",i);
	sleep(2);
    }
    
    pthread_join(pid,NULL);
 
    printf("exit\n");

    return 0;
}
