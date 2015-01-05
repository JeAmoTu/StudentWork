#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static pthread_mutex_t q_mutex;

int main()
{
    int i;

    pthread_mutex_init(&q_mutex,NULL);
    pthread pid[3];
    
    int ret = pthread_create(&pid[0],NULL,thread_handle0,NULL);
    return 0;
}
