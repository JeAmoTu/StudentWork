/*************************************************
  Copyright (C), 1994-2014, wangxin
  File name:      fac
  Author:        wangxin   Version: 1.0       Date:  2014.05.01
  Description:   该函数实现输出一个数的阶乘
  Others:        wu
  Function List:  
                 fac(int n)  实现阶乘
  History:       no
*************************************************/


#include<stdio.h>

/*************************************************
  Function:       fac  
  Description:    实现阶乘
  Calls:          无
  Called By:      main
  Input:          n  要求的数 
  Output:         no
  Return:         result   结果
  Others:         no
*************************************************/

int fac(n)
{
    int result;
    
    if(n == 1)
    {
        result = 1;      /* 为1结果为1 */
    }

    else
    {
        result = n * fac(n - 1);   /* 递归求结果 */
    }

    return result;      /* 返回结果 */

}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          fac
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    int num;

    printf("please input a number:\n");
    scanf("%d",&num);   /* 输入一个数 */
    
    num = fac(num);     /* 函数调用 */
    printf("the number's factorial is %d.\n",num);
    
    return 0;
}
