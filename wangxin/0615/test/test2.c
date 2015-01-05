#include <stdio.h>

int fac(int num)
{
    int result;

    if(num == 0)
    {
        return 1;
    }
    
    result = num*fac(num - 1);
    
    return result;
}

int main()
{
    int i;
    int n;
    int num;
    
    printf("please input how many numbers you want input: \n");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("num%d: ",i + 1);
        scanf("%d",&num);
	printf("num%d's fac is %d\n\n",i + 1,fac(num));
    }

    return 0;
}
