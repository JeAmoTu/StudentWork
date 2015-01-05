#include <stdio.h>

void swap(int *p1, int *p2)
{
    int temp;

    temp = *p1;
    *p1 = *p2;
    *p2 = temp;

}

int main()
{
    int a;
    int b;
    int *p1;
    int *p2;

    printf("please input two numbers: ");
    scanf("%d %d",&a,&b);
    
    printf("\na is %d, b is %d\n",a,b);

    p1 = &a;
    p2 = &b;

    swap(p1,p2);
    printf("now a is %d, b is %d\n\n",a,b);

    return 0;
}
