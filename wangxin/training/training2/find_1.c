/*************************************************
  Copyright (C), 1994-2014   Wangxin
  File name:    find_1
  Author:       Wangxin    Version:   1.0     Date:   2014.05.01
  Description:  该程序实现找出一个字节中被置1的位数 
  Others:       无
  Function List: 
                count_1(char byte) 该函数实现找出一个字节中为置1的位数
  History:      no
*************************************************/

#include<stdio.h>

/*************************************************
  Function:    count_1
  Description: 该函数实现找出一个字节中被置1的位个数
  Calls:       no
  Called By:   main 
  Input:       byte  传入一个字节
  Output:      no
  Return:      count 返回1位的个数
  Others:      no
*************************************************/

int count_1(char byte)
{
    int i;
    int test;
    int count = 0;

    for(i = 0; i < 8; i++)
    {
        test = byte & 1;     /* 该位赋给test */
	byte = byte >> 1;    /* 字节向后移1位 */
	
	if(test == 1)        /* 判断该位是不是1 */ 
	{
	    count++;         /* 计数单位自增 */
	}
    }

    return count;            /* 返回计数 */
}

/*************************************************
  Function:      main
  Description:   实现基本输入输出
  Calls:         count_1
  Called By:     no
  Input:         no
  Output:        no
  Return:        0
  Others:        no
*************************************************/

int main()
{
    int num1;
    char  ibyte;
    
    printf("please input a byte:\n");
    scanf("%c",&ibyte);                /* 输入一个字符 */
 
    num1 = count_1(ibyte);             /* 函数调用 */
    printf("the 1 of a byte is %d.\n",num1);
    
    return 0;
}


