#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
    int data;
    int fd = open("hello_int.txt",O_RDWR|O_CREATE,0666);

    if(fd > 0)
    {
        int n = read(fd,&data,sizeof(data));
        if(n < 0)
        {
            perror(strerror(errno));
            close(fd);
            return 0;
        }
        printf("%0x\n",data);
        close(fd);
    }
    else
    {
        perror(strerror(errno));
    }

    return 0;
}
