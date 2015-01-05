#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int block_write(int fd, char*buf, int len)
{
    int write_size = 0;
    int n = 0;

    while(write_size < len)
    {
        n = write(fd,buf+write_size,len-write_size);
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
	write_size += n;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i = 0;
    int j = 0;
    char content[100];
    char *data;
    int filesize = atoi(argv[2]);
    
    data = (char *)malloc(filesize + 1);
    memset(data,0,filesize + 1);
    
    for(i = 0; i < filesize; i++)
    {	
	data[i] = 'A' + j;
	j++;
	
	if(j == 26)
	{
	    j = 0;
	}
    }
    
    strcpy(content,argv[1]);
    int fd = open(content,O_RDWR|O_CREAT,0666);
    
    block_write(fd,data,filesize);

    close(fd);
    return 0;
}
