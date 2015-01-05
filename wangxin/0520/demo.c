#include<stdio.h>

void print(int num)
{
    int i;
    int num1 = 1;

    for(i = 1; i <= num; i++)
    {
	
	if(num1 == 10)
	{
	    num1 = 0;
	}
	
	printf("%d ",num1);
	
	num1++;
    }

    printf("\n");
}

int main()
{
    int num;
    
    printf("please input a num:\n");
    scanf("%d",&num);

    print(num);
    
    return 0;
}

