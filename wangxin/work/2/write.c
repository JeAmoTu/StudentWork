#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char **argv)
{
    char data[] = "hello world";
    int fd = open("student_info.txt",O_RDWR|O_CREAT,0666);
    write(fd,data,strlen(data));
    close(fd);

    return 0;
}
