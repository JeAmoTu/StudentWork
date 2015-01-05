#include<stdio.h>
#define MAX 1000

char * deal(char *src,int *aim_str)
{
    int i;
    int temp;
    int l_src = strlen(src);
        
    for(i = 0; i < l_src; i++)
    {
        temp = src[i] - 'a';
	aim_str[temp]++;
    }
}

void deal1(int *aim_str)
{
    int i;
    int temp;
    
    temp = 26;
    
    for(i = 0; i < 26; i++)
    {
        if((aim_str[i] != 0) && (aim_str[i] < temp))
	{
	    temp = aim_str[i];
	}
    }

    for(i = 0; i < 26; i++ )
    {
        if(temp == aim_str[i])
	{
	    aim_str[i] = 0;
	}
    }


}

void print(int *aim_str)
{
    int i;
    int j;

    printf("Now the str is :\n");

    for(i = 0; i < 26; i++)
    {
        if(aim_str[i] != 0)
	{
	    for(j = 0; j < aim_str[i]; j++)
	    {
	        printf("%c",i + 'a');
	    }
	}
    }
    printf("\n");
}

int main()
{
    char str[MAX];
    int  aim_str[26]={0};
    
    printf("please input a letter string :\n");
    scanf("%s",str);
    
    deal(str,aim_str);
    deal1(aim_str);
    print(aim_str);

    return 0;
}
