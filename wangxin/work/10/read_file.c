#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    char read_data[64] = {0};
    int fd = open("hello_world.txt",O_RDWR);
    lseek(fd,atoi(argv[1]),SEEK_SET);
    read(fd,read_data,atoi(argv[2]));
    printf("%s\n",read_data);
    return 0;
}
