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
    char data1[] = "ABCDEFGHIJ";
    char data2[] = "hello";
    char ch = 'F';
    int fd = open("char_info.txt",O_RDWR);
    
    if(fd >= 0)
    {
        lseek(fd,2,SEEK_SET);        
	int i = write(fd,data1,strlen(data1));
        
	if(i < 0)
	{
	    perror(strerror(errno));
	    close(fd);
	    return 0;
	}
	
	lseek(fd,4,SEEK_CUR);
        int j = write(fd,data2,strlen(data2));
	
	if(j < 0)
	{
	    perror(strerror(errno));
	    close(fd);
	    return 0;
	}
	
	lseek(fd,0,SEEK_SET);
	int k = write(fd,&ch,sizeof(ch));
	
	if(k < 0)
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
	close(fd);
	return 0;
    }

    return 0;
}
