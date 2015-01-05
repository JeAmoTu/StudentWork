/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:     order
  Author:        Wanxin    Version:  1.0       Date: 2014.05.01
  Description:   该程序实现输入几个数，并对其排序
  Others:        无
  Function List:  
                 order_num(float *dest, int flag)
		 该函数实现对输入的几个数进行排序
  History:       no
*************************************************/

#include<stdio.h>
#include<stdlib.h> 

/*************************************************
  Function:       order_num
  Description:    该函数实现对输入的进行排序
  Calls:          no
  Called By:      main
  Input:          1. folat *dest 传入一个单精度数组 
                  2. flag 传入的单精度数组的长度
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void order_num(float *dest, int flag)
{
    int i;
    int j;
    float point;
    float temp;
    for( j = 0; j < flag - 1; j++)         /* 冒泡法排序 */
    {
        for(i = 0; i < flag - 1 - j; i++)
        {
            if(dest[i] > dest[i + 1])
            {
                temp = dest[i];
                dest[i] = dest[i + 1];
                dest[i + 1] = temp;
            }
        }
    }

    printf("\033[40;33mNow the num is \033[0m");
 
    for(i = 0; i < flag; i++)    
    {
        point = dest[i] - (int)dest[i];   /* 求小数位 */
	if(point == 0)
        {
	    printf("\033[40;33m%.0f \033[0m",dest[i]);      /* 不保留小数 */
        }
	else
        {
	    printf("\033[40;33m%.2f \033[0m",dest[i]);      /* 取两位小数 */
        }
    }

}

/*************************************************
  Function:       main
  Description:    实现基本输入输出
  Calls:          order_num
  Called By:      no
  Input:          1. argc 传入的参数个数
                  2. argv 传入的参数以字符串形式保存在该数组中
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main(int argc , char *argv[])    /* 参数传入 */
{
   int i;
   int num;
   num = argc - 1;   
   float order[num];
   
   for(i = 0; i < num; i++)          /* 数组初始化 */ 
   {
       order[i] = atof(argv[i + 1]); /* 数据类型转换 */
   }

   order_num(order,num);             /* 调用函数 */
 
   printf("\n");
   return 0;
}

