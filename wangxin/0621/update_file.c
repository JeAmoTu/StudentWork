#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char **argv)
{
    int fd = open("student_info.txt",O_RDWR|O_CREAT,0664);
    
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
	perror(strerror(errno));
        //write(STDERR_FILENO,strerror(errno),strlen(strerror(errno)));
    }
    close(fd);
    
    return 0;
}
