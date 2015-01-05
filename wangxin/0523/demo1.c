#include <stdio.h>

int main()
{
    int i;
    int j;

    char a[2][2]={'w','a','n','g'};

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; i++)
	{
	    printf("%c",a[i][j]);
	}
    }

    return 0;
}
