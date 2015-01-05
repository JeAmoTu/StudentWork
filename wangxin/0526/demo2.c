#include<stdio.h>
#define ERROR 1

int main(int argc, char * argv[])
{
    if(argc != 5)
    {
        printf("please input five parameters!\n");
	exit(ERROR);
    }
    
    int i;
    
    for(i = 0; i < argc; i++)
    {
        printf("argc[%d] = %s\n",i,argv[i]);
    }
    
    return 0;
}
