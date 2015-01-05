#include<stdio.h>
int swap(int *num_1,int *num_2)
{
    int temp;
    
    temp = *num_1;
    *num_1 = *num_2;
    *num_2 = temp;

    return 0;
}

int main()
{
    int num1;
    int num2;
    int *num_1;
    int *num_2;

    num_1 = &num1;
    num_2 = &num2;

    printf("please input two numbers : ");
    scanf("%d %d",&num1,&num2);

    printf("the num1 = %d,the num2 = %d\n",num1,num2);

    swap(num_1,num_2);
    printf("now: the num1 = %d,the num2 = %d\n",num1,num2);
    
    return 0;
}
