/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      my_strcmp
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现比较两个字符串大小
  Others:         无
  Function List:  
                  my_strcmp
		  比较两个字符串大小
  History:        no
*************************************************/

#include <stdio.h>

/*************************************************
  Function:       my_strcmp
  Description:    比较字符串大小
  Calls:          no
  Called By:      choose
  Input:          src str
  Output:         no
  Return:         0 -1 1
  Others:         no
*************************************************/

int my_strcmp(char *src, char *str)
{
    int i;

    while((*src  != '\0') && (*str != '\0'))
    {
        if(*src == *str)
	{
	    src++;
            str++;           //相同继续遍历
	}
	
	if(*src > *str)
	{
	    return 1;         //大返回1
	}

        if(*src < *str)       
	{
	    return -1;
	}
    }

    if(*src == '\0')
    {
        if(*str == '\0')
	{
	    return 0;
	}
	else
	{
	    return -1;
        }
    }
    else
    {
        return 1;
    }
}
