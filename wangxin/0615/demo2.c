#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 2

int main(int argc, char **argv)
{
    int n = 0;
    char buf[BUFF_SIZE] = {0};
    
    while((n = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
    {
        if(write(STDOUT_FILENO, buf, n) != n)
	{
	    printf("read error");
	}
    }

    if(n < 0)
    {
       printf("read error");
    }

    return 0;
}
