/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      is_full_stack
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现判断是否满栈
  Others:         无
  Function List:  
                  is_full_stack
		  判断是否满栈
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       is_full_stack
  Description:    判断是否满栈
  Calls:          park
  Called By:      no
  Input:          my_stack
  Output:         no
  Return:         0,-1
  Others:         no
*************************************************/

int is_full_stack(Stack *my_stack)
{
    if(my_stack->top == 9)   //满栈
    {
        return FULL_OK;
    }
    else
    {
        return FULL_NO;     //未满
    }
}
