#include<stdio.h>
#include<string.h>

char *trans(int dest)
{
    char *p;
    char src[100];
    char aim_src[100];
    p = src;

    while(dest > 0)
    {
        *p = '0' + (dest % 10);
        dest = dest / 10;
	p++;
    }
    
    *p = '\0';
    p--;

    int i;
    int j;
    int s_len = strlen(src);

    for(i = 0; i < s_len; i++)
    {
        aim_src[i] = *p;
	p--;
    }
    
    p = aim_src;
    
    return p;

}

int main()
{
    int num;
    char *str;

    printf("please input a num:\n",num);
    scanf("%d",&num);

    str = trans(num);
    printf("the string is %s\n",str);

    return 0;
}
