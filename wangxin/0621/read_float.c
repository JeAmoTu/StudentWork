#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
    float data;
    int fd = open("hello_float.txt",O_RDONLY);
    
    if(fd >= 0)
    {
        int n = read(fd,&data,10);
	if(n < 0)
	{
	    perror(strerror(errno));
	    close(fd);
	    return 0;
	}
	printf("%f\n",data);
        close(fd)l;
    }
    else
    {
        perror(strerror(errno));
    }
    
    return 0;
}
