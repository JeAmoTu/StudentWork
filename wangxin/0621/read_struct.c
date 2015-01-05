#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

typedef struct student_info_tag
{
    char name[16];
    char age;
    char gender;
}student_info_t;

int main(int argc, char **argv)
{
    int fd = open("student_info.txt",O_RDONLY);
    
    if(fd >= 0)
    {
        student_info_t student;
	int n = read(fd,&student,sizeof(student));
	printf("%d",n);
	if(n < 0)
	{
	    perror(strerror(errno));
	    close(fd);
            return 0;
	}
	printf("name: %s",student.name); 
	printf("age: %d",student.age);
	printf("gender: %c",student.gender);
        close(fd);
    }
    else
    {
        perror(strerror(errno));
    }
    
    return 0;
}
