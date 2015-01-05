/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:     find_sub
  Author:        wangxin    Version:  1.0      Date: 2014.05.01
  Description:   该程序实现找出一个字符串中子串出现的次数
  Others:        no
  Function List: 
                 1. find_sub(char *src,char *dest)
		    找出子串
                 2. strncmp(char *src,char *dest,int n)
		    比较两个字符串
  History:       no
*************************************************/

#include<stdio.h>
#include<string.h>
#define INPUT_ERROR 0

/*************************************************
  Function:    find_sub   
  Description: 找出子串出现次数
  Calls:       strncmp
  Called By:   main
  Input:      
              src   原字符串
              dest  子串
  Output:     no
  Return:     返回次数
  Others:     no
*************************************************/

int find_sub(char *src, char *dest)
{
    if(src == NULL || dest == NULL)
    {
        printf("input error!\n");
	exit(INPUT_ERROR);
    }

    int count;
    int d_len = strlen(dest);
    
    while(*src != '0')
    {
        if(strncmp(src,dest,d_len) == 0)  /* 比较字符串 */
	{
	    count++;                      /* 技术单自增 */
	}

	src++;
    }

    return count;                          /* 返回次数 */
} 

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          find_sub
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    
    int count;
    char src[100];
    char sub_str[100];
    
    printf("please input a string(no blank):\n");
    scanf("%s",src);        /* 输入源字符串 */
    
    printf("please input a substring(no blank):\n");
    scanf("%s",sub_str);    /* 输入子字符串 */

    count = find_sub(src,sub_str);   /* 函数掉用 */
    printf("the substring appears %d times.\n",count);

    return 0;
}

