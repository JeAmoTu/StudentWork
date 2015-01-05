/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:     opposite
  Author:        wangxin   Version:  1.0      Date: 2014.05.01
  Description:   该程序实现对一个字符串的逆序
  Others:        无
  Function List: 
                 opposite(char *src, int s_len)
		 该函数实现对一个字符串的逆序
  History:       no
*************************************************/

#include<stdio.h>
#include<string.h>

/*************************************************
  Function:        opposite
  Description:     该函数实现对一个字符串逆序
  Calls:           no
  called By:       main
  Input:           *src    传入一个字符串
                   s_len   传入字符串的长度
  Output:          no
  Return:          no
  Others:          no
*************************************************/

void opposite(char *src, int s_len)
{
    if(s_len >= 1)
    {
        printf("%c",*(src + s_len -1));  /* 最后一位开始输出*/
	s_len--;
    }
    
    if(s_len > 0)
    {
        opposite(src,s_len);             /* 递归调用函数 */
    }
}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          opposite
  called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    char str[1024];
    
    printf("please input a string:\n");
    scanf("%s",str);             /* 输入一个字符串 */

    opposite(str,strlen(str));   /* 函数调用 */
    printf("\n");

    return 0;
}
