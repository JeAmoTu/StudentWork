/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      pop_park_stack
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现返回栈值
  Others:         无
  Function List:  
                  pop_park_stack
		  返回栈值
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       pop_park_stack
  Description:    返回栈值
  Calls:          no
  Called By:      see
  Input:          my_stack  i
  Output:         no
  Return:         my_stack->p_num[i]
  Others:         no
*************************************************/

int pop_park_stack(Stack *my_stack,int i)
{
    i = i - 1;                        

    return my_stack->p_num[i];     //返回第i-1个栈值
}
