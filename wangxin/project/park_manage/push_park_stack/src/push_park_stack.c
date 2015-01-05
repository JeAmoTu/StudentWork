/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      push_park_stack
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现进停车栈
  Others:         无
  Function List:  
                  push_park_stack
		  进停车栈
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       push_park_stack
  Description:    进停车栈
  Calls:          no
  Called By:      park
  Input:          park_stack car_num park_time
  Output:         no
  Return:         park_stack->top+1
  Others:         no
*************************************************/

int push_park_stack(Stack *park_stack, int car_num, time_t park_time)
{
    (park_stack->top)++;
    park_stack->p_num[park_stack->top] = car_num;   //进停车栈
    park_stack->i_time[park_stack->top] = park_time;

    return (park_stack->top) + 1;
}
