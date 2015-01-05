#include<stdio.h>

int find_sub(char *src, char *dest)
{
    int count;
    int d_len = strlen(dest);
    
    while(*src != '0')
    {
        if(strncmp(src,dest,d_len) == 0)
	{
	    count++;
	}

	src++;
    }

    return count;   
}

int main()
{
    
    int count;
    char src[100];
    char sub_str[100];
    
    printf("please input a string:\n");
    scanf("%s",src);
    
    printf("please input a substring:\n");
    scanf("%s",sub_str);

    count = find_sub(src,sub_str);
    printf("the substring appear %d times.\n",count);

    return 0;
}

