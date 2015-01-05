#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fp = open("student_info.txt",O_RDWR|O_TRUNC);
    close(fp);
    
    return 0;
}
