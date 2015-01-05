#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#define MAX_SIZE 4*1024

int block_read(int fd, char*buf, int len)
{
    int read_size = 0;
    int n = 0;
    
    while(read_size < len)
    {
        n = read(fd, buf + read_size,len-read_size);
        if(n < 0)
	{
	    perror(strerror(errno));
	    break;
	}
	else if(0 == n)
	{
	    perror(strerror(errno));
	    break;
	}
	read_size += n;
    }
}

int main(int argc, char **argv)
{
    char src_data[MAX_SIZE] = {0};
    int fd = open(argv[1],O_RDWR|O_EXCL);
    
    if(fd < 0)
    {
        char err_data[] = "no this file! do error!";
	fd = open("err.log",O_RDWR|O_CREAT,0666);
	write(fd,err_data,sizeof(err_data));
	close(fd);
	return 0;
    }
    
    block_read(fd,src_data,MAX_SIZE);
    printf("%s",src_data);
    close(fd);

    return 0;
}
