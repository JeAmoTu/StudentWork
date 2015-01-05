#include<stdio.h>

int main()
{
    int i;
    int j;
    int aa[2][2] = {1,2,3};
    int (*pa)[2];

    pa = aa;

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
	{
	    printf("%d ",*(*(pa + i)+j));
	}
    }
    
    printf("\n");    
    
    return 0;
}
