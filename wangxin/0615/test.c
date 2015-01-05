#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fp = open("student_info.txt",O_EXCL,0666);
    if(fp < 0)
    {
        printf("the txt is not exit!\n");
    }
    else if(fp >= 3)
    {
        printf("the txt is exit!\n");
    }
    close(fp);
    
    return 0;
}
