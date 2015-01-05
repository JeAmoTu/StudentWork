/************************************************************
Copyright (C), 1994-2014   wangxin
FileName:         convert
Author:  wangxin    Version:   1.0        Date:2014.05.01
Description:      整数中相邻两个位异或组成新数以二进制输出
Function List:    
             int change(int num,int *byte);
	     整数中相邻两个位异或组成新数以二进制输出
***********************************************************/

#include <stdio.h>

/*************************************************
Function:         change
Description:      整数中相邻两个位异或组成新数以二进制输出
Calls:            no
Called By:        main
Input:            num   要处理的整数
                  *byte 返回新数数组的头指针
Output:           no
Return:           0
*************************************************/

int change(int num,int *byte)
{
    int i;

    for(i = 0; i < 32; i++) 
    {
        if((i > 0) && (i < 31))               /* 遍历字符串 */
	{
	    if(((num >> (i - 1)) & 1)
		 == ((num >> (i + 1)) & 1))   /* 实现相邻位异或 */
	    {
	        byte[i] = 0;
	    }
	    
	    else
	        {
	            byte[i] = 1;
	        }
	    }
	    
	    else
	    {
	        byte[i] = (num >> i) & 1;     /* 新数首位位赋值 */
	    }
    }

    return 0;
}

/*************************************************
Function:         main
Description:      实现基本输入输出
Calls:            change
Called By:        no
Input:            no
Output:           no
Return:           0
*************************************************/

int main()
{
    int i;
    int num;
    int byte[32];

    printf("Please input a number:");
    scanf("%d",&num);

    change(num,byte);    /* 函数调用 */

    printf("now the number is:\n");

    for(i = 31; i >= 0; i--)
    {
        printf("%d",byte[i]);   
    }
    
    printf("\n");

    return 0;
}
