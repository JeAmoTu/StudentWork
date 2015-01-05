#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    char data[] = "hello ";
    char read_data[64] = {0};
    int fd = open("hello_world.txt",O_RDWR);
    lseek(fd,strlen(data),SEEK_SET);
    read(fd,read_data,sizeof(read_data));
    printf("%s\n",read_data);
    return 0;
}
