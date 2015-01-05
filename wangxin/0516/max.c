#include<stdio.h>

int max(int num1,int num2,int num3)
{
    int temp;
    
    if(num1 > num2)
    {
        temp = num1;
	num1 = num2;
	num2 = temp;
	
	if(num2 > num3)
	{
	    temp = num2;
	    num2 = num3;
	    num3 = temp;
	}
    }
    
    else
    {
        if(num2 > num3)
	{
	    temp = num2;
	    num2 = num3;
	    num3 = temp;
	}
    }
    
    return num3;
}

int main()
{
    int num1;
    int num2;
    int num3;
    int max_num;

    printf("please input three numbers:");
    scanf("%d %d %d",&num1,&num2,&num3);

    max_num = max(num1,num2,num3);
    printf("the max num is %d.\n",max_num);
    
    return 0;
}
