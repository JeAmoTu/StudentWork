#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char **argv)
{
    char data[] = "welcome";
    int fd = open("student_info.txt",O_RDWR);
    
    lseek(fd,40,SEEK_SET);
    write(fd,data,strlen(data));
    close(fd);

    return 0;
}
