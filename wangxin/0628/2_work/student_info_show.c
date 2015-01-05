#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

typedef struct student_info_tag
{
    char name[20];
    char blank_01;
    char age;
    char blank_02;
    char gender;
}student_info_t;

int main(int argc, char **argv)
{
    int i;
    char name[20];
    student_info_t stu;
    
    printf("please input the people's name you want show:");
    scanf("%s",name);

    int fd = open("student_info.db",O_RDONLY);
    if(fd < 0)
    {
        perror(strerror(errno));
	close(fd);
	return 0;
    }
    
    int len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    for(i = 0; i < len; i += 24)
    {
        int ret = read(fd, &stu, sizeof(student_info_t));
        
	if(strcmp(name,stu.name) == 0)
	{
	    printf("name: %s,age: %d,gender: %c\n",stu.name,stu.age,stu.gender);
	}
	
    }
    
    return 0;
}
