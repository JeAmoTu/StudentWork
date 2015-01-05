/*************************************************
  Copyright (C), 1994-2014, Wangxin
  File name:      init
  Author:    Wanxin   Version: 1.0       Date: 2014.6.10
  Description:    该程序实现初始化栈,队列
  Others:         无
  Function List:  
                  init
		  初始化栈,队列
  History:        no
*************************************************/

#include "../../include/typedef.h"

/*************************************************
  Function:       init
  Description:    初始化栈,队列
  Calls:          main
  Called By:      no
  Input:          park_atack,temp_stack,wait_queue
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void init(Stack *park_stack, Stack *temp_stack, Link_queue *wait_queue)
{
    park_stack->top = -1;              //初始化
    temp_stack->top = -1;
    wait_queue->rear = NULL;
    wait_queue->front = NULL;
}
