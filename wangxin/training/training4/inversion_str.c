/************************************************************
Copyright (C), 1994-2014   wangxin
FileName:           inversion_str.c
Author:   wangxin   Version:  1.0      Date:2014.05.01
Description:        将句子中的单词逆序
Function List:    
                    int inversion(char *str);
		    将句子中的单词逆序
***********************************************************/

#include <stdio.h>
#include <string.h>
#define INPUT_ERROR 0
#define FUNCTION_ERROR -1

/*************************************************
Function:         inversion
Description:      将句子中的单词逆序
Calls:            no
Called By:        main
Input:            str  待处理字符串
Output:           no
Return:           0
*************************************************/

char * inversion(char *str)
{
    if(str == NULL)
    {
        printf("input error!\n");
	exit(INPUT_ERROR);
    }

    int i;
    int str_len;
    char temp;
    char *start = str;
    char *end = str;

    str_len = strlen(str);                           //字符串长度

    for(i = 0; i < (str_len / 2); i++)               //字符串逆序
    {
        temp = *(str + i);
        *(str + i) = *(str + (str_len - i - 1));
        *(str + (str_len - i - 1)) = temp;
    }

    while(*(str++) != '\0')                         //遍历字符串
    {
        if((*str == ' ')||(*str == '\0'))           //将单词内容逆序
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

    return str;
}

/*************************************************
Function:         main
Description:      基本输入输出
Calls:            inversion
Called By:        no
Input:            no
Output:           no
Return:           0
*************************************************/

int main()
{
    char *p;
    char str[100];
    
    printf("please input a string:\n");
    gets(str);                                   //input string                                

    p = str;
    printf("now the string is:\n");

    if((p = inversion(str)) == NULL)             //函数调用
    {
        printf("function opporate error!\n");
	exit(FUNCTION_ERROR);
    }
    
    printf("%s\n",str);

    return 0;
}
