/*************************************************
  Copyright (C), 1994-2014   2014.05.01
  File name:     replace_p
  Author:        Wangxin     Version: 1.0       Date: 2014.05.01
  Description:   该程序实现对一个整数的p位替换后输出
  Others:        无
  Function List: 
                 replace_P(int num, int p, int v)
		 该函数实现对该数的p位替换成v后输出
  History:       no
*************************************************/

#include<stdio.h>

/*************************************************
  Function:      replace(int n, int p, int v) 
  Description:   该函数实现对该数的p位替换成v后输出
  Calls:         no
  Called By:     main
  Input:         n   输入的整数
                 p   要替换的位
                 v   要替换的数
  Output:        no
  Return:        no
  Others:        no
*************************************************/

void replace(int num, int p, int v)
{
    int i;
    int temp;
    char aim_num[32];
    
    for(i = 0; i < 32 ; i++)
    {
        temp = (num >> i) & 1;    /* 该为赋值给temp */
	
	if(i == p - 1)
	{
	    aim_num[i] = v;       /* 第p位替换 */
	}
	
	else	
	{
	    aim_num[i] = temp;    /* 保存数组 */
	}
    }

    printf("the number after replaced is : ");
    
    for(i = 31 ; i >= 0; i--)
    {
	printf("%d",aim_num[i]);  /* 逆序输出 */
    }
 
}

/*************************************************
  Function:     mian
  Description:  实现基本输入输出
  Calls:        replace
  Called By:    no
  Input:        no
  Output:       no
  Return:       0
  Others:       no
*************************************************/
int main()
{
    int my_num;
    int my_p;
    int my_v;

    printf("please input a number : ");
    scanf("%d",&my_num);          /* 输入一个整数 */

    printf("please input the p(p<32) and the v(0|1) you want replace : ");
    scanf("%d %d",&my_p,&my_v);   /* 输入要换的位数和数*/

    replace(my_num,my_p,my_v);    /* 函数调用 */
    printf("\n");

    return 0;
}
