/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      push_temp_stack
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现进入临时栈
  Others:         无
  Function List:  
                  push_temp_stack
		  进入临时栈
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       push_temp_stack
  Description:    进入临时栈
  Calls:          no
  Called By:      park
  Input:          temp_stack,car_num,park_time
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void push_temp_stack(Stack *temp_stack, long int car_num, time_t park_time)
{
    (temp_stack->top)++;
    temp_stack->p_num[temp_stack->top] = car_num;  //进临时栈
    temp_stack->i_time[temp_stack->top] = park_time;
}
