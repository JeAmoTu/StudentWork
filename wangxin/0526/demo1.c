#include <stdio.h>

int main()
{
    #if 0
    int i;
    char a[3] = {'A','B','C'};
    char (*p1)[3] = &a;
    
    //char (*p2)[3] = a;

    printf("%s\n",*p1);
    //printf("%s\n",p2);
    #endif

    int i;
    int a[3] = {0,1,2};
    int b[3] = {3,4,5};
    int c[3] = {6,7,8};

    int * p[3];
    
    p[0] = a;
    p[1] = b;
    p[2] = c;

    for(i = 0; i < 3; i++)
    {
        printf("%d ",*(p[i] + i));
    }

    printf("\n");

    return 0;
}
