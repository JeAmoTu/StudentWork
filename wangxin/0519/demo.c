#include<stdio.h>
#include<string.h>
#include<malloc.h>

char *get_num(char *ptr)
{
    ptr = (char *)malloc(sizeof(char) * 100);
    
    return ptr;
}

int main()
{
    char *ptr;

    ptr = get_num(ptr);

    strcpy(ptr,"hello world!");

    printf("ptr = %s\n",ptr);
   
    return 0;
}
