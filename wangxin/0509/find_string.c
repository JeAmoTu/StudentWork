/*************************************************
  Copyright (C), 2014-, Wangxin 
  File name:      find_string
  Author:  Wangxin     Version:  1.0        Date:   2014.05.09
  Description:    
  Others:         // 其它内容的说明
  Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
    1. ....
  History:        // 修改历史记录列表，每条修改记录应包括修改日期、修改
                  // 者及修改内容简述  
    1. Date:
       Author:
       Modification:
    2. ...
*************************************************/
#include<stdio.h>

int continue_max(char *str,char *ptr)
{
    int count=0;
    int max=0;
    while(*str != '\0')
    {
        while(*str>='0'&&*str<='9')
	{
	    count++;
	    str++;
	}
        
	if(count>max)
	{
	    max=count;
	    strncpy(ptr,str-max,max);
	    *(ptr+max)='\0';
	    count=0;
	}
	str++;
    }
    
    return max;

}


int main()
{
    char str[100];
    char ptr[100];
    int max;
    printf("please input a string:\n");
    scanf("%s",str);
    max=continue_max(str,ptr);
    printf("the max is %d\n",max);
    printf("the aim str is %s\n",ptr); 
    return 0;
}
