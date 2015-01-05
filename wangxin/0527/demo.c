#include<stdio.h>

int main()
{
    int a[3] = {0};

    int i;
    
    /*int (*p)[3];
    p = &a;

    **p = 1;*/

    for(i  = 0; i < 3; i++)
    {
        a[i] = i + 1;
	printf("%d ",a[i]);
    }
    
    
    #if 0
    int a = 5;
    int b = 2;
    int *p = &b;
    
    float c = (a/ *p);
    
    printf("a---b = %d\n",a - --b);
    printf("a -- - b = %d\n",a -- - b);
    printf("a - -- b = %d\n",a - -- b);
    printf("c = a/ *p = %f\n",c);
    #endif
    return 0;
}

