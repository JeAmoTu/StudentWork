#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char **argv)
{
    int fd =open ("hello.txt",O_RDWR|O_EXCL);
    printf("fd = %d\n",fd);
    #if 0
    int fd = open("student_info.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    
    if(fd > 0)
    {
        //file exist,open and trunc suc
	//file not exist,creat suc
	printf("file creat suc\n");
    }
    else
    {
        //file exist,open or trunc error
	//file not exist,creat error
	//perror(strerror(errno));
        write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
    }
    #endif
    close(fd);
    
    return 0;
}
