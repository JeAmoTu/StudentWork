#include<stdio.h>

int main()
{
    int i;
    float f;
    int *p;
    float *pf;
    
    p = (int *)malloc(sizeof(int));
    pf = (float *)malloc(sizeof(float));

    *p = 1024;
    *pf = 3.14;

    printf("an integer = %d, a float = %f\n",*p,*pf);
    
    free(p);
    free(pf);
    
    return 0;
}
