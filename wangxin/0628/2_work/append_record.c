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
    printf("%d\n",sizeof(student_info_t));

    student_info_t stu = {.name = "TOM", .blank_01 = ' ', .age = 18, .blank_02 = ' ', .gender = 'M'};
    
    int fd = open("student_info.db",O_RDWR|O_CREAT|O_APPEND,0664);
    
    if(fd < 0)
    {
        perror(strerror(errno));
	close(fd);
	return 0;
    }

    int num = write(fd, &stu, sizeof(stu));
    
    if(num != sizeof(stu))
    {
        perror(strerror(errno));
	close(fd);
	return 0;
    }
    
    close(fd);
    return 0;
}

