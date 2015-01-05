#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

int main()
{
    char data[] = "abcdefghij";
    int fd = open("char_info.txt",O_RDWR|O_CREAT,0664);
    if(fd >= 0)
    {
        int n = write(fd,data,strlen(data));
	if(n < 0)
	{
	    perror(strerror(errno));
	    close(fd);
	    return 0;
	}
	close(fd);
    }
    else
    {
        perror(strerror(errno));
    }
    return 0;

}
