/*************************************************
  Copyright (C), 1944-2014    Wangxin
  File name:     ~p1_p2
  Author:       Wangxin  Version:  1.0      Date: 2014.05.01
  Description:   该程序实现对一个数的p1-p2位取反后以二进制输出
  Others:        无
  Function List: 
                 1. make(int n,int p1,int p2,int mun[])
                    该函数实现对该数的p1-p2位取反后保存在一个数组中
		 2. output(int p1,int p2, int mun[])
		    该函数诗选对p1-p2位的输出
  History:       no 
*************************************************/

#include <stdio.h>  

/*************************************************
  Function:      output  
  Description:   输出p1-p2位
  Calls:         no
  Called By:     main
  Input:         p1     首位
                 p2     末位
		 num[]  数组
  Output:        no
  Return:        no
  Others:        no
*************************************************/

void output(int p1,int p2,int num[])  
{  
    int n = p2 - p1;         /* 求数组长度 */
    int i = 0;  
    
    for(i = n;i >= 0; i--)  
    {  
        printf("%d",num[i]);  /* 逆序输出 */
    }  
    
    printf("\n");  
}  

/*************************************************
  Function:        make
  Description:     该函数实现将该数的p1-p2位取反后保存在一个数组中
  Calls:           no
  Called By:       main
  Input:           n     传入的整数
                   p1    首位
		   p2    末位
		   num[] 数组
  Output:          no
  Return:          no
  Others:          no
*************************************************/

int make(int n,int p1,int p2,int num[])  
{  
    int i = 0;  
    int temp = 0;  
    int a[32];  
    int k  = 0;  
    
    for(i = p1-1;i <= p2; i++)  
    {  
        temp = !((n >>i ) & 1);   
        num[k] = temp;  
        k++;  
    }  
}  

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          1. make
                  2. output
  Called By:      no
  Input:          no
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()  
{  
    int n;  
    int my_p1;
    int my_p2;
    int num[32];  
   
    printf("please input a number : ");  
    scanf("%d",&n);  /* 输入一个整数 */
    
    printf("please input p1 bit and p2 bit (p1<p2) : ");  
    scanf("%d %d",&my_p1,&my_p2);  /* 输入首位末位 */
   
    make(n,my_p1,my_p2,num);       /* 函数调用 */
    printf("the number invert  between p1 and p2 is : ");  
   
    output(my_p1,my_p2,num);       /* 函数调用 */
    
    return 0;  
}  
