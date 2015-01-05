#include<stdio.h>

char * inversion(char *str)
{
    int i;
    char *start;
    char *end;
    char temp;
    int s_len = strlen(str);

    start = str;
    end = str + s_len - 1;
    
    for(i = 0; i < (s_len/2); i++)
    {
        temp = *start;
	*start = *end;
	*end = temp;
	start++;
	end--;
    }
    
    start = str;
    end = str;
    
    while(*str != '\0')
    {
        str++;

	if((*str == ' ')||(*str == '\0'))
	{
	    end = str - 1;

	    while(start < end)
	    {
	        temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	    }

	    start = str + 1;
	    end = str + 1;
	}
    }

    str = str - s_len;
    
    return str;
}

int main()
{
    char *p_str;
    char str[100];

    printf("please input a string:\n");
    gets(str);

    p_str = inversion(str);
    printf("now the string is:\n");

    printf("%s\n",p_str);
    
    return 0;
}
