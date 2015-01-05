/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:     find_str
  Author:        wangxin   Version:  1.0       Date: 2014.05.01
  Description:   该程序实现找出一段字符串
  Others:        无
  Function List:  
                 1. find_str  找出一段字符串
                 2. strnmp    比较字符串
  History:       no
*************************************************/

#include<stdio.h>
#include<string.h>
#define MAX 1024
#define INPUT_ERROR 0
#define FUNCTION_ERROR -1

/*************************************************
  Function:      find_str 
  Description:   该函数实现找出一段字符串
  Calls:         strncmp(char *dest,char *src,int n)
  Called By:     main
  Input:         src  原字符串
                 head 头字符串
		 tail 尾字符串   
  Output:        no
  Return:        aim_str   返回处理后的字符串
  Others:        no
*************************************************/

char *find_str(char *src,char *head,char *tail)
{
    if((src == NULL) || (head == NULL) || (tail == NULL))
    {
        printf("input error!\n");
	exit(INPUT_ERROR);
    }
    
    char *aim_str;
    int h_len = strlen(head);
    int t_len = strlen(tail);

    while(*src != '\0')
    {
        if(strncmp(src,head,h_len) == 0)   /* 找出头字符串 */
	{
	    aim_str = src;                 /* 保存数组 */
	    src = src + h_len;             
	    break;
	}
        
	src++;
    }

    while(*src != '\0')
    {
        if(strncmp(src,tail,t_len) == 0)    /* 找出尾字符串 */
	{
	    src = src + t_len;              
	    *src = '\0';                    /* 尾部赋0 */
            return aim_str;                 /* 返回头指针 */
	}
        
	src++;

    }
}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          find_str
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    char src[MAX];
    char head[MAX];
    char tail[MAX];
    char *aim_str = NULL;

    printf("please input a string(no blank):\n");
    scanf("%s",src);    /* 输入源字符串 */

    printf("please input the head string(no blank):\n");
    scanf("%s",head);   /* 输入头字符串 */

    printf("please input the tail string(no blank):\n");
    scanf("%s",tail);   /* 输入尾字符串 */

    if((aim_str = find_str(src,head,tail)) == NULL)   /* 函数调用 */
    {
        printf("function opporate error!\n");
	exit(FUNCTION_ERROR);
    }

    printf("the aim_str is %s.\n",aim_str);

    return 0;
}
