#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    char data[] = "hello ";
    char insert_data[] = "welcome";
    int fd = open("student_info.txt",O_RDWR);
    
    lseek(fd,strlen(data),SEEK_SET);
    write(fd,insert_data,strlen(insert_data));
    close(fd);

    return 0;
}
