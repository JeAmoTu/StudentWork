/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      count_9
  Author:    Wanxin   Version: 1.0       Date: 2014.5.1
  Description:    该程序实现输入一个数字n，求1到该数中的9的个数的功能。
  Others:         无
  Function List:  
                  1.count_num(int num) 求出1－n中9的个数，返回个数
  History:        no
*************************************************/

#include<stdio.h>
#include<stdlib.h>

/*************************************************
  Function:       count_num
  Description:    求出1－n中9的个数，返回个数
  Calls:          no
  Called By:      main
  Input:          num 传入需要找的数字
  Output:         no
  Return:         返回9的个数
  Others:         no
*************************************************/

int count_num(num)
{
    int i;
    int j = 0;
    int indiv;          /* 定义位数 */
    int ten;
    int hundred;
    int thousand;
    int ten_thousand;
    
    for(i = 1; i <= num; i++)   /* 求位数 */    
    {
        ten_thousand = i / 10000;                    
        thousand = (i - ten_thousand * 10000) / 1000;            
        hundred = (i - ten_thousand * 10000 - thousand * 1000) / 100;       
        ten = (i - ten_thousand * 10000 - thousand * 1000
	         - hundred * 100) / 10;   
        indiv = i - ten_thousand * 10000 - thousand * 1000
	          - hundred * 100 - ten * 10;    
        
        if(ten_thousand == 9)  /* 各位数是否为9 */
        {
	    j++;               /* 计9单位自增 */
	}  
        if(thousand == 9)  
        {
	    j++;
	} 
        if(hundred == 9)
        {
	    j++;
	}
        if(ten == 9)
        {
	    j++;
	}
        if(indiv == 9)
        {
	    j++;
	}
    }  
    
    return j;               /* 返回计数 */
}

/*************************************************
  Function:       main
  Description:    实现基本输入输出，函数调用
  Calls:          count_num
  Called By:      no
  Input:          1. argc 传入的参数个数
                  2. argv 传入的参数保存在此字符串数组中
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main(int argc,char *argv[])   /* 参数传入 */
{
    int num;
    int count = 0;
    num = atoi(argv[argc-1]);     /* 数据类型转换 */
  
    count = count_num(num);       /* 调用函数 */
    printf("\033[40;33mthe num of 9 is %d.\033[0m\n",count);
 
    return 0;

}

