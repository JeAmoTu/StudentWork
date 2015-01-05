#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    char data[] = "i am a b-boy!";
    int fd = open("me.txt",O_RDONLY|O_CREAT,0444);
    write(fd,data,strlen(data));
    close(fd);

    return 0;
}
