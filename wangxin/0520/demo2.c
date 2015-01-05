#include<stdio.h>
#include<string.h>
#define MAX 1000
#define INPUT_FAIL 0
#define OPPORATE_ERROR -1

char * ahead(char *src, int num)
{
    if(src == NULL || num == 0)
    {
        printf("you input error data!\n");
	exit(INPUT_FAIL);
    }
    
    int i;
    int j;
    int l_src;
    char *p_src;
    char *p_dest;
    char dest[MAX];
    
    p_src = src;
    l_src = strlen(src);
    
    for(i = 0; i < num; i++)
    {
	p_dest = dest;

        *p_dest = *(p_src + l_src -1);
    
	for(j = 0; j < l_src - 1; j++)
        {
            p_dest++;
	    *p_dest = *(p_src + j);
        }
	
	*(++p_dest) = '\0';
	
	strcpy(src,dest);
    }
    
    p_dest = dest;
    
    return p_dest;
}

int main()
{
    int num;
    char str[MAX];
    char *aim_str;

    printf("please input a string(no blank):\n");
    scanf("%s",str);
    
    printf("please input the times you want ahead(num > 0):\n");
    scanf("%d",&num);

    if((aim_str = ahead(str,num)) == NULL)
    {
        printf("the function opporated error!\n");
	exit(OPPORATE_ERROR);
    }
    
    printf("now the string is %s\n",aim_str);
    
    return 0;
}
