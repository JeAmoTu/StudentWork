#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    int i = 0;
    int j = 0;
    char src_data[50] = {0};
    int fd = open(argv[1],O_RDWR);
    
    read(fd,src_data,sizeof(src_data));
    for(i = 0; i < sizeof(src_data); i++)
    {
        if(j == 26)
	{
	    j = 0;
	}

	if(src_data[i] != ('A' + j))
	{
	    printf("creat file error!\n");
	    close(fd);
	    return -1;
	}
	
	j++;
    }

    printf("creat file success!\n");
    close(fd);
    return 0;
}
