/*************************************************
  Copyright (C), 1994-2014    Wangxin
  File name:     p1_p2
  Author:        Wangxin  Version: 1.0     Date: 2014.05.01
  Description:   该程序实现把一个数的p1－p2位以二进制输出
  Others:        无
  Function List:  
                 1. make(int n,int p1,int p2,int num[])
		    把该整数转化为二进制保存在数组中 
		 2. output
		    把该数的p1-p2位输出
  History:       no
*************************************************/

#include <stdio.h>  

/*************************************************
  Function:     make  
  Description:  把该整数转化为二进制保存在数组中
  Calls:        no
  Called By:    main
  Input:        n     传入的整数
                p1    首位
		p2    末位
		num[] 保存数组
  Output:       no
  Return:       0
  Others:       no
*************************************************/
int make(int n,int p1,int p2,int num[])  
{  
    int i = 0;  
    int k = 0;  
    int temp = 0;  
    
    for(i = p1 - 1;i <= p2;i++)  
    {  
        temp = (n >> i) & 1;   /* 该位赋值给temp */
        num[k] = temp;         /* 保存数组 */
        k++;                    
    }  
    
    return 0;
}  

/*************************************************
  Function:      output
  Description:   把该数的p1-p2位输出
  Calls:         no
  Called By:     main
  Input:         p1    首位
                 p2    末位
                 num[] 数组
  Output:        no
  Return:        0
  Others:        no
*************************************************/
void output(int p1,int p2,int num[])  
{  
    int i;
    int n_len = p2 - p1;         /* 数组长度 */
    
    for(i = n_len; i >= 0; i--)  
    {  
        printf("%d",num[i]);     /* 逆序输出 */
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
    int my_num[32];  
   
    printf("please input a number:\n");  
    scanf("%d",&n);              /* 输入一个整数 */
    
    printf("please input p1 bit and p2 bit (p1<p2):\n");  
    scanf("%d %d",&my_p1,&my_p2);/* 输入首位末位 */  
   
    make(n,my_p1,my_p2,my_num);  /* 函数调用 */
    printf("the number in p1 and p2 is :");  
    
    output(my_p1,my_p2,my_num);  /* 函数调用 */
    printf("\n");

    return 0; 
}
