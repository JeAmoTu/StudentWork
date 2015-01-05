#include<stdio.h>

void creat(int a[][2])
{
    int i;
    int j;
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
	{
            a[i][j] = i + 1;
	}
    }
}

void display(int a[][2])
{
    int i;
    int j;
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
	{
	    printf("%d\n",a[i][j]);
            printf("%d\n",(*(a + i))[j]);
	    printf("%d\n",*(*(a + i) + j));
	    printf("%d\n",*(a[i] + j));

	}
    }
}

int main()
{
    int a[2][2];
    
    creat(a);
    display(a);

    return 0;
}
