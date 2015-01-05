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
    char num = *((char *)arg);
    free(arg);
    //char a = buf[0];

    int i = 0;
    while(i < 3)
    {
	printf("in thread[%c] = %c\n",num,num);
	i++;
	sleep(1);
    }
    return NULL;
}//线程函数体

int main(int argc, char **argv)
{
    pthread_t pid[3] = {0};
    
    int ret;
    int i = 0;
    
    //buf = (char*)malloc(16);

    for(i = 0; i < 3; i++)
    {
        char *num =(char *) malloc(sizeof(char));
        *num = 'A' + i;

	ret = pthread_create(&pid[i],NULL,thread_handle0,(void *)num);
        if(0 != ret)
        {
            perror(strerror(errno));
	    return 1;
        }
        sleep(1);
    }
    
    int j = 0;
    for(j = 0; j < i; j++)
    {
        pthread_join(pid[j],NULL);
    }

    return 0;
}
