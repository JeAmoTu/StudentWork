#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

struct student_info_t
{
    char name[16];
    char age;
    char gender;
};

int main(int argc, char **argv)
{
    int fd = open("student_info.txt",O_RDWR|O_CREAT,0664);
    
    if(fd > 0)
    {
        struct student_info_t student = {.name = "TOM",.age = 18,.gender = 'M'};

	write(fd,&student,sizeof(student));
	printf("write success\n");
    }
    else
    {
        perror(strerror(errno));
    }
    close(fd);
    
    return 0;
}
