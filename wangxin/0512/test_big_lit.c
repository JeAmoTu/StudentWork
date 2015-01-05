#include<stdio.h>

union node 
{
    int num1;
    int num2;
};

int main()
{
    union node node1;
    node1.num1 = 1;
    node1.num2 = 0;
    
    if(node1.num2 == 0)
    {
        printf("the cpu is little \n");
    }

    if(node1.num2 == 128)
    {
        printf("the cpu is big \n");
    }
    
    return 0;
}
