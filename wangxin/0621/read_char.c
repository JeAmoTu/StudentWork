#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
    char read_data[50] = {0};
    int fd = open("hello_world.txt",O_RDONLY);
    
    if(fd >= 0)
    {
        int n = read(fd,read_data,40);
	
	if(n < 0)
	{
	    perror(strerror(errno));
	    close(fd);
	    return 0;
	}
	
	printf("n = %d\n",n);
	printf("%s\n",read_data);
        
	close(fd);
    }
    else
    {
        perror(strerror(errno));
    }
    
    return 0;
}
