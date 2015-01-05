#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char **argv)
{
    char data[] = "welcome";
    int fd = open("student_info.txt",O_RDWR|O_APPEND);
    write(fd,data,strlen(data));
    close(fd);

    return 0;
}
