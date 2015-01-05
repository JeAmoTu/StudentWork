/*************************************************
  Copyright (C),  Wangxin   2014.05.01 
  File name:      perfectnum
  Author:         Wangxin    Version:  1.0      Date:  2014.05.01
  Description:    该程序找出1－1000中的完数
  Others:         无
  Function List:  find_perfect_num()
  History:        no
*************************************************/

#include<stdio.h>

/*************************************************
  Function:       find_perfect_num
  Description:    该函数实现找出1－1000中的完数
  Calls:          no
  Called By:      main
  Input:          no
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void find_perfect_num()
{
    int i;
    int j;
    int sum = 0;

    printf("\033[40;33mthe perfect num of 1-1000 have:\033[0m\n");
   
    for(i = 2; i <= 1000; i++) 
    {
        sum = 0;                
        for(j = 1; j < i; j++)   
        {
            if(i % j == 0)      /* 求真因子 */
            sum += j;           /* 真因子求和 */
        }
    
        if(sum == i)            /* 为完数 */
        {
            printf("\033[40;33m%d\033[0m\n",i);
        }
    }
}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          find_perfect_num
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    find_perfect_num();  /* 函数调用 */
    
    return 0;
}
