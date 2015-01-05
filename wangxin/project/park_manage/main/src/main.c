/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      main
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现基本输入输出
  Others:         无
  Function List:  
                  main
		  该程序实现基本输入输出
  History:        no
*************************************************/

#include <stdio.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       main
  Description:    该函数实现基本输入输出
  Calls:          init inerface
  Called By:      no
  Input:          head 传入头指针
  Output:         no
  Return:         0
  Others:         no
*************************************************/

int main()
{
    Stack park_stack;
    Stack temp_stack;
    Link_queue wait_queue;

    init(&park_stack,&temp_stack,&wait_queue);          //初始化栈,队列
    interface(&park_stack,&temp_stack,&wait_queue);     //调用界面函数

    return 0;
}
