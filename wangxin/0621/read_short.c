#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
    unsigned short data;
    int fd = open("hello.txt",O_RDONLY);
    
    if(fd > 0)
    {
        int n = read(fd,&data,sizeof(data));
	if(n < 0)
	{
	    perror(strerror(errno));
	    close(fd);
	    return 0;
	}
	printf("%x\n",data);
	close(fd);
    }
    else
    {
        perror(strerror(errno));
    }
    
    return 0;
}
