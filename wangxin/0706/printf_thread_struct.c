#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>

typedef struct student_info_tag
{
    char name[20];
    char age;
    char gender;
}student_info_t;

void *thread_handle0(void *stu)
{
    student_info_t my_stu =*((student_info_t *)stu);
    //char a = buf[0];

    int i = 0;
    while(i < 3)
    {
	printf("name: %s age: %d gender: %c\n",my_stu.name,my_stu.age,my_stu.gender);
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
    student_info_t stu[3] = {"TOM",20,'F',"JACK",18,'M',"ROSE",19,'F'};


    for(i = 0; i < 3; i++)
    {

	ret = pthread_create(&pid[i],NULL,thread_handle0,(void *)&stu[i]);
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
