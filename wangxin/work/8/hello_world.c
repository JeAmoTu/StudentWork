#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    char data[] = "hello world";
    int fd = open("hello_world.txt",O_RDWR|O_CREAT,0666);
    write(fd,data,strlen(data));
    close(fd);

    char read_data[64] = {0};
    fd = open("hello_world.txt",O_RDWR|O_CREAT,0666);
    read(fd,read_data,sizeof(read_data));
    printf("%s\n",read_data);
    close(fd);

    return 0;
}
