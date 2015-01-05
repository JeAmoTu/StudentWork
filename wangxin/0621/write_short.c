#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
    unsigned short data = 0xABCD;
    int fd = open("hello.txt",O_RDWR|O_CREAT|O_TRUNC,0664);
    
    if(fd > 0)
    {
        write(fd,&data,sizeof(data));
	printf("write success\n");
    }
    else
    {
        perror(strerror(errno));
    }
    close(fd);
    
    return 0;
}
