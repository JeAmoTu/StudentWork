#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char **argv)
{
    int fd = open(argv[1],O_RDWR);
    if(fd >= 0)
    {
        int n = lseek(fd,0,SEEK_END);
        printf("size = %d",n);
        close(fd);
    }
    else
    {
        perror(strerror(errno));
    }
    return 0;
}
