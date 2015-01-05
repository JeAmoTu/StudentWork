/*************************************************
  Copyright (C), 1994-2014  , Wangxin
  File name:   left
  Author:      wangxin     Version: 1.0       Date: 2014.05.01
  Description:   该程序实现输入n个人，围成一圈，依次报数1 2 3，报到3的人
                 退出，求最后剩下的是第几个人。
  Others:        无
  Function List:  
                 1. find_left(char *a, int num)
		 该函数实现求出最后剩下的是第几个人
  History:       no
*************************************************/

#include<stdio.h>

/*************************************************
  Function:       find_left
  Description:    该函数实现找出最后剩下的是第几个人
  Calls:          no
  Called By:      main
  Input:          1. *a 传入一个数组
                  2. num 传入有多少人 
  Output:         no
  Return:         返回剩下人的序号
  Others:         no
*************************************************/

int find_left(int *a, int num)
{
    int i;
    int j = 0;
    int k = 0;
    
    for(i = 0; i < num; i++)
    {
        a[i] = i + 1;  /* 编号 */
    }
    
    i = 0;     /* i置零 */
  
    while(k < num-1)  /* 踢出n-1个人后，结束 */
    {
        if(a[i] != 0)  /* 判断是否为0 */
        {
            j++;   /* 计数单位自增 */
        }
    
        if(j == 3)    /* 计数单位为3时 */
        {
            a[i] = 0;  /* 赋0踢出此人 */
            k++;     /* 踢出人数自增 */
            j = 0;     /* 计数单位置零 */
        }   
    
        i++;       
        if(i == num)   /* 到最后一个,i置零 */
        {
            i = 0;
        }

    }
 
    for(i = 0; i < num; i++) /* 找出剩下的一个 */
    {
	if(a[i] != 0) 
        {
	    break;
        }
    }

  
    return a[i];

}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          find_left
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    int max;
    int left;
    printf("\033[40;33mplease input the num of people:\033[0m\n");
    scanf("%d",&max);          /* 输入人数 */
    
    int a[max];    
    left = find_left(a,max);   /* 函数调用 */
    
    printf("\033[40;33mthe last one's num is %d.\033[0m\n",left);
 
    return 0;

}
